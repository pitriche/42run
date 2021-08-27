/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 11:13:45 by pitriche          #+#    #+#             */
/*   Updated: 2021/08/27 15:50:12 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_HPP
# define GAME_HPP

# include "Event.hpp"	/* Keys */
# include <vector>
# include <array>

# define	X_SPEED			10.0f
# define	Z_SPEED			5.0f
# define	Z_ACCELERATION	0.0025f
# define	SECTOR_LENGTH	50
# define	LIFE_BAR		31

typedef		std::array<float, 3> vec3;

enum e_x
{
	left,
	cent,
	righ
};

enum e_y
{
	trip,
	jump,
	wall,
	head,
	roof,
	tall
};

struct Sector
{
	Sector(void);

	unsigned			nb;
	std::vector<vec3>	cube_pos;
	std::vector<float>	cube_size;

	float				pos;	/* sector position */

	bool	check_collision(float pos_x, float pos_y, float crouch);

	Sector	&operator=(const Sector &rhs);
};

struct Game
{
	public :
		Game(void);
		virtual ~Game(void);

		void	init(void);
		void	update(float delta, const Keys &key);

		float		game_speed;
		float		distance;

		float		pos_x;
		float		pos_y;
		float		vel_y;
		float		crouch;

		unsigned	life;

		Sector		sector;
		Sector		sector_next;

		Sector		sector_bank[10];

		unsigned	input_left;
		unsigned	input_right;

	private:
		void	_update_sectors(float delta);
		bool	_check_collision(void);
};

#endif
