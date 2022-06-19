#include "../lcsslib/lcss.h"
#include <stdbool.h>
#include <stdio.h>

bool eqChars(void *a, void *b) {
	char aC = (char)(long)a;
	char bC = (char)(long)b;
	return aC == bC;
}

bool testSimpleSeqs(void) {
	long seq1[5];
	long seq2[5];
	seq1[0] = (long)'a';
	seq1[1] = (long)'b';
	seq1[2] = (long)'c';
	seq1[3] = (long)'d';
	seq1[4] = (long)'e';
	seq2[0] = (long)'a';
	seq2[1] = (long)'e';
	seq2[2] = (long)'b';
	seq2[3] = (long)'c';
	seq2[4] = (long)'d';
	// abcde and aebcd
	ssize_t size; 
	void **lcssArr;
	bool *inLcss1, *inLcss2;
	lcss((void **)&seq1, &inLcss1, 5, (void **)&seq2, &inLcss2, 5, &eqChars, 
		&lcssArr, &size);
	if (size != 4) {
		free(lcssArr);
		free(inLcss1);
		free(inLcss2);
		return false;
	}
	char expected[4] = {'a', 'b', 'c', 'd'};
	for (int i = 0; i < 4; i++) {
		if (expected[i] != (char)(long)lcssArr[i]) {
			free(lcssArr);
			free(inLcss1);
			free(inLcss2);
			return false;
		}
	}
	free(lcssArr);
	free(inLcss1);
	free(inLcss2);
	return true;
}

int main() {	
	if (!testSimpleSeqs())
		printf("FAILED\n");
	else 
		printf("PASSED\n");
	exit(EXIT_SUCCESS);
}

