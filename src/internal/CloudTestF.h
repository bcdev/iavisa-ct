#ifndef CLOUD_TEST_F_H_
#define CLOUD_TEST_F_H_

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
	CloudTestF(long zoneId, long timeId) :
		CloudTest(TEST_F), zoneId(zoneId), timeId(timeId), thrWincor(zoneId,
				timeId) {
	}

	void execute(const double parameters[], const SampleList& samples,
			bool estimates[]) const;

	bool select(const Sample& sample) const;

private:
	const long zoneId;
	const long timeId;
	const THR_WINCOR thrWincor;
};

#endif /*CLOUD_TEST_F_H_*/
