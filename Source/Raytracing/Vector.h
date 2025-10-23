#pragma once

#include <cmath>
#include <iostream>

class vec3 
{
public:
    //creates a double float array variable with a size of 3 indexes.
    double e[3];

    //constructors
    vec3() 
        : e{ 0,0,0 } 
    {
        //empty function body
    }
    vec3(double e0, double e1, double e2) 
        : e{ e0, e1, e2 } 
    {
        //empty function body
    }

    //these functions return specific values in the array.
    double x() const 
    { 
        return e[0]; 
    }
    double y() const 
    { 
        return e[1]; 
    }
    double z() const 
    { 
        return e[2]; 
    }

    //unary(single input/variable) negation
    // This returns a copy of the vec3 class type object
    //-a
    vec3 operator-() const 
    {
        return vec3(-e[0], -e[1], -e[2]); 
    }
    //read access on const vec, if the object is const then the compiler will automatically only use this one
    double operator[](int i) const 
    { 
        return e[i]; 
    }
    //read/write on mutable vec, if the object is not const then the compiler automatically prefers this one
    //the reference declarator lets you overwrite the actual object array element
    //a[i]
    double& operator[](int i) 
    { 
        return e[i]; 
    }

    // a += b  -> a.operator+=(b);
    // 
    //const vec3& v -> the reference is just to avoid unecesary overhead from copying
    //
    //const vec3& v -> insures the b read only
    vec3& operator+=(const vec3& v) 
    {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this; //C++ give you this special pointer by default. *this == the current instance of vec3
    }

    // a *= number#
    vec3& operator*=(double t) 
    {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    // a /= mumber#
    vec3& operator/=(double t) 
    {
        return *this *= 1 / t;//this makes use of a previously defined Assighnment Operator
    }

    double length() const 
    {
        //
        return std::sqrt(length_squared());
    }

    //x^2+y^2+z^2
    double length_squared() const 
    {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }
};

// point3 is just an alias for vec3, but useful for geometric clarity in the code.
using point3 = vec3;
using Color = vec3;

// 
inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

//We put this function outside the class, because we are working with 2 equal outsider object instances. So its a free function for symmetry with the operands.
inline vec3 operator+(const vec3& u, const vec3& v) 
{
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);//creates a new object, so u dont modify the operands
}

inline vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

// #*a number * object
inline vec3 operator*(double t, const vec3& v) 
{
    return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

// a*# object * number, you need this to be able to multiply in the reverse order.
inline vec3 operator*(const vec3& v, double t) 
{
    return t * v;
}

// a/#
inline vec3 operator/(const vec3& v, double t) {
    return (1 / t) * v;
}

inline double dot(const vec3& u, const vec3& v) {
    return u.e[0] * v.e[0]
        + u.e[1] * v.e[1]
        + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
        u.e[2] * v.e[0] - u.e[0] * v.e[2],
        u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector(const vec3& v) {
    return v / v.length(); // object / double 
}