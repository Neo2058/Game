#include "GameCore.h"
#include <cassert>
#include <iostream>

void TestBallReflectsOnPlatformCenter()
{
    GameCore core;
    core.platform.x = 50.0;
    core.platform.width = 40.0; // wide platform

    // place ball just above platform, moving down
    BallCore b;
    // start slightly above platform so one update step causes collision
    b.pos = {50.0, 175.5};
    b.vel = {10.0, 60.0}; // moving down (positive y)
    b.radius = 2.0;
    core.balls.push_back(b);

    core.Update(0.016);

    // after update, expect ball to have negative y velocity (reflected)
    auto &nb = core.balls[0];
    std::cout<<"After collision vel=("<<nb.vel.x<<","<<nb.vel.y<<") pos=("<<nb.pos.x<<","<<nb.pos.y<<")\n";
    assert(nb.vel.y < 0.0);
}

void TestBallReflectsWithAngle()
{
    GameCore core;
    core.platform.x = 50.0;
    core.platform.width = 40.0; // wide platform

    // ball hits near left edge
    BallCore b;
    // start slightly above platform so one update step causes collision
    b.pos = {40.0, 175.5};
    b.vel = {0.0, 50.0};
    b.radius = 2.0;
    core.balls.push_back(b);

    core.Update(0.016);

    auto &nb = core.balls[0];
    std::cout<<"Edge hit vel=("<<nb.vel.x<<","<<nb.vel.y<<")\n";
    assert(nb.vel.y < 0.0);
    assert(nb.vel.x < 0.0); // deflected to left
}

int main()
{
    TestBallReflectsOnPlatformCenter();
    TestBallReflectsWithAngle();
    std::cout<<"All collision tests passed\n";
    return 0;
}
