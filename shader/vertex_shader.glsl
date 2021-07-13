#version 410 core

uniform float	screen_ratio;

in vec3			position_vertex;

out vec3		particle_position_geometry;

void	main()
{
	particle_position_geometry = position_vertex;

	/* to reduce drawn size */
	vec2 reduced_pos = position_vertex.xy * 1.0;

	gl_Position = vec4(reduced_pos.x / screen_ratio, reduced_pos.y, (position_vertex.z - 100) / 100000, 1.0);
}
