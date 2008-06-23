#ifndef ABSTRACT_DATA_READER_H_
#define ABSTRACT_DATA_READER_H_

#include <stdint.h>
#include <algorithm>
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>

/**
 * Abstract data reader.
 */
template<class T> class AbstractDataReader {
public:
	/**
	 * Destructor.
	 */
	virtual ~AbstractDataReader() {
	}

	/**
	 * Reads data from a file.
	 */
	T read(const char* filePath) throw (std::ios_base::failure) {
		std::ifstream ifs(filePath);
		
		if (!ifs) {
			std::string msg("File '");
			msg.append(filePath);
			msg.append("' does not exist.");

			throw std::ios_base::failure(msg);
		}
		
		ifs.exceptions(std::ios_base::badbit | std::ios_base::failbit
				| std::ios::eofbit);

		try {
			return read(ifs);
		} catch (std::exception e) {
			std::string msg("Failed to read file '");
			msg.append(filePath);
			msg.append("'.");

			throw std::ios_base::failure(msg);
		}
	}

protected:
	/**
	 * Constructor.
	 */
	AbstractDataReader() :
		memoryByteOrder(getMemoryByteOrder()) {
	}

	virtual T read(std::istream& is) = 0;

	/**
	 * Reads a single item from a binary (big endian) input stream into
	 * memory.
	 * 
	 * @param is       the input stream. 
	 * @param pointer  the pointer to the location where the item is stored in memory.
	 * 
	 * @return the input stream.
	 */
	template<class X> std::istream& readBE(std::istream& is, X* pointer) const {
		return readBE(is, pointer, 1);
	}

	/**
	 * Reads a sequence of items from a binary (big endian)
	 * input stream into memory.
	 * 
	 * @param is       the input stream. 
	 * @param pointer  the pointer to the location where the items are stored in memory.
	 * @param n        the number of items being read. 
	 * 
	 * @return the input stream.
	 */
	template<class X> std::istream& readBE(std::istream& is, X* pointer,
			size_t n) const {
		assert(memoryByteOrder != UNKNOWN);
		if (is) {
			char* bytes = reinterpret_cast<char*>(pointer);
			is.read(bytes, sizeof(X) * n);

			if (memoryByteOrder == LE) {
				for (size_t i = 0; i < n; ++i, ++pointer) {
					char* bytes = reinterpret_cast<char*>(pointer);
					std::reverse(bytes, bytes + sizeof(X));
				}
			}
		}

		return is;
	}

	/**
	 * Reads a single item from a binary (little endian) input stream into
	 * memory.
	 * 
	 * @param is       the input stream. 
	 * @param pointer  the points to the location where the item is stored in memory.
	 * 
	 * @return the input stream.
	 */
	template<class X> std::istream& readLE(std::istream& is, X* pointer) const {
		return readLE(is, pointer, 1);
	}

	/**
	 * Reads a sequence of items from a binary (little endian)
	 * input stream into memory.
	 * 
	 * @param is       the input stream. 
	 * @param pointer  the pointer to the location where the items are stored in memory.
	 * @param n        the number of items being read. 
	 * 
	 * @return the input stream.
	 */
	template<class X> std::istream& readLE(std::istream& is, X* pointer,
			size_t n) const {
		assert(memoryByteOrder != UNKNOWN);
		if (is) {
			char* bytes = reinterpret_cast<char*>(pointer);
			is.read(bytes, sizeof(X) * n);

			if (memoryByteOrder == BE) {
				for (size_t i = 0; i < n; ++i, ++pointer) {
					char* bytes = reinterpret_cast<char*>(pointer);
					std::reverse(bytes, bytes + sizeof(X));
				}
			}
		}

		return is;
	}

	/**
	 * Reads a single {@code int64_t} item from a binary (big endian)
	 * input stream into memory.
	 * 
	 * @param is       the input stream. 
	 * @param pointer  the pointer to the location where the items are stored in memory.
	 * 
	 * @return the input stream.
	 */
	template<class X> std::istream& readInt64BE(std::istream& is, X* pointer) const {
		return readInt64BE(is, pointer, 1);
	}

	/**
	 * Reads a sequence of {@code int64_t} items from a binary (big endian)
	 * input stream into memory.
	 * 
	 * @param is       the input stream. 
	 * @param pointer  the pointer to the location where the items are stored in memory.
	 * @param n        the number of items being read. 
	 * 
	 * @return the input stream.
	 */
	template<class X> std::istream& readInt64BE(std::istream& is,
			X* pointer, size_t n) const {
		int64_t* buffer = new int64_t[n];

		readBE(is, buffer, n);
		std::copy(buffer, buffer + n, pointer);
		delete[] buffer;

		return is;
	}

	/**
	 * Reads a single {@code int64_t} item from a binary (little endian)
	 * input stream into memory.
	 * 
	 * @param is       the input stream. 
	 * @param pointer  the pointer to the location where the items are stored in memory.
	 * 
	 * @return the input stream.
	 */
	template<class X> std::istream& readInt64LE(std::istream& is, X* pointer) const {
		return readInt64LE(is, pointer, 1);
	}

	/**
	 * Reads a sequence of {@code int64_t} items from a binary (little endian)
	 * input stream into memory.
	 * 
	 * @param is       the input stream. 
	 * @param pointer  the pointer to the location where the items are stored in memory.
	 * @param n        the number of items being read. 
	 * 
	 * @return the input stream.
	 */
	template<class X> std::istream& readInt64LE(std::istream& is,
			X* pointer, size_t n) const {
		int64_t* buffer = new int64_t[n];

		readLE(is, buffer, n);
		std::copy(buffer, buffer + n, pointer);
		delete[] buffer;

		return is;
	}

	/**
	 * Skips an item of type {@code X}.
	 */
	template <class X> std::istream& skip(std::istream& is) const {
		return skip<X>(is, 1);
	}

	/**
	 * Skips a sequence of items of type {@code X}.
	 */
	template <class X> std::istream& skip(std::istream& is, size_t n) const {
		return is.seekg(n * sizeof(X), std::ios_base::cur);
	}

private:
	enum ByteOrder {
		UNKNOWN = 0,
		LE = 1,
		BE = 2
	};

	ByteOrder getMemoryByteOrder() {
		const u_int32_t word = 0x04030201L;
		const unsigned char byte =
				*reinterpret_cast<const unsigned char*>(&word);

		switch (byte) {
		case 1:
			return LE;
		case 4:
			return BE;
		default:
			return UNKNOWN;
		}
	}

	const ByteOrder memoryByteOrder;
};

#endif /*ABSTRACT_DATA_READER_H_*/
