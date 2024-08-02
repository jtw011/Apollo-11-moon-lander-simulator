/***********************************************************************
 * Source File:
 *    LANDER
 * Author:
 *    Br. Helfrich
 * Summary:
 *    All the information about the lunar lander
 ************************************************************************/

#include "lander.h"
#include "acceleration.h"

 /***************************************************************
  * RESET
  * Reset the lander and its position to start the game over
  ***************************************************************/
void Lander :: reset(const Position & posUpperRight)
{
   // Angle up
   angle.setUp();
   // Status
   status = PLAYING;
   // Fuel
   fuel = FUEL_MAX;
   // Velocity
   velocity.setDX(random(-10.0, -4.0));
   velocity.setDY(random(-2.0 , 2.0 ));
   // Position
   pos.setX(posUpperRight.getX() - 1);
   pos.setY(random(posUpperRight.getY() * 0.75, posUpperRight.getY() * 0.95));
}

/***************************************************************
 * DRAW
 * Draw the lander on the screen
 ***************************************************************/
void Lander :: draw(const Thrust & thrust, ogstream & gout) const
{
   // draw the lander on the screen
   gout.drawLander(pos, angle.getRadians());

   // only fire the engines if we are still flying
   if (isFlying() && fuel > 0.0)
      gout.drawLanderFlames(pos, angle.getRadians(),
         thrust.isMain(), thrust.isClock(), thrust.isCounter());
}

/***************************************************************
 * INPUT
 * Accept input from the Neil Armstrong
 ***************************************************************/
Acceleration Lander :: input(const Thrust& thrust, double gravity)
{
   Acceleration a;

   // out of fuel?
   if (fuel <= 0.0)
   {
      a.addDDY(gravity);
      return a;
   }

   // main engines
   if (thrust.isMain())
   {
      double power = (LANDER_THRUST / LANDER_WEIGHT);
      a.addDDX(-sin(angle.getRadians()) * power);
      a.addDDY( cos(angle.getRadians()) * power);
      fuel -= FUEL_MAIN_THRUST;
   }
   // clockwise
   if (thrust.isClock())
   {
      angle.add(0.1);
      fuel -= FUEL_ROTATE;
   }
   // counter-clockwise
   if (thrust.isCounter())
   {
      angle.add(-0.1);
      fuel -= FUEL_ROTATE;
   }
   a.addDDY(gravity);
   return a;
}

/******************************************************************
 * COAST
 * What happens when we coast?
 *******************************************************************/
void Lander :: coast(Acceleration & acceleration, double time)
{
   velocity.add(acceleration, time); // need to update velocity before position!!
   pos.add(acceleration, velocity, time);
}
