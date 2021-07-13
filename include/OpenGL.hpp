/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenGL.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 11:13:45 by pitriche          #+#    #+#             */
/*   Updated: 2021/06/23 15:17:58 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENGL_HPP
# define OPENGL_HPP

# include <OpenGL/gl3.h>
# include <SDL.h>

struct	_Uniform
{
	_Uniform(void);

	GLint	particle_color;		/* vec3 */
	GLint	cursor_position;	/* vec3 */
	GLint	reference_length;	/* float */

	GLint	screen_ratio;
};

struct	_Attribute
{
	_Attribute(void);

	GLuint	position_vertex;	/* vec3, temporary */
};

struct	_Shader
{
	_Shader(void);

	GLuint	vertex;
	GLuint	fragment;

	GLuint	program;
};

/* ########################################################################## */

struct OpenGL
{
	public :
		OpenGL(void);

		SDL_Window		*window;
		SDL_GLContext	glcontext;

		GLuint			vao; /* Vertex Array Object */
		GLuint			vbo; /* Vertex Buffer Object */
		_Shader			shader;
		_Attribute		attribute;
		_Uniform		uniform;

		void	init(SDL_Window *window);

	private:
		void	_init_vao(void);
		void	_init_vbo(void);
		void	_init_shader(void);
		void	_init_attribute(void);
		void	_init_uniform(void);
};

#endif
