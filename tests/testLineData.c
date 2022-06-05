#include <stdio.h>
#include "../diffutilsHelpers.h"

void printLines(FILE *file, line_t *lines) {
	size_t lineNumber = 0;
	for (line_t *ptr = lines; ptr != NULL; ptr = ptr->next) {
		lineNumber++;
		fseek(file, ptr->pos, SEEK_SET);
		char *line = NULL;
		size_t linecap = 0;
		ssize_t numChars = getline(&line, &linecap, file);
		if (numChars == -1) {
			fprintf(stderr, "An error occured in getLine\n");
			free(line);
			exit(EXIT_FAILURE);
		}
		printf("Line %lu printed:\n", lineNumber);
		printf("  Number of chars=%llu\n", ptr->length);
		printf("  Number of chars given by getline=%lu\n", numChars);
		printf("  Line text = \n");
		printf("%s", line);
		free(line);
	}
}

int main(void) {
	FILE *file = fopen("tests/testData/shakespeare.txt", "r");
	if (file == NULL) {
		fprintf(stderr, "Cannot open file\n");
		exit(EXIT_FAILURE);
	}
	printf("Traversing file\n");
	line_t *lines = traverseFile(file);
	printf("Finished traversing file\n");
	printLines(file, lines);
	freeLines(lines);
	fclose(file);
}
