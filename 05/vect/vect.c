/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2025/12/14 12:25:30 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "vect.h"

vect::vect(int a, int b) {
	this->a = a;
	this->b = b;
}

vect::vect() {
	*this = vect(0,0);
}

vect vect::operator+(const vect &y) {
	vect z;
	z.a = a + y.a;
	z.b = b + y.b;
	return z;
}
