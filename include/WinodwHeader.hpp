#pragma once

#include "App.hpp"

// 円用の構造体が無いので、勝手に作る
struct Circle {
    Vector2 center;
    int radius;
};

class WindowHeader {
   private:
    // header の範囲
    Rectangle headerRect = {0, 0, app::SCREEN_W, 30};

    // window close button の描画位置
    Circle shutdownPoint = {{303, 15}, 8};

    // この範囲内をクリックで、window close
    Vector2 shutdownStartPoint = {shutdownPoint.center.x - shutdownPoint.radius, shutdownPoint.center.y - shutdownPoint.radius};

    Vector2 shutdownEndPoint = {shutdownPoint.center.x + shutdownPoint.radius, shutdownPoint.center.y + shutdownPoint.radius};

    // window header color
    Color WindowHeaderFill = {200, 200, 200, 255};

    // window close button color
    Color ShutDownPointFill = {130, 130, 130, 255};
    Color ShutDownPointMouseoverFill = {255, 255, 255, 255};
    Color ShutDownPointStroke = {100, 130, 130, 255};

    // title text style
    Vector2 titlePos = {20, 10};
    Color TitleTextFill = {18, 72, 127, 255};
    const int TitleTextSize = 15;
    const char *title = "Countdown Timer";

   public:
   // window を移動させているか？のフラグ
    bool dragMove = false;

    void DrawTitle();
    void DrawWindowHeader();
    void DrawWindowShutDownPoint();
    bool CheckWindowClose(Vector2 &mousePos, bool click);
    void CheckDragWindowRange(Vector2 &mousePos);
};