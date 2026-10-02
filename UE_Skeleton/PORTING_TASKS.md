Porting tasks — Popcorn -> Unreal Engine 5.4

Goal: Stepwise port so you learn modern C++ (C++23), STL, Unreal C++ and Blueprints.

Phase 1 — Inventory & Refactor (you and I)
1. Identify all platform-dependent code:
   - Drawing functions (HDC, GDI calls) — many files (Active_Brick.cpp, Ball.cpp, Platform.cpp, Level.cpp, etc.)
   - Window/Message loop (Main.cpp)
   - Timer (`SetTimer`) — `Engine.cpp`
   - Resources (`Popcorn.rc`, icons)
   - Text rendering (`TextOut`) — `Info_Panel.cpp`, `Label.cpp`

2. Create `platform-independent` core: move game logic (positions, collisions, state machines) into pure C++ classes using STL (`std::vector`, `std::string`) with no HDC/HWND usage. Candidate classes:
   - `Level` (AsLevel)
   - `Platform` (AsPlatform)
   - `Ball`/`Ball_Set`
   - `Brick`/`Active_Brick`
   - `Monster`/`Monster_Set`
   - `Info_Panel` (logic only; UI in UMG)

3. For each class file, make a mapping: methods that are rendering-only, input-only, or logic-only.

Phase 2 — Unreal skeleton & integration (in UE project)
1. Create UE5.4 C++ project `PopcornUE`.
2. Add Actors: `APlatformActor`, `ABallActor`, `ABrickActor`, `ALevelActor` and `APopcornGameMode` (skeletons in `UE_Skeleton/`).
3. Implement bridging adapters: call pure C++ logic from Actor components.
4. Replace drawing code with Meshes/Sprites; replace `TextOut` with UMG widgets.

Phase 3 — Implement features & polish
1. Implement collision mapping: use UE collision or keep deterministic logic and map positions to world space.
2. Implement input via UE Input system (Enhanced Input optional).
3. Implement Save/Load and player name input with UMG.

PORTING TASKS: Detailed file list (first pass)
- High priority (logic-heavy):
  - `Git_Game/Level.cpp`, `Level.h`
  - `Git_Game/Platform.cpp`, `Platform.h`
  - `Git_Game/Ball.cpp`, `Ball.h`, `Ball_Set.cpp`, `Ball_Set.h`
  - `Git_Game/Monster.cpp`, `Monster_Set.cpp`
  - `Git_Game/Engine.cpp`, `Engine.h` (game loop & timers)

- Rendering/UI heavy (port to UMG/Meshes):
  - `Active_Brick.*`, `Falling_Letter.*`, `Final_Letter.*`, `Info_Panel.*`, `Label.*`, `Game_Title.*`, `Level_Title.*`, `Indicator.*`

- Platform/init: `Main.cpp`, `Popcorn.vcxproj`, `framework.h`, `Config.*`

Next actionable step (you asked for stepwise):
- I will now generate the detailed mapping per file: list each file with categories: Logic-only, Rendering-only, Mixed, Platform-only, and provide recommended action (refactor, port to Actor, move logic to library). This will be saved to `UE_Skeleton/FILE_PORT_MAP.md`.

Do you want me to proceed and produce `FILE_PORT_MAP.md` now? If yes, I'll create it and mark next tasks.