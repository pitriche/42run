/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 11:14:54 by pitriche          #+#    #+#             */
/*   Updated: 2021/08/27 16:10:43 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.hpp"
#include "All.hpp"

/* ########################################################################## */
/* #########################		Sector			######################### */
/* ########################################################################## */

Sector::Sector(void) : nb(0), pos(SECTOR_LENGTH) { }

Sector	&Sector::operator=(const Sector &rhs)
{
	this->nb = rhs.nb;
	this->pos = rhs.pos;
	this->cube_pos = rhs.cube_pos;
	this->cube_size = rhs.cube_size;
	return (*this);
}

bool	Sector::check_collision(float pos_x, float pos_y, float crouch)
{
	vec3	pos;
	float	size;

	for (unsigned i = 0; i < this->nb; ++i)
	{
		pos = this->cube_pos[i];
		pos[2] += this->pos;
		pos[1] += 0.85f - (0.3f - crouch);
		size = this->cube_size[i] + 0.2f;							/* + character's size */
		if (pos[2] - size < 0.0f && pos[2] + size > 0.0f)			/* depth */
			if (pos[0] - size < pos_x && pos[0] + size > pos_x)		/* lateral */
				if (pos[1] - size < pos_y && pos[1] + size > pos_y)	/* vertical */
				return (true);
	}
	return(false);
}

/* ########################################################################## */
/* #########################		Game			######################### */
/* ########################################################################## */

Game::Game(void) { }
Game::~Game(void) { }

static void	_push_cube(Sector &sec, enum e_x x, enum e_y y, float z)
{
	static const float	eq_x[3] = {-1.5f, 0.0f, 1.5f};
	static const float	eq_y[5] = {-1.3f, -1.0f, -0.5f, 0.0f, 0.5f};

	if (y != tall)
		sec.cube_pos.push_back({eq_x[x], eq_y[y], z});
	else
	{
		sec.cube_pos.push_back({eq_x[x], -0.5, z});
		sec.cube_pos.push_back({eq_x[x], 0.5, z});
	}
	
}

static void	_complete_sector(Sector &sec)
{
	sec.nb = (unsigned)sec.cube_pos.size();
	sec.cube_size.resize(sec.nb);
	for (float &size : sec.cube_size)
		size = 0.5f;
}

static Sector	_random_sector(int nb_cubes)
{
	Sector	sec;

	for (unsigned i = 0; i < (unsigned)nb_cubes; ++i)
	{
		_push_cube(sec, (enum e_x)(rand() % 3), (enum e_y)(rand() % 5), -rand() % 50);
		if (sec.cube_pos.back()[0] == 0.0f && sec.cube_pos.back()[1] == 0.5f)
			sec.cube_pos.pop_back();
	}
	_complete_sector(sec);
	return(sec);
}

/* ########################################################################## */

void	Game::init(void)
{
	this->pos_x = 0.0f;
	this->pos_y = 0.0f;
	this->input_left = 0;
	this->input_right = 0;

	this->game_speed = Z_SPEED;
	this->distance = 0.0f;

	this->life = LIFE_BAR;

	this->sector = _random_sector(15);
	this->sector_next = _random_sector(18);
	this->sector.pos += 10.0f;
	this->sector_next.pos += SECTOR_LENGTH + 10.0f;
}

/* ########################################################################## */

void		Game::_update_sectors(float delta)
{
	this->sector.pos -= delta * this->game_speed;
	this->sector_next.pos -= delta * this->game_speed;

	if (this->sector.pos < -6)
	{
		this->sector = this->sector_next;
		this->sector_next = _random_sector(20);
		this->sector_next.pos += SECTOR_LENGTH;
	}
}

bool		Game::_check_collision(void)
{
	return (this->sector.check_collision(this->pos_x, this->pos_y, this->crouch)
		|| this->sector_next.check_collision(this->pos_x, this->pos_y,
		this->crouch));
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

	this->_update_sectors(delta);

	this->distance += delta * this->game_speed;
	this->game_speed += Z_ACCELERATION;
	
	if (this->_check_collision())
		--(this->life);
	if (!this->life)
	{
		std::cout << "Died ! Score : " << (int)this->distance << std::endl;
		exit(0);
	}
}
