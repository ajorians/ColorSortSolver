#include "ColorSortBoard.h"
#include "ColorSortMove.h"

#include <cassert>

namespace
{
   bool AllSame( const std::vector<Ball>& balls )
   {
      assert( !balls.empty() );

      Ball first = balls.front();
      for ( Ball ball : balls )
      {
         if ( ball != first )
         {
            return false;
         }
      }

      return true;
   }
}

ColorSortBoard::ColorSortBoard( int numTubes, int ballsPerTube )
   : _ballsPerTube( ballsPerTube )
{
   for ( int i = 0; i < numTubes; i++ )
   {
      _tubes.push_back( {} );
   }
}

void ColorSortBoard::SetupTube( int tubeIndex, const std::vector<Ball>& balls )
{
   _tubes[tubeIndex] = balls;
}

int ColorSortBoard::GetNumTubes() const
{
   return static_cast<int>( _tubes.size() );
}

int ColorSortBoard::GetNumBallsPerTube() const
{
   return _ballsPerTube;
}

const std::vector<Ball>& ColorSortBoard::GetTube( int tubeIndex ) const
{
   return _tubes[tubeIndex];
}

bool ColorSortBoard::IsSolved() const
{
   for ( int tubeIndex = 0; tubeIndex < _tubes.size(); tubeIndex++ )
   {
      const std::vector<Ball>& balls = _tubes[tubeIndex];

      if ( !balls.empty() && balls.size() != _ballsPerTube )
         return false;

      if ( !balls.empty() && !AllSame( balls ) )
         return false;
   }

   return true;
}

ColorSortBoard ColorSortBoard::ApplyMove( const ColorSortMove& move ) const
{
   ColorSortBoard copyBoard( *this );

   Ball ball = copyBoard._tubes[move.PickUpTubeIndex].back();
   copyBoard._tubes[move.PickUpTubeIndex].pop_back();
   copyBoard._tubes[move.DropTubeIndex].push_back( ball );

   return copyBoard;
}

ColorSortBoard ColorSortBoard::ApplyMoves( const std::vector<ColorSortMove>& moves ) const
{
   ColorSortBoard copyBoard( *this );

   for ( const auto& move : moves )
   {
      Ball ball = copyBoard._tubes[move.PickUpTubeIndex].back();
      copyBoard._tubes[move.PickUpTubeIndex].pop_back();
      copyBoard._tubes[move.DropTubeIndex].push_back( ball );
   }

   return copyBoard;
}

