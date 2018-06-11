#include "tue/serialization/filesystem.h"

#include "tue/serialization/conversions.h"

#include <fstream>

namespace tue
{
namespace serialization
{

// ----------------------------------------------------------------------------------------------------

bool toFile(const Archive& a, const std::string& filename)
{
    // Open filestream
    std::ofstream f_out;
    f_out.open(filename.c_str(), std::ifstream::binary);

    if (!f_out.is_open())
        return false;

    // Copy archive content to file
    convert(a, f_out);

    // Close file
    f_out.close();

    return true;
}

// ----------------------------------------------------------------------------------------------------

bool fromFile(const std::string& filename, Archive& a)
{
    std::ifstream f_in;
    f_in.open(filename.c_str(), std::ifstream::binary);

    if (!f_in.is_open())
        return false;

    // Copy file content into archive
    convert(f_in, a);

    // Close file
    f_in.close();

    return true;
}

}

}
