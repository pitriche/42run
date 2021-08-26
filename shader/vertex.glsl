#version 410 core

uniform int		object;
uniform int		color;	/* temporary */

uniform float	screen_ratio;
uniform int		crouch;

uniform mat4	matrix_char_pos;

uniform mat4	matrix_model;
uniform mat4	matrix_view;
uniform mat4	matrix_proj;

in vec3			position_vertex;

out vec3		color_vertex;

void	main(void)
{
	vec4	tmp_pos;

	if (object == 0)	/* character */
	{
		tmp_pos = vec4(position_vertex.x / screen_ratio, position_vertex.y,
			0.0, 1.0);
	
		tmp_pos.y = (crouch == 1) ? tmp_pos.y * 0.5f : tmp_pos.y * 1.5f + 0.2f;
		tmp_pos.y -= 0.5f;

		gl_Position = matrix_char_pos * tmp_pos;
	}
	else				/* terrain */
	{
		color_vertex = vec3(((color >> 16) & 0xff) / 255.0f,
			((color >> 8) & 0xff) / 255.0f,
			(color & 0xff) / 255.0f);
		tmp_pos = vec4(position_vertex, 1);
		gl_Position = matrix_proj * matrix_view * matrix_model * tmp_pos;
	}
}
