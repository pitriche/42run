#version 410 core

uniform int		object;

in vec3			color_vertex;

out vec4		outColor;

void	main()
{
	if (object == 0)	/* character */
		outColor = vec4(1.0, 0.8, 0.8, 1.0);
	else				/* terrain */
		outColor = vec4(color_vertex, 1.0);
}
