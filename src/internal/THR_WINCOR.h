#ifndef THR_WINCOR_H_
#define THR_WINCOR_H_

/**
 * Structure for threshold values required for cloud test F.
 * <p/>
 * The default values for the fields in this structure are defined in the
 * IASI_L2_PGS_THR_WINCOR auxiliary file described on page 54 of document
 * EUM.EPS.SYS.TEN.03.034.
 */
struct THR_WINCOR {
	friend class AuxiliaryDataProvider;
	friend class CloudTestF;
	
	/**
	 * The number of month.
	 */
	long monthCount_;
	/**
	 * The month identifiers.
	 */
	long* months_;
	/**
	 * The number of channels.
	 */
	long channelCount_;
	/**
	 * The number of spectral lags.
	 */
	long spectralLagCount_;
	/**
	 * The number of latitude zones.
	 */
	long latCount_;
	/**
	 * The latitude zones.
	 */
	double* lats_;
	/**
	 * The reference spectra (brightness temperature measured in K).
	 */
	double* referenceSpectra_;
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
	THR_WINCOR(long zoneId, long timeId);

	/**
	 * Destructor.
	 */
	~THR_WINCOR();

private:
	class Reader;

	THR_WINCOR(long monthCount, long channelCount, long spectralLagCount,
			long latCount);

	void init(long monthCount, long channelCount, long spectralLagCount,
			long latCount);

	static const THR_WINCOR STORE;
};

#endif /*THR_WINCOR_H_*/
