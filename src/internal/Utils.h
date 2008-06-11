#ifndef UTILS_H_
#define UTILS_H_

#include <cmath>

template<class T> long findIndex(T value, const T values[], long n) {
	long i = 0;

	if (n > 1) {
		const T d = (values[n - 1] - values[0]) / (T(2) * (n - 1));

		while (value - d > values[i] && i < n - 1) {
			++i;
		}
	}

	return i;
}

#endif /*UTILS_H_*/
