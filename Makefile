CC = gcc
COPT = -O1
CFLAGS = -std=c99 $(COPT) -g -Wall -Wextra -Wpedantic -Wconversion
CFLAGS += -Wstrict-prototypes -Wwrite-strings -Wno-unused-parameter -Werror

FILES = betterdiff.c
LIB_FILES = diffutils.c lcsslib/lcss.c

bdiff: $(FILES)
	$(CC) $(CFLAGS) $(FILES) $(LIB_FILES) -o $@ $(LDLIBS)
.SILENT: clean
.PHONY: clean
clean:
	-rm -rf *.tar *~ *.o *.bc *.ll *.out *.dSYM *.gch
	-rm -f bdiff
	-rm -f test

.SILENT: testLcss.out
.PHONY: testLcss.out
testLcss.out: tests/testLcss.c
	-echo -n 'TESTING $@.......'
	-$(CC) $(CFLAGS) $^ $(LIB_FILES) -o $@ $(LDLIBS)
	-./$@

.SILENT: testLineData.out
.PHONY: testLineData.out
testLineData.out: tests/testLineData.c
	-echo -n 'TESTING $@.......'
	-$(CC) $(CFLAGS) $^ $(LIB_FILES) -o $@ $(LDLIBS)
	-./$@
	-diff tests/testData tests/cmpFiles

TEST_REQS = setup testLineData.out testLcss.out

.SILENT: setup
.PHONY: setup
setup: 
	-rm -rf tests/cmpFiles
	-mkdir tests/cmpFiles
.SILENT: test
.PHONY: test
test: $(TEST_REQS)
