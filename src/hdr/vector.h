#pragma once

#include <math.h>
#include <stdio.h>

const float ARROW_FACTOR_SIZE = 0.1;

struct Color;
class CoordinateSystem;
class Display;


class Vector2
{
public:
    
    float x;
    float y;

public:

    Vector2();
    Vector2(float x_component, float y_component);
    Vector2(const Vector2& copy_vector);

    void mulXY(float x_factor, float y_factor);
    void xy(float x, float y);

    float getLength() const;
    float getAngle() const;

    Vector2& operator=(const Vector2& copy_vector);

    bool operator==(const Vector2& rhs_vector) const;
    bool operator!=(const Vector2& rhs_vector) const;

    Vector2& operator*=(float scalar);
    Vector2& operator/=(float scalar);

    Vector2& operator+=(const Vector2& rhs_vector);
    Vector2& operator-=(const Vector2& rhs_vector);

    Vector2 operator+(const Vector2& rhs_vector) const;
    Vector2 operator-(const Vector2& rhs_vector) const;

    float operator*(const Vector2& rhs_vector) const;
    Vector2 operator*(float scalar) const;
    
    void Rotate(float angle);
    
    void Draw(Display& display, const CoordinateSystem& coord_system, 
              const Vector2& begin_point, Color color, 
              float arrow_factor_size = ARROW_FACTOR_SIZE);

    void Normalize();

    ~Vector2() = default;

};

class Vector3 : public Vector2
{   
public:

    float z;

public:

    Vector3();
    Vector3(float x_component, float y_component, float z_component);
    Vector3(const Vector3& copy_vector);

    float getLength() const;

    void xyz(float x, float y, float z);

    Vector3& operator=(const Vector3& copy_vector);

    bool operator==(const Vector3& rhs_vector) const;
    bool operator!=(const Vector3& rhs_vector) const;

    Vector3& operator*=(float scalar);
    Vector3& operator/=(float scalar);

    Vector3& operator+=(const Vector3& rhs_vector);
    Vector3& operator-=(const Vector3& rhs_vector);

    Vector3 operator+(const Vector3& rhs_vector) const;
    Vector3 operator-(const Vector3& rhs_vector) const;

    float operator*(const Vector3& rhs_vector) const;
        
    void Normalize();
    
    ~Vector3() = default;
};

float deltaX(const Vector2& vector_a, const Vector2& vector_b);
float deltaY(const Vector2& vector_a, const Vector2& vector_b);
float deltaZ(const Vector3& vector_a, const Vector3& vector_b);

Vector2 getRandomDirection();


// float getAngleXY() const;
// float getAngleXZ() const;
// float getAngleYZ() const;

// float GetLengthProjectionXY() const;
// float GetLengthProjectionXZ() const;
// float GetLengthProjectionYZ() const;

// void RotateX(float angle);
// void RotateY(float angle);
// void RotateZ(float angle);