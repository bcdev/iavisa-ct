#ifndef COMMON_H_
#define COMMON_H_

#include <stdint.h>

#include "internal/CloudTestFactory.h"
#include "internal/SampleCollector.h"

struct CT {
	/**
	 * Constructor.
	 */
	CT(DatasetId datasetId, TestId testId, int32_t zoneId, int32_t timeId) :
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

	void getCloudTruth(int32_t truth[]) const {
		for (size_t i = 0; i < samples.size(); ++i) {
			truth[i] = cloudTest->truth(*samples[i]);
		}
	}

	int32_t getSampleCount() const {
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
