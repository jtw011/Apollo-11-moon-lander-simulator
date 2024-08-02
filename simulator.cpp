/**********************************************************************
 * LAB 06
 * Lunar Lander simulation. This is the Game class and main()
 * Tanner Williams, Chisom Wonodi, and Caleb Schmid
 **********************************************************************/

#include "position.h"    // everything should have a point
#include "acceleration.h"// for ACCELERATION
#include "lander.h"      // for LANDER
#include "star.h"        // for STAR
#include "uiInteract.h"  // for INTERFACE
#include "uiDraw.h"      // for RANDOM and DRAW*
#include "ground.h"      // for GROUND
#include "test.h"        // for the unit tests
#include <cmath>         // for SQRT
#include <cassert>       // for ASSERT
#include <vector>        // for storing stars
using namespace std;

/************************************************************************
 * SIMULATOR CONSTANTS
 * Where everything that is constant is defined.
*************************************************************************/
#define NUM_OF_STARS     50
#define LANDER_WIDTH     20    // width of the lander

/*************************************************************************
 * SIMULATOR
 * Everything pertaining to the simulator.
 *************************************************************************/
class Simulator
{
public:
   Simulator(const Position & posUpperRight) : posUpperRight(posUpperRight), ground(posUpperRight), lander(posUpperRight), thrust() 
   {
      // Makes NUM_OF_STARS stars 
      for (int i = 0; i < NUM_OF_STARS; i++)
      {
         Star star(posUpperRight);
         stars.push_back(star);
      }
   }

   Position posUpperRight;
   Ground ground;
   Lander lander;
   Thrust thrust;
   vector<Star> stars;
};



/*************************************
 * CALLBACK
 * Handle one frame of the simulator
 **************************************/
void callBack(const Interface* pUI, void* p)
{
   // the first step is to cast the void pointer into a game object. This
   // is the first step of every single callback function in OpenGL. 
   Simulator * pSimulator = (Simulator *)p;

   ogstream gout;

   // draw the stars
   for (int i = 0; i < NUM_OF_STARS; i++)
      pSimulator->stars[i].draw(gout);

   // draw the ground
   pSimulator->ground.draw(gout);

   // input
   pSimulator->thrust.set(pUI);
   
   // update lander position
   if (pSimulator->lander.isFlying())
   {
      Acceleration movement = pSimulator->lander.input(pSimulator->thrust, -1.625);
      pSimulator->lander.coast(movement, 1.0 / 10.0);
   }
   
   // draw the lander
   pSimulator->lander.draw(pSimulator->thrust, gout);

   //draw stats in top left corner
   gout.setPosition(Position(10.0, pSimulator->posUpperRight.getY() - 20));
   gout << "Fuel:	" << (int)pSimulator->lander.getFuel() << "lbs" << "\n"
      << "Altitude:" << pSimulator->ground.getElevation(pSimulator->lander.getPosition()) << "meters" << "\n"
      << "Speed:   " << pSimulator->lander.getSpeed() << "m/s";

   //Print end of simulation message
   gout.setPosition(Position(pSimulator->posUpperRight.getX() / 2 - 125, (pSimulator->posUpperRight.getY() / 2) + 90));
   if (pSimulator->lander.isDead())
      gout << "Boom! You crashed the shuttle!... No survivors...";
   else if (pSimulator->lander.isLanded())
      gout << "Congratulations Armstrong! You landed the shuttle!";

   /**************************************************************
    * LAND/CRASH LOGIC
   ***************************************************************/
   // if on platform
   if (pSimulator->ground.onPlatform(pSimulator->lander.getPosition(), LANDER_WIDTH))
   {
      // safe speed
      if (pSimulator->lander.getSpeed() <= 4.0)
         pSimulator->lander.land();
      // unsafe speed
      else
         pSimulator->lander.crash();
   }
   // hitting the ground crashes you
   else if (pSimulator->ground.hitGround(pSimulator->lander.getPosition(), LANDER_WIDTH)
      && !pSimulator->lander.isLanded())
      pSimulator->lander.crash();

   // reset game if game over
   if (!pSimulator->lander.isFlying() && pUI->isSpace())
   {
      pSimulator->lander.reset(pSimulator->posUpperRight);
      pSimulator->ground.reset();
   }
}

/*********************************
 * Main is pretty sparse.  Just initialize
 * my LM type and call the display engine.
 * That is all!
 *********************************/
#ifdef _WIN32
#include <windows.h>
int WINAPI WinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ LPSTR pCmdLine,
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{
   // Run the unit tests
   testRunner();

   
   // Initialize OpenGL
   Position posUpperRight(400, 400);
   Interface ui("Lunar Lander", posUpperRight);

   // Initialize the game class
   Simulator simulator(posUpperRight);

   // set everything into action
   ui.run(callBack, (void *)&simulator);

   return 0;
}
