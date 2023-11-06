#pragma once

#include "ColorSortBall.h"

#include <vector>

struct ColorSortMove
{
   Ball BallColor;
   int PickUpTubeIndex;
   int DropTubeIndex;
};

using MoveSet = std::vector<ColorSortMove>;
