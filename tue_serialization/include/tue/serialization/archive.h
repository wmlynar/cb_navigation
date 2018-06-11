#ifndef TUE_SERIALIZATION_ARCHIVE_H_
#define TUE_SERIALIZATION_ARCHIVE_H_

#include <sstream>
#include <vector>

#include "tue/serialization/version.h"

namespace tue
{
namespace serialization
{

class Archive {

public:

    Archive() : version_(tue::serialization::VERSION)
    {
    }

    virtual ~Archive() {}

    // - - - - - - - - - - - - - - - - - - - - READ - - - - - - - - - - - - - - - - - - - -

    inline Archive& operator>>(unsigned char& c) { stream_.read((char*)&c, sizeof(c)); return *this; }

    inline Archive& operator>>(float& f) { stream_.read((char*)&f, sizeof(f)); return *this; }

    inline Archive& operator>>(double& d) { stream_.read((char*)&d, sizeof(d)); return *this; }

    inline Archive& operator>>(int& i) { stream_.read((char*)&i, sizeof(i)); return *this; }

    inline Archive& operator>>(std::string& s) {
        s.clear();
        char c;
        while(true) {
            stream_.read(&c, 1);
            if (c == '\0') {
                break;
            }
            s += c;
        }
        return *this;
    }

    // - - - - - - - - - - - - - - - - - - - - WRITE - - - - - - - - - - - - - - - - - - - -

    inline Archive& operator<<(unsigned char c) { stream_.write((char*)&c, sizeof(c)); return *this; }

    inline Archive& operator<<(float f) { stream_.write((char*)&f, sizeof(f)); return *this; }

    inline Archive& operator<<(double d) { stream_.write((char*)&d, sizeof(d)); return *this; }

    inline Archive& operator<<(int i) { stream_.write((char*)&i, sizeof(i)); return *this; }

    inline Archive& operator<<(std::string s) { stream_.write(s.c_str(), s.size() + 1); return *this; }

    inline std::stringstream& stream() { return stream_; }

    inline const std::stringstream& stream() const { return stream_; }

    inline int version() const { return version_; }

protected:

    std::stringstream stream_;

    int version_;

    friend void convert(std::vector<unsigned char>& data, Archive& a);

};

}

}

#endif
