#ifndef THR_HORCO_H_
#define THR_HORCO_H_

#include <stdint.h>

/**
 * Structure for threshold values required for cloud test D.
 * <p/>
 * The default values for the fields in this structure are defined in the
 * IASI_L2_PGS_THR_HORCO  auxiliary file described on page 47 of document
 * EUM.EPS.SYS.TEN.03.034.
 */
struct THR_HORCO {
	friend class AuxiliaryDataProvider;
	friend class CloudTestD;
	
	/**
	 * The number of latitudes.
	 */
	int32_t latCount_;
	/**
	 * The latitudes.
	 */
	double* lats_;
	/**
	 * The number of months.
	 */
	int32_t monthCount_;
	/**
	 * The months.
	 */
	int32_t* months_;
	/**
	 * The number of threshold values.
	 */
	int32_t thresholdValueCount_;
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
	THR_HORCO(int32_t zoneId, int32_t timeId);
	
	/**
	 * Destructor.
	 */
	~THR_HORCO();

private:
	class Reader;

	THR_HORCO(int32_t latCount, int32_t monthCount, int32_t thresholdValueCount);
	
	void init(int32_t latCount, int32_t monthCount, int32_t thresholdValueCount);
	
	static const THR_HORCO STORE;	
};

#endif /*THR_HORCO_H_*/
