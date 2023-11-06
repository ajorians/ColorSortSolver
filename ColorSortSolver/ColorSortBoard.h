#pragma once

#include "ColorSortBall.h"
#include "ColorSortMove.h"

#include <vector>

class ColorSortBoard
{
public:
   ColorSortBoard( int numTubes, int ballsPerTube );
   ColorSortBoard( const ColorSortBoard& rhs ) = default;
   bool operator==(const ColorSortBoard& rhs) const;
   void SetupTube( int tubeIndex, const std::vector<Ball>& balls );

   int GetNumTubes() const;
   int GetNumBallsPerTube() const;
   const std::vector<Ball>& GetTube( int tubeIndex ) const;

   bool IsSolved() const;

   ColorSortBoard ApplyMove( const ColorSortMove& move ) const;
   ColorSortBoard ApplyMoves( const std::vector<ColorSortMove>& moves ) const;

private:
   std::vector<std::vector<Ball>> _tubes;
   int _ballsPerTube;
};
