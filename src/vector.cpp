#include "hdr/coordinate_system.h"
#include "hdr/display.h"

const float PI = 3.14159265359;
const float ARROW_ANGLE = PI / 12;

//============================================//
//                  Vector2                   //
//============================================//

Vector2::Vector2() : x(0), y(0) {};
Vector2::Vector2(float x_component, float y_component) : x(x_component), y(y_component) {}
Vector2::Vector2(const Vector2& copy_vector) : x(copy_vector.x), y(copy_vector.y) {}

void Vector2::mulXY(float x_factor, float y_factor)
{
    x *= x_factor;
    y *= y_factor;
}

void Vector2::xy(float x, float y)
{
    this->x = x;
    this->y = y;
}

float Vector2::getLength() const
{
    return sqrt(x * x + y * y);
}

float Vector2::getAngle() const 
{   
    float length = getLength();

    return length > 0 ? acos(x / getLength()) : PI / 2;
}

Vector2& Vector2::operator=(const Vector2& copy_vector)
{
    x = copy_vector.x;
    y = copy_vector.y;

    return *this;
}

bool Vector2::operator==(const Vector2& rhs_vector) const
{
    return (x == rhs_vector.x && y == rhs_vector.y);

}
bool Vector2::operator!=(const Vector2& rhs_vector) const
{
    return (!this->operator==(rhs_vector));
}

Vector2& Vector2::operator*=(float scalar)
{
    xy(x * scalar, y * scalar);

    return *this;
}

Vector2& Vector2::operator/=(float scalar)
{
    xy(x / scalar, y / scalar);

    return *this;
}

Vector2& Vector2::operator+=(const Vector2& rhs_vector)
{
    xy(x + rhs_vector.x, y + rhs_vector.y);

    return *this;
}

Vector2& Vector2::operator-=(const Vector2& rhs_vector)
{
    xy(x - rhs_vector.x, y - rhs_vector.y);

    return *this;
}

Vector2 Vector2::operator+(const Vector2& rhs_vector) const
{
    Vector2 result_vector(x, y);

    result_vector += rhs_vector;

    return result_vector;
}

Vector2 Vector2::operator-(const Vector2& rhs_vector) const
{
    Vector2 result_vector(x, y);

    result_vector -= rhs_vector;

    return result_vector;
}

float Vector2::operator*(const Vector2& rhs_vector) const
{
    return (x * rhs_vector.x + y * rhs_vector.y);
}

Vector2 Vector2::operator*(float scalar) const
{
    return Vector2(x * scalar, y * scalar);
}

void Vector2::Rotate(float rotation_angle)
{   
    float sina = sin(rotation_angle);
    float cosa = cos(rotation_angle);

    float x_component = x;
    float y_component = y;

    x = x_component * cosa - y_component * sina;
    y = x_component * sina + y_component * cosa;    
}

void Vector2::Draw(Display& display, const CoordinateSystem& coord_system, 
                  const Vector2& begin_point, Color color, 
                  float arrow_factor_size)
{
    display.setColor(color);

    Vector2 first(begin_point); 

    Vector2 second(begin_point.x + x, begin_point.y + y);

    float sina = sin(ARROW_ANGLE);
    float cosa = cos(ARROW_ANGLE);

    float delta_x = deltaX(first, second);
    float delta_y = deltaY(first, second);

    float afs = arrow_factor_size;
    Vector2 first_arrow_point(second.x + afs * (delta_x * cosa + delta_y * sina),
                             second.y + afs * (delta_y * cosa - delta_x * sina));
    
    Vector2 second_arrow_point(second.x + afs * (delta_x * cosa - delta_y * sina),
                              second.y + afs * (delta_y * cosa + delta_x * sina));
    
    PixelPoint abs_first_vector_point = coord_system.getAbsolute(first);
    PixelPoint abs_second_vector_point = coord_system.getAbsolute(second);
    PixelPoint abs_first_arrow_point = coord_system.getAbsolute(first_arrow_point);
    PixelPoint abs_second_arrow_point = coord_system.getAbsolute(second_arrow_point);

    display.drawLine(abs_first_vector_point, abs_second_vector_point);
    display.drawLine(abs_second_vector_point, abs_first_arrow_point);
    display.drawLine(abs_second_vector_point, abs_second_arrow_point);
}

void Vector2::Normalize()
{   
    float length = getLength();

    this->operator/=(length);
}


//============================================//
//                  Vector3                   //
//============================================//

Vector3::Vector3() : Vector2(0, 0), z(0) {};
Vector3::Vector3(float x_component, float y_component, float z_component) : Vector2(0, 0), z(z_component) {}
Vector3::Vector3(const Vector3& copy_vector) : Vector2(copy_vector.x, copy_vector.y), z(copy_vector.z) {}

float Vector3::getLength() const { return sqrt(x * x + y * y + z * z); }

void Vector3::xyz(float x, float y, float z)
{
    this->Vector2::xy(x, y);

    this->z = z;
}

Vector3& Vector3::operator=(const Vector3& copy_vector)
{   
    x = copy_vector.x;
    y = copy_vector.y;
    z = copy_vector.z;

    return *this;
}

bool Vector3::operator==(const Vector3& rhs_vector) const 
{
    return (x == rhs_vector.x && y == rhs_vector.y && z == rhs_vector.z);
}

bool Vector3::operator!=(const Vector3& rhs_vector) const
{
    return (!this->operator==(rhs_vector));
}

Vector3& Vector3::operator*=(float scalar)
{
    xyz(x * scalar, y * scalar, z * scalar);

    return *this;
}

Vector3& Vector3::operator/=(float scalar)
{
    xyz(x / scalar, y / scalar, z / scalar);

    return *this;
}

Vector3& Vector3::operator+=(const Vector3& rhs_vector)
{
    xyz(x + rhs_vector.x, y + rhs_vector.y, z + rhs_vector.z);

    return *this;
}

Vector3& Vector3::operator-=(const Vector3& rhs_vector)
{
    xyz(x - rhs_vector.x, y - rhs_vector.y, z - rhs_vector.z);

    return *this;
}

Vector3 Vector3::operator+(const Vector3& rhs_vector) const
{
    Vector3 result_vector(x, y, z);

    result_vector += rhs_vector;

    return result_vector;
}

Vector3 Vector3::operator-(const Vector3& rhs_vector) const
{
    Vector3 result_vector(x, y, z);

    result_vector -= rhs_vector;

    return result_vector;
}

float Vector3::operator*(const Vector3& rhs_vector) const
{
    return (x * rhs_vector.x + y * rhs_vector.y + z * rhs_vector.z);
}


void Vector3::Normalize()
{   
    float length = getLength();

    this->operator/=(length);
}


float deltaX(const Vector2& vector_a, const Vector2& vector_b)
{
    return (vector_a.x - vector_b.x);
}

float deltaY(const Vector2& vector_a, const Vector2& vector_b)
{
    return (vector_a.y - vector_b.y);
}

float deltaZ(const Vector3& vector_a, const Vector3& vector_b)
{
    return (vector_a.z - vector_b.z);
}

Vector2 getRandomDirection()
{
    Vector2 direction(rand(), rand());
    direction.Normalize();

    return direction;
}

// float Vector3::angleXy const
// {
//     return acos(length() / lengthProjectionXy);
// }

// float Vector3::angleXZ() const
// {
//     return acos(length() / lengthProjectionXZ());
// }

// float Vector3::angleYZ() const
// {
//     return acos(length() / lengthProjectionYZ());
// }

// float Vector3::lengthProjectionXy const
// {
//     return sqrt(x_ * x_ + y_ * y_);
// }

// float Vector3::lengthProjectionXZ() const
// {
//     return sqrt(x_ * x_ + z_ * z_);
// }

// float Vector3::lengthProjectionYZ() const
// {
//     return sqrt(z_ * z_ + y_ * y_);
// }

// void Vector3::RotateX(float rotation_angle)
// {   
//     float sina = sin(rotation_angle);
//     float cosa = cos(rotation_angle);

//     float y_component = y_;
//     float z_component = z_;

//     y_ =   y_component * cosa - z_component * sina;
//     z_ = - y_component * sina + z_component * cosa;    
// }

// void Vector3::RotateY(float rotation_angle)
// {   
//     float sina = sin(rotation_angle);
//     float cosa = cos(rotation_angle);

//     float x_component = x_;
//     float z_component = z_;

//     x_ =   x_component * cosa + z_component * sina;
//     z_ = - x_component * sina + z_component * cosa;    
// }

// void Vector3::RotateZ(float rotation_angle)
// {   
//     float sina = sin(rotation_angle);
//     float cosa = cos(rotation_angle);

//     float x_component = x_;
//     float y_component = y_;

//     x_ = x_component * cosa - y_component * sina;
//     y_ = x_component * sina + y_component * cosa;    
// }