#include <iostream>

#include "ColorSortBoard.h"
#include "ColorSortSolver.h"

int main()
{
   /*int numTubes;
   std::cout << "Enter number of tubes:";
   std::cin >> numTubes;

   int numBallsPerTube;
   std::cout << "Enter number of balls per tube:";
   std::cin >> numBallsPerTube;*/

   using enum class Ball;

   ColorSortBoard colorSortBoard( 11/*numTubes*/, 4/*ballsPerTube*/ );
   colorSortBoard.SetupTube( 0, { Blue, Orange, Green, Pink } );
   colorSortBoard.SetupTube( 1, { Aqua, Pink, Purple, Blue } );
   colorSortBoard.SetupTube( 2, { Blue, Lavender, Orange, Red } );
   colorSortBoard.SetupTube( 3, { Green, Red, Red, Aqua } );
   colorSortBoard.SetupTube( 4, { Lavender, Yellow, Yellow, Green } );
   colorSortBoard.SetupTube( 5, { Blue, Red, Purple, Orange } );
   colorSortBoard.SetupTube( 6, { Orange, Yellow, Pink, Aqua } );
   colorSortBoard.SetupTube( 7, { Lavender, Purple, Yellow, Purple } );
   colorSortBoard.SetupTube( 8, { Green, Aqua, Lavender, Pink } );

   //ColorSortBoard colorSortBoard( 2/*numTubes*/, 4/*ballsPerTube*/ );
   //colorSortBoard.SetupTube( 0, { Red, Red, Red } );
   //colorSortBoard.SetupTube( 1, { Red } );

   ColorSortSolver solver( colorSortBoard );
   std::vector steps = solver.Solve();

   int a = 0;
   a++;
}