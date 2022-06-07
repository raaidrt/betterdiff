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
		printf("Line %lu printed:\n", lineNumber);
		printf("  Number of chars=%llu\n", ptr->length);
		printf("  Number of chars given by getline=%ld\n", numChars);
		printf("  Line text = \n");
		printf("%s", line);
		free(line);
	}
}

void writeToNewFile(FILE *fileFrom, const char *newFileName, line_t *lines) {
	FILE *fileTo = fopen(newFileName, "w");
	size_t lineNumber = 0;
	for (line_t *ptr = lines; ptr != NULL; ptr = ptr->next) {
		lineNumber++;
		fseek(fileFrom, ptr->pos, SEEK_SET);
		char *line = NULL;
		size_t linecap = 0;
		ssize_t numChars = getline(&line, &linecap, fileFrom);
		if (numChars >= 0) 
			fwrite(line, sizeof(char), (unsigned long)numChars, fileTo);
		free(line);
	}
	fclose(fileTo);
}

int main(void) {
	FILE *file = fopen("tests/testData/shakespeare.txt", "r");
	if (file == NULL) {
		fprintf(stderr, "Cannot open file\n");
		exit(EXIT_FAILURE);
	}
	line_t *lines = traverseFile(file);
	writeToNewFile(file, "tests/cmpFiles/shakespeare.txt", lines);
	freeLines(lines);
	fclose(file);
}
