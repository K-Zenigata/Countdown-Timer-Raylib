#include "WinodwHeader.hpp"

// titleの表示
void WindowHeader::DrawTitle() {
    //
    DrawText(title, titlePos.x, titlePos.y, TitleTextSize, TitleTextFill);
}

// header 部分の表示
void WindowHeader::DrawWindowHeader() {
    //
    DrawRectangle(headerRect.x, headerRect.y, headerRect.width, headerRect.height, WindowHeaderFill);
}

// window を閉じるボタンの表示
void WindowHeader::DrawWindowShutDownPoint() {
    DrawCircle(shutdownPoint.center.x, shutdownPoint.center.y, shutdownPoint.radius, ShutDownPointFill);
    DrawCircleLines(shutdownPoint.center.x, shutdownPoint.center.y, shutdownPoint.radius, ShutDownPointStroke);
}

// click, mouseover を併用
bool WindowHeader::CheckWindowClose(Vector2 &mousePos, bool click = false) {
    bool flag = false;

    // クリック位置が、 shutdown point ならば、window close
    if (mousePos.x >= shutdownStartPoint.x && mousePos.y >= shutdownStartPoint.y && mousePos.x <= shutdownEndPoint.x &&
        mousePos.y <= shutdownEndPoint.y) {
        // click がfalse なら、mouseover
        if (click) {
            flag = true;
        } else {
            // mouseover で、circle を上書き 
            // css で言うところの、hover の効果
            DrawCircle(shutdownPoint.center.x, shutdownPoint.center.y, shutdownPoint.radius, ShutDownPointMouseoverFill);
        }
    }

    return flag;
}

// windowを、drag move できるかのチェック
// この関数が、boolでないのは、クリックしたらクリックが解除されるまでフラグをtrueにしておく為。そうしないとポインターがずれて、windowを動かせなくなるから。
void WindowHeader::CheckDragWindowRange(Vector2 &mousePos) {
    // クリックした場所が、この範囲内ならば、windowを動かせる
    if (mousePos.x >= headerRect.x && mousePos.x <= headerRect.width && mousePos.y >= headerRect.y && mousePos.y <= headerRect.height) {
        dragMove = true;
    }
}