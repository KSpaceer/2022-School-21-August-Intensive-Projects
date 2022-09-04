.PHONY: state_sort state_search clear_state

COMP=gcc
CFLAGS=-c -Wall -Wextra -Werror

SORT_SOURCES=state_sort.c date_processing.c
SORT_OBJECTS=$(SORT_SOURCES:.c=.o)
EXECUTABLE1=../build/Quest_1

SEARCH_SOURCES=state_search.c date_processing.c
SEARCH_OBJECTS=$(SEARCH_SOURCES:.c=.o)
EXECUTABLE2=../build/Quest_2

CLEAR_SOURCES=clear_state.c date_processing.c
CLEAR_OBJECTS=$(CLEAR_SOURCES:.c=.o)
EXECUTABLE3=../build/Quest_3

all: state_sort state_search clear_state

state_sort: $(SORT_SOURCES) doorstate_struct.h $(EXECUTABLE1)

state_search: $(SEARCH_SOURCES) doorstate_struct.h $(EXECUTABLE2)

clear_state: $(CLEAR_SOURCES) doorstate_struct.h $(EXECUTABLE3)

$(EXECUTABLE1): $(SORT_OBJECTS)
	$(COMP) $^ -o $@

$(EXECUTABLE2): $(SEARCH_OBJECTS)
	$(COMP) $^ -o $@

$(EXECUTABLE3): $(CLEAR_OBJECTS)
	$(COMP) $^ -o $@

.c.o:
	$(COMP) $(CFLAGS) $< -o $@

clean:
	rm -rf $(SORT_OBJECTS) $(EXECUTABLE1) $(SEARCH_OBJECTS) $(EXECUTABLE2) $(CLEAR_OBJECTS) $(EXECUTABLE3)

rebuild: clean all

stylecheck:
	cp ../materials/linters/CPPLINT.cfg .
	python3 ../materials/linters/cpplint.py --extensions=c $(SORT_SOURCES) $(SEARCH_SOURCES) $(CLEAR_SOURCES) *.h
