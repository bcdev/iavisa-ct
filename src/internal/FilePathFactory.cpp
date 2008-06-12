#include <ctime>
#include <sstream>

#include "FilePathFactory.h"
#include "FilePathResolver.h"

using namespace std;

string FilePathFactory::createDirectoryPath() const {
	string path("opt");

	path.append("/");
	path.append(baseId);

	return FilePathResolver::getAbsolutePath(path);
}

string FilePathFactory::createParameterFilePath() const {
	string path = createDirectoryPath();

	path.append("/");
	path.append(baseId);
	path.append("_");
	path.append(initId);
	path.append(".par");

	return path;
}

string FilePathFactory::createLogFilePath() const {
	string path = createDirectoryPath();

	path.append("/");
	path.append(baseId);
	path.append("_");
	path.append(initId);
	path.append(".log");

	return path;
}

string FilePathFactory::toString(DatasetId datasetId, TestId testId,
		long zoneId, long timeId) {
	string s;

	s.append(toString(datasetId));
	s.append(toString(testId));
	s.append("_");
	s.append(toString(zoneId, 4));
	s.append("_");
	s.append(toString(timeId, 2));

	return s;
}

string FilePathFactory::toString(TestId testId) {
	switch (testId) {
	case TEST_A:
		return string("A");
	case TEST_B:
		return string("B");
	case TEST_D:
		return string("D");
	case TEST_E:
		return string("E");
	case TEST_F:
		return string("F");
	case TEST_G:
		return string("G");
	case TEST_H:
		return string("H");
	default:
		return string("X");
	}
}

string FilePathFactory::toString(DatasetId datasetId) {
	switch (datasetId) {
	case TRAINING:
		return string("T");
	case VERIFICATION:
		return string("V");
	default:
		return string("X");
	}
}

string FilePathFactory::toString(long id, long width) {
	ostringstream oss;
	oss.width(width);

	if (id < 0) {
		oss.fill('9');
		oss << 9;
	} else {
		oss.fill('0');
		oss << id;
	}

	return oss.str();
}
