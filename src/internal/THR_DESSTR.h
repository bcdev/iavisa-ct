#ifndef AUX_DESSTR_H_
#define AUX_DESSTR_H_

#include <stdint.h>

/**
 * Structure for channel numbers and threshold values required for the test
 * of desert dust storms.
 * <p/>
 * The default values for the fields in this structure are defined in the
 * IASI_L2_PGS_THR_DESSTR auxiliary file described on page 43 of document
 * EUM.EPS.SYS.TEN.03.034.
 */
struct THR_DESSTR {
	friend class AuxiliaryDataProvider;	
	friend class CloudTestH;
	
	/**
	 * The number of latitude-int32_titude grid points.
	 */
	int32_t latLonGridPointCount_;
	
	/**
	 * The number of months.
	 */
	int32_t monthCount_;
	
	/**
	 * The latitudes.
	 */
	double* lats_;
	
	/**
	 * The int32_titudes.
	 */
	double* lons_;
	
	/**
	 * The months.
	 */
	int32_t* months_;
	
	/**
	 * The threshold values.
	 */
	double* thresholdValues_;
	
	/**
	 * Constructor.
	 * 
	 * @param zoneId the zone selected.
	 * @param timeId the time selected.
	 */
	THR_DESSTR(int32_t zoneId, int32_t timeId);
	
	/**
	 * Destructor.
	 */
	~THR_DESSTR();

private:
	class Reader;

	THR_DESSTR(int32_t latLonGridPointCount, int32_t monthCount, int32_t channelCount);

	void init(int32_t latLonGridPointCount, int32_t monthCount);

	static const THR_DESSTR STORE;
};

#endif /*AUX_DESSTR_H_*/
