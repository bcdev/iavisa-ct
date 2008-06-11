#ifndef CLOUD_TEST_B_H_
#define CLOUD_TEST_B_H_

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
	CloudTestB(long zoneId, long timeId) :
		CloudTest(TEST_B), zoneId(zoneId), timeId(timeId), cofIasint(zoneId,
				timeId) {
	}

	void execute(const double parameters[], const SampleList& samples,
			bool estimates[]) const;

	bool select(const Sample& sample) const;

private:
	const long zoneId;
	const long timeId;
	const COF_IASINT cofIasint;
};

#endif /*CLOUD_TEST_B_H_*/
