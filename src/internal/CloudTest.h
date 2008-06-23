#ifndef CLOUD_TEST_H_
#define CLOUD_TEST_H_

#include "Sample.h"

typedef std::vector<const Sample*> SampleList;

/**
 * Base class for all cloud tests.
 */
class CloudTest {
public:
	/**
	 * Executes the cloud test.
	 * 
	 * @param parameters the parameters being used for this test.
	 * @param samples    the samples.
	 * @param estimates  the cloud test estimates.
	 */
	virtual void execute(const double parameters[], const SampleList& samples,
			bool estimates[]) const = 0;

	/**
	 * Defines the sample selector.
	 * 
	 * @param sample the sample.
	 */
	virtual bool select(const Sample& sample) const  = 0;

	/**
	 * Defines when a sample is valid.
	 * 
	 * @param sample the sample.
	 */
	virtual bool accept(const Sample& sample) const {
		return sample.isIfovValid() && !sample.isDustStorm();
	}

	/**
	 * Defines the cloud truth.
	 * 
	 * @param sample the sample.
	 */
	virtual int32_t truth(const Sample& sample) const {
		return sample.getCloudType();
	}

	/** 
	 * Returns the test ID.
	 */
	TestId getTestId() const {
		return testId;
	}
		
	/**
	 * Destructor.
	 */
	virtual ~CloudTest() {
	}
	
protected:
	/**
	 * Constructor.
	 */
	CloudTest(TestId testId) : testId(testId) {
	}

	
private:
	const TestId testId;
};

#endif /*CLOUD_TEST_H_*/
