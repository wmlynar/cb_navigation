#ifndef TUE_SERIALIZATION_CONVERSIONS_H_
#define TUE_SERIALIZATION_CONVERSIONS_H_

#include <istream>
#include <vector>

#include "input_archive.h"
#include "output_archive.h"
#include "archive.h"

namespace tue
{
namespace serialization
{


// ----------------------------------------------------------------------------------------------------

void convert(Archive& a, std::vector<unsigned char>& data);

void convert(const Archive& a, std::ostream& out);

void convert(std::istream& s, Archive& a);

void convert(std::istream& s, std::vector<unsigned char>& data, int d_offset = 0);

void convert(std::vector<unsigned char>& data, Archive& a);

void convert(const std::vector<unsigned char>& data, std::ostream& s, int d_offset = 0);


}

}

#endif
