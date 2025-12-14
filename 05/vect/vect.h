#include <iostream>

class vect {
	int _x;
	int _y;

	public:
	vect(int a, int b);
	vect(const vect& other);
	vect();

	int x();
	int y();

	vect operator+(const vect &x) const;
	vect operator+(int i) const;
	vect operator-(const vect &x) const;
	vect operator-(int i) const;
	vect operator*(const vect &x) const;
	vect operator*(int i) const;
	vect operator/(const vect &x) const;
	vect operator/(int i) const;

	vect operator-() const;
	vect operator++();
	vect &operator++(int);
	vect operator--();
	vect &operator--(int);
};

std::ostream &operator<<(std::ostream &os, vect &x);
