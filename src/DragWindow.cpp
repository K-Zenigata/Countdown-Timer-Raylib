#include "DragWindow.hpp"

// DragWindow::DragWindow() {}
// DragWindow::~DragWindow() {}

void DragWindow::SetDragWindowPosition(Vector2 &mousePos) {
    

    if (!getMousePosFlag) {
        // trueにより、左クリックされた時の座標が、クリックが解除されるまで保持される
        getMousePosFlag = true;

        // window を移動させる為にクリックした座標を、ここで保持しておく
        mouseWindowClickPoint.x = mousePos.x;
        mouseWindowClickPoint.y = mousePos.y;
    }

    // 現在のwindow の座標を取得
    Vector2 currentWindowPos = GetWindowPosition();

    // 新しいwindowの座標取得用
    Vector2 newWindowPos;

    // この計算をしないと、クリックした場所にwindowの左上が来てしまう
    newWindowPos.x = mousePos.x + currentWindowPos.x - mouseWindowClickPoint.x;
    newWindowPos.y = mousePos.y + currentWindowPos.y - mouseWindowClickPoint.y;

    // ウィンドウが画面外に出ないように制限
    if (newWindowPos.x < 0) newWindowPos.x = 0;
    if (newWindowPos.y < 0) newWindowPos.y = 0;

    // デュアルモニターは、非対応
    if (newWindowPos.x > WINDOW_MAX_X) newWindowPos.x = WINDOW_MAX_X;
    if (newWindowPos.y > WINDOW_MAX_Y) newWindowPos.y = WINDOW_MAX_Y;
    
    // 新たなwindow の座標をセット
    SetWindowPosition(newWindowPos.x, newWindowPos.y);
}