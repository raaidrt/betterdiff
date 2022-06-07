#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef DIFF_UTILS_HELPERS_H
#define DIFF_UTILS_HELPERS_H


#define BUF_SIZE 1024

/**
 * struct line - Stores a single line's metadata using a linked list 
 */
typedef struct line {
/**
 * @length Length of the line
 */
	unsigned long long length;
/**
 * @pos Position in the file of the line
 */
	ssize_t pos;
/**
 * struct line - Pointer to the next line in the linked list structure
 */
	struct line *next;
} line_t;

/**
 * @brief Changes the terminal to print pink text
 */
void makePink(void);

/**
 * @brief Changes the terminal to print cyan text
 */
void makeCyan(void);

/**
 * @brief Resets the terminal color
 */
void resetColor(void);

/**
 * @brief Used to traverse a file to generate a line_t linked list.
 *
 * @param file The file to traverse
 * @return The line_t linked list pointer
 */
line_t *traverseFile(FILE *file);

/**
 * @brief Frees the line_t linked list
 *
 * @param lines the line_t linked list to free
 */
void freeLines(line_t *lines);

/**
 * struct lineData - stores a single line's metadata
 */
typedef struct lineData {
/**
 * @length a field storing the length of the data
 */
	unsigned long long length;
/**
 * @pos a field storing the position on the file of the data
 */
	ssize_t pos;
} lineData_t;


/**
 * struct fileData - Stores a file's data
 */
typedef struct fileData {
	FILE *file;
	lineData_t *data;
} fileData_t;

/**
 * @brief Checks whether the lines of two different files are equal
 *
 * @param fileData1 The first file's data
 * @param fileData2 The second file's data
 * @return true if they are equal, false otherwise
 */
bool eq(void *fileData1, void *fileData2);

#endif
