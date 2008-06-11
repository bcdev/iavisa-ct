#ifndef CLOUD_TEST_D_H_
#define CLOUD_TEST_D_H_

#include "CloudTest.h"
#include "THR_HORCO.h"

class CloudTestD : virtual public CloudTest {
public:

	/**
	 * Constructor.
	 * 
	 * @param zoneId the zone selected.
	 * @param timeId the time selected.
	 */
	CloudTestD(long zoneId, long timeId) :
		CloudTest(TEST_D), zoneId(zoneId), timeId(timeId), thrHorco(zoneId,
				timeId) {
	}

	void execute(const double parameters[], const SampleList& samples,
			bool estimates[]) const;

	bool select(const Sample& sample) const;

	bool accept(const Sample& sample) const {
		return sample.isEfovValid() && !sample.isDustStorm();
	}

private:
	const long zoneId;
	const long timeId;
	const THR_HORCO thrHorco;
};

#endif /*CLOUD_TEST_D_H_*/
