#ifndef TUE_SERIALIZATION_FILESYSTEM_H_
#define TUE_SERIALIZATION_FILESYSTEM_H_

#include <istream>
#include <vector>

#include "input_archive.h"
#include "output_archive.h"
#include "archive.h"

namespace tue
{
namespace serialization
{

bool toFile(const Archive& a, const std::string& filename);

bool fromFile(const std::string& filename, Archive& a);

}

}

#endif
