COMP=gcc
CFLAGS=-c -Wall -Wextra -Werror
SOURCES=main_executable_module.c ../yet_another_decision_module/decision.c

ORIGINAL_IO=../data_libs/data_io.c
MACRO_IO=../data_libs/data_io_macro.h

DATA_STAT=../data_libs/data_stat.c
STATIC_LIBRARY=../data_libs/data_stat.a

DATA_PROCESS=../data_module/data_process.c
DYNAMIC_LIBRARY=../data_module/data_process.so

OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=../../build/Quest_3
MACRO_EXECUTABLE=../../build/Quest_4
STAT_LIB_EXECUTABLE=../../build/Quest_5
DYNAMIC_LIB_EXECUTABLE=../../build/Quest_6

all: $(ORIGINAL_IO) $(DATA_STAT) $(DATA_PROCESS) $(SOURCES) $(EXECUTABLE)

build_with_static: $(OBJECTS) $(ORIGINAL_IO:.c=.o) $(DATA_PROCESS:.c=.o) $(STATIC_LIBRARY)
	$(COMP) $^ -o $(STAT_LIB_EXECUTABLE)

build_with_dynamic: $(OBJECTS) $(ORIGINAL_IO:.c=.o) $(DATA_STAT:.c=.o) $(DYNAMIC_LIBRARY)
	$(COMP) $(OBJECTS) $(ORIGINAL_IO:.c=.o) $(DATA_STAT:.c=.o) $(DYNAMIC_LIBRARY) -o  $(DYNAMIC_LIB_EXECUTABLE)

build_with_macro: $(DATA_STAT:.c=.o) $(DATA_PROCESS:.c=.o) $(OBJECTS) $(MACRO_IO)
	$(COMP) $(OBJECTS) -o $(MACRO_EXECUTABLE)

$(STATIC_LIBRARY): $(DATA_STAT:.c=.o)
	ar rcs $@ $^

$(DYNAMIC_LIBRARY): $(DATA_PROCESS:.c=.o)
	$(COMP) -shared -o $@ $^

$(EXECUTABLE): $(DATA_STAT:.c=.o) $(DATA_PROCESS:.c=.o) $(ORIGINAL_IO:.c=.o)  $(OBJECTS) 
	$(COMP) $(OBJECTS) $(ORIGINAL_IO:.c=.o) -o $@

.c.o:
	$(COMP) $(CFLAGS) $< -o $@

clean:
	rm -rf $(STATIC_LIBRARY) $(DYNAMIC_LIBRARY) $(OBJECTS) $(EXECUTABLE) $(MACRO_EXECUTABLE) $(STAT_LIB_EXECUTABLE) $(DYNAMIC_LIB_EXECUTABLE) $(ORIGINAL_IO:.c=.o) $(DATA_STAT:.c=.o)

rebuild: clean all
