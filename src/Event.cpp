/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Event.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 21:03:42 by pitriche          #+#    #+#             */
/*   Updated: 2021/07/19 15:32:50 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Event.hpp"
#include "All.hpp"

Event::Event(void) { }
Event::Event(const Event &) { }
Event::~Event(void) { }

void	Event::_keychange(SDL_Keycode kc, unsigned key_state)
{
	switch (kc)
	{
		// ADD WASD SUPPORT
		case (SDLK_w): this->key.w = key_state; break;
		case (SDLK_UP): this->key.up = key_state; break;
		case (SDLK_LEFT): case (SDLK_a):
			if (key_state && all.game.pos_y != -1.0)
			{
				all.game.input_left++;
				all.game.input_right = 0;
			}
			break;
		case (SDLK_RIGHT): case (SDLK_d):
			if (key_state && all.game.pos_y != -1.0)
			{
				all.game.input_right++;
				all.game.input_left = 0;
			}
			break;
		case (SDLK_SPACE): this->key.space = key_state; break;
		
		case (SDLK_s):
			this->key.s = key_state; 
			glUniform1i(all.gl.uniform.crouch, (GLint)key_state);
			break;
		case (SDLK_DOWN):
			this->key.down = key_state;
			glUniform1i(all.gl.uniform.crouch, (GLint)key_state);
			break;

		case (SDLK_ESCAPE): exit(0); break;
	}
}

void	Event::update(void)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			exit(0);
		if ((event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) &&
			!event.key.repeat)
			this->_keychange(event.key.keysym.sym, event.type == SDL_KEYDOWN);
	}
}

void	Event::operator=(const Event &) { }
