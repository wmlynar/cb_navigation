#ifndef TUE_SERIALIZATION_INPUT_ARCHIVE_H_
#define TUE_SERIALIZATION_INPUT_ARCHIVE_H_

#include <iostream>

namespace tue
{
namespace serialization
{

class InputArchive {

public:

    InputArchive(std::istream& stream) : stream_(stream) {
        stream_.read((char*)&version_, sizeof(version_));
    }

    virtual ~InputArchive() {}

    inline InputArchive& operator>>(unsigned char& c) { stream_.read((char*)&c, sizeof(c)); return *this; }

    inline InputArchive& operator>>(float& f) { stream_.read((char*)&f, sizeof(f)); return *this; }

    inline InputArchive& operator>>(double& d) { stream_.read((char*)&d, sizeof(d)); return *this; }

    inline InputArchive& operator>>(int& i) { stream_.read((char*)&i, sizeof(i)); return *this; }

    inline InputArchive& operator>>(std::string& s) {
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

    inline std::istream& getStream() { return stream_; }

    inline int getVersion() { return version_; }

protected:

    std::istream& stream_;

    int version_;

};

}

}

#endif
