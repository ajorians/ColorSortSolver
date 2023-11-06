#include "ColorSortSolver.h"

#include "ColorSortMove.h"

#include <algorithm>
#include <deque>
#include <iostream>

namespace
{
   template<typename T>
   bool AllOf( const std::vector<T>& vec, const T& t )
   {
      if ( vec.empty() )
         return false;

      for ( const auto& elem : vec )
         if ( elem != t )
            return false;

      return true;
   }

   bool NoGainMove( const ColorSortBoard& board, const ColorSortMove& move )
   {
      const auto& pickUpTube = board.GetTube( move.PickUpTubeIndex );
      const auto& dropTube = board.GetTube( move.DropTubeIndex );

      //If moving only ball to an empty tube
      if ( pickUpTube.size() == 1 && dropTube.size() == 0 )
         return true;

      //If moving from a completed tube
      if ( pickUpTube.size() == board.GetNumBallsPerTube() && AllOf( pickUpTube, pickUpTube[0]) )
         return true;

      return false;
   }

   bool haveSeenBoardBefore( const std::vector<ColorSortBoard>& boardsSeen, const ColorSortBoard& board )
   {
      if ( boardsSeen.cend() != std::find( boardsSeen.cbegin(), boardsSeen.cend(), board ) )
      {
         return true;
      }

      return false;
   }
}

ColorSortSolver::ColorSortSolver( const ColorSortBoard& board )
   : _board( board )
{

}

std::vector<ColorSortMove> ColorSortSolver::Solve() const
{
   int movesInvolved = 0;

   std::vector<ColorSortBoard> boardsPositionsSeen{ _board };

   std::deque<MoveSet> movesConsidering;
   for( const auto& move : GetPossibleMoves( _board ) )
   {
      movesConsidering.push_back( { move } );
   }

   while ( true )
   {
      //pop front set of moves off
      MoveSet moves = movesConsidering.front();
      movesConsidering.pop_front();

      if ( static_cast<int>( moves.size() ) > movesInvolved )
      {
         std::cout << "Considering " << moves.size() << " moves" << std::endl;
         movesInvolved = static_cast<int>( moves.size() );
      }

      ColorSortBoard board = _board.ApplyMoves( moves );

      //Check if solved
      if ( board.IsSolved() )
      {
         return moves;
      }

      //see possibles moves from this position
      std::vector possibleMoves = GetPossibleMoves( board );

      //evaluate them
      for ( const auto& possibleMove : possibleMoves )
      {
         if ( NoGainMove( board, possibleMove ) )
         {
            continue;
         }

         //Is this a revert of last move
         if ( possibleMove.BallColor == moves.back().BallColor &&
              possibleMove.DropTubeIndex == moves.back().PickUpTubeIndex &&
              possibleMove.PickUpTubeIndex == moves.back().DropTubeIndex )
         {
            continue;
         }

         ColorSortBoard newboard = board.ApplyMove( possibleMove );

         //Check if seen this board before and if so discard it
         if ( haveSeenBoardBefore( boardsPositionsSeen, newboard ) )
         {
            //Seen this before so skip it
            continue;
         }

         boardsPositionsSeen.push_back( newboard );

         MoveSet newMoves = moves;
         newMoves.push_back( possibleMove );

         //add moves to end
         movesConsidering.push_back( newMoves );
      }
   }

   return {};
}

std::vector<ColorSortMove> ColorSortSolver::GetPossibleMoves( const ColorSortBoard& board ) const
{
   std::vector<ColorSortMove> result;

   for ( int pickUpTubeIndex = 0; pickUpTubeIndex < board.GetNumTubes(); pickUpTubeIndex++ )
   {
      const auto& pickUpTube = board.GetTube( pickUpTubeIndex );

      for ( int dropTubeIndex = 0; dropTubeIndex < board.GetNumTubes(); dropTubeIndex++ )
      {
         if ( pickUpTubeIndex == dropTubeIndex )
            continue;

         const auto& dropTube = board.GetTube( dropTubeIndex );

         if ( pickUpTube.empty() )
            continue;

         if ( dropTube.size() >= board.GetNumBallsPerTube() )
            continue;

         if( !dropTube.empty() && pickUpTube.back() != dropTube.back() )
            continue;

         result.emplace_back( ColorSortMove
                              {
                                 .BallColor = pickUpTube.back(),
                                 .PickUpTubeIndex = pickUpTubeIndex,
                                 .DropTubeIndex = dropTubeIndex
                              } );
      }
   }

   return result;
}
