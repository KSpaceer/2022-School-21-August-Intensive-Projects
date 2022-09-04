COMP=gcc
CFLAGS=-c -Wall -Wextra -Werror
SOURCES=expression_input.c rpn_data_structures.c expression_parsing.c reverse_polish_notation.c graph_rendering.c graph.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=../build/graph

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(COMP) $^ -o $@

.c.o:
	$(COMP) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)

rebuild: clean all

stylecheck:
	cp ../materials/linters/CPPLINT.cfg .
	python3 ../materials/linters/cpplint.py --extensions=c $(SOURCES)

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem $(SOURCES)