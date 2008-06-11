#ifndef CLOUD_TEST_H_H_
#define CLOUD_TEST_H_H_

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
	CloudTestH(long zoneId, long timeId) :
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

	long truth(const Sample& sample) const {
		return sample.isDustStorm() ? 3 : 0;
	}

private:
	const long zoneId;
	const long timeId;
	const THR_DESSTR thrDesstr;
};

#endif /*CLOUD_TEST_H_H_*/
