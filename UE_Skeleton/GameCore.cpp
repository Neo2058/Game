#include "GameCore.h"

// Currently contains inline simple implementations in header; expand here if needed.

// Example helper: initialize a simple grid of bricks
void InitializeBricks(GameCore &core, int rows, int cols, double startX, double startY, double dx, double dy)
{
    for (int r = 0; r < rows; ++r)
    {
        for (int c = 0; c < cols; ++c)
        {
            core.SpawnBrick(startX + c * dx, startY + r * dy, 0);
        }
    }
}
