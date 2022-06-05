#include <stdbool.h>

#ifndef DIFF_UTILS_H
#define DIFF_UTILS_H

/**
 * @brief Runs the core LCS algorithm
 *
 * @param file1 The first file's name
 * @param file2 The second file's name
 * @param recursive Whether to compare recursively
 * @return true if successful, false otherwise
 */
bool runDiff(char *file1, char *file2, bool recursive);

#endif
