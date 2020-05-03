#pragma once
////////////////////////////////////////////////////////////////////////////////
/// Copyright (c) <TODO: year> by Alex Armstrong
///
/// @file cpp_class_skeleton.h
/// @author Alex Armstrong <alarmstr@cern.ch>
/// @date <TODO: 1 Jan 1111>
/// @brief <TODO: file description>
///
/// "Detailed description" goes here
/// @see http://www.stack.nl/~dimitri/doxygen/manual/commands.html
////////////////////////////////////////////////////////////////////////////////

// Important formatting guidelines
// - No 'using' directives in the header

// C++ std
#include <string>
#include <vector>

// 3rd-party libraries

// Project libraries

////////////////////////////////////////////////////////////////////////////////
namespace skeleton {

class ClassSkeleton : public ClassSkeletonBase {
  public:
    ClassSkeleton();
    virtual ~ClassSkeleton(){};

    // Setters
    void setInt(int usr_uint) { m_uint = usr_uint; }
    void setDouble(double usr_double) { m_double = usr_double; }
    void setStringVector(std::vector<std::string> usr_string_vector) { m_string_vector = usr_string_vector; }

    // Getters
    int getInt() const { return m_uint; }
    double getDouble() const { return m_double; }
    std::vector<std::string> getStringVector() const { return m_string_vector; }

    // Utilities
    int multiplyInt(int multiplier);

    void clear() {
        m_uint = 0;
        m_double = 0;
        m_string_vector.clear();
    }

  protected:

  private:
    // Class members
    int m_uint;
    double m_double;
    std::vector<std::string> m_string_vector;
};

} // namespace skeleton