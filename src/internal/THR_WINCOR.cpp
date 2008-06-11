#include <algorithm>
#include <vector>

#include "AbstractDataReader.h"
#include "FilePathResolver.h"
#include "Utils.h"

#include "THR_WINCOR.h"

using namespace std;

THR_WINCOR::THR_WINCOR(long zoneId, long timeId) {
	init(1, STORE.channelCount_, STORE.spectralLagCount_, 1);

	const long l = zoneId;
	const long m = timeId;

	long k = 0;
	for (long i = 0; i < 3; ++i) {
		for (long j = 0; j < STORE.channelCount_; ++j) {
			referenceSpectra_[k]
					= STORE.referenceSpectra_[j + STORE.channelCount_ * (i + 3 * (m + l * STORE.monthCount_))];
			++k;
		}
	}
	for (long i = 0; i < 3; ++i) {
		thresholdValues_[i] = STORE.thresholdValues_[i + 3 * (m + l * STORE.monthCount_)];
	}
}

THR_WINCOR::THR_WINCOR(long monthCount, long channelCount,
		long spectralLagCount, long latCount) {
	init(monthCount, channelCount, spectralLagCount, latCount);
}

THR_WINCOR::~THR_WINCOR() {
	delete[] months_;
	delete[] lats_;
	delete[] referenceSpectra_;
	delete[] thresholdValues_;
}

void THR_WINCOR::init(long monthCount, long channelCount,
		long spectralLagCount, long latCount) {
	monthCount_ = monthCount;
	channelCount_ = channelCount;
	spectralLagCount_ = spectralLagCount;
	latCount_ = latCount;

	months_ = new long[monthCount];
	lats_ = new double[latCount];

	referenceSpectra_ = new double[3 * latCount * channelCount * monthCount];
	thresholdValues_ = new double[3 * latCount * monthCount];
}

class THR_WINCOR::Reader : public AbstractDataReader<THR_WINCOR> {
public:
	THR_WINCOR read(istream& is) {
		long monthCount;
		long channelCount;
		long spectralLagCount;
		long latCount;

		readLongLongBE(is, &monthCount);

		long* months = new long[monthCount];
		readLongLongBE(is, months, monthCount);

		readLongLongBE(is, &channelCount);

		skip<long long>(is, channelCount);

		readLongLongBE(is, &spectralLagCount);
		readLongLongBE(is, &latCount);

		THR_WINCOR cofWincor(monthCount, channelCount, spectralLagCount,
				latCount);
		copy(months, months + monthCount, cofWincor.months_);

		readLongLongBE(is, cofWincor.lats_, latCount);

		long surfaceConditionCount;
		readLongLongBE(is, &surfaceConditionCount);
		skip<long long>(is, surfaceConditionCount);

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
