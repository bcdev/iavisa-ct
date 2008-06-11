#ifndef THR_HORCO_H_
#define THR_HORCO_H_

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
	long latCount_;
	/**
	 * The latitudes.
	 */
	double* lats_;
	/**
	 * The number of months.
	 */
	long monthCount_;
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
	THR_HORCO(long zoneId, long timeId);
	
	/**
	 * Destructor.
	 */
	~THR_HORCO();

private:
	class Reader;

	THR_HORCO(long latCount, long monthCount, long thresholdValueCount);
	
	void init(long latCount, long monthCount, long thresholdValueCount);
	
	static const THR_HORCO STORE;	
};

#endif /*THR_HORCO_H_*/
