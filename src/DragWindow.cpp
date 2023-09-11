#include "DragWindow.hpp"

// DragWindow::DragWindow() {}
// DragWindow::~DragWindow() {}

void DragWindow::SetDragWindowPosition(Vector2 &mousePos) {
    

    if (!getMousePosFlag) {
        // true�ɂ��A���N���b�N���ꂽ���̍��W���A�N���b�N�����������܂ŕێ������
        getMousePosFlag = true;

        // window ���ړ�������ׂɃN���b�N�������W���A�����ŕێ����Ă���
        mouseWindowClickPoint.x = mousePos.x;
        mouseWindowClickPoint.y = mousePos.y;
    }

    // ���݂�window �̍��W���擾
    Vector2 currentWindowPos = GetWindowPosition();

    // �V����window�̍��W�擾�p
    Vector2 newWindowPos;

    // ���̌v�Z�����Ȃ��ƁA�N���b�N�����ꏊ��window�̍��オ���Ă��܂�
    newWindowPos.x = mousePos.x + currentWindowPos.x - mouseWindowClickPoint.x;
    newWindowPos.y = mousePos.y + currentWindowPos.y - mouseWindowClickPoint.y;

    // �E�B���h�E����ʊO�ɏo�Ȃ��悤�ɐ���
    if (newWindowPos.x < 0) newWindowPos.x = 0;
    if (newWindowPos.y < 0) newWindowPos.y = 0;

    // �f���A�����j�^�[�́A��Ή�
    if (newWindowPos.x > WINDOW_MAX_X) newWindowPos.x = WINDOW_MAX_X;
    if (newWindowPos.y > WINDOW_MAX_Y) newWindowPos.y = WINDOW_MAX_Y;
    
    // �V����window �̍��W���Z�b�g
    SetWindowPosition(newWindowPos.x, newWindowPos.y);
}