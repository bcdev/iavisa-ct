#ifndef COF_IASINT_H_
#define COF_IASINT_H_

#include <stdint.h>

/**
 * Structure for coefficients and threshold values required for cloud test B.
 * <p/>
 * The default values for the fields in this structure are defined in the
 * IASI_L2_PGS_COF_IASINT auxiliary file described on page 21 of document
 * EUM.EPS.SYS.TEN.03.034.
 */
struct COF_IASINT {
	friend class AuxiliaryDataProvider;
	friend class CloudTestB;
	
	/**
	 * The number of months.
	 */
	int32_t monthCount_;
	
	/**
	 * The months.
	 */
	int32_t* months_;
	
	/**
	 * The number of latitudes.
	 */
	int32_t latCount_;
	
	/**
	 * The latitudes.
	 */
	double* lats_;
	
	/**
	 * The number of surface types.
	 */
	int32_t surfaceTypeCount_;
	
	/**
	 * The threshold values.
	 * 
	 * Note that for each surface type, the first, second, and last threshold values do
	 * correspond to Equations 204, 205, and 206 PGS, respectively. 
	 */
	double* thresholdValues_;
	
	/**
	 * The regression coefficients for Equation 204 PGS.
	 */
	double* coefficientsA1_;
	
	/**
	 * The regression coefficients for Equation 205 PGS.
	 */
	double* coefficientsA2_;
	
	/**
	 * The regression coefficients for Equation 206 PGS.
	 */
	double* coefficientsA3_;

	/**
	 * Constructor.
	 * 
	 * @param zoneId the zone selected.
	 * @param timeId the time selected.
	 */
	COF_IASINT(int32_t zoneId, int32_t timeId);

	/**
	 * Destructor.
	 */
	~COF_IASINT();
	

private:
	class Reader;

	COF_IASINT(int32_t monthCount, int32_t latCount, int32_t surfaceTypeCount);

	void init(int32_t monthCount, int32_t latCount, int32_t surfaceTypeCount);

	static const COF_IASINT STORE;
};

#endif /*COF_IASINT_H_*/
