#ifndef FILE_PATH_FACTORY_H_
#define FILE_PATH_FACTORY_H_

#include <stdint.h>
#include <string>

#include "Enums.h"

class FilePathFactory {
public:
	FilePathFactory(DatasetId datasetId, TestId testId, int32_t zoneId,
			int32_t timeId, const char* initId) :
		baseId(toString(datasetId, testId, zoneId, timeId)), initId(initId) {
	}

	~FilePathFactory() {
	}

	/**
	 * Creates the (absolute) path of the cloud test directory.
	 */
	std::string createDirectoryPath() const;

	/**
	 * Creates the (absolute) path of the parameter file.
	 */
	std::string createParameterFilePath() const;

	/**
	 * Creates the (absolute) path of the log file.
	 */
	std::string createLogFilePath() const;

private:
	static std::string toString(DatasetId datasetId, TestId testId,
			int32_t zoneId, int32_t timeId);
	static std::string toString(DatasetId datasetId);
	static std::string toString(TestId testId);
	static std::string toString(int32_t id, int32_t width);

	const std::string baseId;
	const std::string initId;
};

#endif /*FILE_PATH_FACTORY_H_*/
