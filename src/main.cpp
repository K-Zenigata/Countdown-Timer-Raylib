#include "App.hpp"
#include "CountdownTimer.hpp"
#include "DragWindow.hpp"
#include "WinodwHeader.hpp"

class Game {
   public:
   // window �𓮂������߂̃N���X
    DragWindow dragWindow;
    // window �̃w�b�_�[����(drag�o���镔��)�̃N���X
    WindowHeader windowHeader;
    // countdownTimer �{���̃N���X
    CountdownTimer countdownTimer;
    // window �̔w�i�F
    Color WindowBackground = BLACK;
    // window �̘g���̐F
    Color WindowFrameStroke = GRAY;
    // window �̘g�́A{x, y, width, height}
    Rectangle windowFrameRect = {0, 0, 320, 450};
    // �}�E�X�|�C���^�[�̍��W�p x, y
    Vector2 mousePos;
    // window ����鎞�́A�{�^���̃t���O
    bool gameLoop = true;

    void input() {
        // ���݂̃}�E�X�|�C���^�[�̍��W���擾
        mousePos = GetMousePosition();

        // ���N���b�N
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            // window close �{�^�� ���A�N���b�N���ꂽ���H
            // �N���b�N���ꂽ�Ȃ�AgameLoop ��false �ɂ��āAwhile������E�o
            // window �𓮂����Ă���Œ��́A�����ɂ��Ă���
            if (windowHeader.CheckWindowClose(mousePos, true) && !windowHeader.dragMove) gameLoop = false;

            // �N���b�N�����ꏊ���Aheader ���ł���Ȃ�΁Awindow �𓮂�����
            // ���̊֐���bool�ɂ��Ă͂����Ȃ�
            windowHeader.CheckDragWindowRange(mousePos);

            // window���h���b�O���ē�����
            if (windowHeader.dragMove) {
                dragWindow.SetDragWindowPosition(mousePos);
            }
        }

        // ���N���b�N���������ꂽ��
        if (IsMouseButtonUp(MOUSE_LEFT_BUTTON)) {

            // window�𓮂������߂ɃN���b�N�����A�N���b�N���W�擾�̃t���O������
            dragWindow.getMousePosFlag = false;

            // window �̈ړ����I��
            windowHeader.dragMove = false;
        }
    }

    void update() {
        // timer�̃J�E���g�� Update
        countdownTimer.UpdateSetCount();
    }

    void draw() {
        // header �����̕\��
        windowHeader.DrawWindowHeader();
        // title ��\��
        windowHeader.DrawTitle();
        // ����{�^���̕\��
        windowHeader.DrawWindowShutDownPoint();
        // ����́Amouseover�p�Ȃ̂ōŌ�ɋL�q
        windowHeader.CheckWindowClose(mousePos, false);

        // Window�̘g����`��
        DrawRectangleLinesEx(windowFrameRect, 3, WindowFrameStroke);

        // button �̕`��
        countdownTimer.DrawSetCountButton();
        countdownTimer.DrawControlButton();
    }

    void run() {
        SetTargetFPS(60);

        while (!WindowShouldClose() && gameLoop)  // Detect window close button or ESC key
        {
            BeginDrawing();
            ClearBackground(WindowBackground);
            // window close ��mouseover�ŁA�|�C���^�[��ς���̂ŁA������default��ݒ�
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);

            input();
            update();
            draw();

            EndDrawing();
        }

        // sound file �̉��
        UnloadSound(countdownTimer.sound);

        CloseWindow();
    }
};

int main() {
    // raylib ���g���Ȃ�A�K�����ꂪ1�Ԗ�?
    InitWindow(app::SCREEN_W, app::SCREEN_H, "Countdown Timer");

    // window�̐ݒ��ύX���ă{�[�_�[���X�E�B���h�E�ɂ���
    SetWindowState(FLAG_WINDOW_UNDECORATED);

    // window�̏������W
    SetWindowPosition(300, 50);

    // ���y�t�@�C���p
    InitAudioDevice();

    Game game;
    game.run();

    return 0;
}
