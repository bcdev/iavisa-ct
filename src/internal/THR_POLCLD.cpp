#include "AbstractDataReader.h"
#include "FilePathResolver.h"
#include "Utils.h"

#include "THR_POLCLD.h"

using namespace std;

THR_POLCLD::THR_POLCLD(long zoneId, long timeId) {
	init(1);
	thresholdValues_[0] = STORE.thresholdValues_[timeId];
}

THR_POLCLD::THR_POLCLD(long monthCount) {
	init(monthCount);
}

THR_POLCLD::~THR_POLCLD() {
	delete[] thresholdValues_;
	delete[] months_;
}

void THR_POLCLD::init(long monthCount) {
	monthCount_ = monthCount;

	months_ = new long[monthCount];
	thresholdValues_ = new double[monthCount];
}

class THR_POLCLD::Reader : public AbstractDataReader<THR_POLCLD> {
public:
	THR_POLCLD read(istream& is) {
		skip<long long>(is, 2);

		long monthCount;
		readLongLongBE(is, &monthCount);

		THR_POLCLD thrPolcld(monthCount);

		readLongLongBE(is, thrPolcld.months_, monthCount);

		long latLonGridPointCount;
		readLongLongBE(is, &latLonGridPointCount, 1);
		skip<double>(is, latLonGridPointCount * 2);
		skip<long long>(is, latLonGridPointCount);

		readBE(is, thrPolcld.thresholdValues_, monthCount);

		return thrPolcld;
	}
};

const THR_POLCLD
		THR_POLCLD::STORE =
				THR_POLCLD::Reader().AbstractDataReader<THR_POLCLD>::read(FilePathResolver::getAbsolutePath("auxdata/IASI_L2_PGS_THR_POLCLD").c_str());
