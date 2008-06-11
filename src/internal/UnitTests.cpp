#include <cassert>
#include <iostream>

#include "Utils.h"
#include "UnitTests.h"


static void testFindIndexForMonths() {
	const int months[] = {2, 5, 8, 11};
	
	assert(equals(0, findIndex(1, months, 4)));
	assert(equals(0, findIndex(2, months, 4)));
	assert(equals(0, findIndex(3, months, 4)));
	assert(equals(1, findIndex(4, months, 4)));
	assert(equals(1, findIndex(5, months, 4)));
	assert(equals(1, findIndex(6, months, 4)));
	assert(equals(2, findIndex(7, months, 4)));
	assert(equals(2, findIndex(8, months, 4)));
	assert(equals(2, findIndex(9, months, 4)));
	assert(equals(3, findIndex(10, months, 4)));
	assert(equals(3, findIndex(11, months, 4)));
	assert(equals(3, findIndex(12, months, 4)));
}

static void testFindIndexForSingleMonth() {
	const int months[] = {6};
	
	assert(equals(0, findIndex(1, months, 1)));
	assert(equals(0, findIndex(2, months, 1)));
	assert(equals(0, findIndex(3, months, 1)));
	assert(equals(0, findIndex(4, months, 1)));
	assert(equals(0, findIndex(5, months, 1)));
	assert(equals(0, findIndex(6, months, 1)));
	assert(equals(0, findIndex(7, months, 1)));
	assert(equals(0, findIndex(8, months, 1)));
	assert(equals(0, findIndex(9, months, 1)));
	assert(equals(0, findIndex(10, months, 1)));
	assert(equals(0, findIndex(11, months, 1)));
	assert(equals(0, findIndex(12, months, 1)));
}

static void testFindIndexForAllMonths() {
	const int months[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
	
	assert(equals(0, findIndex(1, months, 12)));
	assert(equals(1, findIndex(2, months, 12)));
	assert(equals(2, findIndex(3, months, 12)));
	assert(equals(3, findIndex(4, months, 12)));
	assert(equals(4, findIndex(5, months, 12)));
	assert(equals(5, findIndex(6, months, 12)));
	assert(equals(6, findIndex(7, months, 12)));
	assert(equals(7, findIndex(8, months, 12)));
	assert(equals(8, findIndex(9, months, 12)));
	assert(equals(9, findIndex(10, months, 12)));
	assert(equals(10, findIndex(11, months, 12)));
	assert(equals(11, findIndex(12, months, 12)));
}

static void testFindIndexForLats() {
	const double lats[] = {-75, -45, -15, 15, 45, 75};
	
	assert(equals(0, findIndex(-85.0, lats, 6)));
	assert(equals(0, findIndex(-75.0, lats, 6)));
	assert(equals(0, findIndex(-65.0, lats, 6)));
	assert(equals(1, findIndex(-55.0, lats, 6)));
	assert(equals(1, findIndex(-45.0, lats, 6)));
	assert(equals(1, findIndex(-35.0, lats, 6)));
	assert(equals(2, findIndex(-25.0, lats, 6)));
	assert(equals(2, findIndex(-15.0, lats, 6)));
	assert(equals(2, findIndex(-5.0, lats, 6)));
	assert(equals(3, findIndex(5.0, lats, 6)));
	assert(equals(3, findIndex(15.0, lats, 6)));
	assert(equals(3, findIndex(25.0, lats, 6)));
	assert(equals(4, findIndex(35.0, lats, 6)));
	assert(equals(4, findIndex(45.0, lats, 6)));
	assert(equals(4, findIndex(55.0, lats, 6)));
	assert(equals(5, findIndex(65.0, lats, 6)));
	assert(equals(5, findIndex(75.0, lats, 6)));
	assert(equals(5, findIndex(85.0, lats, 6)));
}

void runAllTests() {
	testFindIndexForMonths();
	testFindIndexForSingleMonth();
	testFindIndexForAllMonths();
	testFindIndexForLats();
	
	std::cout << "All tests successfully completed" << std::endl;
}
