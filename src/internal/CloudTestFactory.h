#ifndef CLOUD_TEST_FACTORY_H_
#define CLOUD_TEST_FACTORY_H_

#include "CloudTestA.h"
#include "CloudTestB.h"
#include "CloudTestD.h"
#include "CloudTestE.h"
#include "CloudTestF.h"
#include "CloudTestG.h"
#include "CloudTestH.h"

class CloudTestFactory {
public:
	static CloudTest* createCloudTest(TestId testId, int32_t zoneId, int32_t timeId) {
		switch (testId) {
		case TEST_A:
			return new CloudTestA(zoneId, timeId);
		case TEST_B:
			return new CloudTestB(zoneId, timeId);
		case TEST_D:
			return new CloudTestD(zoneId, timeId);
		case TEST_E:
			return new CloudTestE(zoneId, timeId);
		case TEST_F:
			return new CloudTestF(zoneId, timeId);
		case TEST_G:
			return new CloudTestG(zoneId, timeId);
		case TEST_H:
			return new CloudTestH(zoneId, timeId);
		default:
			return 0;
		}
	}
};

#endif /*CLOUD_TEST_FACTORY_H_*/
