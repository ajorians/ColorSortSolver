#pragma once

#include "ColorSortBoard.h"

#include <vector>

struct ColorSortMove;

class ColorSortSolver
{
public:
   ColorSortSolver( const ColorSortBoard& board );

   std::vector<ColorSortMove> Solve() const;

private:
   std::vector<ColorSortMove> GetPossibleMoves( const ColorSortBoard& board ) const;

private:
   ColorSortBoard _board;
};

