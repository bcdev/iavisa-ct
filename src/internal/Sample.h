#ifndef SAMPLE_H_
#define SAMPLE_H_

#include <vector>

#include "Enums.h"

class Sample {

public:
	friend class SampleRecordReader;
	
	/**
	 * Constructs a new instance of this class.
	 */
	Sample() : brightnessTemperatures(7) {
	}

	/**
	 * Destructor.
	 */
	~Sample() {
	}

	/**
	 * Returns the random number associated with the sample.
	 */
	double getRandomNumber() const {
		return randomNumber;
	}

	/**
	 * Returns the IFOV-in-EFOV index.
	 */
	long getIfovInEfovIndex() const {
		return ifovInEfovIndex;
	}

	/** 
	 * Returns the latitude.
	 */
	double getLat() const {
		return lat;
	}

	/** 
	 * Returns the longitude.
	 */
	double getLon() const {
		return lon;
	}
	
	/**
	 * Returns the month of obervation.
	 */
	long getMonth() const {
		return month;
	}

	/**
	 * Tests whether the IFOV associated with the sample is valid.
	 */
	bool isIfovValid() const {
		return ifovValid != 0;
	}

	/**
	 * Tests whether all IFOVs in the EFOV associated with the sample are valid.
	 */
	bool isEfovValid() const {
		return efovValid != 0;
	}

	/**
	 * Tests whether the sample is located  in an elevated polar region.
	 */
	bool isElevatedPolarRegion() const {
		return elevatedPolarRegion != 0;
	}

	/**
	 * Tests whether the sample is located in a desert region.
	 */
	bool isDesertRegion() const {
		return desertRegion != 0;
	}

	/**
	 * Tests whether the sample represents a dust storm.
	 */
	bool isDustStorm() const {
		return dustStorm != 0;
	}

	/**
	 * Tests whether the sample is classified as cloudy.
	 */
	bool isCloudy() const {
		return cloudType != 0;
	}
	
	/**
	 * Returns the cloud type.
	 */
	long getCloudType() const {
		return cloudType;
	}
	
	/**
	 * Returns the fractional land cover.
	 */
	double getFractionalLandCover() const {
		return fractionalLandCover;
	}

	/**
	 * Returns the brightness temperatures for the IFOV associated
	 * with this sample.
	 */
	const double* getBrightnessTemperatures(TestId testId) const {
		return &brightnessTemperatures[testId][0];
	}

private:
	long ifovId;
	double randomNumber;
	long ifovInEfovIndex;
	double lat;
	double lon;
	long month;
	long cloudType;
	long ifovValid;
	long efovValid;
	long elevatedPolarRegion;
	long desertRegion;
	long dustStorm;
	double fractionalLandCover;

	std::vector<std::vector<double> > brightnessTemperatures;
};

#endif /*SAMPLE_H_*/
