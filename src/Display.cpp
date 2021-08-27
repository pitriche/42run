/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Display.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 21:03:42 by pitriche          #+#    #+#             */
/*   Updated: 2021/08/27 16:23:01 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Display.hpp"
#include "All.hpp"

#include "Defines.hpp"	/* OPENGL defines */
#include <OpenGL/gl3.h>	/* opengl functions */

#include "Utils.hpp"	/* draw_cube */

Display::Display(void) : window(0) { }
Display::Display(const Display &) { }
Display::~Display(void) { }

void	Display::init(void)
{
	this->res_x = 1920;
	this->res_y = 1080;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		exit(0);

	/* This is out of place, i have no way around */
	if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
		SDL_GL_CONTEXT_PROFILE_CORE) < 0 ||
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,
			OPENGL_VERSION_MAJOR) < 0 ||
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,
			OPENGL_VERSION_MINOR) < 0 ||
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8) < 0)
		exit(0);

	/* create window */
	if (!(this->window = SDL_CreateWindow(WIN_TITLE, WIN_POSX, WIN_POSY,
				WIN_SIZEX, WIN_SIZEY, SDL_WINDOW_OPENGL)))
		exit(0);
}

void	Display::operator=(const Display &) { }

/* ########################################################################## */

static void	draw_number(unsigned n, vec3 pos)
{
	static const unsigned	number[10][15] =
	{
		{ 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1 },	/* 0 */
		{ 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1 },	/* 1 */
		{ 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1 },	/* 2 */
		{ 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1 },	/* 3 */
		{ 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1 },	/* 4 */
		{ 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1 },	/* 5 */
		{ 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1 },	/* 6 */
		{ 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1 },	/* 7 */
		{ 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1 },	/* 8 */
		{ 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1 }		/* 9 */
	};
	Matrix tmp_mat;

	if (n < 0 || n > 9)
		Utils::error_quit("dumb, imbecile cretin");
	tmp_mat = tmp_mat * (NUM_PIXEL_SIZE / 2);
	tmp_mat.translate(pos[0], pos[1], pos[2]);
	for (unsigned i = 0; i < 15; ++i)
	{
		if (i % 3 == 0 && i != 0)
			tmp_mat.translate(NUM_PIXEL_SIZE * 3, -NUM_PIXEL_SIZE, 0);
		if (number[n][i])
			Utils::draw_cube(tmp_mat, NUM_COLOR, NUM_COLOR, NUM_COLOR);
		tmp_mat.translate(-NUM_PIXEL_SIZE, 0, 0);
	}
}

static void	draw_counter(void)
{
	vec3	pos;

	pos = { -NUM_PIXEL_SIZE * 13, 1.9f, -3 };
	pos[0] += NUM_PIXEL_SIZE * 4;
	draw_number((unsigned)(all.game.distance / 1e0) % 10, pos);
	pos[0] += NUM_PIXEL_SIZE * 4;
	draw_number((unsigned)(all.game.distance / 1e1) % 10, pos);
	pos[0] += NUM_PIXEL_SIZE * 4;
	draw_number((unsigned)(all.game.distance / 1e2) % 10, pos);
	pos[0] += NUM_PIXEL_SIZE * 4;
	draw_number((unsigned)(all.game.distance / 1e3) % 10, pos);
	pos[0] += NUM_PIXEL_SIZE * 4;
	draw_number((unsigned)(all.game.distance / 1e4) % 10, pos);
	pos[0] += NUM_PIXEL_SIZE * 4;
	draw_number((unsigned)(all.game.distance / 1e5) % 10, pos);
}

/* ########################################################################## */

static void	draw_health(void)
{
	Matrix		tmp_matrix;
	unsigned	color;
	unsigned	on;

	tmp_matrix = tmp_matrix.translate((LIFE_BAR / 2) * BAR_PIXEL_SIZE, 1.65f, -3);
	tmp_matrix = tmp_matrix * (BAR_PIXEL_SIZE / 1.5f);
	on = 1;
	for (unsigned i = 0; i < LIFE_BAR; ++i)
	{
		if (on && i >= all.game.life)
		{
			on = 0;
			tmp_matrix = tmp_matrix * 0.75;
		}
		color = on ? 0xff0000 : 0x404040;
		Utils::draw_cube(tmp_matrix, color, color, color);
		tmp_matrix.translate(-BAR_PIXEL_SIZE, 0, 0);
	}
}

static void	draw_terrain(void)
{
	Matrix	tmp_matrix;

	tmp_matrix = tmp_matrix.translate(0, 102, 0);
	tmp_matrix = tmp_matrix * 100;
	Utils::draw_cube(tmp_matrix, 0x585050, 0, 0); /* top */
	tmp_matrix = tmp_matrix.translate(0, -203, 0);
	Utils::draw_cube(tmp_matrix, 0x4d4242, 0, 0); /* bottom */
	tmp_matrix = tmp_matrix.translate(-102, 101, 0);
	Utils::draw_cube(tmp_matrix, 0, 0xe0efe0, 0); /* right */
	tmp_matrix = tmp_matrix.translate(204, 0, 0);
	Utils::draw_cube(tmp_matrix, 0, 0xe0efe0, 0); /* left */
}

static void	draw_sectors(void)
{
	for (unsigned i = 0; i < all.game.sector.nb; ++i)
	{
		std::array<float, 3>	&tmp = all.game.sector.cube_pos[i];
		Matrix					tmp_matrix;

		tmp_matrix = tmp_matrix.translate(0, 0, all.game.sector.pos);
		tmp_matrix = tmp_matrix.translate(-tmp[0], tmp[1], tmp[2]);
		tmp_matrix = tmp_matrix * all.game.sector.cube_size[i];
		Utils::draw_cube(tmp_matrix, 0xc0c5c0, 0xc0c5c0, 0xd0d5d0);
	}

	for (unsigned i = 0; i < all.game.sector_next.nb; ++i)
	{
		std::array<float, 3>	&tmp = all.game.sector_next.cube_pos[i];
		Matrix					tmp_matrix;

		tmp_matrix = tmp_matrix.translate(0, 0, all.game.sector_next.pos);
		tmp_matrix = tmp_matrix.translate(-tmp[0], tmp[1], tmp[2]);
		tmp_matrix = tmp_matrix * all.game.sector_next.cube_size[i];
		Utils::draw_cube(tmp_matrix, 0xc0c5c0, 0xc0c5c0, 0xd0d5d0);
	}
}

static void	draw_character(void)
{
	Matrix	base;
	Matrix	tmp_matrix;

	base = base.translate(-all.game.pos_x, -0.85f + all.game.pos_y, 0);

	/* leg and head */
	tmp_matrix = base * 0.16f;
	Utils::draw_cube(tmp_matrix, 0x585956, 0x586556, 0x686966);
	tmp_matrix = base;
	tmp_matrix = tmp_matrix.translate(0, 0.3f - all.game.crouch, 0);
	tmp_matrix = tmp_matrix * 0.2f;
	Utils::draw_cube(tmp_matrix, 0xc3c2be, 0xc3c2be, 0xd3c2ce);

	/* eyes */
	tmp_matrix = base;
	tmp_matrix = tmp_matrix.translate(0.2f, 0.3f - all.game.crouch, 0);
	tmp_matrix = tmp_matrix * 0.08f;
	Utils::draw_cube(tmp_matrix, 0x38b458, 0x38b458, 0x43c464);
	tmp_matrix = base;
	tmp_matrix = tmp_matrix.translate(-0.2f, 0.3f - all.game.crouch, 0);
	tmp_matrix = tmp_matrix * 0.08f;
	Utils::draw_cube(tmp_matrix, 0x38b458, 0x38b458, 0x43c464);
}

void		Display::update(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	draw_terrain();
	draw_counter();
	draw_character();
	draw_sectors();
	draw_health();

	glFinish();
	SDL_GL_SwapWindow(this->window);
}
