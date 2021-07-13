/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Event.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunomartin <brunomartin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 18:57:00 by pitriche          #+#    #+#             */
/*   Updated: 2021/03/20 22:38:29 by brunomartin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENT_HPP
# define EVENT_HPP

# include <SDL.h>

struct Keys
{
	unsigned w:1;
	unsigned s:1;
	unsigned up:1;
	unsigned down:1;
	unsigned space:1;
};

/*
** Interface to event library, with currently pressed keys
*/
struct Event
{
	public :
		Event(void);
		virtual ~Event(void);

		Keys	key;

		void	update(void);

	protected:
	private:
		void	_keychange(SDL_Keycode kc, unsigned key_state);

		Event(const Event &src);
		void	operator=(const Event &rhs);
};

#endif
