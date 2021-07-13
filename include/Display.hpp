/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Display.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 18:57:00 by pitriche          #+#    #+#             */
/*   Updated: 2021/07/07 13:52:07 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_HPP
# define DISPLAY_HPP

# include <iostream>
# include <SDL.h>

/*
** Interface to the graphic library
*/
struct Display
{
	public :
		Display(void);
		virtual ~Display(void);

		SDL_Window	*window;

		unsigned	res_x;
		unsigned	res_y;

		void		init(void);
		void		update(void);

	protected:
	private:
		Display(const Display &);
		void	operator=(const Display &);
};

#endif
