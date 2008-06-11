#ifndef THR_CLDDET_H_
#define THR_CLDDET_H_

#include <stdint.h>

/**
 * Structure for threshold values required for cloud test A.
 * <p/>
 * The default values for the fields in this structure are defined in the
 * IASI_L2_PGS_THR_CLDDET auxiliary file described on page 42 of document
 * EUM.EPS.SYS.TEN.03.034.
 */
struct THR_CLDDET {
	friend class AuxiliaryDataProvider;
	friend class CloudTestA;
	
	/**
	 * The number channels.
	 */
	long channelCount_;
	
	/**
	 * The number of latitudes.
	 */
	long latCount_;
	
	/**
	 * The number of months.
	 */
	long monthCount_;
	
	/**
	 * The latitudes.
	 */
	double* lats_;
	
	/**
	 * The months.
	 */
	long* months_;

	/**
	 * The number of threshold values.
	 */
	long thresholdValueCount_;
	
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
	THR_CLDDET(long zoneId, long timeId);
	
	/**
	 * Destructor.
	 */
	~THR_CLDDET();

private:
	class Reader;

	THR_CLDDET(long channelCount, long latCount, long monthCount);
	
	void init(long channelCount, long latCount, long monthCount);
	
	static const THR_CLDDET STORE;
};

#endif /*THR_CLDDET_H_*/
