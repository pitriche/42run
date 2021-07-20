#version 410 core

uniform float	screen_ratio;
uniform int		crouch;
uniform mat4	matrix_pos;

in vec2			position_vertex;

void	main(void)
{
	vec2	tmp_pos;

	tmp_pos = vec2(position_vertex.x / screen_ratio, position_vertex.y);
	
	tmp_pos.y = (crouch == 1) ? tmp_pos.y * 0.5f : tmp_pos.y * 1.5f + 0.2f;
	tmp_pos.y -= 0.5f;

	gl_Position = matrix_pos * vec4(tmp_pos, 0.0, 1.0);
}
