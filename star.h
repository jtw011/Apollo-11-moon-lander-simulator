/***********************************************************************
 * Header File:
 *    STAR
 * Author:
 *    Br. Helfrich
 * Summary:
 *    A single star that twinkles
 ************************************************************************/

#pragma once
#include "position.h"   // for POSITION
#include "uiDraw.h"     // for RANDOM and DRAWSTAR

/*****************************************************
 * STAR
 * A star that twinkles
 *****************************************************/
class Star
{
public:
   Star(const Position& posUpperRight) : phase(0) 
   { 
      reset(posUpperRight.getX(), posUpperRight.getY()); 
   }

   // Resets position of star randomly
   void reset(double width, double height)
   {
      pos.setX(random(0.0, width));
      pos.setY(random(0.0, height));
      // staggers the phase of each star
      phase = random(0, 255);
   }
   
   // Draws star to the screen and increments phase
   void draw(ogstream & gout)
   {
      gout.drawStar(pos, phase++);
   }
private:
   Position pos;
   unsigned char phase;
};
