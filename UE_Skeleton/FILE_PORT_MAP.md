File port map — Popcorn -> UE5.4

Format: File — Category — Description — Action

Main files (game core)
- Git_Game/Engine.cpp — Mixed (Game loop + logic + SetTimer) — Controls game state and timer.
  Action: Extract logic into pure C++ GameCore; implement Tick in UE GameMode that calls GameCore->Update(DeltaTime).

- Git_Game/Main.cpp — Platform-only (Win32 window/message loop, double-buffering) — Creates window, message loop.
  Action: Remove; UE handles window and events.

- Git_Game/Level.* — Logic+Rendering — Level data, bricks, falling letters.
  Action: Split: move logic/data to GameCore C++ class; create `ALevelActor` to drive visuals and spawn `ABrickActor`.

- Git_Game/Platform.* — Logic+Rendering — Platform physics, states (Glue, Expanding, Laser).
  Action: Move state machine logic to GameCore; implement `APlatformActor` for visuals and input binding.

- Git_Game/Ball*. — Logic+Rendering — Ball physics and collisions.
  Action: Extract physics to GameCore ABall class; in UE use `ABallActor` to sync position/visuals.

- Git_Game/Ball_Set.* — Logic — Manages multiple balls.
  Action: Port logic into GameCore container (std::vector/UE TArray) and expose spawn/despawn to UE.

Rendering/UI heavy
- Active_Brick.* — Rendering heavy (GDI shapes) + some logic (teleport, states).
  Action: Logic -> GameCore brick state; visuals -> `ABrickActor` with mesh/material.

- Info_Panel.*, Label.* — UI rendering (TextOut) and indicators.
  Action: Use UMG for UI; move indicator logic into GameCore and update UMG widgets.

- Game_Title.*, Level_Title.* — Title animations and drawing.
  Action: Implement as UMG widgets or actors for animated HUD.

Misc / tools / config
- Config.* — Constants, colors, fonts.
  Action: Convert constants to UE `UPROPERTY(EditDefaultsOnly)` or keep in GameCore.

- Common.*, Tools.* — Utility functions, collision math.
  Action: Port utility code to portable C++ (STL) and reuse in UE.

Platform/resource
- Popcorn.rc, *.ico — Windows resources.
  Action: Convert icons to PNG and import into UE Content.

Next step: I'll create `FILE_PORT_MAP.md` with the above content saved. Then proceed to generate an initial `GameCore` C++ header in `UE_Skeleton/` that contains platform-independent classes (`GameCore`, `LevelCore`, `BallCore`, `PlatformCore`) implemented with STL and ready to be called from UE Actors. Proceed?