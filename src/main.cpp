/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 09:29:13 by pitriche          #+#    #+#             */
/*   Updated: 2021/07/13 17:06:01 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "All.hpp"
#include "Defines.hpp"
#include "Utils.hpp"

All	all;

static void	loop(void)
{
	all.event.update();
	all.disp.update();
	all.time.update();
	all.game.update(all.time.delta / 1000000000.0f, all.event.key);

	// std::cout << "[l>" << all.game.input_left << " r>" << all.game.input_right << "] " << all.game.pos_x << std::endl;
	std::cout << "[v>" << all.game.vel_y << "] " << all.game.pos_y << std::endl;
}

int			main(void)
{
	all.init();

	while (1)
		loop();
	return (0);
}
