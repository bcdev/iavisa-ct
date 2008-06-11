#include <algorithm>

#include "AbstractDataReader.h"
#include "FilePathResolver.h"
#include "Utils.h"

#include "THR_CLDDET.h"

using namespace std;

THR_CLDDET::THR_CLDDET(long zoneId, long timeId) {
	init(STORE.channelCount_, 1, 1);

	const long l = zoneId;
	const long m = timeId;

	for (long i = 0, k = 0; i < channelCount_; ++i) {
		for (long j = 0; j < 2; ++j) {
			thresholdValues_[k] = STORE.thresholdValues_[j + 2 * (m + STORE.monthCount_ * (l + i * STORE.latCount_))];
			++k;
		}
	}
}

THR_CLDDET::THR_CLDDET(long channelCount, long latCount, long monthCount) {
	init(channelCount, latCount, monthCount);
}

THR_CLDDET::~THR_CLDDET() {
	delete[] thresholdValues_;
	delete[] months_;
	delete[] lats_;
}

void THR_CLDDET::init(long channelCount, long latCount, long monthCount) {
	channelCount_ = channelCount;
	latCount_ = latCount;
	monthCount_ = monthCount;

	lats_ = new double[latCount];
	months_ = new long[monthCount];

	thresholdValueCount_ = channelCount * latCount * monthCount * 2;
	thresholdValues_ = new double[thresholdValueCount_];
}

class THR_CLDDET::Reader : public AbstractDataReader<THR_CLDDET> {
protected:
	THR_CLDDET read(istream& is) {
		long channelCount;
		long latCount;
		long monthCount;

		readLongLongBE(is, &channelCount);
		readLongLongBE(is, &latCount);
		readLongLongBE(is, &monthCount);

		THR_CLDDET thrClddet(channelCount, latCount, monthCount);

		readBE(is, thrClddet.lats_, latCount);
		readLongLongBE(is, thrClddet.months_, monthCount);
		skip<long long>(is, channelCount);
		readBE(is, thrClddet.thresholdValues_, thrClddet.thresholdValueCount_);

		return thrClddet;
	}
};

const THR_CLDDET
		THR_CLDDET::STORE =
				THR_CLDDET::Reader().AbstractDataReader<THR_CLDDET>::read(FilePathResolver::getAbsolutePath("auxdata/IASI_L2_PGS_THR_CLDDET").c_str());
