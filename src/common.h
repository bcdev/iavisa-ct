#ifndef COMMON_H_
#define COMMON_H_

#include "internal/CloudTestFactory.h"
#include "internal/SampleCollector.h"

struct CT {
	/**
	 * Constructor.
	 */
	CT(DatasetId datasetId, TestId testId, long zoneId, long timeId) :
		cloudTest(CloudTestFactory::createCloudTest(testId, zoneId, timeId)),
				samples(SampleCollector(datasetId).collectSamples(*cloudTest)) {
	}

	/**
	 * Destructor.
	 */
	~CT() {
		if (cloudTest != 0) {
			delete cloudTest;
		}
	}

	void getCloudGuess(const double parameters[], bool estimates[]) const {
		cloudTest->execute(parameters, samples, estimates);
	}

	void getCloudTruth(long truth[]) const {
		for (size_t i = 0; i < samples.size(); ++i) {
			truth[i] = cloudTest->truth(*samples[i]);
		}
	}

	long getSampleCount() const {
		return samples.size();
	}

	TestId getTestId() const {
		return cloudTest->getTestId();
	}

private:
	const CloudTest* cloudTest;
	const SampleList samples;
};

#endif /*COMMON_H_*/
