#ifndef FILE_PATH_RESOLVER_H_
#define FILE_PATH_RESOLVER_H_

#include <stdexcept>
#include <string>

class FilePathResolver {
public:

	/**
	 * Creates an absolute path from a relative path.
	 */
	static std::string getAbsolutePath(const std::string& relativePath)
			throw (std::runtime_error);

};

#endif /*FILE_PATH_RESOLVER_H_*/
