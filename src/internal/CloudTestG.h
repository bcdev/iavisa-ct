#ifndef CLOUD_TEST_G_H_
#define CLOUD_TEST_G_H_

#include <stdint.h>

#include "CloudTest.h"
#include "THR_POLCLD.h"

class CloudTestG : virtual public CloudTest {
public:

	/**
	 * Constructor.
	 * 
	 * @param zoneId the zone selected - not used.
	 * @param timeId the time selected.
	 */
	CloudTestG(int32_t zoneId, int32_t timeId) :
		CloudTest(TEST_G), zoneId(zoneId), timeId(timeId), thrPolcld(zoneId,
				timeId) {
	}

	void execute(const double parameters[], const SampleList& samples,
			bool estimates[]) const;

	bool select(const Sample& sample) const;

	bool accept(const Sample& sample) const {
		return sample.isIfovValid() && sample.isElevatedPolarRegion()
				&& !sample.isDustStorm();
	}

private:
	const int32_t zoneId;
	const int32_t timeId;
	const THR_POLCLD thrPolcld;
};

#endif /*CLOUD_TEST_G_H_*/
