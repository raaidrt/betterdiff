#include "diffutils.h"
#include "diffutilsHelpers.h"
#include <errno.h>

const char pink[] = "\033[0;31m"; 
const char cyan[] = "\033[0;36m";
const char reset[] = "\033[0m";

/**
 * @brief Changes the terminal to print pink text
 */
void makePink(void) {
	printf(pink);
}

/**
 * @brief Changes the terminal to print cyan text
 */
void makeCyan(void) {
	printf(cyan);
}

/**
 * @brief Resets the terminal color
 */
void resetColor(void) {
	printf(reset);
}

/**
 * @brief Used to traverse a file to generate a line_t linked list.
 *
 * @param file The file to traverse
 * @return The line_t linked list pointer
 */
line_t *traverseFile(FILE *file) {
	line_t *toReturn = malloc(sizeof(line_t));
	if (toReturn == NULL) {
		fprintf(stderr, "Malloc error\n");
		exit(EXIT_FAILURE);
	}
	line_t *last = toReturn;
	toReturn->pos = ftell(file);
	toReturn->length = 0;
	toReturn->next = NULL;
	char buf[BUF_SIZE];
	while (fgets(buf, BUF_SIZE, file)) {
		size_t len = strlen(buf);
		last->length += len;
		if (buf[len - 1] == '\n') {
			last->next = malloc(sizeof(line_t));
			if (last->next == NULL) {
				fprintf(stderr, "Malloc error\n");
				exit(EXIT_FAILURE);
			}
			last = last->next;
			last->length = 0;
			last->next = NULL;
			last->pos = ftell(file);
		}
	}
	return toReturn;
}

/**
 * @brief counts the total number of lines stored by the line_t linked list
 *
 * @param lines the linked list pointer
 * @return the number of lines
 */
size_t countLines(line_t *lines) {
	size_t result = 0;
	for (line_t *ptr = lines; ptr != NULL; ptr = ptr->next) {
		result++;
	}
	return result;
}

/**
 * @brief Frees the line_t linked list
 *
 * @param lines the line_t linked list to free
 */
void freeLines(line_t *lines) {
	line_t *next = NULL;
	while (lines != NULL) {
		next = lines->next;
		free(lines);
		lines = next;
	}
}

/**
 * @brief Copies a lines_t linked list to a lineData_t array
 *
 * @param data the array to copy to 
 * @param lines the linked list to copy from
 * @param numLines the number of lines in the linked list
 */
void copyToArr(lineData_t **data, line_t *lines, size_t numLines) {
	size_t i = 0;
	for (line_t *ptr = lines; ptr != NULL; ptr = ptr->next) {
		if (i >= numLines) {
			fprintf(stderr, "Trying to copy more lines than are present\n");
		}
		data[i] = malloc(sizeof(lineData_t));
		if (data[i] == NULL) {
			fprintf(stderr, "Malloc error\n");
			exit(EXIT_FAILURE);
		}
		data[i]->length = ptr->length;
		data[i]->pos = ptr->pos;
		i++;
	}
}

/**
 * @brief Frees a lineData_t array
 *
 * @param data the array to free
 * @param numLines the number of lines in the array
 */
void freeArr(lineData_t **data, size_t numLines) {
	for (size_t i = 0; i < numLines; i++) {
		free(data[i]);
	}
	free(data);
}

/**
 * @brief Checks whether the lines of two different files are equal
 *
 * @param fileData1 The first file's data
 * @param fileData2 The second file's data
 * @return true if they are equal, false otherwise
 */
bool eq(fileData_t *fileData1, fileData_t *fileData2) {
	FILE *file1 = fileData1->file;
	lineData_t *data1 = fileData1->data;
	FILE *file2 = fileData2->file;
	lineData_t *data2 = fileData2->data;
	if (data1->length != data2->length) {
		return false;
	}
	char *res1;
	char *res2;
	char buf1[BUF_SIZE];
	char buf2[BUF_SIZE];
	fseek(file1, data1->pos, SEEK_SET);
	fseek(file2, data2->pos, SEEK_SET);
	while ((res1 = fgets(buf1, BUF_SIZE, file1)) && (res2 = fgets(buf2, BUF_SIZE, file2))) {
		if (strncmp(buf1, buf2, BUF_SIZE) != 0) {
			return false;
		}
	}
	if (res1 != res2) 
		return false;
	else
		return true;
}

/**
 * @brief Runs the core LCS algorithm
 *
 * @param file1 The first file's name
 * @param file2 The second file's name
 * @param recursive Whether to compare recursively
 * @return true if successful, false otherwise
 */
bool runDiff(char *file1, char *file2, bool recursive) {
	if (recursive) {
		return false;
	}
	FILE *file1Opened = fopen(file1, "r");
	if (file1Opened == NULL) {
		fprintf(stderr, "Error: %s\n", strerror(errno));
		return false;
	}
	FILE *file2Opened = fopen(file2, "r");
	if (file2Opened == NULL) {
		fprintf(stderr, "Error: %s\n", strerror(errno));
		fclose(file1Opened);
		return false;
	}
	line_t *file1Lines = traverseFile(file1Opened);
	line_t *file2Lines = traverseFile(file2Opened);
	
	size_t numLinesFile1 = countLines(file1Lines);
	size_t numLinesFile2 = countLines(file2Lines);
	
	lineData_t **lines1Data = calloc(numLinesFile1, sizeof(lineData_t *));
	lineData_t **lines2Data = calloc(numLinesFile2, sizeof(lineData_t *));

	copyToArr(lines1Data, file1Lines, numLinesFile1);
	copyToArr(lines2Data, file1Lines, numLinesFile1);
	
	freeLines(file1Lines);
	freeLines(file2Lines);

	freeArr(lines1Data, numLinesFile1);
	freeArr(lines2Data, numLinesFile2);

	return true;
}












