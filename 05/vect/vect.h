#include <iostream>
class vect {
	public:
	int a;
	int b;
	vect(int a, int b);
	vect();

	vect operator+(const vect &x);
};
std::ostream &operator<<(std::ostream &os, vect &x);
