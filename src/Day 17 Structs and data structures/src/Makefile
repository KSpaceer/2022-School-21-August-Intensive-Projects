COMP=gcc
.PHONY: list_test stack_test

CFLAGS=-c -Wall -Wextra -Werror
SOURCES=dmanager_module.c
LIST_SOURCES=list.c list_test.c
STACK_SOURCES=stack.c stack_test.c
OBJECTS=$(SOURCES:.c=.o)
LIST_OBJECTS=$(LIST_SOURCES:.c=.o)
STACK_OBJECTS=$(STACK_SOURCES:.c=.o)
EXECUTABLE1=../build/Quest_1
EXECUTABLE2=../build/Quest_2
EXECUTABLE3=../build/Quest_3

all: door_struct list_test stack_test

door_struct: $(SOURCES) $(EXECUTABLE1)

list_test: $(LIST_SOURCES) $(EXECUTABLE2)

stack_test: $(STACK_SOURCES) $(EXECUTABLE3)

$(EXECUTABLE1): $(OBJECTS)
	$(COMP) $^ -o $@

$(EXECUTABLE2): $(LIST_OBJECTS)
	$(COMP) $^ -o $@

$(EXECUTABLE3): $(STACK_OBJECTS)
	$(COMP) $^ -o $@

.c.o:
	$(COMP) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS) $(LIST_OBJECTS) $(STACK_OBJECTS) $(EXECUTABLE1) $(EXECUTABLE2) $(EXECUTABLE3)

rebuild: clean all

stylecheck:
	python3 ../materials/linters/cpplint.py --extensions=c $(SOURCES) $(LIST_SOURCES) $(STACK_SOURCES) *.h