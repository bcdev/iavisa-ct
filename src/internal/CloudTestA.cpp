#include <algorithm>

#include "CloudTestConstants.h"
#include "CloudTestA.h"
#include "Utils.h"

using namespace std;

/**
 * Window channel tests (ALG.A8315.10-50)
 * <p/>
 * For 5 selected window channels the brightness temperature is compared to
 * a threshold value.
 * 
 * @param thrClddet the threshold values for the window channel tests.
 * @param landCover the fractional land cover for the IASI IFOV of interest.
 * @param BT the brightness temperature spectrum for the IASI IFOV of interest.
 * 
 * @return {@code true} if clouds are detected.  
 */
static bool cloudTestImpl(const THR_CLDDET& thrClddet, double landCover,
		const double* BT) {
	bool retValue = false;

	// We should simplify this when using the definitive RTIASI version
	// [ALG.A8315.10]
	int nbrChlTestA = thrClddet.channelCount_;
	int offsetThr = 0;

	if (landCover >= LAND_SEA_THRESHOLD) {
		offsetThr++; // offset to land 
		// The difference values are delivered in the following order : 
		//day/land, night/land, day/sea, night/sea
	}

	for (int k = 0; k < nbrChlTestA; k++) {
		double threshold;
		// [ALG.A8315.30] - Threshold values are from THR_CLDDET
		threshold = thrClddet.thresholdValues_[offsetThr];

		offsetThr += 2; // move to the next channel

		// [ALG.A8315.40/50]
		if (BT[k] < threshold) {
			retValue = true;
			break;
		}
	}

	return retValue;
}

void CloudTestA::execute(const double parameters[], const SampleList& samples,
		bool estimates[]) const {
	copy(parameters, parameters + 2 * thrClddet.channelCount_,
			thrClddet.thresholdValues_);

	for (size_t i = 0; i < samples.size(); ++i) {
		estimates[i] = cloudTestImpl(thrClddet,
				samples[i]->getFractionalLandCover(),
				samples[i]->getBrightnessTemperatures(TEST_A));
	}
}

bool CloudTestA::select(const Sample& sample) const {
	if (zoneId != findIndex(sample.getLat(), THR_CLDDET::STORE.lats_,
			THR_CLDDET::STORE.latCount_)) {
		return false;
	}
	if (timeId != findIndex(sample.getMonth(), THR_CLDDET::STORE.months_,
			THR_CLDDET::STORE.monthCount_)) {
		return false;
	}

	return true;
}
