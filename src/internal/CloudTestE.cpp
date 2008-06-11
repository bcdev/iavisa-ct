#include<algorithm>

#include "CloudTestConstants.h"
#include "CloudTestE.h"
#include "Utils.h"

using namespace std;

/**
 * Thresholds on IASI EOF residuals (ALG.A8315.100-115).
 * 
 * @param BT the brightness temperature spectra for the IASI IFOV of interest.
 * @param thrEofres the thresholds for the EOF residual test of the cloud detection.
 * @param landCover the fractional land cover for the IASI IFOV of interest.
 * 
 * @return {@code true} if clouds are detected.
 */
static bool cloudTestImpl(const double* BT, const THR_EOFRES& thrEofres,
		double landCover) {
	bool retValue = false;

	// [ALG.A8315.110]
	int nbrEofChannels = thrEofres.channelCount_;
	int nbrEofs = thrEofres.clearSkyEofCount_;

	const double* U = thrEofres.clearSkyEofs_;
	const double* t = thrEofres.thresholdValues_;

	double* s = (double*)malloc(nbrEofChannels*sizeof(double));
	if (!s)
		fprintf(stderr,"allocation failure in Cloud_detection\n");
	double* c = (double*)malloc(nbrEofs*sizeof(double));
	if (!c)
		fprintf(stderr,"allocation failure in Cloud_detection\n");

	if (!s || !c)
		return false;

	if (landCover > PURE_LAND_THRESHOLD) {// pure land surface
		t += 1;
	} else if (landCover > PURE_SEA_THRESHOLD) { // mixed surface
		t += 2;
	}
	// else they are pointing to sea surface

	// [ALG.A8315.100]
	for (int i=0; i<nbrEofChannels; i++) {
		s[i] = BT[i];
	}

	// equation 209 PGS v5.4 (c = U^t s)
	for (int j=0; j<nbrEofs; j++) {
		c[j] = 0.0;

		for (int i=0; i<nbrEofChannels; i++) {
			c[j] += U[j*nbrEofChannels + i]*s[i];
		}
	}

	for (int i=0; i<nbrEofs; i++) {
		if (c[i] > t[0]) { //if (fabs(residuals[i]) > t[0]) 
			retValue = true;
		}
	}

	if (s)
		free(s);
	if (c)
		free(c);

	return retValue;
}

void CloudTestE::execute(const double parameters[], const SampleList& samples,
		bool estimates[]) const {
	copy(parameters, parameters + thrEofres.surfaceTypeCount_,
			thrEofres.thresholdValues_);

	for (size_t i = 0; i < samples.size(); ++i) {
		estimates[i] = cloudTestImpl(
				samples[i]->getBrightnessTemperatures(TEST_E), thrEofres,
				samples[i]->getFractionalLandCover());
	}
}

bool CloudTestE::select(const Sample& sample) const {
	if (zoneId != findIndex(sample.getLat(), THR_EOFRES::STORE.lats_,
			THR_EOFRES::STORE.latCount_)) {
		return false;
	}
	if (timeId != findIndex(sample.getMonth(), THR_EOFRES::STORE.months_,
			THR_EOFRES::STORE.monthCount_)) {
		return false;
	}

	return true;
}
