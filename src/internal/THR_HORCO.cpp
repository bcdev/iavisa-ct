#include <algorithm>

#include "AbstractDataReader.h"
#include "FilePathResolver.h"
#include "Utils.h"

#include "THR_HORCO.h"

using namespace std;

THR_HORCO::THR_HORCO(long zoneId, long timeId) {
	init(1, 1, 0);

	const long l = zoneId;
	const long m = timeId;

	const long offset = l + STORE.latCount_ * m;
	const long stride = STORE.latCount_ * STORE.monthCount_;

	for (long j = 0; j < 3; ++j) {
		thresholdValues_[j] = STORE.thresholdValues_[offset + j * stride];
	}
}

THR_HORCO::THR_HORCO(long latCount, long monthCount, long notUsed) {
	init(latCount, monthCount, notUsed);
}

THR_HORCO::~THR_HORCO() {
	delete[] lats_;
	delete[] months_;
	delete[] thresholdValues_;
}

void THR_HORCO::init(long latCount, long monthCount, long notUsed) {
	latCount_ = latCount;
	monthCount_ = monthCount;

	lats_ = new double[latCount];
	months_ = new long[monthCount];
	thresholdValueCount_ = latCount * monthCount * 3;
	thresholdValues_ = new double[thresholdValueCount_];
}

class THR_HORCO::Reader : public AbstractDataReader<THR_HORCO> {
public:
	THR_HORCO read(istream& is) {
		skip<long long>(is, 1);
		long latCount;
		readLongLongBE(is, &latCount);

		double* latLonPairs = new double[latCount * 2];
		readBE(is, latLonPairs, latCount * 2);

		long monthCount;
		readLongLongBE(is, &monthCount);

		THR_HORCO thrHorco(latCount, monthCount, 0);
		for (int i = 0, j = 0; i < latCount; ++i, j += 2) {
			thrHorco.lats_[i] = latLonPairs[j];
		}
		readLongLongBE(is, thrHorco.months_, monthCount);
		readBE(is, thrHorco.thresholdValues_, thrHorco.thresholdValueCount_);

		delete[] latLonPairs;

		return thrHorco;
	}
};

const THR_HORCO
		THR_HORCO::STORE =
				THR_HORCO::Reader().AbstractDataReader<THR_HORCO>::read(FilePathResolver::getAbsolutePath("auxdata/IASI_L2_PGS_THR_HORCO").c_str());
