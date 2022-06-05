CC = gcc
COPT = -O1
CFLAGS = -std=c99 $(COPT) -g -Wall -Wextra -Wpedantic -Wconversion
CFLAGS += -Wstrict-prototypes -Wwrite-strings -Wno-unused-parameter -Werror

FILES = betterdiff.c
LIB_FILES = diffutils.c

bdiff: $(FILES)
	$(CC) $(CFLAGS) $(FILES) $(LIB_FILES) -o $@ $(LDLIBS)

.PHONY: clean
clean:
	-rm -rf *.tar *~ *.o *.bc *.ll *.out *.dSYM *.gch
	-rm -f bdiff
	-rm -f test

TEST_FILES = tests/testLineData.c 
.PHONY: test
test: $(TEST_FILES)
	$(CC) $(CFLAGS) $(TEST_FILES) $(LIB_FILES) -o $@ $(LDLIBS)
	
