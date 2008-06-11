#include <algorithm>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <string>

#include "internal/AuxiliaryDataProvider.h"
#include "internal/FilePathFactory.h"

#include "ct.h"
#include "common.h"

using namespace std;

static CT* ct_;
static vector<double> parameters_;

static string directoryPath_;
static string parameterFilePath_;
static FILE* logFile_;

void ctGetCloudGuess(bool estimates[]) {
	ctGetCloudGuess(estimates, &parameters_[0]);
}

void ctGetCloudGuess(bool estimates[], const double parameters[]) {
	ct_->getCloudGuess(&parameters[0], estimates);
}

void ctGetCloudTruth(long truth[]) {
	ct_->getCloudTruth(truth);
}

long ctSampleCount() {
	return ct_->getSampleCount();
}

void ctGetParameters(double parameters[]) {
	copy(parameters_.begin(), parameters_.end(), parameters);
}

void ctGetDefaultParameters(TestId testId, long zoneId, long timeId,
		double parameters[]) {
	return AuxiliaryDataProvider::getDefaultParameters(testId, zoneId, timeId,
			parameters);
}

long ctParameterCount() {
	return parameters_.size();
}

long ctParameterCount(TestId testId) {
	return AuxiliaryDataProvider::getParameterCount(testId);
}

long ctZoneCount(TestId testId) {
	return AuxiliaryDataProvider::getZoneCount(testId);
}

long ctTimeCount(TestId testId) {
	return AuxiliaryDataProvider::getTimeCount(testId);
}

FILE* ctLogFile() {
	return 0;
}

const char* ctDirectoryPath() {
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

void ctInit(DatasetId datasetId, TestId testId, long zoneId, long timeId,
		const char* initId, const char* parameterFilePath) throw() {
	ctExit();
	ct_ = new CT(datasetId, testId, zoneId, timeId);

	parameters_.resize(ctParameterCount(testId), 0.0);

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
		ctGetDefaultParameters(testId, zoneId, timeId, &parameters_[0]);
	}

	if (initId != 0) {
		const FilePathFactory filePathFactory(datasetId, testId, zoneId,
				timeId, initId);
		directoryPath_ = filePathFactory.createDirectoryPath();
		parameterFilePath_ = filePathFactory.createParameterFilePath();

		gtCreateDirectory(directoryPath_.c_str());
		gtCreateFile(filePathFactory.createLogFilePath().c_str());
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
