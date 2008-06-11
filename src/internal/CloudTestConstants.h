#ifndef CLOUD_TEST_CONSTANTS_H_
#define CLOUD_TEST_CONSTANTS_H_

/**
 * The threshold to be exceeded by the fractional land coverage for an IASI IFOV to
 * be considered as land.
 */
const double LAND_SEA_THRESHOLD = 0.50;

/**
 * The threshold not to be exceeded by the fractional land coverage for an IASI IFOV
 * to be considered as pure sea.
 */
const double PURE_SEA_THRESHOLD = 0.05;

/**
 * The threshold to be exceeded by the fractional land coverage for an IASI IFOV
 * to be considered as pure land.
 */
const double PURE_LAND_THRESHOLD = 0.95;

/**
 * The number of IASI spectral channels.
 */
const int IASI_CHANNEL_COUNT = 8461;

/**
 * The number of IFOVs per IASI EFOV.
 */
const int IFOV_IN_EFOV_COUNT = 4;

/**
 * The number of EFOVs per line.
 */
const int EFOV_COUNT = 30;

/**
 * The number of IFOVs per line.
 */
const int IFOV_COUNT = EFOV_COUNT * IFOV_IN_EFOV_COUNT;

#endif /*CLOUD_TEST_CONSTANTS_H_*/
