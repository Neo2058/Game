#pragma once

#include <vector>
#include <string>
#include <cmath>

// Platform-independent game core for Popcorn
// Use C++23 and STL-friendly types. This is minimal and intended
// as the logic backbone to be called from UE Actors.

struct Vec2
{
    double x{0.0}, y{0.0};
    Vec2() = default;
    Vec2(double X, double Y) : x(X), y(Y) {}
    Vec2 operator+(const Vec2& o) const { return {x+o.x, y+o.y}; }
    Vec2 operator-(const Vec2& o) const { return {x-o.x, y-o.y}; }
    Vec2 operator*(double s) const { return {x*s, y*s}; }
};

struct BallCore
{
    Vec2 pos;
    Vec2 vel;
    double radius{4.0};
    bool active{true};

    void Update(double dt)
    {
        pos.x += vel.x * dt;
        pos.y += vel.y * dt;
    }
};

struct PlatformCore
{
    double x{0.0};
    double width{30.0};
    double speed{200.0};

    void MoveLeft(double dt) { x -= speed * dt; }
    void MoveRight(double dt) { x += speed * dt; }
};

struct BrickCore
{
    int type{0};
    int hp{1};
    double x{0.0}, y{0.0};
    bool alive{true};
};

class GameCore
{
public:
    std::vector<BallCore> balls;
    std::vector<BrickCore> bricks;
    PlatformCore platform;
    int score{0};

    GameCore() = default;

    void Update(double dt)
    {
        for (auto &b : balls)
            if (b.active)
                b.Update(dt);

        // simplistic collision with bottom
        for (auto &b : balls)
            if (b.active && b.pos.y > 200.0)
                b.active = false;

        // collisions with platform (circle-AABB). Compute collision and reflect with angle
        const double platY = 180.0; // platform y in core coords
        const double platHalfW = platform.width * 0.5;
        const double platHalfH = 4.0; // half-height for platform thickness
        const double maxDeflectAngle = 65.0 * M_PI / 180.0; // max deflection from vertical

        for (auto &b : balls)
        {
            if (!b.active) continue;

            // AABB for platform
            double left = platform.x - platHalfW;
            double right = platform.x + platHalfW;
            double top = platY - platHalfH;
            double bottom = platY + platHalfH;

            // Find nearest point on AABB to circle center
            double nearestX = std::max(left, std::min(b.pos.x, right));
            double nearestY = std::max(top, std::min(b.pos.y, bottom));

            double dx = b.pos.x - nearestX;
            double dy = b.pos.y - nearestY;
            double dist2 = dx*dx + dy*dy;

            if (dist2 <= (b.radius * b.radius) && b.vel.y > 0.0)
            {
                // collision occurred; compute hit relative position along platform
                double hitRel = 0.0;
                if (platHalfW > 0.0)
                    hitRel = (b.pos.x - platform.x) / platHalfW; // -1..1

                // clamp
                if (hitRel < -1.0) hitRel = -1.0;
                if (hitRel > 1.0) hitRel = 1.0;

                // compute new angle: vertical up plus deflection
                double angle = hitRel * maxDeflectAngle; // negative=left, positive=right
                double speed = std::sqrt(b.vel.x*b.vel.x + b.vel.y*b.vel.y);
                if (speed < 1e-6) speed = 60.0; // default speed if nearly zero

                // new velocity: up is negative y
                b.vel.x = speed * std::sin(angle);
                b.vel.y = -fabs(speed * std::cos(angle));

                // push ball just above platform to avoid sticking
                b.pos.y = top - b.radius - 0.01;
            }
        }

        // TODO: add collision detection with bricks
    }

    void LaunchBall(const Vec2 &dir, double speed)
    {
        BallCore b;
        b.pos = {platform.x, 180.0};
        b.vel = {dir.x * speed, dir.y * speed};
        balls.push_back(b);
    }

    void SpawnBrick(double x, double y, int type = 0)
    {
        BrickCore br;
        br.x = x; br.y = y; br.type = type;
        bricks.push_back(br);
    }
};
