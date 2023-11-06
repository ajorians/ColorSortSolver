#include <iostream>

#include "ColorSortBoard.h"
#include "ColorSortSolver.h"

//35 steps
ColorSortBoard Get11TubeBoard()
{
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

   return colorSortBoard;
}

//21 steps
ColorSortBoard Get8TubeBoard()
{
   using enum class Ball;

   ColorSortBoard colorSortBoard( 8/*numTubes*/, 4/*ballsPerTube*/ );
   colorSortBoard.SetupTube( 0, { Blue, Yellow, Red, Purple} );
   colorSortBoard.SetupTube( 1, { Orange, Green, Green, Orange} );
   colorSortBoard.SetupTube( 2, { Blue, Yellow, Red, Blue} );
   colorSortBoard.SetupTube( 3, { Red, Blue, Purple, Yellow} );
   colorSortBoard.SetupTube( 4, { Purple, Orange, Yellow, Green } );
   colorSortBoard.SetupTube( 5, { Red, Orange, Green, Purple } );

   return colorSortBoard;
}

//6 steps
ColorSortBoard Get3TubeBoard()
{
   using enum class Ball;

   ColorSortBoard colorSortBoard( 3/*numTubes*/, 4/*ballsPerTube*/ );
   colorSortBoard.SetupTube( 0, { Yellow, Yellow, Blue, Blue } );
   colorSortBoard.SetupTube( 1, { Yellow, Yellow, Blue, Blue } );

   return colorSortBoard;
}

//1 steps
ColorSortBoard Get2TubeBoard()
{
   using enum class Ball;

   ColorSortBoard colorSortBoard( 2/*numTubes*/, 4/*ballsPerTube*/ );
   colorSortBoard.SetupTube( 0, { Red, Red, Red } );
   colorSortBoard.SetupTube( 1, { Red } );

   return colorSortBoard;
}

int main()
{
   using enum class Ball;

   std::vector<ColorSortBoard> boardsToSolve{
      Get2TubeBoard(),
      Get3TubeBoard(),
      Get8TubeBoard(),
      Get11TubeBoard()
   };

   for ( const auto& boardToSolve : boardsToSolve )
   {
      ColorSortSolver solver( boardToSolve );
      std::vector steps = solver.Solve();

      if ( steps.empty() )
      {
         std::cout << "Wasn't able to solve :(" << std::endl;
         continue;
      }

      int stepNumber = 0;
      for ( const auto& move : steps )
      {
         stepNumber++;
         std::cout << stepNumber << ": Move from tube " << move.PickUpTubeIndex + 1 << " to tube " << move.DropTubeIndex + 1 << std::endl;
      }
   }
}