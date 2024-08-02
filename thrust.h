/***********************************************************************
 * Header File:
 *    Thrust : Represents activation of thrusters
 * Author:
 *    Br. Helfrich
 * Summary:
 *    down, clockwise, and counterclockwise
 ************************************************************************/

#pragma once

#include "uiInteract.h"  // for Interface

class TestLander;
class TestThrust;

 /*****************************************************
  * THRUST
  * Represents activation of thrusters
  *****************************************************/
class Thrust
{
   friend TestLander;
   friend TestThrust;
   
public:
   // Thrust is initially turned off
   Thrust() : mainEngine(false), clockwise(false), counterClockwise(false) {}

   // Get rotation in radians per second
   double rotation() const
   {
      return (clockwise ? 0.1 : 0.0) +
      (counterClockwise ? -0.1 : 0.0);
   }

   // get main engine thrust in  m / s ^ 2
   double mainEngineThrust() const
   {
      double THRUST = 45000.0; // in Newtons
      double WEIGHT = 15103.0; // in kg
      return THRUST / WEIGHT;
   }

   // reflect what is firing
   bool isMain()    const { return mainEngine;       }
   bool isClock()   const { return clockwise;        }
   bool isCounter() const { return counterClockwise; }

   // set the thrusters
   void set(const Interface * pUI)
   {
      // Casts int return type to bool
      mainEngine       = (pUI->isDown()  != 0);
      clockwise        = (pUI->isLeft()  != 0);
      counterClockwise = (pUI->isRight() != 0);
   }

private:
   bool mainEngine;
   bool clockwise;
   bool counterClockwise;
};
