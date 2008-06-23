#include <algorithm>
#include <vector>

#include "AbstractDataReader.h"
#include "FilePathResolver.h"
#include "Utils.h"

#include "THR_WINCOR.h"

using namespace std;

THR_WINCOR::THR_WINCOR(int32_t zoneId, int32_t timeId) {
	init(1, STORE.channelCount_, STORE.spectralLagCount_, 1);

	const int32_t l = zoneId;
	const int32_t m = timeId;

	int32_t k = 0;
	for (int32_t i = 0; i < 3; ++i) {
		for (int32_t j = 0; j < STORE.channelCount_; ++j) {
			referenceSpectra_[k]
					= STORE.referenceSpectra_[j + STORE.channelCount_ * (i + 3 * (m + l * STORE.monthCount_))];
			++k;
		}
	}
	for (int32_t i = 0; i < 3; ++i) {
		thresholdValues_[i] = STORE.thresholdValues_[i + 3 * (m + l * STORE.monthCount_)];
	}
}

THR_WINCOR::THR_WINCOR(int32_t monthCount, int32_t channelCount,
		int32_t spectralLagCount, int32_t latCount) {
	init(monthCount, channelCount, spectralLagCount, latCount);
}

THR_WINCOR::~THR_WINCOR() {
	delete[] months_;
	delete[] lats_;
	delete[] referenceSpectra_;
	delete[] thresholdValues_;
}

void THR_WINCOR::init(int32_t monthCount, int32_t channelCount,
		int32_t spectralLagCount, int32_t latCount) {
	monthCount_ = monthCount;
	channelCount_ = channelCount;
	spectralLagCount_ = spectralLagCount;
	latCount_ = latCount;

	months_ = new int32_t[monthCount];
	lats_ = new double[latCount];

	referenceSpectra_ = new double[3 * latCount * channelCount * monthCount];
	thresholdValues_ = new double[3 * latCount * monthCount];
}

class THR_WINCOR::Reader : public AbstractDataReader<THR_WINCOR> {
public:
	THR_WINCOR read(istream& is) {
		int32_t monthCount;
		int32_t channelCount;
		int32_t spectralLagCount;
		int32_t latCount;

		readInt64BE(is, &monthCount);

		int32_t* months = new int32_t[monthCount];
		readInt64BE(is, months, monthCount);

		readInt64BE(is, &channelCount);

		skip<int64_t>(is, channelCount);

		readInt64BE(is, &spectralLagCount);
		readInt64BE(is, &latCount);

		THR_WINCOR cofWincor(monthCount, channelCount, spectralLagCount,
				latCount);
		copy(months, months + monthCount, cofWincor.months_);

		readInt64BE(is, cofWincor.lats_, latCount);

		int32_t surfaceConditionCount;
		readInt64BE(is, &surfaceConditionCount);
		skip<int64_t>(is, surfaceConditionCount);

		readBE(is, cofWincor.referenceSpectra_, 3 * latCount * channelCount
				* monthCount);
		readBE(is, cofWincor.thresholdValues_, 3 * latCount * monthCount);

		delete[] months;

		return cofWincor;
	}
};

const THR_WINCOR
		THR_WINCOR::STORE =
				THR_WINCOR::Reader().AbstractDataReader<THR_WINCOR>::read(FilePathResolver::getAbsolutePath("auxdata/IASI_L2_PGS_THR_WINCOR").c_str());
