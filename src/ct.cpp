#include <algorithm>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <string>

#include "internal/AuxiliaryDataProvider.h"
#include "internal/FilePathFactory.h"

extern "C" {
#include "ct.h"
}

#include "common.h"

using namespace std;

static CT* ct_;
static vector<double> parameters_;

static string directoryPath_;
static string parameterFilePath_;
static FILE* logFile_;

void ctGetCloudGuess(bool estimates[]) {
	ctGetCloudGuessForParameters(&parameters_[0], estimates);
}

void ctGetCloudGuessForParameters(const double parameters[], bool estimates[]) {
	ct_->getCloudGuess(&parameters[0], estimates);
}

void ctGetCloudTruth(int32_t truth[]) {
	ct_->getCloudTruth(truth);
}

int32_t ctSampleCount() {
	return ct_->getSampleCount();
}

void ctGetParameters(double parameters[]) {
	copy(parameters_.begin(), parameters_.end(), parameters);
}

void ctGetDefaultParametersForTest(enum TestId testId, int32_t zoneId,
		int32_t timeId, double parameters[]) {
	return AuxiliaryDataProvider::getDefaultParameters(testId, zoneId, timeId,
			parameters);
}

int32_t ctParameterCount() {
	return parameters_.size();
}

int32_t ctParameterCountForTest(enum TestId testId) {
	return AuxiliaryDataProvider::getParameterCount(testId);
}

int32_t ctZoneCountForTest(enum TestId testId) {
	return AuxiliaryDataProvider::getZoneCount(testId);
}

int32_t ctTimeCountForTest(enum TestId testId) {
	return AuxiliaryDataProvider::getTimeCount(testId);
}

FILE* ctLogFile() {
	return 0;
}

const char* ctDirectoryPath() {
	return directoryPath_.c_str();
}

static int32_t ctCreateDirectory(const char* path) {
	string command = "mkdir -p ";
	command.append(path);

	return system(command.c_str());
}

static FILE* ctCreateFile(const char* path) {
	return fopen(path, "w");
}

void ctInit(enum DatasetId datasetId, enum TestId testId, int32_t zoneId,
		int32_t timeId, const char* initId, const char* parameterFilePath) {
	ctExit();
	ct_ = new CT(datasetId, testId, zoneId, timeId);

	parameters_.resize(ctParameterCountForTest(testId), 0.0);

	if (parameterFilePath != 0) {
		ifstream ifs(parameterFilePath);

		if (ifs) {
			for (size_t i = 0; i < parameters_.size(); ++i) {
				if (ifs) {
					ifs >> parameters_[i];
				} else {
					string msg("Failed to read file '");
					msg.append(parameterFilePath);
					msg.append("'.");

					ctExit();
					throw ios_base::failure(msg);
				}
			}
		} else {
			string msg("File '");
			msg.append(parameterFilePath);
			msg.append("' not found.");

			ctExit();
			throw ios_base::failure(msg);
		}
	} else {
		ctGetDefaultParametersForTest(testId, zoneId, timeId, &parameters_[0]);
	}

	if (initId != 0) {
		const FilePathFactory filePathFactory(datasetId, testId, zoneId,
				timeId, initId);
		directoryPath_ = filePathFactory.createDirectoryPath();
		parameterFilePath_ = filePathFactory.createParameterFilePath();

		const int32_t status = ctCreateDirectory(directoryPath_.c_str());
		if (status == -1) {
			string msg("Directory '");
			msg.append(directoryPath_);
			msg.append("' could no be created.");

			ctExit();
			throw runtime_error(msg);
		}
		ctCreateFile(filePathFactory.createLogFilePath().c_str());
	}
}

void ctExit() {
	if (ct_ != 0) {
		delete ct_;
		ct_ = 0;
	}

	parameters_.clear();
	directoryPath_.clear();
	parameterFilePath_.clear();

	if (logFile_ != 0) {
		fclose(logFile_);
		logFile_ = 0;
	}
}

const char* ctSave(const double parameters[]) {
	if (parameterFilePath_.length() != 0) {
		ofstream ofs(parameterFilePath_.c_str());

		if (ofs) {
			for (size_t i = 0; i < parameters_.size(); ++i) {
				if (ofs) {
					ofs << parameters_[i] << endl;
				} else {
					string msg("Failed to write file '");
					msg.append(parameterFilePath_);
					msg.append("'.");

					cerr << msg << endl;
					return 0;
				}
			}
		} else {
			string msg("File '");
			msg.append(parameterFilePath_);
			msg.append("' could not be created.");

			cerr << msg << endl;
			return 0;
		}
	}

	return parameterFilePath_.c_str();
}
