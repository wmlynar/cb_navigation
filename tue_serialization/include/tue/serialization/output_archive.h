#ifndef TUE_SERIALIZATION_OUTPUT_ARCHIVE_H_
#define TUE_SERIALIZATION_OUTPUT_ARCHIVE_H_

#include <iostream>

#include "tue/serialization/version.h"

namespace tue
{
namespace serialization
{

class OutputArchive {

public:

    OutputArchive(std::ostream& stream) : stream_(stream) {
        stream_.write((char*)&tue::serialization::VERSION, sizeof(tue::serialization::VERSION));
    }

    virtual ~OutputArchive() {}

    inline OutputArchive& operator<<(unsigned char c) { stream_.write((char*)&c, sizeof(c)); return *this; }

    inline OutputArchive& operator<<(float f) { stream_.write((char*)&f, sizeof(f)); return *this; }

    inline OutputArchive& operator<<(double d) { stream_.write((char*)&d, sizeof(d)); return *this; }

    inline OutputArchive& operator<<(int i) { stream_.write((char*)&i, sizeof(i)); return *this; }

    inline OutputArchive& operator<<(std::string s) { stream_.write(s.c_str(), s.size() + 1); return *this; }

    inline OutputArchive& write(const char* data, unsigned int size) { stream_.write(data, size); return *this; }

    inline std::ostream& stream() { return stream_; }

protected:

    std::ostream& stream_;

};

}

}

#endif
