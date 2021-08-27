#version 410 core

uniform int		color;	/* temporary */ /* definitely not temporary lol */

uniform mat4	matrix_model;
uniform mat4	matrix_view;
uniform mat4	matrix_proj;

in vec3			position_vertex;

out vec3		color_vertex;
out float		pos_z_vertex;

void	main(void)
{
	vec4	tmp_pos;

	color_vertex = vec3(((color >> 16) & 0xff) / 255.0f,
		((color >> 8) & 0xff) / 255.0f,
		(color & 0xff) / 255.0f);
	tmp_pos = vec4(position_vertex, 1);
	gl_Position = matrix_proj * matrix_view * matrix_model * tmp_pos;
	pos_z_vertex = gl_Position.z;
}
