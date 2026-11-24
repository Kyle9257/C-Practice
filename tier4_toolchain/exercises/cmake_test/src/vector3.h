#include <iostream>

class vector3
{
private:
    double x_ = 0, y_ = 0, z_ = 0;
public:
    vector3(double x,double y,double z);

    vector3 operator+(const vector3 & vec){
        return { x_ + vec.x_ , y_ + vec.y_ , z_ + vec.z_ };
    };

    double dot( const vector3 &vec)const;

    ~vector3();
};

