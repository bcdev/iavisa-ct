#ifndef UNITTESTS_H_
#define UNITTESTS_H_

template<class A, class B> inline bool equals(A actual, B expected) {
	return actual == expected;
}

void runAllTests();

#endif /*UNITTESTS_H_*/
