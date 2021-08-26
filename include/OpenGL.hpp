/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenGL.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 11:13:45 by pitriche          #+#    #+#             */
/*   Updated: 2021/08/26 12:14:39 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENGL_HPP
# define OPENGL_HPP

# include <OpenGL/gl3.h>
# include <SDL.h>
# include "Matrix.hpp"

struct	_Uniform
{
	GLint	object;

	GLint	matrix_char_pos;
	GLint	matrix_proj;
	GLint	matrix_view;
	GLint	matrix_model;

	GLint	crouch;
	GLint	screen_ratio;

	GLint	color;
};

struct	_Shader
{
	GLuint	vertex;
	GLuint	fragment;

	GLuint	program;
};

/* ########################################################################## */

struct	VAO
{
	private :
		struct _Attribute
		{
			GLuint	position_vertex;
		};

	public :
		GLuint		vao;
		GLuint		vbo;
		_Attribute	att;


};

struct OpenGL
{
	public :
		OpenGL(void);
		SDL_Window		*window;
		SDL_GLContext	glcontext;

		VAO				terrain;
		VAO				character;
		_Shader			shader;
		_Uniform		uniform;

		// Matrix			matrix_character;
		Matrix			matrix_proj;
		Matrix			matrix_view;
		Matrix			matrix_model;

		void	init(SDL_Window *window);

	private:
		void	_init_vao_terrain(void);
		void	_init_vao_player(void);
		void	_init_shader(void);
		void	_init_uniform(void);
		void	_init_matrix(void);
};

#endif
