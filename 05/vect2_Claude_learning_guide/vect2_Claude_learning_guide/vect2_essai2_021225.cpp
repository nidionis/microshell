#include "vect2_essai2_021225.hpp"

vect2::vect2(int x, int y): _x(x), _y(y){}
vect2::vect2(const vect2& other): _x(other._x), _y(other._y){}
vect2& vect2::operator=(const vect2& rhs){
	if(this!= &rhs)
	{
		_x = rhs._x;
		_y = rhs._y;
	}
	return *this;
}
vect2::~vect2(){}

int& vect2::operator[](int i){
	return(i == 0? _x : _y);
}
int vect2::operator[](int i) const{
	return(i == 0? _x : _y);
}

vect2 vect2::operator+(int i)const{
	return(vect2(_x + i, _y + i));
}
vect2 vect2::operator- (int i)const{
	return(vect2(_x - i, _y - i));
}
vect2 vect2::operator*(int i)const{
	return(vect2(_x * i, _y * i));
}

vect2 vect2::operator*(const vect2& vect)const{
	return(vect2(_x * vect._x, _y * vect._y));
}

vect2 vect2::operator+(const vect2& vect)const{
	return(vect2(_x + vect._x, _y + vect._y));
}

vect2 vect2::operator-(const vect2& vect)const{
	return(vect2(_x - vect._x, _y - vect._y));
}


//inc/dec
vect2& vect2::operator++(){
	_x++;
	_y++;
	return *this;
}
vect2 vect2::operator++(int){
	vect2 vect(_x, _y);
	this->_x++;
	this->_y++;
	return vect;
}
vect2& vect2::operator--(){
	_x--;
	_y--;
	return *this;
}

vect2 vect2::operator--(int){
	vect2 vect(_x, _y);
	this->_x--;
	this->_y--;
	return vect;
}

//comp
bool vect2::operator==(const vect2& vect)const{
	return(this->_x == vect._x && this->_y == vect._y);
}
bool vect2::operator!=(const vect2& vect)const{
	return(this->_x != vect._x || this->_y != vect._y);
}

//compound ops + unary-
vect2 vect2::operator-()const{
	vect2 vect(-_x, -_y);
	return vect;
}
vect2& vect2::operator+=(const vect2& vect){
	this->_x += vect._x;
	this->_y += vect._y;
	return *this;
}
vect2& vect2::operator-=(const vect2& vect){
	this->_x -= vect._x;
	this->_y -= vect._y;
	return *this;
}
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

//print
void vect2::print(std::ostream& os)const{
	os << "{" << _x << ", " << _y << "}";
}

//friends!
vect2 operator+(int i, const vect2& vect){
	vect2 vect(i + vect._x, i + vect._y);
	return vect;
}
vect2 operator-(int i, const vect2& vect){
	vect2 vect(i - vect._x, i - vect._y);
	return vect;
}
vect2 operator*(int i, const vect2& vect){
	vect2 vect(i * vect._x, i * vect._y);
	return vect;
}
std::ostream& operator<<(std::ostream& os, const vect2& obj){
	obj.print(os);
	return os;
}