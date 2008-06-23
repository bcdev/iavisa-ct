#ifndef IAVISA_CT_H_
#define IAVISA_CT_H_

#include <stdint.h>

#ifndef ENUMS_H_
#define ENUMS_H_

/**
 * The cloud tests.
 */
enum TestId {
	TEST_A,
	TEST_B,
	TEST_D,
	TEST_E,
	TEST_F,
	TEST_G,
	TEST_H
};

/**
 * The datasets.
 */
enum DatasetId {
	TRAINING,
	VERIFICATION
};

#endif /*ENUMS_H_*/

/**
 * Returns the cloud test estimates for the parameters set by {@code ctInit()}.
 * 
 * @param estimates the array being used to store the cloud test estimates.
 */
void ctGetCloudGuess(bool estimates[]);

/**
 * Returns the cloud test estimates for the given test parameters.
 * 
 * @param estimates  the array being used to store the cloud test estimates.
 * @param parameters the cloud test parameters.
 */
void ctGetCloudGuess(bool estimates[], const double parameters[]);

/**
 * Returns the cloud truth.
 * 
 * @param truths the array being used to store the cloud truth.
 */
void ctGetCloudTruth(int32_t truths[]);

/**
 * Returns the number of samples for the test selected.
 * 
 * Corresponds to the length of the arrays returned by {@code ctGetCloudGuess()}
 * and {@code ctGetCloudTruth()}.
 * 
 * @return the number of samples for the test selected.
 */
int32_t ctSampleCount();

/**
 * Returns a copy of the parameters set by {@code ctInit()}.
 * 
 * @param parameters the array used to store the copy of the parameter set by {@code ctInit()}.
 */
void ctGetParameters(double parameters[]);

/**
 * Returns a copy of the default parameters for the cloud test selected.
 * 
 * @param testId     the cloud test selected.
 * @param zoneId     the zone selected.
 * @param timeId     the time selected.
 * @param parameters the array used to store the copy of the default parameters.
 */
void ctGetDefaultParameters(TestId testId, int32_t zoneId, int32_t timeId,
		double parameters[]);

/**
 * Returns the number of parameters set by {@code ctInit()}.
 * 
 * @return the number of parameters set by {@code ctInit()}.
 */
int32_t ctParameterCount();

/**
 * Returns the number of cloud test parameters for the cloud test selected.
 * 
 * @param testId the cloud test selected.
 * 
 * @return the number of cloud test parameters for the cloud test selected.
 */
int32_t ctParameterCount(TestId testId);

/**
 * Returns the number of geographical zones considered by the cloud test selected.
 *
 * @param testId the cloud test selected.
 */
int32_t ctZoneCount(TestId testId);

/**
 * Returns the number of time periods considered by the cloud test selected.
 *
 * @param testId the cloud test selected.
 */
int32_t ctTimeCount(TestId testId);

/**
 * Returns the log file associated with the cloud test.
 * 
 * @return the log file.
 */
FILE* ctLogFile();

/**
 * Returns the directory path associated with the cloud test.
 * 
 * @return the directory path associated with the cloud test.
 */
const char* ctDirectoryPath();

/**
 * Initializes the cloud test.
 * 
 * @param datasetId         the dataset selected.
 * @param testId            the cloud test selected.
 * @param zoneId			the zone selected.
 * @param timeId			the time selected.
 * @param initId			the initialisation identifier.
 * @param parameterFilePath the path of the file with the initial parameters
 *                          for the cloud test selected.
 */
void ctInit(DatasetId datasetId, TestId testId, int32_t zoneId, int32_t timeId,
		const char* initId, const char* parameterFilePath) throw();

/**
 * Exits the cloud test.
 */
void ctExit();

/**
 * Saves the given parameters to a file.
 * 
 * @return the path of the file saved.
 */
const char* ctSave(const double parameters[]);

#endif /*IAVISA_CT_H_*/
