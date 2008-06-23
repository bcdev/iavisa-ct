#ifndef THR_WINCOR_H_
#define THR_WINCOR_H_

#include <stdint.h>

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
	int32_t monthCount_;
	/**
	 * The month identifiers.
	 */
	int32_t* months_;
	/**
	 * The number of channels.
	 */
	int32_t channelCount_;
	/**
	 * The number of spectral lags.
	 */
	int32_t spectralLagCount_;
	/**
	 * The number of latitude zones.
	 */
	int32_t latCount_;
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
	THR_WINCOR(int32_t zoneId, int32_t timeId);

	/**
	 * Destructor.
	 */
	~THR_WINCOR();

private:
	class Reader;

	THR_WINCOR(int32_t monthCount, int32_t channelCount, int32_t spectralLagCount,
			int32_t latCount);

	void init(int32_t monthCount, int32_t channelCount, int32_t spectralLagCount,
			int32_t latCount);

	static const THR_WINCOR STORE;
};

#endif /*THR_WINCOR_H_*/
