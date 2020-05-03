#include "cpp_class_skeleton.h"
////////////////////////////////////////////////////////////////////////////////
/// Copyright (c) <TODO: year> by Alex Armstrong
///
/// @file cpp_class_skeleton.h
/// @author Alex Armstrong <alarmstr@cern.ch>
/// @date <TODO: 1 Jan 1111>
/// @brief See cpp_class_skeleton.h
////////////////////////////////////////////////////////////////////////////////

// C++ std
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

// 3rd-party libraries

// Project libraries

////////////////////////////////////////////////////////////////////////////////
namespace skeleton {

ClassSkeleton::ClassSkeleton() {};

ClassSkeleton::multiplyInt(int multiplier) {
    return getInt() * multiplier;
}

} // namespace skeleton
