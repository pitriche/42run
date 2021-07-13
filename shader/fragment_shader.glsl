#version 410 core

uniform vec3	particle_color;
uniform vec3	cursor_position;
uniform float	reference_length;

in vec3			particle_position_geometry;

out vec4		outColor;

void	main()
{
	float dist;
	
	dist = length(particle_position_geometry - cursor_position);
	// dist = reference_length / exp(dist);
	dist = reference_length / dist;
	
	/* floor brightness */
	dist -= 0.6;

	outColor = vec4(particle_color * dist, 1.0);
}
