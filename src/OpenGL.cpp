/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenGL.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 11:14:54 by pitriche          #+#    #+#             */
/*   Updated: 2021/-/27 12:54:54 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "OpenGL.hpp"
#include "Defines.hpp"
#include "Utils.hpp"

OpenGL::OpenGL(void) { }

/* ########################################################################## */
/* #####################			Buffers				##################### */
/* ########################################################################## */

void	OpenGL::_init_vao_terrain(void)
{
	float	cube_data[] =
	{
		1,	1,	-1,	1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	-1,
		1,	1,	1,	1,	-1,	1,	-1,	-1,	1,	-1,	1,	1,
		1,	-1,	1,	-1,	-1,	1,	-1,	-1,	-1,	1,	-1,	-1,
		1,	1,	1,	-1,	1,	1,	-1,	1,	-1,	1,	1,	-1,
		-1,	1,	1,	-1,	-1,	1,	-1,	-1,	-1,	-1,	1,	-1,
		1,	1,	1,	1,	-1,	1,	1,	-1,	-1,	1,	1,	-1,
	};

	/* init and load vao */
	glGenVertexArrays(1, &this->terrain.vao);
	glBindVertexArray(this->terrain.vao);
	std::cout << "Terrain   VAO:[" << this->terrain.vao << "/1] ";

	/* init and fill vbo with cube data */
	glGenBuffers(1, &this->terrain.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->terrain.vbo);
	std::cout << "VBO:[" << this->terrain.vbo << "/1]" << std::endl;
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_data), cube_data, GL_STATIC_DRAW);

	/* init attributes */
	this->terrain.att.position_vertex =
	(GLuint)glGetAttribLocation(this->shader.program, "position_vertex");
	glVertexAttribPointer(this->terrain.att.position_vertex, 3, GL_FLOAT,
		GL_FALSE, sizeof(float) * 3, (void *)(0));
	glEnableVertexAttribArray(this->terrain.att.position_vertex);
}

/* ########################################################################## */
/* #####################			Shaders				##################### */
/* ########################################################################## */

static GLuint compile_shader(const char *filename, GLenum type)
{
	GLuint		shader;
	std::string	scode;
	const char	*code;
	GLint		status;

	/* fetch code in stack */
	scode = Utils::read_file(filename);
	code = scode.c_str();
	shader = glCreateShader(type);
	glShaderSource(shader, 1, &code, 0);

	/* compile and check for errors */
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE)
		Utils::openGL_error_log(shader, status, filename);
	return (shader);
}

void	OpenGL::_init_shader(void)
{
	this->shader.vertex = compile_shader("shader/vertex.glsl",
		GL_VERTEX_SHADER);
	this->shader.fragment = compile_shader("shader/fragment.glsl",
		GL_FRAGMENT_SHADER);

	/* create shader program and attach shaders */
	this->shader.program = glCreateProgram();
	std::cout << "Program: [" << this->shader.program << "/3]" << std::endl;
	glAttachShader(this->shader.program, this->shader.vertex);
	glAttachShader(this->shader.program, this->shader.fragment);
	glBindFragDataLocation(this->shader.program, 0, "outColor");

	/* link and use shader program */
	glLinkProgram(this->shader.program);
	glUseProgram(this->shader.program);
}

/* ########################################################################## */
/* #####################		Uniforms & Data			##################### */
/* ########################################################################## */

void	OpenGL::_init_uniform(void)
{
	this->uniform.matrix_proj = glGetUniformLocation(this->shader.program,
		"matrix_proj");
	this->uniform.matrix_view = glGetUniformLocation(this->shader.program,
		"matrix_view");
	this->uniform.matrix_model = glGetUniformLocation(this->shader.program,
		"matrix_model");

	this->uniform.color = glGetUniformLocation(this->shader.program,
		"color");
}

void	OpenGL::_init_matrix(void)
{
	this->matrix_model = Matrix();

	/* set the camera to face positive Z and stand back */
	this->matrix_view = Matrix();
	this->matrix_view.translate(0, -1.2f, 6.0f);
	this->matrix_view.rotate(0.1f, (float)M_PI, 0);

	this->matrix_proj.set_projection((float)M_PI * CAMERA_FOV / 360.0f,
		CAMERA_NEAR, CAMERA_FAR, (float)WIN_SIZEX / WIN_SIZEY);

	glUniformMatrix4fv(this->uniform.matrix_model, 1, true,
		this->matrix_model.data());
	glUniformMatrix4fv(this->uniform.matrix_view, 1, true,
		this->matrix_view.data());
	glUniformMatrix4fv(this->uniform.matrix_proj, 1, true,
		this->matrix_proj.data());
}

/* ########################################################################## */
/* #####################			Main init			##################### */
/* ########################################################################## */

void	OpenGL::init(SDL_Window *window)
{
	/* create OpenGL context */
	this->glcontext = SDL_GL_CreateContext(window);
	std::cout << "Supported OpenGL version: " << glGetString(GL_VERSION) <<
		std::endl << "Using OpenGL " << OPENGL_VERSION_MAJOR << '.' <<
		OPENGL_VERSION_MINOR << std::endl << std::endl;

	this->_init_shader();
	this->_init_uniform();
	this->_init_vao_terrain();
	this->_init_matrix();

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}
