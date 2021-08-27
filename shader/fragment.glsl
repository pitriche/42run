#version 410 core

in vec3			color_vertex;
in float		pos_z_vertex;


out vec4		outColor;

void	main()
{
	if (pos_z_vertex < 10)
		outColor = vec4(color_vertex, 1.0);
	else if (pos_z_vertex < 50)
		outColor = vec4(color_vertex * ((50 - pos_z_vertex) / 40), 1.0);
	else
		outColor = vec4(0, 0, 0, 1.0);
}
