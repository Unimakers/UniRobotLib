#pragma once
#include <string>
#include <vector>
#include <functional>
#include <iostream>
/// @brief type of value
enum struct TYPE
{
    INT,
    STRING,
    DOUBLE,
    VECTORINT,
    VECTORDOUBLE,
    VECTORSTRING,
    CUSTOM
};
/// @brief Custom Data Config Type to get custom value types referenced by \ref TYPE
struct CustomDataConfigType
{
    TYPE type;
    int intValue;
    double doubleValue;
    std::vector<int> vectorIntValue;
    std::vector<double> vectorDoubleValue;
    std::vector<std::string> vectorStringValue;
    std::string stringValue;
    std::string customValue;
};

template <typename T, bool defaultSetLocked=true>
class ValType
{
public:
    bool locked = false;
    ValType() : getter([&]() -> T { return this->m_value; }),
                setter([&](T value){ this->m_value = value; }),
                m_value()
    {
        this->locked=defaultSetLocked;
    }
    T operator()(){ return getter();}
    void operator()(T value){ if(!locked)setter(value);}
    ValType operator=(T rhs){
        if(locked)return *this;
        setter(rhs);
        return *this;
    }
    T operator=(ValType rhs){
        return rhs.getter();
    }
    operator T(){
        return getter();
    }
    void setLocked(bool a){this->locked=a;};
    void securSetValue(T value, bool ok){if(ok)setter(value);}
    T& GetRawData(){return m_value;}
    private:
    T m_value;
    std::function<const T()> getter;
    std::function<void (T)> setter;
    template<typename TT>
    friend std::ostream & operator<<(std::ostream &os, const ValType<TT>& p);

    template <typename TT>
    friend std::istream & operator>>(std::istream &is, const ValType<TT>& p);

};