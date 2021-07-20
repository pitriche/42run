/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 11:14:54 by pitriche          #+#    #+#             */
/*   Updated: 2021/07/19 15:38:18 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.hpp"
#include "All.hpp"

Game::Game(void) { }
Game::~Game(void) { }

void	Game::init(void)
{
	pos_x = 0.0f;
	pos_y = 0.0f;
	input_left = 0;
	input_right = 0;
}

void		Game::update(float delta, const Keys &key)
{
	float	disp_x;
	
	/* lateral movements */
	disp_x = delta * X_SPEED;
	if (this->input_left && this->pos_x > -1.0)
	{
		this->pos_x -= disp_x;
		if (this->pos_x < -1.0)
			this->pos_x = -1.0;
		if (this->pos_x <= 0.0f && this->pos_x + disp_x > 0.0f)
		{
			this->pos_x = 0.0f;
			this->input_left--;
		}
	}
	else if (this->input_right && this->pos_x < 1.0)
	{
		this->pos_x += disp_x;
		if (this->pos_x > 1.0)
			this->pos_x = 1.0;
		if (this->pos_x >= 0.0f && this->pos_x - disp_x < 0.0f)
		{
			this->pos_x = 0.0f;
			this->input_right--;
		}
	}

	/* jumps and crouch */
	if ((key.space || key.up || key.w) && this->pos_y <= 0.0f)
	{
		this->pos_y = 0.01f;
		this->vel_y = 2.0f;
	}
	if (this->pos_y > 0.0f)
	{
		this->pos_y += delta * this->vel_y;
		this->vel_y -= delta * 9.81f;
		if (this->pos_y < 0.0f)
			this->pos_y = 0.0f;
	}
	if ((key.down || key.s || key.down) && this->pos_y == 0.0f)
		this->pos_y = -1.0f;
	if (!(key.down || key.s || key.down) && this->pos_y == -1.0f)
		this->pos_y = 0.0f;


	/* update matrix */
	float	tmp_mat[] =
	{
		1.0f, 0.0f, 0.0f, this->pos_x * 0.8f,
		0.0f, 1.0f, 0.0f, this->pos_y * 3.5f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	if (this->pos_y == -1)
		tmp_mat[7] = 0;
	
	glUniformMatrix4fv(all.gl.uniform.matrix_pos, 1, true, tmp_mat);
}
