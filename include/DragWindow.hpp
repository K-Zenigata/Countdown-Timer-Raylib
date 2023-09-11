#pragma once


#include "App.hpp"

class DragWindow {
   private:
   // ���j�^�[�̃T�C�Y���擾
    const int MONITOR_WIDTH = GetMonitorWidth(1);
    const int MONITOR_HEIGHT = GetMonitorHeight(1);

    // window �����j�^�[�̉����܂ňړ��������邩�A�̍��W�B
    const int WINDOW_MAX_X = MONITOR_WIDTH - app::SCREEN_W;
    const int WINDOW_MAX_Y = MONITOR_HEIGHT - app::SCREEN_H;

    // window ���ړ�������ׂɃN���b�N�������W
    Vector2 mouseWindowClickPoint;

    // DragWindow();
    // ~DragWindow();

   public:
    // ���N���b�N���ꂽ���̍��W��ێ����邽�߂̃t���O
    bool getMousePosFlag = false;
    
    void SetDragWindowPosition(Vector2 &mousePos);
};