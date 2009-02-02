#include <stdio.h>

#include "gt.h"

int main(int argc, char* argv[]) {
	char* initId = "";
	if (argc > 0) {
		initId = argv[1];
	} 

	gtInit(TRAINING, TEST_B, initId, 0);
	printf("TEST B: %d\n", gtSampleCount());

	gtInit(TRAINING, TEST_D, initId, 0);
	printf("TEST D: %d\n", gtSampleCount());

	gtInit(TRAINING, TEST_E, initId, 0);
	printf("TEST E: %d\n", gtSampleCount());
	
	gtInit(TRAINING, TEST_F, initId, 0);
	printf("TEST F: %d\n", gtSampleCount());

	gtInit(TRAINING, TEST_G, initId, 0);
	printf("TEST G: %d\n", gtSampleCount());

	gtInit(TRAINING, TEST_H, initId, 0);
	printf("TEST H: %d\n", gtSampleCount());
	gtExit();

	return 0;
}
