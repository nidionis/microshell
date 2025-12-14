#pragma once
#include <iostream>

class vect2 {
	private:
		int _x ;
		int _y ;

	public:
		vect2(int x, int y);
		vect2(const vect2& other);
		vect2& operator=(const vect2& other);
		~vect2();

	//[]
		int operator[]( int i)const;
		int& operator[]( int i);

	//Arithmetic with ints
		vect2 operator+(int i)const;
		vect2 operator-(int i)const;
		vect2 operator*(int i)const;

	//Arithmetic with objects
		vect2 operator+(const vect2& vect)const;
		vect2 operator-(const vect2& vect)const;
		vect2 operator*(const vect2& vect)const;

	//increment/decrement
		vect2 operator-()const;
		vect2 operator++(int);
		vect2& operator++();
		vect2 operator--(int);
		vect2& operator--();

	//comparison
		bool operator==(const vect2& vect)const;
		bool operator!=(const vect2& vect)const;

	//compound operators
		vect2& operator+=(const vect2& vect);
		vect2& operator-=(const vect2& vect);
		vect2& operator+=(int i);
		vect2& operator-=(int i);
		vect2& operator*=(int i);

	//print
		void print(std::ostream& os)const;

	//friends!
		friend vect2 operator+(int i, const vect2& vect);
		friend vect2 operator-(int i, const vect2& vect);
		friend vect2 operator*(int i, const vect2& vect);
		friend std::ostream& operator<<(std::ostream& os, const vect2& obj);

};