#ifndef CLOUD_TEST_E_H_
#define CLOUD_TEST_E_H_

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
	CloudTestE(long zoneId, long timeId) :
		CloudTest(TEST_E), zoneId(zoneId), timeId(timeId), thrEofres(zoneId,
				timeId) {
	}

	void execute(const double parameters[], const SampleList& samples,
			bool estimates[]) const;

	bool select(const Sample& sample) const;

private:
	const long zoneId;
	const long timeId;
	const THR_EOFRES thrEofres;
};

#endif /*CLOUD_TEST_E_H_*/
