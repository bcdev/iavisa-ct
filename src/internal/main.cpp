#include <iostream>

#include "SampleCollector.h"

using namespace std;

void writeVector(ostream& os, vector<double> vector) {
	cout << vector.size() << "; ";
	for (size_t i = 0; i < vector.size(); ++i) {
		cout << vector[i] << "; ";
	}
	
}

int main(int argc, char* argv[]) {
	vector<Sample> samples = SampleCollector::getSamples();

	cout << "randomNumber; lat; lon; month; cloudType; ifovValid; efovValid; elevatedPolarRegion; desertRegion; dustStorm; fractionalLandCover; brightnessTemperatureCount(A); brightnessTemperatures(A); brightnessTemperatureCount(B); brightnessTemperatures(B); brightnessTemperatureCount(G); brightnessTemperatures(G); brightnessTemperatureCount(H); brightnessTemperatures(H)" << endl;
	
	for (size_t i = 0; i < samples.size(); ++i) {
		const Sample sample = samples[i];
		
		cout << sample.getRandomNumber() << "; ";
		cout << sample.getLat() << "; ";
		cout << sample.getLon() << "; ";
		cout << sample.getMonth() << "; ";
		cout << sample.getCloudType() << "; ";
		cout << sample.isIfovValid() << "; ";
		cout << sample.isEfovValid() << "; ";
		cout << sample.isElevatedPolarRegion() << "; ";
		cout << sample.isDesertRegion() << "; ";
		cout << sample.isDustStorm() << "; ";
		cout << sample.getFractionalLandCover() << "; ";
		
		writeVector(cout, sample.getBrightnessTemperatureVector(TEST_A));
		writeVector(cout, sample.getBrightnessTemperatureVector(TEST_B));
//		writeVector(cout, sample.getBrightnessTemperatureVector(TEST_E)); // 980 values
//		writeVector(cout, sample.getBrightnessTemperatureVector(TEST_F)); // 400 values
		writeVector(cout, sample.getBrightnessTemperatureVector(TEST_G));
		writeVector(cout, sample.getBrightnessTemperatureVector(TEST_H));		

		cout << endl;
	}
		
	return 0;
}
