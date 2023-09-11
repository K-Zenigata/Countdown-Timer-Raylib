#pragma once

#include "App.hpp"

// �~�p�̍\���̂������̂ŁA����ɍ��
struct Circle {
    Vector2 center;
    int radius;
};

class WindowHeader {
   private:
    // header �͈̔�
    Rectangle headerRect = {0, 0, app::SCREEN_W, 30};

    // window close button �̕`��ʒu
    Circle shutdownPoint = {{303, 15}, 8};

    // ���͈͓̔����N���b�N�ŁAwindow close
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
   // window ���ړ������Ă��邩�H�̃t���O
    bool dragMove = false;

    void DrawTitle();
    void DrawWindowHeader();
    void DrawWindowShutDownPoint();
    bool CheckWindowClose(Vector2 &mousePos, bool click);
    void CheckDragWindowRange(Vector2 &mousePos);
};