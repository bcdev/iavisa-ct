#ifndef THR_EOFRES_H_
#define THR_EOFRES_H_

/**
 * Structure for threshold values required for cloud test E.
 * <p/>
 * The default values for the fields in this structure are defined in the
 * IASI_L2_PGS_THR_EOFRES auxiliary file described on page 43 of document
 * EUM.EPS.SYS.TEN.03.034.
 */
struct THR_EOFRES {
	friend class AuxiliaryDataProvider;
	friend class CloudTestE;
	
	/**
	 * The number of channels.
	 */
	long channelCount_;

	/**
	 * The number of longitude/latitude bins.
	 */
	long latCount_;

	/**
	 * The number of months.
	 */
	long monthCount_;

	/**
	 * The number of surface types.
	 */
	long surfaceTypeCount_;

	/**
	 * The latitudes.
	 */
	double* lats_;

	/**
	 * The months.
	 */
	long* months_;

	/**
	 * The number of clear-sky EOFs.
	 */
	long clearSkyEofCount_;

	/**
	 * The clear-sky EOFs.
	 */
	double* clearSkyEofs_;

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
	THR_EOFRES(long zoneId, long timeId);

	/**
	 * Destructor.
	 */
	~THR_EOFRES();

private:
	class Reader;

	THR_EOFRES(long channelCount, long latCount, long monthCount,
			long surfaceTypeCount, long clearSkyEofCount);

	void init(long channelCount, long latCount, long monthCount,
			long surfaceTypeCount, long clearSkyEofCount);

	static const THR_EOFRES STORE;
};

#endif /*THR_EOFRES_H_*/
