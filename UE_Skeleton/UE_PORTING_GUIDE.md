Porting Popcorn to Unreal Engine 5.4 - Guide

Goals:
- Teach C++23, STL, UE C++ and Blueprints while porting.
- Incremental steps: prototype core mechanics -> integrate UI/assets -> polish.

Workflow:
1. Create a new UE5.4 C++ project named PopcornUE (Blank, with Starter Content optional).
2. Copy `UE_Skeleton` headers into `Source/PopcornUE/` and add corresponding .cpp implementations.
3. Replace Win32 drawing with `UStaticMeshComponent`, `UPaperSprite`, or `UCanvas` in UMG.
4. Use `Tick` + DeltaTime, not fixed FPS; if deterministic step required, implement fixed-step loop in GameMode.
5. Move game logic into Actors/Components: `Level` -> `ALevelActor`, `Platform` -> `APlatformActor`, `Ball` -> `ABallActor`, `Bricks` -> `ABrickActor`.
6. Use Blueprints for rapid iteration: expose properties with `UPROPERTY(EditAnywhere)` and functions with `UFUNCTION(BlueprintCallable)`.
7. Use STL (std::vector, std::string) in game logic where appropriate; prefer UE containers (`TArray`, `FString`) for UObject properties and replication.

Learning path suggestions:
- Phase 1: Modernize C++ code to C++23 and use STL locally (refactor data structures). Keep platform-independent logic in pure C++ files.
- Phase 2: Learn UE basics: Actors, Components, UPROPERTY, UFUNCTION, Blueprints, UMG.
- Phase 3: Implement core gameplay in UE C++ and expose to Blueprints for UI and tuning.

Files created in `UE_Skeleton/` are headers only; next step is to create a real UE project and implement .cpp files.
