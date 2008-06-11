#ifndef UTILITY_FUNCTIONS_H_
#define UTILITY_FUNCTIONS_H_

#include <cmath>

/**
 * Planck constants.
 */
const double planck_c1 = 1.1910427e-16;
const double planck_c2 = 1.4387752e-02;

inline double planckFunction(const double wavenumber,
		const double tunedBrightnessTemperature) {
	return ((planck_c1 * std::pow(wavenumber, 3)) / (std::exp((planck_c2
			* wavenumber) / tunedBrightnessTemperature) -1));
}

inline double invertedPlanckFunction(const double wavenumber,
		const double radiance) {
	return ((planck_c2 * wavenumber) / (std::log(1 + planck_c1 * std::pow(
			wavenumber, 3) / radiance)));
}

inline double wavenumberCenter(const int k) {
	return (64500.0 + (k - 1) * 25.0);
}

inline bool checkAssociatedChan(int nbChan, int* chanIds,
		unsigned char* chanStatus) {
	for (int idChan=0; idChan<nbChan; idChan++) {
		if (chanStatus[chanIds[idChan] - 1] == 0) {
			return false;
		}
	}

	return true;
}

inline double radianceTuning(int Nkt, int* chanId, double* tuningCoeff,
		double* Tb) {
	double tunedTb;

	tunedTb = tuningCoeff[0];
	for (int i=0; i < Nkt; i++)
		tunedTb += tuningCoeff[i+1] * Tb[chanId[i]-1];

	return tunedTb;
}

inline double planck(int k, double t) {
	return planckFunction(wavenumberCenter(k), t);
}

inline double inverse_planck(int k, double r) {
	return invertedPlanckFunction(wavenumberCenter(k), r);
}

#endif /*UTILITY_FUNCTIONS_H_*/
