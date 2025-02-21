#pragma once

template<typename T>
struct  vec3
{
    T x;
    T y;
    T z; 
    vec3(): x(0.f), y(0.f), z(0.f){};
    vec3(T x_, T y_, T z_): x(x_), y(y_), z(z_) {};
};

