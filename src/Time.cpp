/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Time.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 21:03:42 by pitriche          #+#    #+#             */
/*   Updated: 2021/07/07 13:46:30 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Time.hpp"
#include <unistd.h>
#include <ctime>	/* clock_gettime_nsec_np, nanosleep */

// no more than MAX_SAMPLE_AVERAGE samples
Time::Time(void) : delta(0), _min_delta(0), _old_ts(timestamp()),
	_sample_average(10), _elapsed_frame(0)
{
	for (int i = 0; i < MAX_SAMPLE_AVERAGE; i++)
		this->_delta_sample[i] = 0;
}

Time::Time(const Time &) { }
Time::~Time(void) { }

std::string	Time::time_to_frame(void)
{
	return ("Frame time: " + std::to_string(this->_pure_delta / 1000000.0) +
		"\tms");
}

std::string	Time::fps_average(void)
{
	unsigned	tot;
	float		result;
	
	tot = 0;
	for (unsigned i = 0; i < this->_sample_average; i++)
		tot += this->_delta_sample[i];
	tot /= this->_sample_average;
	result = 1000000000.0f / tot;
	return ("Average: " + std::to_string(result) + " Hz");
}

void		Time::set_average_sample(unsigned nb)
{
	if (nb > MAX_SAMPLE_AVERAGE)
	{
		nb = MAX_SAMPLE_AVERAGE;
		std::cout << "Maximum sample for average is " << MAX_SAMPLE_AVERAGE <<
			std::endl;
	}
	else if (nb == 0)
	{
		nb = 1;
		std::cout << "Averaging requires at least one sample" << std::endl;
	}
	this->_sample_average = nb;
}

void		Time::set_fps(unsigned long fps)
{
	if (fps == 0)
		this->_min_delta = 0;
	else
		this->_min_delta = 1000000000UL / fps;
}

void		Time::nsleep(unsigned long nsec)
{
	struct timespec tc;

	tc.tv_sec = 0L;
	while (nsec >= 1000000000UL)
	{
		++tc.tv_sec;
		nsec -= 1000000000UL; 
	}
	tc.tv_nsec = static_cast<long>(nsec);
	nanosleep(&tc, 0);
}

void		Time::update(void)
{
	this->_pure_delta = Time::timestamp() - this->_old_ts;
	this->delta = this->_pure_delta;
	if (this->_pure_delta < this->_min_delta)
	{
		Time::nsleep(this->_min_delta - this->_pure_delta);
		this->delta = this->_min_delta;
	}
	this->_old_ts += this->delta;
	this->_delta_sample[this->_sample_current++] = this->delta;
	if (this->_sample_current >= this->_sample_average)
		this->_sample_current = 0;
	this->_elapsed_frame++;
}

unsigned long	Time::elapsed_frame(void) { return (this->_elapsed_frame); }

unsigned long	Time::timestamp(void)
{
	#ifdef __MACH__
	return (clock_gettime_nsec_np(CLOCK_MONOTONIC_RAW));
	#endif
	#ifndef __MACH__
	struct timespec ts;

	//clock_gettime(CLOCK_MONOTONIC, &ts); // REQUIRES TESTING ON LINUX
	clock_gettime(CLOCK_UPTIME_RAW, &ts);
	return (static_cast<unsigned long>(ts.tv_sec) * 1000000000UL +
		static_cast<unsigned long>(ts.tv_nsec));
	#endif
}

void	Time::operator=(const Time &) { }
std::ostream	&operator<<(std::ostream &lhs, const Time &vec)
{
	return (lhs << 1000000000.0 / vec.delta << "\tHz");
}
