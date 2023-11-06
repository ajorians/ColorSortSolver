#pragma once

#include "ColorSortBoard.h"

#include <vector>

enum class Ball;
struct ColorSortMove;

class ColorSortSolver
{
public:
   ColorSortSolver( const ColorSortBoard& board );

   std::vector<ColorSortMove> Solve() const;

private:
   std::vector<ColorSortMove> GetPossibleMoves( const ColorSortBoard& board ) const;

   std::vector<ColorSortBoard> MoveOnBoards( const std::vector<ColorSortBoard>& boards ) const;

private:
   ColorSortBoard _board;
};

