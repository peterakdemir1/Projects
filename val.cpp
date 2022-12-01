#include <iostream>
#include <string>
#include <vector> 
using namespace std; 

#include "val.h"

Value Value::operator+(const Value& op) const{
    if (this->IsInt() && op.IsInt())
        return Value(this->GetInt() + op.GetInt());
    else if (this->IsInt() && op.IsReal())
        return Value(this->GetInt() + op.GetReal());
    else if (this->IsReal() && op.IsInt())
        return Value(this->GetReal() + op.GetInt());
    else if (this->IsReal() && op.IsReal())
        return Value(this->GetReal() + op.GetReal());
    else if (this->IsString() && op.IsString())
        return Value(this->GetString() + op.GetString());
    return Value();
}

Value Value::operator*(const Value& op) const{
    if (this->IsInt() && op.IsInt())
        return Value(this->GetInt() * op.GetInt());
    else if (this->IsInt() && op.IsReal())
        return Value(this->GetInt() * op.GetReal());
    else if (this->IsReal() && op.IsInt())
        return Value(this->GetReal() * op.GetInt());
    else if (this->IsReal() && op.IsReal())
        return Value(this->GetReal() * op.GetReal());
    return Value();
}

Value Value::operator==(const Value& op) const{
    if (this->IsInt() && op.IsInt())
        return Value(this->GetInt() == op.GetInt());
    else if (this->IsInt() && op.IsReal())
        return Value(this->GetInt() == op.GetReal());
    else if (this->IsReal() && op.IsInt())
        return Value(this->GetReal() == op.GetInt());
    else if (this->IsReal() && op.IsReal())
        return Value(this->GetReal() == op.GetReal());
    else if (this->IsString() && op.IsString())
        return Value(this->GetString() == op.GetString());
    return Value();
}

    
Value Value::operator-(const Value& op) const{
    if (this->IsInt() && op.IsInt())
        return Value(this->GetInt() - op.GetInt());
    else if (this->IsInt() && op.IsReal())
        return Value(this->GetInt() - op.GetReal());
    else if (this->IsReal() && op.IsInt())
        return Value(this->GetReal() - op.GetInt());
    else if (this->IsReal() && op.IsReal())
        return Value(this->GetReal() - op.GetReal());
    return Value();
}
    
Value Value::operator/(const Value& op) const{
    if (this->IsInt() && op.IsInt())
        return Value(this->GetInt() / op.GetInt());
    else if (this->IsInt() && op.IsReal())
        return Value(this->GetInt() / op.GetReal());
    else if (this->IsReal() && op.IsInt())
        return Value(this->GetReal() / op.GetInt());
    else if (this->IsReal() && op.IsReal())
        return Value(this->GetReal() / op.GetReal());
    return Value();
}
    
Value Value::operator>(const Value& op) const{
    if (this->IsInt() && op.IsInt())
        return Value(this->GetInt() > op.GetInt());
    else if (this->IsInt() && op.IsReal())
        return Value(this->GetInt() > op.GetReal());
    else if (this->IsReal() && op.IsInt())
        return Value(this->GetReal() > op.GetInt());
    else if (this->IsReal() && op.IsReal())
        return Value(this->GetReal() > op.GetReal());
    else if (this->IsString() && op.IsString())
        return Value(this->GetString() > op.GetString());
    return Value();
}

Value Value::operator<(const Value& op) const{
    if (this->IsInt() && op.IsInt())
        return Value(this->GetInt() < op.GetInt());
    else if (this->IsInt() && op.IsReal())
        return Value(this->GetInt() < op.GetReal());
    else if (this->IsReal() && op.IsInt())
        return Value(this->GetReal() < op.GetInt());
    else if (this->IsReal() && op.IsReal())
        return Value(this->GetReal() < op.GetReal());
    else if (this->IsString() && op.IsString())
        return Value(this->GetString() < op.GetString());
    return Value();
}