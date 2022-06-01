CC = gcc
COPT = -O1
CFLAGS = -std=c99 $(COPT) -g -Wall -Wextra -Wpedantic -Wconversion
CFLAGS += -Wstrict-prototypes -Wwrite-strings -Wno-unused-parameter -Werror

FILES = betterdiff.c diffutils.c

bdiff: $(FILES)
	$(CC) $(CFLAGS) $(FILES) -o $@ $(LDLIBS)

.PHONY: clean
clean:
	-rm -rf *.tar *~ *.o *.bc *.ll *.out *.dSYM *.gch
	-rm bdiff
