UE5.4 Skeleton for Popcorn port

Goals:
- Provide minimal Unreal Engine 5.4 project skeleton for port planning.
- Map core game classes to UE equivalents.
- Provide starter C++ Actor headers for `Platform`, `Ball`, `Brick`, `Level`, and a `GameMode`.

Steps:
1. Create new UE5 C++ project (Blank) in Unreal Editor named `PopcornUE`.
2. Copy skeleton headers into `Source/PopcornUE/` and implement logic progressively.
3. Replace GDI drawing calls with UE `UStaticMeshComponent`/`UPaperSprite`/UMG for UI.

Note: This skeleton contains headers only. Implementation should be added in UE after creating the project and integrating into its module.
