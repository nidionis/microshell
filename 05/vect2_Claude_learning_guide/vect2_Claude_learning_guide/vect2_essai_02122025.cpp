#include "vect2_essai_02122025.hpp"

		vect2::vect2(int x, int y) : _x(x), _y(y){}
		vect2::vect2(const vect2& other): _x(other._x), _y(other._y){}
		vect2& vect2::operator=(const vect2& other){
			if (this != &other)
			{
				_x = other._x;
				_y = other._y;
			}
			return *this;
		}
		vect2::~vect2(){}

	//[]
		int vect2::operator[](int i)const{
			return(i == 0? _x : _y);
		}
		int& vect2::operator[]( int i){
			return(i == 0? _x : _y);
		}

	//Arithmetic with ints
		vect2 vect2::operator+(int i)const{
			return (vect2(_x +i, _y +i));
		}
		vect2 vect2::operator-(int i)const{
			return (vect2(_x - i, _y - i));

		}
		vect2 vect2::operator*(int i)const{
			return (vect2(_x *i, _y *i));
		}

	//Arithmetic with objects
		vect2 vect2::operator+(const vect2& vect)const{
			return (vect2(_x + vect._x, _y + vect._y));
		}

		vect2 vect2::operator-(const vect2& vect)const{
			return (vect2(_x - vect._x, _y - vect._y));
		}

		vect2 vect2::operator*(const vect2& vect)const{
			return (vect2(_x * vect._x, _y * vect._y));
		}

	//increment/decrement
		vect2 vect2::operator-()const{
			return (vect2(-_x, -_y));
		}
		vect2 vect2::operator++(int){
			vect2 temp(_x, _y);
			_x++;
			_y++;
			return temp;
		}
		vect2& vect2::operator++(){
			this-> _x++;
			this-> _y++;
			return *this;
		}
		vect2 vect2::operator--(int){
			vect2 temp(_x, _y);
			_x--;
			_y--;
			return temp;
		}
	
		vect2& vect2::operator--(){
			this-> _x--;
			this-> _y--;
			return *this;
		}

	//comparison
		bool vect2::operator==(const vect2& vect)const{
			return (_x == vect._x && _y == vect._y);
		}
		bool vect2::operator!=(const vect2& vect)const{
			return (_x != vect._x || _y != vect._y);
		}

	//compound operators
		vect2& vect2::operator+=(const vect2& vect){
			_x = _x + vect._x;
			_y = _y + vect._y;
			return *this;
		}
		vect2& vect2::operator-=(const vect2& vect){
			_x = _x - vect._x;
			_y = _y - vect._y;
			return *this;
		}
		vect2& vect2::operator+=(int i){
			_x = _x + i;
			_y = _y + i;
			return *this;
		}
		vect2& vect2::operator-=(int i){
			_x = _x - i;
			_y = _y - i;
			return *this;
		}
		vect2& vect2::operator*=(int i){
			_x = _x * i;
			_y = _y * i;
			return *this;
		}

	//print
		void vect2::print(std::ostream& os)const{
			os<<"{" << _x << ", " << _y << "}";
		}

	//friends!
		vect2 operator+(int i, const vect2& vect){
			return (vect2(i + vect._x, i + vect._y));
		}
		vect2 operator-(int i, const vect2& vect){
			return (vect2(i - vect._x, i - vect._y));
		}
		vect2 operator*(int i, const vect2& vect){
			return (vect2(i * vect._x, i * vect._y));
		}
		std::ostream& operator<<(std::ostream& os, const vect2& obj){
			obj.print(os);
			return os;
		}
