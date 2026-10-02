#include "GameCore.h"
#include <iostream>

int main()
{
    GameCore core;
    core.platform.x = 50.0;
    core.platform.width = 30.0;

    core.LaunchBall({0.0, 1.0}, 60.0);

    for (int i = 0; i < 200; ++i)
    {
        core.Update(0.016); // ~60fps
        if (!core.balls.empty())
        {
            auto &b = core.balls[0];
            std::cout << "t="<< i << " pos=("<< b.pos.x <<","<< b.pos.y <<") vel=("<< b.vel.x <<","<< b.vel.y <<") active="<< b.active <<"\n";
        }
    }

    return 0;
}
