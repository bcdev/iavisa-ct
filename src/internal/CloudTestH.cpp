#include <cstdio>
#include <cstdlib>
#include <cmath>

#include "CloudTestConstants.h"
#include "CloudTestH.h"
#include "Utils.h"

using namespace std;

/**
 * Detection of dust storms (ALG.A8315.160-175).
 * 
 * @param BT the brightness temperature spectra for the IASI IFOV of interest.
 * @param thrDesstr the IASI channel numbers and thresholds for the cloud test of desert dust storms.
 * @param fractionalLandCover the fractional land cover for the IASI IFOV of interest.
 * 
 * @return {@code true} if clouds are detected.
 */
static bool cloudTestImpl(const double* BT, const THR_DESSTR& thrDesstr,
		double fractionalLandCover) {
	// Equation 218g PGS v5.4
	// [ALG.A8315.170]
	if (fractionalLandCover < PURE_SEA_THRESHOLD) { // Pure sea surface type
		if (BT[0] - BT[1] > thrDesstr.thresholdValues_[0]) {
			return true;
		}
	} else if (fractionalLandCover < PURE_LAND_THRESHOLD) { // Mixed surface type
		if (BT[0] - BT[1] > thrDesstr.thresholdValues_[1]) {
			return true;
		}
	} else { // Pure land surface type    
		if (BT[0] - BT[1] > thrDesstr.thresholdValues_[1]) { // same threshold as for mixed
			return true;
		}
	}

	return false;
}

void CloudTestH::execute(const double parameters[], const SampleList& samples,
		bool estimates[]) const {
	copy(parameters, parameters + 2, thrDesstr.thresholdValues_);

	for (size_t i = 0; i < samples.size(); ++i) {
		estimates[i] = cloudTestImpl(
				samples[i]->getBrightnessTemperatures(TEST_H), thrDesstr,
				samples[i]->getFractionalLandCover());
	}
}

bool CloudTestH::select(const Sample& sample) const {
	if (fabs(sample.getLat() - THR_DESSTR::STORE.lats_[zoneId]) > 2.5) {
		return false;
	}
	if (fabs(sample.getLon() - THR_DESSTR::STORE.lons_[zoneId]) > 2.5) {
		return false;
	}
	if (timeId != findIndex(sample.getMonth(), THR_DESSTR::STORE.months_,
			THR_DESSTR::STORE.monthCount_)) {
		return false;
	}

	return true;
}
