#include <stdio.h>

#define N 15
#define M 13

void transform(int *buf, int **matr, int n, int m);
void make_picture(int **picture, int n, int m);
void reset_picture(int **picture, int n, int m);
void print_picture(int **picture, int n, int m);
void upper_frames(int **picture, int *tree_trunk, int *tree_foliage,
                  int *sun_data);
void lower_frames(int **picture, int *tree_trunk, int *sun_data);

int main(void) {
  int picture_data[N][M];
  int *picture[N];
  transform((int *)picture_data, picture, N, M);
  make_picture(picture, N, M);
  print_picture(picture, N, M);
  return 0;
}

void make_picture(int **picture, int n, int m) {
  int frame_w[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  int frame_h[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  int tree_trunk[] = {7, 7, 7, 7};
  int tree_foliage[] = {3, 3, 3, 3};
  int sun_data[6][5] = {{0, 6, 6, 6, 6}, {0, 0, 6, 6, 6}, {0, 0, 6, 6, 6},
                        {0, 6, 0, 0, 6}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}};

  reset_picture(picture, n, m);
  int length_frame_w = sizeof(frame_w) / sizeof(frame_w[0]);
  int height_frame_h = sizeof(frame_h) / sizeof(frame_h[0]);
  for (int i = 0; i < height_frame_h; i += 7) {
    for (int j = 0; j < length_frame_w; j++) {
      picture[i][j] = frame_w[j];
    }
  }
  for (int i = 0; i < length_frame_w; i += 6) {
    for (int j = 0; j < height_frame_h; j++) {
      picture[j][i] = frame_h[j];
    }
  }
  upper_frames(picture, tree_trunk, tree_foliage, (int *)sun_data);
  lower_frames(picture, tree_trunk, (int *)sun_data);
}

void upper_frames(int **picture, int *tree_trunk, int *tree_foliage,
                  int *sun_data) {
  for (int i = 1; i < 7; i++) {
    for (int j = 1; j < 6; j++) {
      if (1 == i) {
        picture[i][j] = sun_data[0];
      } else if (2 == i || 5 == i) {
        picture[i][j] = j > 2 && j < 5 ? tree_foliage[0] : sun_data[0];
      } else if (3 == i || 4 == i) {
        picture[i][j] = j == 1 ? sun_data[0] : tree_foliage[j - 2];
      } else {
        picture[i][j] = j > 2 && j < 5 ? tree_trunk[0] : sun_data[0];
      }
    }
    for (int j = 7; j < 12; j++) {
      picture[i][j] = *(sun_data + (i - 1) * 5 + j - 7);
    }
  }
}

void lower_frames(int **picture, int *tree_trunk, int *sun_data) {
  for (int i = 8; i < 14; i++) {
    for (int j = 1; j < 6; j++) {
      if (i < 10) {
        picture[i][j] = j > 2 && j < 5 ? tree_trunk[0] : sun_data[0];
      } else if (10 == i) {
        picture[i][j] = j == 1 ? sun_data[0] : tree_trunk[j - 2];
      } else {
        picture[i][j] = *(sun_data + 5 * 5 + j - 2);
      }
    }
    for (int j = 7; j < 12; j++) {
      picture[i][j] = *(sun_data + 5 * 5 + j - 7);
    }
  }
}

void reset_picture(int **picture, int n, int m) {
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      picture[i][j] = 0;
    }
  }
}

void transform(int *buf, int **matr, int n, int m) {
  for (int i = 0; i < n; i++) {
    matr[i] = buf + i * m;
  }
}

void print_picture(int **picture, int n, int m) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m - 1; j++) {
      printf("%d ", picture[i][j]);
    }
    printf("%d", picture[i][m - 1]);
    if (i != n - 1) {
      printf("\n");
    }
  }
}
