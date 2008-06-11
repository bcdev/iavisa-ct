#include <algorithm>

#include "CloudTestConstants.h"
#include "CloudTestG.h"
#include "Utils.h"

using namespace std;

/**
 * Test for clouds over elevated polar regions (ALG.A8315.140-155).
 * 
 * @param BT the brightness temperature spectra for the IASI IFOV of interest.
 * @param thrPolcld the IASI channel numbers and thresholds for the cloud test over elevated polar regions.
 * 
 * @return {@code true} if clouds are detected.
 */
static bool cloudTestImpl(const double* BT, const THR_POLCLD& thrPolcld) {
	// [ALG.A8315.150]
	// equation 217 PGS v5.4
	if (BT[0] - BT[1] > thrPolcld.thresholdValues_[0]) {
		return true;
	}

	return false;
}

void CloudTestG::execute(const double parameters[], const SampleList& samples,
		bool estimates[]) const {
	copy(parameters, parameters + 1, thrPolcld.thresholdValues_);

	for (size_t i = 0; i < samples.size(); ++i) {
		estimates[i] = cloudTestImpl(
				samples[i]->getBrightnessTemperatures(TEST_G), thrPolcld);
	}
}

bool CloudTestG::select(const Sample& sample) const {
	if (timeId != findIndex(sample.getMonth(), THR_POLCLD::STORE.months_,
			THR_POLCLD::STORE.monthCount_)) {
		return false;
	}

	return true;
}
