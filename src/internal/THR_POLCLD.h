#ifndef AUX_POLCLD_H_
#define AUX_POLCLD_H_

#include <stdint.h>

/**
 * Structure for channel numbers and threshold values required for the cloud test
 * over elevated polar regions.
 * <p/>
 * The default values for the fields in this structure are defined in the
 * IASI_L2_PGS_THR_POLCLD auxiliary file described on page 52 of document
 * EUM.EPS.SYS.TEN.03.034.
 */
struct THR_POLCLD {
	friend class AuxiliaryDataProvider;
	friend class CloudTestG;
	
	/**
	 * The number of months.
	 */
	int32_t monthCount_;

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
	 * @param zoneId the zone selected - not used.
	 * @param timeId the time selected.
	 */
	THR_POLCLD(int32_t zoneId, int32_t timeId);
	
	/**
	 * Destructor.
	 */
	~THR_POLCLD();

private:
	class Reader;

	THR_POLCLD(int32_t monthCount);

	void init(int32_t monthCount);

	static const THR_POLCLD STORE;
};

#endif /*AUX_POLCLD_H_*/
