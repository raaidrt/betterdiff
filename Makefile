CC = gcc
COPT = -O1
CFLAGS = -std=c99 $(COPT) -g -Wall -Wextra -Wpedantic -Wconversion
CFLAGS += -Wstrict-prototypes -Wwrite-strings -Wno-unused-parameter -Werror

bdiff: betterdiff.c
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

FILES = bdiff

.PHONY: clean
clean:
	-rm -f *.tar *~ *.o *.bc *.ll
	-rm -f $(FILES)
