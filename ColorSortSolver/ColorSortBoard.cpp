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

bool ColorSortBoard::operator==( const ColorSortBoard& rhs ) const
{
   assert( _tubes.size() == rhs._tubes.size() );
   int numTubes = static_cast<int>( _tubes.size() );

   for ( int tubeIndex = 0; tubeIndex < numTubes; tubeIndex++ )
   {
      bool matchesAnotherTube = false;
      for ( int inputTubeIndex = 0; inputTubeIndex < numTubes; inputTubeIndex++ )
      {
         if ( _tubes[tubeIndex] == rhs._tubes[inputTubeIndex] )
         {
            matchesAnotherTube = true;
            break;
         }
      }

      if ( !matchesAnotherTube )
      {
         //Tube doesn't match another tube so they are not equal
         return false;
      }
   }

   return true;
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
   return ApplyMoves( { move } );
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

