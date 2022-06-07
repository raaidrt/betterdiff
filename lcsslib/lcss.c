#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lcss.h"

size_t max(size_t n1, size_t n2) {
	if (n1 > n2) 
		return n1;
	else
		return n2;
}

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
bool lcss(void **seq1, bool **inLcss1, size_t n1, void **seq2, bool **inLcss2, 
	size_t n2, eq_fn eq, void ***lcssArrPtr, size_t *lcssLen) {
	// First find the length of the longest common subsequence
	size_t **dp = calloc(n1 + 1, sizeof(size_t *));
	for (size_t i = 0; i <= n1; i++) {
		dp[i] = calloc(n2 + 1, sizeof(size_t));
		if (dp[i] == NULL) {
			for (size_t j = i - 1; j >= 0; j--) {
				free(dp[j]);
			}
			free(dp);
			return false;
		}
	}
	for (size_t i = 1; i <= n1; i++) {
		for (size_t j = 1; j <= n2; j++) {
			if ((*eq)(seq1[i], seq2[j]))
				dp[i][j] = dp[i - 1][j - 1] + 1;
			else
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
		}
	}
	if (lcssLen != NULL)
		*lcssLen = dp[n1][n2];
	
	// Now find the actual longest common subsequence with help from DP array
	if (lcssArrPtr != NULL)
		*lcssArrPtr = calloc(*lcssLen, sizeof(void *));
	size_t i = n1;
	size_t j = n2;
	size_t k = dp[n1][n2] - 1;

	if (inLcss1 != NULL) {
		*inLcss1 = calloc(n1, sizeof(bool));
		if (*inLcss1 == NULL) {
			for (size_t i = 0; i <= n1; i++) {
				free(dp[i]);
			}
			free(dp);
			return false;
		}
	}

	if (inLcss2 != NULL) {
		*inLcss2 = calloc(n2, sizeof(bool));
		if (*inLcss2 == NULL) {
			for (size_t i = 0; i <= n2; i++) {
				free(dp[i]);
			}
			free(dp);
			if (inLcss1 != NULL)
				free(inLcss1);
			return false;
		}
	}
	
	while (k >= 0) {
		if ((*eq)(seq1[i - 1], seq2[j - 1])) {
			if (lcssArrPtr != NULL)
				(*lcssArrPtr)[k] = seq1[i - 1];
			i--;
			if (inLcss1 != NULL)
				(*inLcss1)[i] = true;
			j--;
			if (inLcss2 != NULL)
				(*inLcss2)[i] = true;
			k--;
		} else if (dp[i - 1][j] > dp[j - 1][i]) {
			i--;
		} else {
			j--;
		}
	}
	for (size_t i = 0; i <= n1; i++) {
		free(dp[i]);
	}
	free(dp);
	return true;
}
