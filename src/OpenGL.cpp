/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenGL.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 11:14:54 by pitriche          #+#    #+#             */
/*   Updated: 2021/07/20 15:28:15 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "OpenGL.hpp"
#include "Defines.hpp"
#include "Utils.hpp"

OpenGL::OpenGL(void) { }

/* ########################################################################## */

void	OpenGL::_init_vao_terrain(void)
{
	/* init and load vao */
	glGenVertexArrays(1, &this->terrain.vao);
	glBindVertexArray(this->terrain.vao);
	std::cout << "Terrain   VAO:[" << this->terrain.vao << "/2] ";

	/* init and fill vbo */
	glGenBuffers(1, &this->terrain.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->terrain.vbo);
	std::cout << "VBO:[" << this->terrain.vbo << "/2]" << std::endl;
	float	tmp_data[] = 
	{
		-0.3f, 0.2f, 0.0f,
		0.2f, 0.2f, 0.0f,
		0.2f, 0.8f, 0.0f,
		-0.2f, 0.7f, 0.0f
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(tmp_data), tmp_data, GL_STATIC_DRAW);

	/* init attributes */
	this->terrain.att.position_vertex =
	(GLuint)glGetAttribLocation(this->shader.program, "position_vertex");
	glVertexAttribPointer(this->terrain.att.position_vertex, 3, GL_FLOAT, GL_FALSE,
		sizeof(float) * 3, (void *)(0));
	glEnableVertexAttribArray(this->terrain.att.position_vertex);
}

void	OpenGL::_init_vao_player(void)
{
	/* init and load vao */
	glGenVertexArrays(1, &this->character.vao);
	glBindVertexArray(this->character.vao);
	std::cout << "Character VAO:[" << this->character.vao << "/1] ";

	/* init and fill vbo */
	glGenBuffers(1, &this->character.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->character.vbo);
	std::cout << "VBO:[" << this->character.vbo << "/1]" << std::endl;
	float	tmp_data[] = 
	{
		-0.2f, 0.2f, 0.0f,
		0.2f, 0.2f, 0.0f,
		0.2f, -0.2f, 0.0f,
		-0.2f, -0.2f, 0.0f
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(tmp_data), tmp_data, GL_STATIC_DRAW);

	/* init attributes */
	this->character.att.position_vertex =
	(GLuint)glGetAttribLocation(this->shader.program, "position_vertex");
	glVertexAttribPointer(this->character.att.position_vertex, 3, GL_FLOAT, GL_FALSE,
		sizeof(float) * 3, (void *)(0));
	glEnableVertexAttribArray(this->character.att.position_vertex);
}

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
	this->shader.vertex = compile_shader("shader/vertex_character.glsl",
		GL_VERTEX_SHADER);
	this->shader.fragment = compile_shader("shader/fragment_character.glsl",
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


void	OpenGL::_init_uniform(void)
{
	float	tmp_mat[] =
	{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	this->uniform.matrix_pos = glGetUniformLocation(this->shader.program,
		"matrix_pos");
	glUniformMatrix4fv(this->uniform.matrix_pos, 1, true, tmp_mat);

	this->uniform.screen_ratio = glGetUniformLocation(this->shader.program,
		"screen_ratio");
	glUniform1f(this->uniform.screen_ratio, WIN_SIZEX / (float)WIN_SIZEY);

	this->uniform.crouch = glGetUniformLocation(this->shader.program,
		"crouch");
	glUniform1i(this->uniform.crouch, 0);
}

/* ########################################################################## */

void	OpenGL::init(SDL_Window *window)
{
	/* create OpenGL context */
	this->glcontext = SDL_GL_CreateContext(window);
	printf("Supported OpenGL version: %s\nUsing OpenGL %d.%d\n\n",
		glGetString(GL_VERSION), OPENGL_VERSION_MAJOR, OPENGL_VERSION_MINOR);

	this->_init_shader();
	this->_init_uniform();
	this->_init_vao_player();
	this->_init_vao_terrain();
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}
