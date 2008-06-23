#ifndef CLOUD_TEST_H_H_
#define CLOUD_TEST_H_H_

#include <stdint.h>

#include "CloudTest.h"
#include "THR_DESSTR.h"

class CloudTestH : virtual public CloudTest {
public:

	/**
	 * Constructor.
	 * 
	 * @param zoneId the zone selected.
	 * @param timeId the time selected.
	 */
	CloudTestH(int32_t zoneId, int32_t timeId) :
		CloudTest(TEST_H), zoneId(zoneId), timeId(timeId), thrDesstr(zoneId,
				timeId) {
	}

	void execute(const double parameters[], const SampleList& samples,
			bool estimates[]) const;

	bool select(const Sample& sample) const;

	bool accept(const Sample& sample) const {
		return sample.isIfovValid() && (sample.isDesertRegion()
				|| sample.isDustStorm());
	}

	int32_t truth(const Sample& sample) const {
		return sample.isDustStorm() ? 4 : 1;
	}

private:
	const int32_t zoneId;
	const int32_t timeId;
	const THR_DESSTR thrDesstr;
};

#endif /*CLOUD_TEST_H_H_*/
