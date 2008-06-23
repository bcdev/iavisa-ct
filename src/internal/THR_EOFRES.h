#ifndef THR_EOFRES_H_
#define THR_EOFRES_H_

#include <stdint.h>

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
	int32_t channelCount_;

	/**
	 * The number of int32_titude/latitude bins.
	 */
	int32_t latCount_;

	/**
	 * The number of months.
	 */
	int32_t monthCount_;

	/**
	 * The number of surface types.
	 */
	int32_t surfaceTypeCount_;

	/**
	 * The latitudes.
	 */
	double* lats_;

	/**
	 * The months.
	 */
	int32_t* months_;

	/**
	 * The number of clear-sky EOFs.
	 */
	int32_t clearSkyEofCount_;

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
	THR_EOFRES(int32_t zoneId, int32_t timeId);

	/**
	 * Destructor.
	 */
	~THR_EOFRES();

private:
	class Reader;

	THR_EOFRES(int32_t channelCount, int32_t latCount, int32_t monthCount,
			int32_t surfaceTypeCount, int32_t clearSkyEofCount);

	void init(int32_t channelCount, int32_t latCount, int32_t monthCount,
			int32_t surfaceTypeCount, int32_t clearSkyEofCount);

	static const THR_EOFRES STORE;
};

#endif /*THR_EOFRES_H_*/
