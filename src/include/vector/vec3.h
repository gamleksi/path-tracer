//
// Created by aleksi on 5.11.2018.
//

#ifndef PATH_TRACER_VEC3_H
#define PATH_TRACER_VEC3_H

#include <ostream>
#include <cmath>

template <typename T>

class vec3 {

    public:
        vec3() = default;
        vec3(T e1, T e2, T e3) { e[0] = e1; e[1] = e2; e[2] = e3; };

        ~vec3() = default;

        T operator[](int i) const;
        T& operator[](int i);

        vec3& operator = (const vec3& v);

        vec3& operator += (const vec3& v);
        vec3& operator -= (const vec3& v);
        vec3& operator *= (const vec3& v);
        vec3& operator /= (const vec3& v);

        vec3& operator += (const T &a);
        vec3& operator -= (const T &a);
        vec3& operator *= (const T &a);
        vec3& operator /= (const T &a);

        T Norm2() const;
        vec3 Unit() const;
        vec3 Turn_unit();

        float Squared_length() {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        };

    private:
        T e[3];
};


/** External functions defintions

 Regular algebra +, -, /, * for vec2vec, scalar2vec, vec2scalar
 Returns a new vec3 object

 Scalar is required to be the same type as T!!

 OutStream (<<) operator produces:

    os << v[0] << " " << v[1] << " " << v[2];

 Cross product of two vectors:
 **/

template <typename T>
vec3<T> cross(const vec3<T> &v1, const vec3<T> &v2);

// Dot product of two vectors:
template <typename T>
T dot(const vec3<T> &v1, const vec3<T> &v2);

/**
 * Source code
 */

// Returns ith element
template <typename T>
T vec3<T>::operator[](int i) const {
    return e[i];
}

template <typename T>
T& vec3<T>::operator[](int i) {
    return e[i];
}

// Copy
template <typename T>
vec3<T>& vec3<T>::operator=(const vec3<T> &v) {
    e[0] = v[0];
    e[1] = v[1];
    e[2] = v[2];
    return *this;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const vec3<T> &v) {
    os << v[0] << " " << v[1] << " " << v[2];
    return os;
}

// Vector <> Vector Operators

template <typename T>

vec3<T>& vec3<T>::operator+=(const vec3<T> &v) {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
};

template <typename T>
vec3<T>& vec3<T>::operator-=(const vec3<T> &v) {
    e[0] -= v.e[0];
    e[1] -= v.e[1];
    e[2] -= v.e[2];
    return *this;
};

template <typename T>
vec3<T>& vec3<T>::operator*=(const vec3<T> &v) {
    e[0] *= v.e[0];
    e[1] *= v.e[1];
    e[2] *= v.e[2];
    return *this;
};

template <typename T>
vec3<T>& vec3<T>::operator/=(const vec3<T> &v) {
    e[0] /= v.e[0];
    e[1] /= v.e[1];
    e[2] /= v.e[2];
    return *this;
};


// Vector <> Scalar Operators

template <typename T>
vec3<T>& vec3<T>::operator+=(const T &a) {
    e[0] += a;
    e[1] += a;
    e[2] += a;
    return *this;
};


template <typename T>
vec3<T>& vec3<T>::operator-=(const T &a) {
    e[0] -= a;
    e[1] -= a;
    e[2] -= a;
    return *this;
};

template <typename T>
vec3<T>& vec3<T>::operator*=(const T &a) {
    e[0] *= a;
    e[1] *= a;
    e[2] *= a;
    return *this;
};

template <typename T>
vec3<T>& vec3<T>::operator/=(const T &a) {
    e[0] /= a;
    e[1] /= a;
    e[2] /= a;
    return *this;
};

template <typename T>
vec3<T> operator-(const vec3<T> &v1) {
    return vec3<T>(-v1[0], -v1[1], -v1[2]);
};

template <typename T>
vec3<T> operator+(const vec3<T> &v1) {
    return vec3<T>(v1[0], v1[1], v1[2]);
};

// Vector <> Vector Algebra

template <typename T>
vec3<T> operator+(const vec3<T> &v1, const vec3<T> &v2) {
    return vec3<T> (v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2]);
};

template <typename T>
vec3<T> operator-(const vec3<T> &v1, const vec3<T> &v2) {
    return vec3<T> (v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2]);
};

template <typename T>
vec3<T> operator*(const vec3<T> &v1, const vec3<T> &v2) {
    return vec3<T> (v1[0] * v2[0], v1[1] * v2[1], v1[2] * v2[2]);
};

template <typename T>
vec3<T> operator/(const vec3<T> &v1, const vec3<T> &v2) {
    return vec3<T> (v1[0] / v2[0], v1[1] / v2[1], v1[2] / v2[2]);
};


// Vector <> Scalar Algebra

template <typename T>
vec3<T> operator+(const vec3<T> &v1, const T &a) {
    return vec3<T> (v1[0] + a, v1[1] + a, v1[2] + a);
};

template <typename T>
vec3<T> operator-(const vec3<T> &v1, const T &a) {
    return vec3<T> (v1[0] - a, v1[1] - a, v1[2] - a);
};

template <typename T>
vec3<T> operator*(const vec3<T> &v1, const T &a) {
    return vec3<T> (v1[0] * a, v1[1] * a, v1[2] * a);
};

template <typename T>
vec3<T> operator/(const vec3<T> &v1, const T &a) {
    return vec3<T> (v1[0] / a, v1[1] / a, v1[2] / a);
};

// Scalar <> Vector Algebra

template <typename T>
vec3<T> operator+(const T &a, const vec3<T> &v1) {
    return v1 + a;
};

template <typename T>
vec3<T> operator-(const T &a, const vec3<T> &v1) {
    return -v1 + a;
};

template <typename T>
vec3<T> operator*(const T &a, const vec3<T> &v1) {
    return v1 * a;
};

template <typename T>
vec3<T> operator/(const T &a, const vec3<T> &v1) {
    return v1 / a;
};

//Cross product
template <typename T>
vec3<T> cross(const vec3<T> &v1, const vec3<T> &v2){
    vec3<T> vc(v1[1]*v2[2]-v1[2]*v2[1],v1[2]*v2[0]-v1[0]*v2[2],v1[0]*v2[1]-v1[1]*v2[0]);
    return vc;
};

// Dot product
template <typename T>
T Dot(const vec3<T> &v1, const vec3<T> &v2) {
    return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
};

// Norm
template <typename T>
T vec3<T>::Norm2() const {
    return std::sqrt(dot(*this, *this));
};

//unit vector
template <typename T>
vec3<T> vec3<T>::Unit() const {
    return *this / this->norm2();
};

// make unit
template <typename T>
vec3<T> vec3<T>::Turn_unit() {
    return *this /= this->norm2();
};

#endif //PATH_TRACER_VEC3_H

