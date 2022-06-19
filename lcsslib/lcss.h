#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef LCSS_H
#define LCSS_H

typedef bool (*eq_fn)(void *, void *);

/**
 * @brief A function that runs LCSS on two different sequences.
 *
 * @param[in] seq1 The first sequence
 * @param[out] inLcss1 A boolean array that will say whether each line 
 *  in the first sequence is in the LCSS
 * @param[in] s1 Size of the first sequence
 * @param[in] seq2 The second sequence
 * @param[out] inLcss2 A boolean array that will say whether each line 
 *  in the second sequence is in the LCSS
 * @param[in] s2 Size of the second sequence
 * @param eq[in] An equality function for items in both sequences. 
 * @param[out] lcssArrPtr Pointer to the longest common subsequence 
 *  (needs to be freed by user)
 * @param[out] lcssLen Pointer to the length of the longest common subsequence
 */
bool lcss(void **seq1, bool **inLcss1, ssize_t n1, void **seq2, bool **inLcss2, 
	ssize_t n2, eq_fn eq, void ***lcssArrPtr, ssize_t *lcssLen);

#endif
