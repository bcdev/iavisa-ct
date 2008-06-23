#ifndef CLOUD_TEST_E_H_
#define CLOUD_TEST_E_H_

#include <stdint.h>

#include "CloudTest.h"
#include "THR_EOFRES.h"

class CloudTestE : virtual public CloudTest {
public:

	/**
	 * Constructor.
	 * 
	 * @param zoneId the zone selected.
	 * @param timeId the time selected.
	 */
	CloudTestE(int32_t zoneId, int32_t timeId) :
		CloudTest(TEST_E), zoneId(zoneId), timeId(timeId), thrEofres(zoneId,
				timeId) {
	}

	void execute(const double parameters[], const SampleList& samples,
			bool estimates[]) const;

	bool select(const Sample& sample) const;

private:
	const int32_t zoneId;
	const int32_t timeId;
	const THR_EOFRES thrEofres;
};

#endif /*CLOUD_TEST_E_H_*/
