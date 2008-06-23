#ifndef AUXILIARY_DATA_PROVIDER_H_
#define AUXILIARY_DATA_PROVIDER_H_

#include <stdint.h>

#include "Enums.h"
#include "THR_CLDDET.h"
#include "COF_IASINT.h"
#include "THR_HORCO.h"
#include "THR_EOFRES.h"
#include "THR_WINCOR.h"
#include "THR_POLCLD.h"
#include "THR_DESSTR.h"

class AuxiliaryDataProvider {
public:

	static int getZoneCount(TestId testId) {
		switch (testId) {
		case TEST_A:
			return THR_CLDDET::STORE.latCount_;
		case TEST_B:
			return COF_IASINT::STORE.latCount_;
		case TEST_D:
			return THR_HORCO::STORE.latCount_;
		case TEST_E:
			return THR_EOFRES::STORE.latCount_;
		case TEST_F:
			return THR_WINCOR::STORE.latCount_;
		case TEST_G:
			return 1;
		case TEST_H:
			return THR_DESSTR::STORE.latLonGridPointCount_;
		default:
			return 0;
		}
	}

	static int getTimeCount(TestId testId) {
		switch (testId) {
		case TEST_A:
			return THR_CLDDET::STORE.monthCount_;
		case TEST_B:
			return COF_IASINT::STORE.monthCount_;
		case TEST_D:
			return THR_HORCO::STORE.monthCount_;
		case TEST_E:
			return THR_EOFRES::STORE.monthCount_;
		case TEST_F:
			return THR_WINCOR::STORE.monthCount_;
		case TEST_G:
			return THR_POLCLD::STORE.monthCount_;
		case TEST_H:
			return THR_DESSTR::STORE.monthCount_;
		default:
			return 0;
		}
	}

	static int getParameterCount(TestId testId) {
		switch (testId) {
		case TEST_A:
			return THR_CLDDET::STORE.channelCount_ * 2;
		case TEST_B:
			return COF_IASINT::STORE.surfaceTypeCount_ * 19;
		case TEST_D:
			return 3;
		case TEST_E:
			return THR_EOFRES::STORE.surfaceTypeCount_;
		case TEST_F:
			return 3;
		case TEST_G:
			return 1;
		case TEST_H:
			return 2;
		default:
			return 0;
		}
	}

	static void getDefaultParameters(TestId testId, int32_t zoneId, int32_t timeId,
			double parameters[]) {
		const int32_t l = zoneId;
		const int32_t m = timeId;

		switch (testId) {
		case TEST_A:
			for (int32_t i = 0, k = 0; i < THR_CLDDET::STORE.channelCount_; ++i) {
				for (int32_t j = 0; j < 2; ++j) {
					parameters[k] = THR_CLDDET::STORE.thresholdValues_[j + 2 * (m + THR_CLDDET::STORE.monthCount_ * (l + i * THR_CLDDET::STORE.latCount_))];
					++k;
				}
			}
			return;
		case TEST_B: {
			int32_t k = 0;
			for (int32_t i = 0; i < 3; ++i) {
				for (int32_t j = 0; j < COF_IASINT::STORE.surfaceTypeCount_; ++j) {
					parameters[k]
							= COF_IASINT::STORE.thresholdValues_[l + COF_IASINT::STORE.latCount_ * (m + COF_IASINT::STORE.monthCount_ * (j + i * COF_IASINT::STORE.surfaceTypeCount_))];
					++k;
				}
			}
			for (int32_t i = 0; i < 7; ++i) {
				for (int32_t j = 0; j < COF_IASINT::STORE.surfaceTypeCount_; ++j) {
					parameters[k]
							= COF_IASINT::STORE.coefficientsA1_[l + COF_IASINT::STORE.latCount_ * (m + COF_IASINT::STORE.monthCount_ * (j + i * COF_IASINT::STORE.surfaceTypeCount_))];
					++k;
				}
			}
			for (int32_t i = 0; i < 7; ++i) {
				for (int32_t j = 0; j < COF_IASINT::STORE.surfaceTypeCount_; ++j) {
					parameters[k]
							= COF_IASINT::STORE.coefficientsA2_[l + COF_IASINT::STORE.latCount_ * (m + COF_IASINT::STORE.monthCount_ * (j + i * COF_IASINT::STORE.surfaceTypeCount_))];
					++k;
				}
			}
			for (int32_t i = 0; i < 2; ++i) {
				for (int32_t j = 0; j < COF_IASINT::STORE.surfaceTypeCount_; ++j) {
					parameters[k]
							= COF_IASINT::STORE.coefficientsA3_[l + COF_IASINT::STORE.latCount_ * (m + COF_IASINT::STORE.monthCount_ * (j + i * COF_IASINT::STORE.surfaceTypeCount_))];
					++k;
				}
			}
			return;
		}
		case TEST_D:
			for (int32_t k = 0; k < 3; ++k) {
				parameters[k]
						= THR_HORCO::STORE.thresholdValues_[l + THR_HORCO::STORE.latCount_ * (m + k * THR_HORCO::STORE.monthCount_)];
			}
			return;
		case TEST_E:
			for (int32_t k = 0; k < THR_EOFRES::STORE.surfaceTypeCount_; ++k) {
				parameters[k]
						= THR_EOFRES::STORE.thresholdValues_[k + THR_EOFRES::STORE.surfaceTypeCount_ * (m + l * THR_EOFRES::STORE.monthCount_)];
			}
			return;
		case TEST_F:
			for (int32_t k = 0; k < 3; ++k) {
				parameters[k] = THR_WINCOR::STORE.thresholdValues_[k + 3 * (m + l * THR_WINCOR::STORE.monthCount_)];
			}
			return;
		case TEST_G:
			parameters[0] = THR_POLCLD::STORE.thresholdValues_[m];
			return;
		case TEST_H:
			for (int32_t i = 0, k = 0; i < 2; ++i) {
				parameters[k] = THR_DESSTR::STORE.thresholdValues_[i + 2 * (m + THR_DESSTR::STORE.monthCount_ * l)];
				++k;
			}
			return;
		}
	}
};

#endif /*AUXILIARY_DATA_PROVIDER_H_*/
