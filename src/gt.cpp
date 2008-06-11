#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

#include "internal/AuxiliaryDataProvider.h"
#include "internal/CloudTestFactory.h"
#include "internal/FilePathFactory.h"
#include "internal/SampleCollector.h"

#include "gt.h"
#include "common.h"

using namespace std;

static long zoneCount_;
static long timeCount_;

static vector<const CT*> cts_;
static vector<double> parameters_;

static string directoryPath_;
static string parameterFilePath_;
static FILE* logFile_;

void gtGetCloudGuess(bool estimates[]) {
	gtGetCloudGuess(estimates, &parameters_[0]);
}

void gtGetCloudGuess(bool estimates[], const double parameters[]) {
	for (size_t i = 0, k = 0; i < cts_.size(); ++i) {
		cts_[i]->getCloudGuess(&parameters[0], &estimates[k]);
		k += cts_[i]->getSampleCount();
	}
}

long gtSampleCount() {
	long sampleCount = 0;

	for (size_t i = 0; i < cts_.size(); ++i) {
		sampleCount += cts_[i]->getSampleCount();
	}

	return sampleCount;
}

void gtGetCloudTruth(long truth[]) {
	for (size_t i = 0, k = 0; i < cts_.size(); ++i) {
		cts_[i]->getCloudTruth(&truth[k]);
		k += cts_[i]->getSampleCount();
	}
}

void gtGetParameters(double parameters[]) {
	copy(parameters_.begin(), parameters_.end(), parameters);
}

void gtGetDefaultParameters(TestId test, long zoneId, long timeId,
		double parameters[]) {
	return AuxiliaryDataProvider::getDefaultParameters(test, zoneId, timeId,
			parameters);
}

long gtParameterCount() {
	return parameters_.size();
}

long gtParameterCount(TestId test) {
	return AuxiliaryDataProvider::getParameterCount(test);
}

long gtZoneCount(TestId test) {
	return AuxiliaryDataProvider::getZoneCount(test);
}

long gtTimeCount(TestId test) {
	return AuxiliaryDataProvider::getTimeCount(test);
}

FILE* gtLogFile() {
	return logFile_;
}

const char* gtDirectoryPath() {
	return directoryPath_.c_str();
}

static void gtCreateDirectory(const char* path) {
	string command = "mkdir -p ";
	command.append(path);
	system(command.c_str());
}

static FILE* gtCreateFile(const char* path) {
	return fopen(path, "w");
}

void gtInit(DatasetId datasetId, TestId testId, const char* initId,
		const char* parameterFilePath) throw() {
	gtExit();

	zoneCount_ = gtZoneCount(testId);
	timeCount_ = gtTimeCount(testId);

	for (long zoneId = 0; zoneId < zoneCount_; ++zoneId) {
		for (long timeId = 0; timeId < timeCount_; ++timeId) {
			cts_.push_back(new CT(datasetId, testId, zoneId, timeId));
		}
	}

	parameters_.resize(gtParameterCount(testId), 0.0);

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

					gtExit();
					throw ios_base::failure(msg);
				}
			}
		} else {
			string msg("File '");
			msg.append(parameterFilePath);
			msg.append("' not found.");

			gtExit();
			throw ios_base::failure(msg);
		}
	}

	if (initId != 0) {
		const FilePathFactory
				filePathFactory(datasetId, testId, -1, -1, initId);
		directoryPath_ = filePathFactory.createDirectoryPath();
		parameterFilePath_ = filePathFactory.createParameterFilePath();

		gtCreateDirectory(directoryPath_.c_str());
		gtCreateFile(filePathFactory.createLogFilePath().c_str());
	}
}

void gtExit() {
	for (size_t i = 0; i < cts_.size(); ++i) {
		if (cts_[i] != 0) {
			delete cts_[i];
		}
	}
	cts_.clear();

	parameters_.clear();
	directoryPath_.clear();
	parameterFilePath_.clear();

	if (logFile_ != 0) {
		fclose(logFile_);
		logFile_ = 0;
	}

	zoneCount_ = 0;
	timeCount_ = 0;
}

const char* gtSave(const double parameters[]) {
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
