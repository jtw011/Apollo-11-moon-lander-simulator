/***********************************************************************
 * Source File:
 *    ACCELERATION 
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about changing speed
 ************************************************************************/

#include "acceleration.h"
#include "angle.h"

#include <cmath>

 /*********************************************
   * ACCELERATION : ADD
   *  a += a
   *********************************************/
void Acceleration::add(const Acceleration& acceleration)
{
   ddx += acceleration.ddx;
   ddy += acceleration.ddy;
}

/*********************************************
 * ACCELERATION : SET
 *  set from angle and magnitude using the following formulas:
 *	x = (sin(a) * total)
 *	y = (cos(a) * total)
 *	where:
 *	x = horizontal component (ddx)
 *	y = vertical component (ddy)
 *	a = angle (in radians)
 *	total = total acceleration (magnitude)
 *********************************************/
void Acceleration::set(const Angle& angle, double magnitude)
{
   ddx = sin(angle.getRadians()) * magnitude;
   ddy = cos(angle.getRadians()) * magnitude;
}