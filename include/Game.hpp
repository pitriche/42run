/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 11:13:45 by pitriche          #+#    #+#             */
/*   Updated: 2021/08/26 14:55:07 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_HPP
# define GAME_HPP

# include "Event.hpp"	/* Keys */
# include <vector>
# include <array>

# define	X_SPEED 10.0f

typedef		std::array<float, 3> vec3;

struct Sector
{
	Sector(void);

	unsigned			nb;
	std::vector<vec3>	cube_pos;
	std::vector<float>	cube_size;

	float				pos;	/* sector position */

	Sector	&operator=(const Sector &rhs);
};

struct Game
{
	public :
		Game(void);
		virtual ~Game(void);

		void	init(void);
		void	update(float delta, const Keys &key);

		float		pos_x;
		float		pos_y;
		float		vel_y;
		float		crouch;

		Sector		sector;
		Sector		sector_next;

		unsigned	input_left;
		unsigned	input_right;

	private:
		void	_update_matrices(float delta);
		bool	_check_collision(void);
};

#endif
