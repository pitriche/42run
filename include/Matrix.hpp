/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Matrix.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 11:13:45 by pitriche          #+#    #+#             */
/*   Updated: 2021/08/27 16:15:36 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_HPP
# define MATRIX_HPP

# include <iostream>
# include <array>

/*
** 4x4 32 bit floating point matrix
*/
struct Matrix : public std::array<float, 16>
{
	public :
		Matrix(void);	/* set matrix as identity */
		Matrix(const Matrix &src);
		virtual ~Matrix(void);

		void	transpose(void);
		void	set_projection(float fov, float near, float far, float aspect);
		Matrix	&rotate(float x, float y, float z);
		Matrix	&translate(float x, float y, float z);

		Matrix	&operator=(const Matrix &rhs);
		Matrix	operator*(const Matrix &rhs) const;
		Matrix	operator*(float rhs) const;

	private :
		void	_rotate_x(float angle);
		void	_rotate_y(float angle);
		void	_rotate_z(float angle);
};

std::ostream	&operator<<(std::ostream &lhs, const Matrix &rhs);

#endif
