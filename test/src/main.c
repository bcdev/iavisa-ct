#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "gt.h"

int main(int argc, char* argv[]) {
	char* initId = "";
	if (argc > 0) {
		initId = argv[1];
	}

	gtInit(TRAINING, TEST_E, initId, "test.par");
	const int32_t sampleCount = gtSampleCount();

	int32_t* truths = (int32_t*) malloc(sampleCount * sizeof(int32_t));
	gtGetCloudTruth(truths);

	bool* estimates = (bool*) malloc(sampleCount * sizeof(bool));
	
	const clock_t start = clock();
	gtGetCloudGuess(estimates);
	const clock_t stop = clock();
	
	int cloudCloud = 0;
	int cloudClear = 0;
	int clearCloud = 0;
	int clearClear = 0;

	// build contingency table
	int i;
	for (i = 0; i < sampleCount; ++i) {
		if (estimates[i]) {
			if (truths[i] != 1) {
				++cloudCloud;
			} else {
				++cloudClear;
			}
		} else {
			if (truths[i] != 1) {
				++clearCloud;
			} else {
				++clearClear;
			}
		}
	}

	printf("cloud-cloud: %d\n", cloudCloud);
	printf("cloud-clear: %d\n", cloudClear);
	printf("clear-cloud: %d\n", clearCloud);
	printf("clear-clear: %d\n", clearClear);
	printf("\n");
	printf("test execution time: %d microseconds\n", (stop - start) / 1000);

	if (estimates != 0) {
		free(estimates);
	}
	if (truths != 0) {
		free(truths);
	}

	return 0;
}
