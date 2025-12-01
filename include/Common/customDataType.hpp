#pragma once
#include <string>
#include <vector>
/// @brief type of value
enum struct TYPE{
    INT,STRING,DOUBLE,VECTORINT,VECTORDOUBLE,VECTORSTRING,CUSTOM
};
/// @brief Custom Data Config Type to get custom value types referenced by \ref TYPE
struct CustomDataConfigType{
    TYPE type;
    int intValue;
    double doubleValue;
    std::vector<int> vectorIntValue;
    std::vector<double> vectorDoubleValue;
    std::vector<std::string> vectorStringValue;
    std::string stringValue;
    std::string customValue;

};