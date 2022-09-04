.PHONY: print_module documentation_module bst_create_test bst_insert_test bst_traverse_test

COMP=gcc
CFLAGS=-c -Wall -Wextra -Werror
Q2_MFLAG=-D Q2_VARARGS

MAIN_MODULE=main_module_entry_point.c
MM_OBJECT=$(MAIN_MODULE:.c=.o)
Q1_SOURCES=print_module.c 
Q1_OBJECTS=$(Q1_SOURCES:.c=.o)

Q2_SOURCES=documentation_module.c
Q2_OBJECTS=$(Q2_SOURCES:.c=.o)

BST_SOURCE=bst.c
BST_OBJECT=$(BST_SOURCE:.c=.o)

Q3_SOURCES=bst_create_test.c
Q3_OBJECTS=$(Q3_SOURCES:.c=.o)

Q4_SOURCES=bst_insert_test.c
Q4_OBJECTS=$(Q4_SOURCES:.c=.o)

Q5_SOURCES=bst_traverse_test.c
Q5_OBJECTS=$(Q5_SOURCES:.c=.o)

EXECUTABLE1=../build/Quest_1
EXECUTABLE2=../build/Quest_2
EXECUTABLE3=../build/Quest_3
EXECUTABLE4=../build/Quest_4
EXECUTABLE5=../build/Quest_5

all: print_module documentation_module bst_create_test bst_insert_test bst_traverse_test

print_module: $(Q1_SOURCES) $(MAIN_MODULE) $(EXECUTABLE1)

documentation_module: $(Q1_SOURCES) $(Q2_SOURCES) $(MAIN_MODULE) $(EXECUTABLE2)

bst_create_test: $(BST_SOURCE) $(Q3_SOURCES) $(EXECUTABLE3)

bst_insert_test: $(BST_SOURCE) $(Q4_SOURCES) $(EXECUTABLE4)

bst_traverse_test: $(BST_SOURCE) $(Q5_SOURCES) $(EXECUTABLE5)

$(EXECUTABLE1): $(Q1_OBJECTS) $(MM_OBJECT)
	$(COMP) $^ -o $@

$(EXECUTABLE2): $(Q1_OBJECTS) $(Q2_OBJECTS) activate_q2_macro
	$(COMP) $(Q1_OBJECTS) $(Q2_OBJECTS) $(MM_OBJECT) -o $@

$(EXECUTABLE3): $(BST_OBJECT) $(Q3_OBJECTS)
	$(COMP) $^ -o $@

$(EXECUTABLE4): $(BST_OBJECT) $(Q4_OBJECTS)
	$(COMP) $^ -o $@

$(EXECUTABLE5): $(BST_OBJECT) $(Q5_OBJECTS)
	$(COMP) $^ -o $@

activate_q2_macro:
	$(COMP) $(CFLAGS) $(Q2_MFLAG) $(MAIN_MODULE) -o $(MM_OBJECT)

.c.o:
	$(COMP) $(CFLAGS) $< -o $@

clean:
	rm -rf $(Q1_OBJECTS) $(Q2_OBJECTS) $(MM_OBJECT) $(BST_OBJECT) $(Q3_OBJECTS) $(Q4_OBJECTS) $(Q5_OBJECTS) $(EXECUTABLE1) $(EXECUTABLE2) $(EXECUTABLE3) $(EXECUTABLE4) $(EXECUTABLE5)

rebuild: clean all

stylecheck:
	python3 ../materials/linters/cpplint.py --extensions=c $(Q1_SOURCES) $(Q2_SOURCES) $(BST_SOURCE) $(Q3_SOURCES) $(Q4_SOURCES) $(Q5_SOURCES) *.h

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem ./