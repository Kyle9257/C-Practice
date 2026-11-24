#include "vector3.h"

vector3::vector3(double x,double y,double z)
:x_(x),y_(y),z_(z)
{
}

vector3::~vector3()
{
}

double vector3::dot(const vector3& vec)const{
    return x_ * vec.x_ + y_ * vec.y_ + z_ + vec.z_;
}