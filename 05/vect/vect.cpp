/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2025/12/14 17:22:17 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "Vect2.hpp"

vect2::vect2(const vect2 &v) {
	this->_x = v.x();
	this->_y = v.y();
}

vect2::vect2(int a, int b) {
	this->_x = a;
	this->_y = b;
}

vect2::vect2() {
	*this = vect2(0,0);
}

int vect2::x() const {
	return _x;
}

int vect2::y() const {
	return _y;
}

vect2 vect2::operator+(const vect2 &y) const {
	vect2 z;
	z._x = _x + y._x;
	z._y = _y + y._y;
	return z;
}

vect2 vect2::operator/(const vect2 &y) const {
	vect2 z;
	z._x = _x / y._x;
	z._y = _y / y._y;
	return z;
}

vect2 vect2::operator-(const vect2 &y) const {
	vect2 z;
	z._x = _x - y._x;
	z._y = _y - y._y;
	return z;
}

vect2 vect2::operator*(const vect2 &y) const {
	vect2 z;
	z._x = _x * y._x;
	z._y = _y * y._y;
	return z;
}

vect2 vect2::operator*(const int i) const {
	vect2 z;
	z._x = _x * i;
	z._y = _y * i;
	return z;
}

vect2 vect2::operator/(const int i) const {
	vect2 z;
	z._x = _x / i;
	z._y = _y / i;
	return z;
}

vect2 vect2::operator+(const int i) const {
	vect2 z;
	z._x = _x + i;
	z._y = _y + i;
	return z;
}

vect2 vect2::operator-(const int i) const {
	vect2 z;
	z._x = _x - i;
	z._y = _y - i;
	return z;
}

vect2 vect2::operator-() const {
	return vect2(-1 * _x, -1 * _y);
}

vect2 vect2::operator--() {
	vect2 v = vect2(_x - 1, _y - 1);
	return v;
}

vect2 vect2::operator++() {
	vect2 v = vect2(_x + 1, _y + 1);
	return v;
}

vect2 &vect2::operator--(int) {
	this->_x--;
	this->_y--;
	return *this;
}

vect2 &vect2::operator++(int) {
	this->_x++;
	this->_y++;
	return *this;
}

bool vect2::operator==(const vect2 &v) const {
	if (v.x() == _x && v.y() == _y)
		return true;
	return false;
}

bool vect2::operator!=(const vect2 &v) const {
	if (v.x() != _x || v.y() != _y)
		return true;
	return false;
}

vect2 &vect2::operator+=(int i) {
	this->_x += i;
	this->_y += i;
	return *this;
}

vect2 &vect2::operator-=(int i) {
	this->_x -= i;
	this->_y -= i;
	return *this;
}

vect2 &vect2::operator*=(int i) {
	this->_x *= i;
	this->_y *= i;
	return *this;
}

vect2 &vect2::operator/=(int i) {
	this->_x /= i;
	this->_y /= i;
	return *this;
}

vect2 &vect2::operator+=(const vect2 &v) {
	this->_x += v.x();
	this->_y += v.y();
	return *this;
}

vect2 &vect2::operator-=(const vect2 &v) {
	this->_x -= v.x();
	this->_y -= v.y();
	return *this;
}

vect2 &vect2::operator*=(const vect2 &v) {
	this->_x *= v.x();
	this->_y *= v.y();
	return *this;
}

vect2 &vect2::operator/=(const vect2 &v) {
	this->_x /= v.x();
	this->_y /= v.y();
	return *this;
}

int vect2::operator[](int i) const {
	if (i == 0)
		return _x;
	return _y;
}

int &vect2::operator[](int i) {
	if (i == 0)
		return _x;
	return _y;
}

vect2 operator+(int i, const vect2& v) {
	return vect2(v.x() + i, v.y() + i);
}

vect2 operator-(int i, const vect2& v) {
	return vect2(v.x() - i, v.y() + i);
}

vect2 operator*(int i, const vect2& v) {
	return vect2(v.x() * i, v.y() * i);
}

std::ostream &operator<<(std::ostream &os, vect2 const &x) {
	os << x.x() << " ";
	os << x.y() << "\n";
	return os;
}
