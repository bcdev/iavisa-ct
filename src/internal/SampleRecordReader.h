#ifndef SAMPLE_RECORD_READER_H_
#define SAMPLE_RECORDR_EADER_H_

#include <vector>

#include "AbstractDataReader.h"
#include "Sample.h"

class SampleRecordReader : public AbstractDataReader<std::vector<Sample> > {
public:
	SampleRecordReader();
	~SampleRecordReader();

protected:
	std::vector<Sample> read(std::istream& is);

private:
	std::istream& read(std::istream& is, Sample& sampleRecord) const;
};

#endif /*SAMPLE_RECORD_READER_H_*/
