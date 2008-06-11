#include <algorithm>

#include "AbstractDataReader.h"
#include "FilePathResolver.h"
#include "Utils.h"

#include "THR_DESSTR.h"

using namespace std;

THR_DESSTR::THR_DESSTR(long zoneId, long timeId) {
	init(1, 1);

	const long l = zoneId;
	const long m = timeId;

	for (long i = 0, k = 0; i < 2; ++i) {
		thresholdValues_[k] = STORE.thresholdValues_[i + 2 * (m + STORE.monthCount_ * l)];
		++k;
	}
}

THR_DESSTR::~THR_DESSTR() {
	delete[] thresholdValues_;
	delete[] months_;
}

THR_DESSTR::THR_DESSTR(long latLonGridPointCount, long monthCount, long channelCount) {
	init(latLonGridPointCount, monthCount);
}

void THR_DESSTR::init(long latLonGridPointCount, long monthCount) {
	latLonGridPointCount_ = latLonGridPointCount;
	monthCount_ = monthCount;
	
	lats_ = new double[latLonGridPointCount];
	lons_ = new double[latLonGridPointCount];
	
	months_ = new long[monthCount];
	thresholdValues_ = new double[latLonGridPointCount * monthCount * 2];
}

class THR_DESSTR::Reader : public AbstractDataReader<THR_DESSTR> {
public:
	THR_DESSTR read(istream& is) {
		long latLonGridPointCount;
		long monthCount;

		readLongLongBE(is, &latLonGridPointCount);
		readLongLongBE(is, &monthCount);

		THR_DESSTR thrDesstr(latLonGridPointCount, monthCount, 0);
		
		for (long i = 0; i < latLonGridPointCount; ++i) {
			readBE(is, thrDesstr.lats_ + i);
			readBE(is, thrDesstr.lons_ + i);
		}

		readLongLongBE(is, thrDesstr.months_, monthCount);

		// skip channels
		skip<long long>(is, 2);
		// skip desert map
		skip<long long>(is, latLonGridPointCount);

		readBE(is, thrDesstr.thresholdValues_, latLonGridPointCount * monthCount * 2);

		return thrDesstr;
	}
};

const THR_DESSTR
		THR_DESSTR::STORE =
				THR_DESSTR::Reader().AbstractDataReader<THR_DESSTR>::read(FilePathResolver::getAbsolutePath("auxdata/IASI_L2_PGS_THR_DESSTR").c_str());
