#include "WinodwHeader.hpp"

// title�̕\��
void WindowHeader::DrawTitle() {
    //
    DrawText(title, titlePos.x, titlePos.y, TitleTextSize, TitleTextFill);
}

// header �����̕\��
void WindowHeader::DrawWindowHeader() {
    //
    DrawRectangle(headerRect.x, headerRect.y, headerRect.width, headerRect.height, WindowHeaderFill);
}

// window �����{�^���̕\��
void WindowHeader::DrawWindowShutDownPoint() {
    DrawCircle(shutdownPoint.center.x, shutdownPoint.center.y, shutdownPoint.radius, ShutDownPointFill);
    DrawCircleLines(shutdownPoint.center.x, shutdownPoint.center.y, shutdownPoint.radius, ShutDownPointStroke);
}

// click, mouseover �𕹗p
bool WindowHeader::CheckWindowClose(Vector2 &mousePos, bool click = false) {
    bool flag = false;

    // �N���b�N�ʒu���A shutdown point �Ȃ�΁Awindow close
    if (mousePos.x >= shutdownStartPoint.x && mousePos.y >= shutdownStartPoint.y && mousePos.x <= shutdownEndPoint.x &&
        mousePos.y <= shutdownEndPoint.y) {
        // click ��false �Ȃ�Amouseover
        if (click) {
            flag = true;
        } else {
            // mouseover �ŁAcircle ���㏑�� 
            // css �Ō����Ƃ���́Ahover �̌���
            DrawCircle(shutdownPoint.center.x, shutdownPoint.center.y, shutdownPoint.radius, ShutDownPointMouseoverFill);
        }
    }

    return flag;
}

// window���Adrag move �ł��邩�̃`�F�b�N
// ���̊֐����Abool�łȂ��̂́A�N���b�N������N���b�N�����������܂Ńt���O��true�ɂ��Ă����ׁB�������Ȃ��ƃ|�C���^�[������āAwindow�𓮂����Ȃ��Ȃ邩��B
void WindowHeader::CheckDragWindowRange(Vector2 &mousePos) {
    // �N���b�N�����ꏊ���A���͈͓̔��Ȃ�΁Awindow�𓮂�����
    if (mousePos.x >= headerRect.x && mousePos.x <= headerRect.width && mousePos.y >= headerRect.y && mousePos.y <= headerRect.height) {
        dragMove = true;
    }
}