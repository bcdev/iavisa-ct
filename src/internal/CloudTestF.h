#ifndef CLOUD_TEST_F_H_
#define CLOUD_TEST_F_H_

#include <stdint.h>

#include "CloudTest.h"
#include "THR_WINCOR.h"

class CloudTestF : virtual public CloudTest {
public:

	/**
	 * Constructor.
	 * 
	 * @param zoneId the zone selected.
	 * @param timeId the time selected.
	 */
	CloudTestF(int32_t zoneId, int32_t timeId) :
		CloudTest(TEST_F), zoneId(zoneId), timeId(timeId), thrWincor(zoneId,
				timeId) {
	}

	void execute(const double parameters[], const SampleList& samples,
			bool estimates[]) const;

	bool select(const Sample& sample) const;

private:
	const int32_t zoneId;
	const int32_t timeId;
	const THR_WINCOR thrWincor;
};

#endif /*CLOUD_TEST_F_H_*/
