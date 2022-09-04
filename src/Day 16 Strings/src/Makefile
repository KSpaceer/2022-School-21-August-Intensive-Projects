.PHONY: text_processor

COMP=gcc
CFLAGS=-c -Wall -Wextra -Werror
STRLEN_FLAG=-D STRLEN
STRCMP_FLAG=-D STRCMP
STRCPY_FLAG=-D STRCPY
STRCAT_FLAG=-D STRCAT
STRCHR_FLAG=-D STRCHR
STRSTR_FLAG=-D STRSTR
STRTOK_FLAG=-D STRTOK
SOURCES=s21_string.c
TEXT_PRSR=text_processor.c 
TEST=s21_string_test.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE1=../build/Quest_1
EXECUTABLE2=../build/Quest_2
EXECUTABLE3=../build/Quest_3
EXECUTABLE4=../build/Quest_4
EXECUTABLE5=../build/Quest_5
EXECUTABLE6=../build/Quest_6
EXECUTABLE7=../build/Quest_7
EXECUTABLE8=../build/Quest_8

all: strlen_tests strcmp_tests strcpy_tests strcat_tests strchr_tests strstr_tests strtok_tests text_processor

text_processor: $(SOURCES) $(TEXT_PRSR) $(EXECUTABLE8)

strlen_tests: $(SOURCES) $(TEST) $(EXECUTABLE1)

strcmp_tests: $(SOURCES) $(TEST) $(EXECUTABLE2)

strcpy_tests: $(SOURCES) $(TEST) $(EXECUTABLE3)

strcat_tests: $(SOURCES) $(TEST) $(EXECUTABLE4)

strchr_tests: $(SOURCES) $(TEST) $(EXECUTABLE5)

strstr_tests: $(SOURCES) $(TEST) $(EXECUTABLE6)

strtok_tests: $(SOURCES) $(TEST) $(EXECUTABLE7)

$(EXECUTABLE1): $(OBJECTS) strlen_macro
	$(COMP) $(OBJECTS) $(TEST:.c=.o) -o $@

$(EXECUTABLE2): $(OBJECTS) strcmp_macro
	$(COMP) $(OBJECTS) $(TEST:.c=.o) -o $@

$(EXECUTABLE3): $(OBJECTS) strcpy_macro
	$(COMP) $(OBJECTS) $(TEST:.c=.o) -o $@

$(EXECUTABLE4): $(OBJECTS) strcat_macro
	$(COMP) $(OBJECTS) $(TEST:.c=.o) -o $@

$(EXECUTABLE5): $(OBJECTS) strchr_macro
	$(COMP) $(OBJECTS) $(TEST:.c=.o) -o $@

$(EXECUTABLE6): $(OBJECTS) strstr_macro
	$(COMP) $(OBJECTS) $(TEST:.c=.o) -o $@

$(EXECUTABLE7): $(OBJECTS) strtok_macro
	$(COMP) $(OBJECTS) $(TEST:.c=.o) -o $@

$(EXECUTABLE8): $(OBJECTS) $(TEXT_PRSR:.c=.o)
	$(COMP) $(OBJECTS) $(TEXT_PRSR:.c=.o) -o $@

.c.o:
	$(COMP) $(CFLAGS) $< -o $@

strlen_macro: $(TEST)
	$(COMP) $(CFLAGS) $(STRLEN_FLAG) $(TEST) -o $(TEST:.c=.o)

strcmp_macro: $(TEST)
	$(COMP) $(CFLAGS) $(STRCMP_FLAG) $(TEST) -o $(TEST:.c=.o)

strcpy_macro: $(TEST)
	$(COMP) $(CFLAGS) $(STRCPY_FLAG) $(TEST) -o $(TEST:.c=.o)

strcat_macro: $(TEST)
	$(COMP) $(CFLAGS) $(STRCAT_FLAG) $(TEST) -o $(TEST:.c=.o)

strchr_macro: $(TEST)
	$(COMP) $(CFLAGS) $(STRCHR_FLAG) $(TEST) -o $(TEST:.c=.o)

strstr_macro: $(TEST)
	$(COMP) $(CFLAGS) $(STRSTR_FLAG) $(TEST) -o $(TEST:.c=.o)

strtok_macro: $(TEST)
	$(COMP) $(CFLAGS) $(STRTOK_FLAG) $(TEST) -o $(TEST:.c=.o)

clean:
	rm -rf $(OBJECTS) $(TEST:.c=.o) $(TEXT_PRSR:.c=.o)  $(EXECUTABLE1) $(EXECUTABLE2) $(EXECUTABLE3) $(EXECUTABLE4) $(EXECUTABLE5) $(EXECUTABLE6) $(EXECUTABLE7) $(EXECUTABLE8)

rebuild: clean all

stylecheck:
	python3 ../materials/linters/cpplint.py --extensions=c $(SOURCES) $(TEST) $(TEXT_PRSR) s21_string.h
 