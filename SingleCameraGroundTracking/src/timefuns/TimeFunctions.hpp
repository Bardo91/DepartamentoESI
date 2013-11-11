/*
 * TimeFunctions.hpp
 *
 *  Created on: Oct 9, 2013
 *      Author: pablo
 */

#ifndef TIMEFUNCTIONS_HPP_
#define TIMEFUNCTIONS_HPP_

#include <time.h>

inline double diffTime(struct timespec t2, struct timespec t1) {
	if (t2.tv_nsec < t1.tv_nsec) {
		return ((double) (t2.tv_nsec - t1.tv_nsec + 1000000000)) / 1000000000
				+ t2.tv_sec - t1.tv_sec - 1;
	} else {
		return ((double) (t2.tv_nsec - t1.tv_nsec)) / 1000000000 + t2.tv_sec
				- t1.tv_sec;
	}
}

#endif /* TIMEFUNCTIONS_HPP_ */
