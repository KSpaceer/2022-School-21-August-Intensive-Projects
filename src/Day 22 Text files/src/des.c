#include "des.h"


void block_cipher(char *buf, size_t shift, long key) {
  long *block = (long*)(buf + shift);
  initial_permutation(block);
  long keys[16];
  keygen(key, keys);
  feistel_permutations(block, keys);
}

void initial_permutation(long *block) {
  long new_block = 0;
  long shift = 63;
  long init_per[] = IP;
  for (int i = 0; i < 64; i++, shift--) {
    new_block |= (*block >> shift & 1) << (init_per[i] - 1);
  }
  *block = new_block;
}

void keygen(long key, long *keys) {
  long extended_key = 0;
  int shift = 63;
  long kg_arr[] = KG;
  for (int i = 0; i < 56; i++, shift--) {
    extended_key |= (key >> shift & 1) << (kg_arr[i] - 1);
  }
  long vectors[16];
  vectors[0] = extended_key;
  long kgs_arr[] = KGS;
  for (int i = 1; i < 16; i++) {
    long c = vectors[i - 1] & 0xFFFFFFF000000000;
    long d = vectors[i - 1] & 0x0000000FFFFFFF00;
    vectors[i] = 0;
    vectors[i] = (c << kgs_arr[i - 1]) | (c >> (28 - kgs_arr[i - 1]));
    vectors[i] |= (d << kgs_arr[i - 1]) | (d >> (28 - kgs_arr[i - 1]));
  }
  long vtk_arr[] = VTK;
  for (int i = 0; i < 16; i++) {
    keys[i] = 0;
    long shift = 55;
    for (int j = 0; j < 48; j++, shift--) {
      keys[i] |= (vectors[i] >> (vtk_arr[i] - 1) & 1) << shift;
    }
  }
}

void feistel_permutations(long *block, long *keys) {
  int left = *(int*)block;
  int right = *((int*)block + 1);
  for (int i = 0; i < 16; i++) {
    int new_left = right;
    int new_right = left ^ feistel_func(right, keys[i]);
    left = new_left;
    right = new_right;
  }
  long final_t = ((long)left << 32) | right;
  long result = 0;
  int shift = 63;
  int rp_arr[] = RP;
  for (int i = 0; i < 64; i++, shift--) {
    result |= (final_t >> shift & 1) << (rp_arr[i] - 1);
  }
  *block = result;
}

int feistel_func(int right, long key) {
  long extended = 0;
  int shift = 47;
  long e_arr[] = E;
  for (int i = 0; i < 48; i++, shift--) {
    extended |= (long)(right >> (e_arr[i] - 1) & 1) << shift;
  }
  extended ^= key;
  int Sboxes[8][64] = {S1, S2, S3, S4, S5, S6, S7, S8};
  long boxed = 0;
  shift = 42;
  for (int i = 0; i < 8; i++, shift -= 6) {
    long b_i = extended >> shift & 63;
    long a = (b_i >> 4 & 2) | (b_i & 1);
    long b = b_i >> 1 & 15;
    b_i = Sboxes[i][a * 16 + b];
    boxed |= b_i << (shift + i * 2);
  }
  int result = 0;
  shift = 31;
  int ffp_arr[] = FFP;
  for (int i = 0; i < 32; i++) {
    result |= (boxed >> shift & 1) << (ffp_arr[i] - 1);
  }
  return result;
}

