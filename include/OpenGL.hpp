/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenGL.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 11:13:45 by pitriche          #+#    #+#             */
/*   Updated: 2021/07/20 15:16:13 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENGL_HPP
# define OPENGL_HPP

# include <OpenGL/gl3.h>
# include <SDL.h>

struct	_Uniform
{
	GLint	matrix_pos;
	GLint	crouch;
	GLint	screen_ratio;
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
	GLuint			vao;
	GLuint			vbo;

	struct			_Attribute
	{
		GLuint	position_vertex;
	}				att;	/* attributes */
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

		void	init(SDL_Window *window);

	private:
		void	_init_vao_terrain(void);
		void	_init_vao_player(void);
		void	_init_shader(void);
		void	_init_uniform(void);
};

#endif
