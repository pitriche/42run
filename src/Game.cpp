/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 11:14:54 by pitriche          #+#    #+#             */
/*   Updated: 2021/08/26 15:37:27 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.hpp"
#include "All.hpp"

/* ########################################################################## */
/* #########################		Sector			######################### */
/* ########################################################################## */

Sector::Sector(void) : nb(0), pos(50) { }

Sector	&Sector::operator=(const Sector &rhs)
{
	this->nb = rhs.nb;
	this->pos = rhs.pos;
	this->cube_pos = rhs.cube_pos;
	this->cube_size = rhs.cube_size;
	return (*this);
}

/* ########################################################################## */
/* #########################		Game			######################### */
/* ########################################################################## */

Game::Game(void) { }
Game::~Game(void) { }

void	Game::init(void)
{
	this->pos_x = 0.0f;
	this->pos_y = 0.0f;
	this->input_left = 0;
	this->input_right = 0;

	// this->sector.cube_pos.push_back({1, 0, 0});
	// this->sector.cube_pos.push_back({-1.5, 0, 0});
	// this->sector.cube_pos.push_back({1.5, 0, -5});
	// this->sector.cube_pos.push_back({-1.5, 0, -10});
	// this->sector.cube_pos.push_back({1.5, 0, -15});
	// this->sector.cube_pos.push_back({-1.5, 0, -20});
	this->sector.cube_pos.push_back({1.5, 0, -25});
	this->sector.cube_pos.push_back({-1.5, 0, -30});
	this->sector.cube_pos.push_back({1.5, 0, -35});
	this->sector.cube_pos.push_back({-1.5, 0, -40});
	this->sector.cube_pos.push_back({0, -1, -30});
	this->sector.cube_pos.push_back({0, -1, -32});
	this->sector.cube_pos.push_back({0, -1.3, -34});
	this->sector.cube_pos.push_back({0, -1.3, -36});
	this->sector.cube_size = {0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f};
	this->sector.nb = (unsigned)this->sector.cube_pos.size();
}

/* ########################################################################## */

void		Game::_update_matrices(float delta)
{
	static float	speed = 4;

	speed *= 1.02f;

	this->sector.pos -= delta * speed;
	this->sector_next.pos -= delta * speed;
}

bool		Game::_check_collision(void)
{
	vec3	pos;
	float	size;

	for (unsigned i = 0; i < this->sector.nb; ++i)
	{
		pos = this->sector.cube_pos[i];
		pos[2] += this->sector.pos;
		pos[1] += 0.85f - (0.3 - this->crouch);
		size = this->sector.cube_size[i] + 0.2f;	/* character's size */

		// std::cout << "pos:"<<pos_y << " min pos:"<<pos[1] - size << " max pos:" << pos[1] + size << std::endl;

		if (pos[2] - size < 0.0f && pos[2] + size > 0.0f)					/* depth */
			if (pos[0] - size < this->pos_x && pos[0] + size > this->pos_x)	/* lateral */
				if (pos[1] - size < this->pos_y &&
					pos[1] + size > this->pos_y)							/* vertical */
				return (true);
	}
	return (false);
}

/* ########################################################################## */

void		Game::update(float delta, const Keys &key)
{
	float	disp_x;

	/* lateral movements */
	disp_x = delta * X_SPEED;
	if (this->input_left && this->pos_x > -1.5f)
	{
		this->pos_x -= disp_x;
		if (this->pos_x < -1.5f)
			this->pos_x = -1.5f;
		if (this->pos_x <= 0.0f && this->pos_x + disp_x > 0.0f)
		{
			this->pos_x = 0.0f;
			this->input_left--;
		}
	}
	else if (this->input_right && this->pos_x < 1.5f)
	{
		this->pos_x += disp_x;
		if (this->pos_x > 1.5f)
			this->pos_x = 1.5f;
		if (this->pos_x >= 0.0f && this->pos_x - disp_x < 0.0f)
		{
			this->pos_x = 0.0f;
			this->input_right--;
		}
	}

	/* jump */
	if ((key.space || key.up || key.w) && this->pos_y <= 0.0f && crouch == 0.0f)
	{
		this->pos_y = 0.01f;
		this->vel_y = 8.0f;
	}
	if (this->pos_y > 0.0f)
	{
		this->pos_y += delta * this->vel_y;
		this->vel_y -= delta * 35.0f;
		if (this->pos_y < 0.0f)
			this->pos_y = 0.0f;
	}

	/* crouch */
	this->crouch += delta * ((key.down || key.s || key.down) ? 4 : -4);
	if (this->crouch > 0.25f)
		this->crouch = 0.25f;
	if (this->crouch < 0.0f)
		this->crouch = 0.0f;

	this->_update_matrices(delta);
	if (this->_check_collision())
		std::cout << "HIT !" << std::endl;
	else
		std::cout << "no hit" << std::endl;
}
