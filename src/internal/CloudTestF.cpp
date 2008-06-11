#include <algorithm>
#include <cmath>

#include "CloudTestConstants.h"
#include "CloudTestF.h"
#include "Utils.h"

using namespace std;

/**
 * Window cross-correlation tests (ALG.A8315.120-135).
 * 
 * @param R the brightness temperature spectra for the IASI IFOV of interest.
 * @param thrWincor the thresholds for the window cross correlation cloud detection method.
 * @param landCover the fractional land cover for the IASI IFOV of interest.
 * 
 * @return {@code true} if clouds are detected.
 */
inline bool cloudTestImpl(const double* R, const THR_WINCOR& thrWincor,
		double fractionalLandCover) {
	const int maxSpectralLags = 200; // PGS p.165

	int surfaceType = 0;

	// [ALG.A8315.130]
	int NS = thrWincor.spectralLagCount_;
	int NK = thrWincor.channelCount_;

	double c1[maxSpectralLags];
	double c2[maxSpectralLags];
	double c12[maxSpectralLags];

	double RrefAverage = 0.0;
	double Raverage = 0.0;

	if (fractionalLandCover < PURE_SEA_THRESHOLD) {
		surfaceType = 0; // Sea surface type
	} else if (fractionalLandCover < PURE_LAND_THRESHOLD) {
		surfaceType = 2; // Mixed surface type      
	} else {
		surfaceType = 1; // pure Land surface type      
	}

	// Calculate this fter actual "surfaceType" computation
	double t = thrWincor.thresholdValues_[surfaceType];
	double* Rref =
			&thrWincor.referenceSpectra_[surfaceType*thrWincor.channelCount_];

	// [ALG.A8315.120]
	for (int j=0; j<NK; j++) {
		RrefAverage += Rref[j];
		Raverage += R[j];
	}

	RrefAverage /= NK;
	Raverage /= NK;

	for (int i=0; i<=NS; i++) {
		double sum1 = 0.0;
		double sum2 = 0.0;
		double sum12 = 0.0;

		for (int j=0; j<NK-i; j++) {
			sum1 += (Rref[j]-RrefAverage)*(Rref[j+i]-RrefAverage); // eq. 214 PGS v5.4
			sum2 += (R[j]-Raverage)*(R[j+i]-Raverage); // eq. 214 PGS v5.4
			sum12 += (Rref[j]-RrefAverage)*(R[j+i]-Raverage); // eq. 215 PGS v5.4
		}

		c1[i] = sum1/NK;
		c2[i] = sum2/NK;
		c12[i] = sum12/NK;
	}

	// equation 211 PGS v5.4
	double sum1 = 0.0;
	double sum2 = 0.0;

	for (int i=0; i<=NS; i++) {
		sum1 += c1[i]/c1[0] - c2[i]/c2[0];
		sum2 += c12[i]/sqrt(c1[0]*c2[0]);
	}

	//if (fabs(sum1/sum2) > t) // Equation 216 PGS v5.4
	// Equation 216 PGS v5.4
	if (fabs(sum1/sum2) > t) //thr is surface type dependant
	{
		return true;
	}

	return false;
}

void CloudTestF::execute(const double parameters[], const SampleList& samples,
		bool estimates[]) const {
	copy(parameters, parameters + 3, thrWincor.thresholdValues_);

	for (size_t i = 0; i < samples.size(); ++i) {
		estimates[i] = cloudTestImpl(
				samples[i]->getBrightnessTemperatures(TEST_F), thrWincor,
				samples[i]->getFractionalLandCover());
	}
}

bool CloudTestF::select(const Sample& sample) const {
	if (zoneId != findIndex(sample.getLat(), THR_WINCOR::STORE.lats_,
			THR_WINCOR::STORE.latCount_)) {
		return false;
	}
	if (timeId != findIndex(sample.getMonth(), THR_WINCOR::STORE.months_,
			THR_WINCOR::STORE.monthCount_)) {
		return false;
	}

	return true;
}
