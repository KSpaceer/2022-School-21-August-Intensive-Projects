.PHONY: cipher

COMP=gcc
CFLAGS=-c -Wall -Werror -Wextra
DFLAG=
SOURCES=cipher_input.c cipher_operations.c cipher.c des.c logger.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE1=../build/cipher
EXECUTABLE2=../build/logging_cipher

all: cipher logging_cipher

cipher: $(SOURCES) $(EXECUTABLE1)

logging_cipher: $(SOURCES) $(EXECUTABLE2)

with_macro:
	$(COMP) $(CFLAGS) -D LOGGER cipher_input.c -o cipher_input.o
	$(COMP) $(CFLAGS) -D LOGGER cipher_operations.c -o cipher_operations.o 
	$(COMP) $(CFLAGS) -D LOGGER cipher.c -o cipher.o 
	$(COMP) $(CFLAGS) -D LOGGER des.c -o des.o 
	$(COMP) $(CFLAGS) -D LOGGER logger.c -o logger.o 

$(EXECUTABLE1): $(OBJECTS)
	$(COMP) $^ -o $@

$(EXECUTABLE2): with_macro $(OBJECTS)
	$(COMP) $(OBJECTS) -o $@

.c.o:
	$(COMP) $(CFLAGS) $(DFLAG) $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE1) $(EXECUTABLE2)

rebuild: clean all

stylecheck:
	cp ../materials/linters/CPPLINT.cfg .
	python3 ../materials/linters/cpplint.py --extensions=c $(SOURCES) *.h

  