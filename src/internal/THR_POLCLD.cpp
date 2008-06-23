#include "AbstractDataReader.h"
#include "FilePathResolver.h"
#include "Utils.h"

#include "THR_POLCLD.h"

using namespace std;

THR_POLCLD::THR_POLCLD(int32_t zoneId, int32_t timeId) {
	init(1);
	thresholdValues_[0] = STORE.thresholdValues_[timeId];
}

THR_POLCLD::THR_POLCLD(int32_t monthCount) {
	init(monthCount);
}

THR_POLCLD::~THR_POLCLD() {
	delete[] thresholdValues_;
	delete[] months_;
}

void THR_POLCLD::init(int32_t monthCount) {
	monthCount_ = monthCount;

	months_ = new int32_t[monthCount];
	thresholdValues_ = new double[monthCount];
}

class THR_POLCLD::Reader : public AbstractDataReader<THR_POLCLD> {
public:
	THR_POLCLD read(istream& is) {
		skip<int64_t>(is, 2);

		int32_t monthCount;
		readInt64BE(is, &monthCount);

		THR_POLCLD thrPolcld(monthCount);

		readInt64BE(is, thrPolcld.months_, monthCount);

		int32_t latLonGridPointCount;
		readInt64BE(is, &latLonGridPointCount, 1);
		skip<double>(is, latLonGridPointCount * 2);
		skip<int64_t>(is, latLonGridPointCount);

		readBE(is, thrPolcld.thresholdValues_, monthCount);

		return thrPolcld;
	}
};

const THR_POLCLD
		THR_POLCLD::STORE =
				THR_POLCLD::Reader().AbstractDataReader<THR_POLCLD>::read(FilePathResolver::getAbsolutePath("auxdata/IASI_L2_PGS_THR_POLCLD").c_str());
