#include <stdio.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdlib.h>
#include "diffutils.h"

static const char helpMessage[] = "Usage:\n\
./bdiff [-r] [-h] <file1> <file2>\n\
  -r recursive: allows you to compare two folders instead of files\n\
  -h help: prints this help message\n";

int main(int argc, char **argv) {
	int c;
	opterr = 0;
	bool recursive = false;
	bool help = false;
	bool other = false;
	while ((c = getopt(argc, argv, "rh")) != -1) {
		switch (c) {
		case 'r':
			recursive = true;
			break;
		case 'h':
			help = true;
			break;
		default:
			other = true;
		}
	}
	if (other) {
		fprintf(stderr, "Error: invalid option(s) specified\n");
	}

	int numArgs = argc - optind;
	if (numArgs != 2) {
		fprintf(stderr, "Must specify exactly two files or \
directories to compare\n");
	}

	if (numArgs != 2 || other || help) {
		printf(helpMessage);
		exit(EXIT_SUCCESS);
	}

	char *file1 = argv[optind];
	char *file2 = argv[optind + 1];
	
	bool ok = runDiff(file1, file2, recursive);
	printf("ok = %d\n", ok);

	exit(EXIT_SUCCESS);
}
