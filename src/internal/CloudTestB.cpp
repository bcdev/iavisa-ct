#include <algorithm>
#include <cmath>

#include "CloudTestConstants.h"
#include "CloudTestB.h"
#include "Utils.h"

using namespace std;

/**
 * IASI inter-channel regression tests (ALG.A315.55-64)
 * 
 * @param BT the brightness temperature spectrum for the IASI IFOV of interest.
 * @param landCover the fractional land cover for the IASI IFOV of interest.
 * @param cofIasint the coefficient and threshold values for the IASI inter-channel
 *                  regression tests of the cloud detection.
 * 
 * @return {@code true} if clouds are detected.
 */
static bool cloudTestImpl(const double* BT, double landCover,
		const COF_IASINT& cofIasint) {
	// [ALG.A8315.55]
	double* a1 = &(cofIasint.coefficientsA1_[0]);
	double* a2 = &(cofIasint.coefficientsA2_[0]);
	double* a3 = &(cofIasint.coefficientsA3_[0]);
	double* t = &(cofIasint.thresholdValues_[0]);

	// Assumption J8.
	if (landCover > LAND_SEA_THRESHOLD) { // Land surface
		a1 += 1;
		a2 += 1;
		a3 += 1;
		t += 1;
		//AUGUST!! with the current implementation, 
		//the order for thresholds is th1_sea,   [0] ; th1_land,  [1]
		//th2_sea,   [2] ; th2_land,  [3]
		//th3_sea,   [4] ; th3_land,  [5]
	}

	// [ALG.A8315.60]
	// Equation 204 PGS v5.6
	if (fabs(BT[0] - (a1[0] + a1[2]*BT[1] + a1[4] *BT[2] + a1[6] *BT[3] + a1[8]
			*BT[4] + a1[10] *BT[5] + a1[12] *BT[6])) > t[0]) {
		return true;
	}

	// Equation 205 PGS v5.6
	if (fabs(BT[7] - (a2[0] + a2[2]*BT[8] + a2[4]*BT[9] + a2[6] *BT[10] + a2[8]
			*BT[11] + a2[10]*BT[12] + a2[12] *BT[13])) > t[2]) {
		return true;
	}

	// Equation 206 PGS v5.6
	if (fabs(BT[14] - (a3[0] +a3[2]*BT[15])) > t[4]) {
		return true;
	}

	return false;
}

void CloudTestB::execute(const double parameters[], const SampleList& samples,
		bool estimates[]) const {
	const int32_t count = cofIasint.surfaceTypeCount_;
	copy(parameters, parameters + 3 * count, cofIasint.thresholdValues_);

	copy(parameters + 3 * count, parameters + 10 * count,
			cofIasint.coefficientsA1_);
	copy(parameters + 10 * count, parameters + 17 * count,
			cofIasint.coefficientsA2_);
	copy(parameters + 17 * count, parameters + 19 * count,
			cofIasint.coefficientsA3_);

	for (size_t i = 0; i < samples.size(); ++i) {
		estimates[i] = cloudTestImpl(
				samples[i]->getBrightnessTemperatures(TEST_B),
				samples[i]->getFractionalLandCover(), cofIasint);
	}
}

bool CloudTestB::select(const Sample& sample) const {
	if (zoneId != findIndex(sample.getLat(), COF_IASINT::STORE.lats_,
			COF_IASINT::STORE.latCount_)) {
		return false;
	}
	if (timeId != findIndex(sample.getMonth(), COF_IASINT::STORE.months_,
			COF_IASINT::STORE.monthCount_)) {
		return false;
	}

	return true;
}
