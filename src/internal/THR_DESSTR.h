#ifndef AUX_DESSTR_H_
#define AUX_DESSTR_H_

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
	 * The number of latitude-longitude grid points.
	 */
	long latLonGridPointCount_;
	
	/**
	 * The number of months.
	 */
	long monthCount_;
	
	/**
	 * The latitudes.
	 */
	double* lats_;
	
	/**
	 * The longitudes.
	 */
	double* lons_;
	
	/**
	 * The months.
	 */
	long* months_;
	
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
	THR_DESSTR(long zoneId, long timeId);
	
	/**
	 * Destructor.
	 */
	~THR_DESSTR();

private:
	class Reader;

	THR_DESSTR(long latLonGridPointCount, long monthCount, long channelCount);

	void init(long latLonGridPointCount, long monthCount);

	static const THR_DESSTR STORE;
};

#endif /*AUX_DESSTR_H_*/
