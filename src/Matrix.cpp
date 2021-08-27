/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Matrix.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 11:14:54 by pitriche          #+#    #+#             */
/*   Updated: 2021/08/27 16:12:07 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Matrix.hpp"
#include "Utils.hpp"	/* round */
#include <cmath>		/* tan */

Matrix::Matrix(void)
{
	for (unsigned i = 0; i < 16; ++i)
		(*this)[i] = (i % 5 == 0) ? 1.0f : 0.0f;
}
Matrix::Matrix(const Matrix &src) { *this = src; }
Matrix::~Matrix(void) { }

void	Matrix::transpose(void)
{
	Matrix	tmp;

	tmp = *this;
	(*this)[1] = tmp[4];
	(*this)[2] = tmp[8];
	(*this)[3] = tmp[12];

	(*this)[4] = tmp[1];
	(*this)[6] = tmp[9];
	(*this)[7] = tmp[13];

	(*this)[8] = tmp[2];
	(*this)[9] = tmp[6];
	(*this)[11] = tmp[14];

	(*this)[12] = tmp[3];
	(*this)[13] = tmp[7];
	(*this)[14] = tmp[11];
}

void	Matrix::set_projection(float fov, float near, float far, float aspect)
{
	float	e;

	e = 1 / (std::tan(fov / 2.0f));
	(*this) = Matrix();
	(*this)[0] = e / aspect;
	(*this)[5] = e;
	(*this)[10] = (near + far) / (near - far);
	(*this)[11] = (2 * near * far) / (near - far);
	(*this)[14] = -1;
}

Matrix	&Matrix::translate(float x, float y, float z)
{
	(*this)[3] += x;
	(*this)[7] += y;
	(*this)[11] += z;
	return (*this);
}

/* ########################################################################## */

Matrix	&Matrix::rotate(float x, float y, float z)
{
	Matrix rot_x;
	Matrix rot_y;
	Matrix rot_z;

	rot_x._rotate_x(x);
	rot_y._rotate_y(y);
	rot_z._rotate_z(z);

	/* Z * X * Y */
	*this = rot_z * rot_x * rot_y * (*this);
	return (*this);
}

/* set identity matrix to rotation matrix on x axis */
void	Matrix::_rotate_x(float angle)
{
	(*this)[5] = cosf(angle);
	(*this)[6] = -sinf(angle);
	(*this)[9] = sinf(angle);
	(*this)[10] = cosf(angle);
}

/* set identity matrix to rotation matrix on y axis */
void	Matrix::_rotate_y(float angle)
{
	(*this)[0] = cosf(angle);
	(*this)[2] = sinf(angle);
	(*this)[8] = -sinf(angle);
	(*this)[10] = cosf(angle);
}

/* set identity matrix to rotation matrix on z axis */
void	Matrix::_rotate_z(float angle)
{
	(*this)[0] = cosf(angle);
	(*this)[1] = -sinf(angle);
	(*this)[4] = sinf(angle);
	(*this)[5] = cosf(angle);
}

/* ########################################################################## */

Matrix	&Matrix::operator=(const Matrix &rhs)
{
	for (unsigned i = 0; i < 16; ++i)
		(*this)[i] = rhs[i];
	return (*this);
}

/* matrix multiplication */
Matrix	Matrix::operator*(const Matrix &rhs) const
{
	Matrix res;

	for (unsigned j = 0; j < 4; ++j)
		for (unsigned i = 0; i < 4; ++i)
			res[j * 4 + i] =
			(*this)[j * 4 + 0] * rhs[0 * 4 + i] +
			(*this)[j * 4 + 1] * rhs[1 * 4 + i] +
			(*this)[j * 4 + 2] * rhs[2 * 4 + i] +
			(*this)[j * 4 + 3] * rhs[3 * 4 + i];
	return (res);
}

/* /!\ use only for model scaling */
Matrix	Matrix::operator*(float rhs) const
{
	Matrix res;

	res = (*this);
	res[0] *= rhs;
	res[5] *= rhs;
	res[10] *= rhs;
	return (res);
}

std::ostream	&operator<<(std::ostream &lhs, const Matrix &rhs)
{
	const static unsigned dec = 2; /* number of decimals in display */

	for(unsigned i = 0; i < 16; i += 4)
		lhs << Utils::round(rhs[i + 0], dec) << '\t' <<
		Utils::round(rhs[i + 1], dec) << '\t' <<
		Utils::round(rhs[i + 2], dec) << '\t' <<
		Utils::round(rhs[i + 3], dec) << std::endl;
	return (lhs);
}
