COMP=gcc
CFLAGS=-c -Wall -Wextra -Werror
SOURCES=main_executable_module.c ../yet_another_decision_module/decision.c

ORIGINAL_IO=../data_libs/data_io.c
MACRO_IO=../data_libs/data_io_macro.h

DATA_STAT=../data_libs/data_stat.c


DATA_PROCESS=../data_module/data_process.c


OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=../../build/Quest_3
MACRO_EXECUTABLE=../../build/Quest_4
STAT_LIB_EXECUTABLE=../../build/Quest_5
DYNAMIC_LIB_EXECUTABLE=../../build/Quest_6

all: $(ORIGINAL_IO) $(DATA_STAT) $(DATA_PROCESS) $(SOURCES) $(EXECUTABLE)

build_with_static: $(OBJECTS) $(ORIGINAL_IO:.c=.o) $(DATA_PROCESS:.c=.o) data_stat.a
	$(COMP) $^ -o $(STAT_LIB_EXECUTABLE)

build_with_dynamic: $(OBJECTS) $(ORIGINAL_IO:.c=.o) $(DATA_STAT:.c=.o) data_process.so
	$(COMP) $^ -o  $(DYNAMIC_LIB_EXECUTABLE)

build_with_macro: $(DATA_STAT:.c=.o) $(DATA_PROCESS:.c=.o) $(OBJECTS) $(MACRO_IO)
	$(COMP) $(DATA_STAT:.c=.o) $(DATA_PROCESS:.c=.o) $(OBJECTS) -o $(MACRO_EXECUTABLE)

data_stat.a: $(DATA_STAT:.c=.o)
	ar rcs $@ $^

data_process.so: $(DATA_PROCESS:.c=.o) $(DATA_STAT:.c=.o)
	$(COMP) -shared -o $@ $^

$(EXECUTABLE): $(DATA_STAT:.c=.o) $(DATA_PROCESS:.c=.o) $(ORIGINAL_IO:.c=.o)  $(OBJECTS) 
	$(COMP) $^ -o $@

.c.o:
	$(COMP) $(CFLAGS) $^ -o $@

clean:
	rm -rf data_stat.a data_process.so $(OBJECTS) $(EXECUTABLE) $(MACRO_EXECUTABLE) $(STAT_LIB_EXECUTABLE) $(DYNAMIC_LIB_EXECUTABLE) $(ORIGINAL_IO:.c=.o) $(DATA_STAT:.c=.o)

rebuild: clean all
