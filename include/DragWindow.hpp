#pragma once


#include "App.hpp"

class DragWindow {
   private:
   // モニターのサイズを取得
    const int MONITOR_WIDTH = GetMonitorWidth(1);
    const int MONITOR_HEIGHT = GetMonitorHeight(1);

    // window をモニターの何処まで移動させられるか、の座標。
    const int WINDOW_MAX_X = MONITOR_WIDTH - app::SCREEN_W;
    const int WINDOW_MAX_Y = MONITOR_HEIGHT - app::SCREEN_H;

    // window を移動させる為にクリックした座標
    Vector2 mouseWindowClickPoint;

    // DragWindow();
    // ~DragWindow();

   public:
    // 左クリックされた時の座標を保持するためのフラグ
    bool getMousePosFlag = false;
    
    void SetDragWindowPosition(Vector2 &mousePos);
};