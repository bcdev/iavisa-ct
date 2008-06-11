#include <algorithm>
#include <iostream>

#include "CloudTestConstants.h"
#include "CloudTestD.h"
#include "Utils.h"

using namespace std;

/**
 * Horizontal coherence test (ALG.A8315.80-95).
 * <p/>
 * Note that this test is applicable only if <em>all</em> IFOVs in the EFOV of
 * interest are valid.
 * 
 * @param BT the brightness temperature spectra for all IFOVs in the IASI EFOV of interest.
 * @param ifovInEfov the actual index of the IASI IFOV of interest.
 * @param thrHorco the threshold for the horizontal coherence test of cloud detection.
 * @param landCover the fractional land cover for the IASI IFOV of interest.
 * 
 * @return {@code true} if clouds are detected.
 */
static bool cloudTestImpl(const double* BT, unsigned ifovInEfov,
		const THR_HORCO& thrHorco, double landCover) {
	double average = 0.0;

	// [ALG.A8315.90]
	for (int i=0; i<IFOV_IN_EFOV_COUNT; i++) {
		average += BT[i];
	}

	average = average/ IFOV_IN_EFOV_COUNT;
	
#ifdef TEST_D_
	cout << "  meanBt = " << average;
	cout << "  ifovBt = " << BT[ifovInEfov] << endl;
#endif
	
	if (landCover < PURE_SEA_THRESHOLD) { // pure sea case
		if (average-BT[ifovInEfov]
				> thrHorco.thresholdValues_[0]) {
			return true;
		}
	} else if (landCover < PURE_LAND_THRESHOLD) { // Mixed surface type
		if (average-BT[ifovInEfov]
				> thrHorco.thresholdValues_[2]) {
			return true;
		}
	} else { // pure land surface type 
		if (average-BT[ifovInEfov]
				> thrHorco.thresholdValues_[1]) {
			return true;
		}
	}

	return false;
}


void CloudTestD::execute(const double parameters[], const SampleList& samples,
		bool estimates[]) const {
	copy(parameters, parameters + 3, thrHorco.thresholdValues_);

	for (size_t i = 0; i < samples.size(); ++i) {
#ifdef TEST_D_
		cout << "  lat = " << samples[i]->getLat();
		cout << "  lon = " << samples[i]->getLon();
#endif		
		estimates[i] = cloudTestImpl(
				samples[i]->getBrightnessTemperatures(TEST_D),
				samples[i]->getIfovInEfovIndex(),
				thrHorco,
				samples[i]->getFractionalLandCover());
	}
}

bool CloudTestD::select(const Sample& sample) const {
	if (zoneId != findIndex(sample.getLat(), THR_HORCO::STORE.lats_,
			THR_HORCO::STORE.latCount_)) {
		return false;
	}
	if (timeId != findIndex(sample.getMonth(), THR_HORCO::STORE.months_,
			THR_HORCO::STORE.monthCount_)) {
		return false;
	}

	return true;
}
