How to integrate GameCore into a UE5.4 C++ project

1. Create UE project:
   - Open Unreal Engine 5.4 Editor
   - Create New Project -> C++ -> Blank -> Name: PopcornUE

2. Add GameCore files:
   - Copy `UE_Skeleton/GameCore.h` and `GameCore.cpp` into `Source/PopcornUE/` (or module source folder).
   - In Visual Studio / VS Code, add both files to the project (should be auto-detected).

3. Use in Actor:
   - Include "GameCore.h" in your Actor header.
   - Add a `GameCore Core;` member variable to your Actor or to `AGameMode`.
   - Call `Core.Update(DeltaSeconds);` from `Tick` or `APopcornGameMode::Tick`.
   - Sync Actor transforms with core state (e.g., set `ABallActor` location to `Core.balls[i].pos`).

4. Build and run. Use Blueprints to expose properties and tweak values.

Notes:
- For UE property reflection and replication, keep game data in UE types when needed. Use GameCore for pure logic and unit tests.
- To learn C++23 with STL: prefer `std::vector` in GameCore; convert to `TArray` only when exposing to UE's reflection system.
