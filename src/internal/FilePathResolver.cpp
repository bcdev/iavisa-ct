#include <cstdlib>

#include "FilePathResolver.h"

using namespace std;

string FilePathResolver::getAbsolutePath(const string& relativePath)
		throw (runtime_error) {
	const char* home = getenv("IAVISA_HOME");

	if (home == 0) {
		throw runtime_error("The environment variable 'IAVISA_HOME' is not set.");
	}
	
	string path(home);
	if (path[path.length() - 1]) {
		path.append("/");
	}
	path.append(relativePath);

	return path;
}
