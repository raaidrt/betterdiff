CC = gcc
COPT = -O1
CFLAGS = -std=c99 $(COPT) -g -Wall -Wextra -Wpedantic -Wconversion
CFLAGS += -Wstrict-prototypes -Wwrite-strings -Wno-unused-parameter -Werror

FILES = betterdiff.c
LIB_FILES = diffutils.c lcsslib/lcss.c

bdiff: $(FILES)
	$(CC) $(CFLAGS) $(FILES) $(LIB_FILES) -o $@ $(LDLIBS)

TEST_FILES = testLineData

.PHONY: clean
clean:
	-rm -rf *.tar *~ *.o *.bc *.ll *.out *.dSYM *.gch
	-rm -f bdiff
	-rm -f $(TEST_FILES)
	-rm -f test

testLineData: tests/testLineData.c
	$(CC) $(CFLAGS) $^ $(LIB_FILES) -o $@ $(LDLIBS)

.PHONY: test
test: $(TEST_FILES)
	-rm -rf tests/cmpFiles
	-mkdir tests/cmpFiles
	- ./$(TEST_FILES)
	-diff tests/testData tests/cmpFiles
	
