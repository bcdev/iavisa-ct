#ifndef CLOUD_TEST_B_H_
#define CLOUD_TEST_B_H_

#include <stdint.h>

#include "CloudTest.h"
#include "COF_IASINT.h"

class CloudTestB : virtual public CloudTest {
public:

	/**
	 * Constructor.
	 * 
	 * @param zoneId the zone selected.
	 * @param timeId the time selected.
	 */
	CloudTestB(int32_t zoneId, int32_t timeId) :
		CloudTest(TEST_B), zoneId(zoneId), timeId(timeId), cofIasint(zoneId,
				timeId) {
	}

	void execute(const double parameters[], const SampleList& samples,
			bool estimates[]) const;

	bool select(const Sample& sample) const;

private:
	const int32_t zoneId;
	const int32_t timeId;
	const COF_IASINT cofIasint;
};

#endif /*CLOUD_TEST_B_H_*/
