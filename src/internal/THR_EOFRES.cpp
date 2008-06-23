#include <algorithm>
#include <cmath>

#include "AbstractDataReader.h"
#include "FilePathResolver.h"
#include "Utils.h"

#include "THR_EOFRES.h"

using namespace std;

THR_EOFRES::THR_EOFRES(int32_t zoneId, int32_t timeId) {
	init(STORE.channelCount_, 1, 1, STORE.surfaceTypeCount_,
			STORE.clearSkyEofCount_);

	copy(STORE.lats_, STORE.lats_ + latCount_, lats_);
	copy(STORE.months_, STORE.months_ + monthCount_, months_);
	copy(STORE.clearSkyEofs_, STORE.clearSkyEofs_ + clearSkyEofCount_
			* channelCount_, clearSkyEofs_);

	const int32_t l = zoneId;
	const int32_t m = timeId;

	const int32_t offset = STORE.surfaceTypeCount_ * (m + l * STORE.monthCount_);
	for (int32_t i = 0; i < STORE.surfaceTypeCount_; ++i) {
		thresholdValues_[i] = STORE.thresholdValues_[offset + i];
	}
}

THR_EOFRES::THR_EOFRES(int32_t channelCount, int32_t latCount, int32_t monthCount,
		int32_t surfaceTypeCount, int32_t clearSkyEofCount) {
	init(channelCount, latCount, monthCount, surfaceTypeCount, clearSkyEofCount);
}

THR_EOFRES::~THR_EOFRES() {
	delete[] thresholdValues_;
	delete[] clearSkyEofs_;
	delete[] months_;
	delete[] lats_;
}

void THR_EOFRES::init(int32_t channelCount, int32_t latCount, int32_t monthCount,
		int32_t surfaceTypeCount, int32_t clearSkyEofCount) {
	channelCount_ = channelCount;
	latCount_ = latCount;
	monthCount_ = monthCount;
	surfaceTypeCount_ = surfaceTypeCount;
	clearSkyEofCount_ = clearSkyEofCount;

	lats_ = new double[latCount];
	months_ = new int32_t[monthCount];
	clearSkyEofs_ = new double[clearSkyEofCount * channelCount];
	thresholdValues_ = new double[surfaceTypeCount * latCount * monthCount];
}

class THR_EOFRES::Reader : public AbstractDataReader<THR_EOFRES> {
public:
	THR_EOFRES read(istream& is) {
		int32_t channelCount;
		int32_t latCount;
		int32_t monthCount;
		int32_t surfaceTypeCount;

		readInt64BE(is, &channelCount);
		readInt64BE(is, &latCount);
		readInt64BE(is, &monthCount);
		readInt64BE(is, &surfaceTypeCount);

		skip<int64_t>(is, channelCount);

		double* latLonPairs = new double[latCount * 2];
		readBE(is, latLonPairs, latCount * 2);

		int32_t* months = new int32_t[monthCount];
		readInt64BE(is, months, monthCount);

		skip<int64_t>(is, surfaceTypeCount);

		int32_t clearSkyEofCount;
		readInt64BE(is, &clearSkyEofCount);

		THR_EOFRES thrEofres(channelCount, latCount, monthCount,
				surfaceTypeCount, clearSkyEofCount);

		for (int i = 0, j = 0; i < latCount; ++i, j += 2) {
			thrEofres.lats_[i] = latLonPairs[j];
		}
		copy(months, months + monthCount, thrEofres.months_);

		readBE(is, thrEofres.clearSkyEofs_, clearSkyEofCount * channelCount);
		readBE(is, thrEofres.thresholdValues_, surfaceTypeCount * latCount
				* monthCount);

		delete[] months;
		delete[] latLonPairs;

		return thrEofres;
	}
};

const THR_EOFRES
		THR_EOFRES::STORE =
				THR_EOFRES::Reader().AbstractDataReader<THR_EOFRES>::read(FilePathResolver::getAbsolutePath("auxdata/IASI_L2_PGS_THR_EOFRES").c_str());
