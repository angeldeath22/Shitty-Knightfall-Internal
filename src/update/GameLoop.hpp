#pragma once

class GameLoop {
public:
    static void Initialize();
    static void Update();

    static bool IsInGame();
    static void OnFrame();
};