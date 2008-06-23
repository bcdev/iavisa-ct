#include <algorithm>
#include <cmath>

#include "AbstractDataReader.h"
#include "FilePathResolver.h"
#include "Utils.h"

#include "COF_IASINT.h"

using namespace std;

COF_IASINT::COF_IASINT(int32_t zoneId, int32_t timeId) {
	init(1, 1, STORE.surfaceTypeCount_);

	const int32_t l = zoneId;
	const int32_t m = timeId;
	
	for (int32_t i = 0, k = 0; i < 3; ++i) {
		for (int32_t j = 0; j < STORE.surfaceTypeCount_; ++j) {
			thresholdValues_[k] = STORE.thresholdValues_[l + STORE.latCount_ * (m + STORE.monthCount_ * (j + i * STORE.surfaceTypeCount_))];
			++k;
		}
	}
	for (int32_t i = 0, k = 0; i < 7; ++i) {
		for (int32_t j = 0; j < STORE.surfaceTypeCount_; ++j) {
			coefficientsA1_[k] = STORE.coefficientsA1_[l + STORE.latCount_ * (m + STORE.monthCount_ * (j + i * STORE.surfaceTypeCount_))];
			coefficientsA2_[k] = STORE.coefficientsA2_[l + STORE.latCount_ * (m + STORE.monthCount_ * (j + i * STORE.surfaceTypeCount_))];
			++k;
		}
	}
	for (int32_t i = 0, k = 0; i < 2; ++i) {
		for (int32_t j = 0; j < STORE.surfaceTypeCount_; ++j) {
			coefficientsA3_[k] = STORE.coefficientsA3_[l + STORE.latCount_ * (m + STORE.monthCount_ * (j + i * STORE.surfaceTypeCount_))];
			++k;
		}
	}
}

COF_IASINT::COF_IASINT(int32_t monthCount, int32_t latCount, int32_t surfaceTypeCount) {
	init(monthCount, latCount, surfaceTypeCount);
}

COF_IASINT::~COF_IASINT() {
	delete[] coefficientsA3_;
	delete[] coefficientsA2_;
	delete[] coefficientsA1_;
	delete[] thresholdValues_;
	delete[] lats_;
	delete[] months_;
}

void COF_IASINT::init(int32_t monthCount, int32_t latCount, int32_t surfaceTypeCount) {
	monthCount_ = monthCount;
	latCount_ = latCount;
	surfaceTypeCount_ = surfaceTypeCount;

	months_ = new int32_t[monthCount];
	lats_ = new double[latCount];

	const int32_t count = surfaceTypeCount * latCount * monthCount;
	thresholdValues_ = new double[3 * count];

	coefficientsA1_ = new double[7 * count];
	coefficientsA2_ = new double[7 * count];
	coefficientsA3_ = new double[2 * count];
}

class COF_IASINT::Reader : public AbstractDataReader<COF_IASINT> {
protected:
	COF_IASINT read(istream& is) {
		int32_t monthCount;
		int32_t latCount;
		int32_t surfaceConditionCount = 2;

		readInt64BE(is, &monthCount);

		int32_t* months = new int32_t[monthCount];
		readInt64BE(is, months, monthCount);
		readInt64BE(is, &latCount);

		double* lats = new double[latCount];
		readInt64BE(is, lats, latCount);

		skip<int64_t>(is, surfaceConditionCount);

		COF_IASINT cofIasint(monthCount, latCount, surfaceConditionCount);
		copy(months, months + monthCount, cofIasint.months_);
		copy(lats, lats + latCount, cofIasint.lats_);

		skip<int64_t>(is, 16);

		const int count = 2 * latCount * monthCount;
		readBE(is, cofIasint.thresholdValues_, 3 * count);

		readBE(is, cofIasint.coefficientsA1_, 7 * count);
		readBE(is, cofIasint.coefficientsA2_, 7 * count);
		readBE(is, cofIasint.coefficientsA3_, 2 * count);

		delete[] lats;
		delete[] months;

		return cofIasint;
	}
};

const COF_IASINT
		COF_IASINT::STORE =
				COF_IASINT::Reader().AbstractDataReader<COF_IASINT>::read(FilePathResolver::getAbsolutePath("auxdata/IASI_L2_PGS_COF_IASINT").c_str());
