#include <algorithm>

#include "AbstractDataReader.h"
#include "FilePathResolver.h"
#include "Utils.h"

#include "THR_HORCO.h"

using namespace std;

THR_HORCO::THR_HORCO(int32_t zoneId, int32_t timeId) {
	init(1, 1, 0);

	const int32_t l = zoneId;
	const int32_t m = timeId;

	const int32_t offset = l + STORE.latCount_ * m;
	const int32_t stride = STORE.latCount_ * STORE.monthCount_;

	for (int32_t j = 0; j < 3; ++j) {
		thresholdValues_[j] = STORE.thresholdValues_[offset + j * stride];
	}
}

THR_HORCO::THR_HORCO(int32_t latCount, int32_t monthCount, int32_t notUsed) {
	init(latCount, monthCount, notUsed);
}

THR_HORCO::~THR_HORCO() {
	delete[] lats_;
	delete[] months_;
	delete[] thresholdValues_;
}

void THR_HORCO::init(int32_t latCount, int32_t monthCount, int32_t notUsed) {
	latCount_ = latCount;
	monthCount_ = monthCount;

	lats_ = new double[latCount];
	months_ = new int32_t[monthCount];
	thresholdValueCount_ = latCount * monthCount * 3;
	thresholdValues_ = new double[thresholdValueCount_];
}

class THR_HORCO::Reader : public AbstractDataReader<THR_HORCO> {
public:
	THR_HORCO read(istream& is) {
		skip<int64_t>(is, 1);
		int32_t latCount;
		readInt64BE(is, &latCount);

		double* latLonPairs = new double[latCount * 2];
		readBE(is, latLonPairs, latCount * 2);

		int32_t monthCount;
		readInt64BE(is, &monthCount);

		THR_HORCO thrHorco(latCount, monthCount, 0);
		for (int i = 0, j = 0; i < latCount; ++i, j += 2) {
			thrHorco.lats_[i] = latLonPairs[j];
		}
		readInt64BE(is, thrHorco.months_, monthCount);
		readBE(is, thrHorco.thresholdValues_, thrHorco.thresholdValueCount_);

		delete[] latLonPairs;

		return thrHorco;
	}
};

const THR_HORCO
		THR_HORCO::STORE =
				THR_HORCO::Reader().AbstractDataReader<THR_HORCO>::read(FilePathResolver::getAbsolutePath("auxdata/IASI_L2_PGS_THR_HORCO").c_str());
