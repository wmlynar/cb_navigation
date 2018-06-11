#include "tue/serialization/conversions.h"
#include "tue/serialization/output_archive.h"

#include <string.h>   // memcpy

namespace tue
{
namespace serialization
{

// ----------------------------------------------------------------------------------------------------

void convert(Archive& a, std::vector<unsigned char>& data)
{
    int version = a.version();
    convert(a.stream(), data, sizeof(version));

    // Fill version bytes
    memcpy(&data[0], (char*)&version, sizeof(version));
}

// ----------------------------------------------------------------------------------------------------

void convert(const Archive& a, std::ostream& out)
{
    // Write the version to out
    OutputArchive a_out(out);

    // Write data to out
    out << a.stream().rdbuf();
}

// ----------------------------------------------------------------------------------------------------

void convert(std::istream& s, Archive& a)
{
    std::vector<unsigned char> data;
    convert(s, data);
    convert(data, a);
}

// ----------------------------------------------------------------------------------------------------

void convert(std::istream& s, std::vector<unsigned char>& data, int d_offset)
{   
    // get its size:
    s.seekg(0, std::ios::end);
    int size = s.tellg();
    s.seekg(0, std::ios::beg);

    data.resize(size + d_offset);
    s.read((char*)&data[d_offset], size);
}

// ----------------------------------------------------------------------------------------------------

void convert(std::vector<unsigned char>& data, Archive& a)
{
    // Read version (int)
    int version;
    memcpy((char*)&(a.version_), &data[0], sizeof(version));

    // Read the rest
    convert(data, a.stream(), sizeof(version));
}

// ----------------------------------------------------------------------------------------------------

void convert(const std::vector<unsigned char>& data, std::ostream& s, int d_offset)
{   
    s.write((char*)&data[d_offset], data.size() - d_offset);
}

}

}
