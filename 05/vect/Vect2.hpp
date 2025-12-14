#include <iostream>

class vect2 {
	int _x;
	int _y;

	public:
	vect2(int a, int b);
	vect2(const vect2& other);
	vect2();

	int x() const;
	int y() const;

	vect2 operator+(const vect2 &x) const;
	vect2 operator+(int i) const;
	vect2 operator-(const vect2 &x) const;
	vect2 operator-(int i) const;
	vect2 operator*(const vect2 &x) const;
	vect2 operator*(int i) const;
	vect2 operator/(const vect2 &x) const;
	vect2 operator/(int i) const;

	vect2 operator-() const;
	vect2 operator++();
	vect2 &operator++(int);
	vect2 operator--();
	vect2 &operator--(int);

	bool operator==(const vect2 &v) const;
	bool operator!=(const vect2 &v) const;

	vect2 &operator-=(int i);
	vect2 &operator+=(int i);
	vect2 &operator*=(int i);
	vect2 &operator/=(int i);
	vect2 &operator-=(const vect2 &v);
	vect2 &operator+=(const vect2 &v);
	vect2 &operator*=(const vect2 &v);
	vect2 &operator/=(const vect2 &v);

	int operator[](int i) const;
	int &operator[](int i);

	friend vect2 operator+(int i, const vect2& vect);
	friend vect2 operator-(int i, const vect2& vect);
	friend vect2 operator*(int i, const vect2& vect);
	friend std::ostream& operator<<(std::ostream& os, const vect2& obj);
};
std::ostream& operator<<(std::ostream& os, vect2 const &obj);



