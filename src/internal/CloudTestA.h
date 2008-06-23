#ifndef CLOUD_TEST_A_H_
#define CLOUD_TEST_A_H_

#include <stdint.h>

#include "CloudTest.h"
#include "THR_CLDDET.h"

class CloudTestA : virtual public CloudTest {
public:

	/**
	 * Constructor.
	 * 
	 * @param zoneId the zone selected.
	 * @param timeId the time selected.
	 */
	CloudTestA(int32_t zoneId, int32_t timeId) :
		CloudTest(TEST_A), zoneId(zoneId), timeId(timeId), thrClddet(zoneId,
				timeId) {
	}

	void execute(const double parameters[], const SampleList& samples,
			bool estimates[]) const;

	bool select(const Sample& sample) const;

private:
	const int32_t zoneId;
	const int32_t timeId;
	const THR_CLDDET thrClddet;
};

#endif /*CLOUD_TEST_A_H_*/
