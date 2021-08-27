/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 09:29:13 by pitriche          #+#    #+#             */
/*   Updated: 2021/08/27 16:08:24 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>		/* srand */
#include <ctime>		/* time */
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
}

int			main(void)
{
	srand((unsigned)time(0));
	all.init();

	while (1)
		loop();
	return (0);
}
