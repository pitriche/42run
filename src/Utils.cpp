/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 11:14:54 by pitriche          #+#    #+#             */
/*   Updated: 2021/08/27 09:02:01 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"
#include "OpenGL.hpp"	/* glGetShaderInfoLog */
#include "All.hpp"		/* all for draw_cube */
#include <iostream>		/* cerr, string */
#include <fstream>		/* ifstream */
#include <sstream>		/* stringstream */
#include <cstdlib>		/* exit */
#include <cmath>		/* round */


namespace Utils
{
	void	error_quit(const std::string &str)
	{
		std::cerr << str << std::endl;
		exit(0);
	}

	std::string	read_file(const char *filename)
	{
		std::ifstream		fs;
		std::stringstream	ss;

		fs.open(filename);
		if (!fs.is_open())
			error_quit("Cannot open source file");
		ss << fs.rdbuf();
		return (ss.str());
	}

	void		openGL_error_log(unsigned int shader, int err_code,
				const char *filename)
	{
		char	buffer[512];

		std::cerr << "[" << filename << "] shader compilation failed: [" <<
		err_code << "/1]" << std::endl;
		glGetShaderInfoLog(shader, 512, NULL, buffer);
		std::cerr << "Compilation log:" << std::endl << buffer;
		exit(0);
	}

	float	round(float f, int decimal)
	{
		float	n;

		n = std::powf(10.0f, decimal);
		return (std::roundf(f * n) / n);
	}

	/* preset colors */
	void	draw_cube(const Matrix &model)
	{
		glUniformMatrix4fv(all.gl.uniform.matrix_model, 1, true, model.data());
		glUniform1i(all.gl.uniform.color, 0x8080ff);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		glDrawArrays(GL_TRIANGLE_FAN, 4, 4);
		glUniform1i(all.gl.uniform.color, 0xff8080);
		glDrawArrays(GL_TRIANGLE_FAN, 8, 4);
		glDrawArrays(GL_TRIANGLE_FAN, 12, 4);
		glUniform1i(all.gl.uniform.color, 0x80ff80);
		glDrawArrays(GL_TRIANGLE_FAN, 16, 4);
		glDrawArrays(GL_TRIANGLE_FAN, 20, 4);
	}

	/* set colors */
	void	draw_cube(const Matrix &model, unsigned top_bot,
		unsigned left_right, unsigned far_near)
	{
		glUniformMatrix4fv(all.gl.uniform.matrix_model, 1, true, model.data());
		glUniform1i(all.gl.uniform.color, (GLint)top_bot);
		glDrawArrays(GL_TRIANGLE_FAN, 8, 4);
		glDrawArrays(GL_TRIANGLE_FAN, 12, 4);
		glUniform1i(all.gl.uniform.color, (GLint)left_right);
		glDrawArrays(GL_TRIANGLE_FAN, 16, 4);
		glDrawArrays(GL_TRIANGLE_FAN, 20, 4);
		glUniform1i(all.gl.uniform.color, (GLint)far_near);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		glDrawArrays(GL_TRIANGLE_FAN, 4, 4);
	}
}
