#include "App.hpp"
#include "CountdownTimer.hpp"
#include "DragWindow.hpp"
#include "WinodwHeader.hpp"

class Game {
   public:
   // window を動かすためのクラス
    DragWindow dragWindow;
    // window のヘッダー部分(drag出来る部分)のクラス
    WindowHeader windowHeader;
    // countdownTimer 本隊のクラス
    CountdownTimer countdownTimer;
    // window の背景色
    Color WindowBackground = BLACK;
    // window の枠線の色
    Color WindowFrameStroke = GRAY;
    // window の枠の、{x, y, width, height}
    Rectangle windowFrameRect = {0, 0, 320, 450};
    // マウスポインターの座標用 x, y
    Vector2 mousePos;
    // window を閉じる時の、ボタンのフラグ
    bool gameLoop = true;

    void input() {
        // 現在のマウスポインターの座標を取得
        mousePos = GetMousePosition();

        // 左クリック
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            // window close ボタン が、クリックされたか？
            // クリックされたなら、gameLoop をfalse にして、while文から脱出
            // window を動かしている最中は、無効にしておく
            if (windowHeader.CheckWindowClose(mousePos, true) && !windowHeader.dragMove) gameLoop = false;

            // クリックした場所が、header 内であるならば、window を動かせる
            // この関数をboolにしてはいけない
            windowHeader.CheckDragWindowRange(mousePos);

            // windowをドラッグして動かす
            if (windowHeader.dragMove) {
                dragWindow.SetDragWindowPosition(mousePos);
            }
        }

        // 左クリックが解除されたら
        if (IsMouseButtonUp(MOUSE_LEFT_BUTTON)) {

            // windowを動かすためにクリックした、クリック座標取得のフラグを解除
            dragWindow.getMousePosFlag = false;

            // window の移動を終了
            windowHeader.dragMove = false;
        }
    }

    void update() {
        // timerのカウントを Update
        countdownTimer.UpdateSetCount();
    }

    void draw() {
        // header 部分の表示
        windowHeader.DrawWindowHeader();
        // title を表示
        windowHeader.DrawTitle();
        // 閉じるボタンの表示
        windowHeader.DrawWindowShutDownPoint();
        // これは、mouseover用なので最後に記述
        windowHeader.CheckWindowClose(mousePos, false);

        // Windowの枠線を描画
        DrawRectangleLinesEx(windowFrameRect, 3, WindowFrameStroke);

        // button の描画
        countdownTimer.DrawSetCountButton();
        countdownTimer.DrawControlButton();
    }

    void run() {
        SetTargetFPS(60);

        while (!WindowShouldClose() && gameLoop)  // Detect window close button or ESC key
        {
            BeginDrawing();
            ClearBackground(WindowBackground);
            // window close のmouseoverで、ポインターを変えるので、ここでdefaultを設定
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);

            input();
            update();
            draw();

            EndDrawing();
        }

        // sound file の解放
        UnloadSound(countdownTimer.sound);

        CloseWindow();
    }
};

int main() {
    // raylib を使うなら、必ずこれが1番目?
    InitWindow(app::SCREEN_W, app::SCREEN_H, "Countdown Timer");

    // windowの設定を変更してボーダーレスウィンドウにする
    SetWindowState(FLAG_WINDOW_UNDECORATED);

    // windowの初期座標
    SetWindowPosition(300, 50);

    // 音楽ファイル用
    InitAudioDevice();

    Game game;
    game.run();

    return 0;
}
