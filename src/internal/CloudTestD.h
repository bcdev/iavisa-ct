#ifndef CLOUD_TEST_D_H_
#define CLOUD_TEST_D_H_

#include <stdint.h>

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
	CloudTestD(int32_t zoneId, int32_t timeId) :
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
	const int32_t zoneId;
	const int32_t timeId;
	const THR_HORCO thrHorco;
};

#endif /*CLOUD_TEST_D_H_*/
