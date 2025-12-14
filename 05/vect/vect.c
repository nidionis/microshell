/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2025/12/14 14:29:00 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "vect.h"

vect::vect(int a, int b) {
	this->_x = a;
	this->_y = b;
}

vect::vect() {
	*this = vect(0,0);
}

int vect::x() {
	return _x;
}

int vect::y() {
	return _y;
}

vect vect::operator+(const vect &y) const {
	vect z;
	z._x = _x + y._x;
	z._y = _y + y._y;
	return z;
}

vect vect::operator/(const vect &y) const {
	vect z;
	z._x = _x / y._x;
	z._y = _y / y._y;
	return z;
}

vect vect::operator-(const vect &y) const {
	vect z;
	z._x = _x - y._x;
	z._y = _y - y._y;
	return z;
}

vect vect::operator*(const vect &y) const {
	vect z;
	z._x = _x * y._x;
	z._y = _y * y._y;
	return z;
}

vect vect::operator*(const int i) const {
	vect z;
	z._x = _x * i;
	z._y = _y * i;
	return z;
}

vect vect::operator/(const int i) const {
	vect z;
	z._x = _x / i;
	z._y = _y / i;
	return z;
}

vect vect::operator+(const int i) const {
	vect z;
	z._x = _x + i;
	z._y = _y + i;
	return z;
}

vect vect::operator-(const int i) const {
	vect z;
	z._x = _x - i;
	z._y = _y - i;
	return z;
}

vect vect::operator-() const {
	return vect(-_x, -_y);
}

vect vect::operator--() {
	vect v = vect(_x - 1, _y - 1);
	return v;
}

vect vect::operator++() {
	vect v = vect(_x + 1, _y + 1);
	return v;
}

vect &vect::operator--(int) {
	this->_x--;
	this->_y--;
	return *this;
}

vect &vect::operator++(int) {
	this->_x++;
	this->_y++;
	return *this;
}

std::ostream &operator<<(std::ostream &os, vect &x) {
	os << x.x() << " ";
	os << x.y() << "\n";
	return os;
}
