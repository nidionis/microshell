#include "Vect2.hpp"
#include <iostream>

vect2::vect2(int x, int y) : _x(x), _y(y){}
vect2::vect2(const vect2& other) : _x(other._x), _y(other._y){}
vect2& vect2::operator=(const vect2& rhs){
    if (this != &rhs){
        _x = rhs._x;
        _y = rhs._y;
    }
    return *this;
}
vect2::~vect2(){}

int& vect2::operator[](const int i){
    return  (i == 0) ? _x : _y;
}

int vect2::operator[](int i) const{
    return  (i == 0) ? _x : _y;
}

// Binary arithmetic operators with scalar (MUST BE CONST)
vect2 vect2::operator+(int i) const{
    vect2 vec(_x + i, _y + i);
    return vec;
}

vect2 vect2::operator-(int i) const{
    vect2 vec(_x - i, _y - i);
    return vec;
}

vect2 vect2::operator*(int i) const{
    vect2 vec(_x * i, _y * i);
    return vec;
}

// Binary arithmetic operators with vector (MUST BE CONST)
vect2 vect2::operator+(const vect2& vec) const{
    vect2 vecr(_x + vec._x, _y + vec._y);
    return vecr;
}

vect2 vect2::operator-(const vect2& vec) const{
    vect2 vecr(_x - vec._x, _y - vec._y);
    return vecr;
}

vect2 vect2::operator*(const vect2& vec) const{
    vect2 vecr(_x * vec._x, _y * vec._y);
    return vecr;
}

// Unary negation operator (MUST BE CONST)
vect2 vect2::operator-() const{
    vect2 vec(-_x, -_y);
    return vec;
}

vect2 vect2::operator++(int){
    vect2 vec(_x, _y);
    _x++;
    _y++;
    return vec;
}
vect2& vect2::operator++(){
    this->_x++;
    this->_y++;
    return *this;
}
vect2 vect2::operator--(int){
    vect2 vec(_x, _y);
    _x--;
    _y--;
    return vec;
}

vect2& vect2::operator--(){
    this->_x--;
    this->_y--;
    return *this;
}

// Compound assignment operators with scalar
vect2& vect2::operator+=(int i){
    this->_x += i;
    this->_y += i;
    return *this;
}

vect2& vect2::operator-=(int i){
    this->_x -= i;
    this->_y -= i;
    return *this;
}

vect2& vect2::operator*=(int i){
    this->_x *= i;
    this->_y *= i;
    return *this;
}

// Compound assignment operators with vector
vect2& vect2::operator+=(const vect2& vec){
    _x += vec._x;
    _y += vec._y;
    return *this;
}

vect2& vect2::operator-=(const vect2& vec){
    this->_x -= vec._x;
    this->_y -= vec._y;
    return *this;
}

// Comparison operators (MUST BE CONST)
bool vect2::operator==(const vect2& vec) const{
    return (_x == vec._x && _y == vec._y);
}

bool vect2::operator!=(const vect2& vec) const{
    return (_x != vec._x || _y != vec._y);
}

// Friend functions for reverse scalar operations
vect2 operator+(int i, const vect2& vect){
    vect2 vec(i + vect._x, i + vect._y);
    return vec;
}

vect2 operator-(int i, const vect2& vect){
    vect2 vec(i - vect._x, i - vect._y);
    return vec;
}

vect2 operator*(int i, const vect2& vect){
    vect2 vec(i * vect._x, i * vect._y);
    return vec;
}

void vect2::print(std::ostream& os) const{
    os << "{" << _x << ", " << _y << "}";  // NO std::endl here!
}

std::ostream& operator<<(std::ostream& os, const vect2& obj){
    obj.print(os);
    return os;
}