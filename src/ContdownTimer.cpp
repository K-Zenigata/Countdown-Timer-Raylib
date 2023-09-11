#include "CountdownTimer.hpp"

// raygui.h  は、ここに無いとだめ！.hppに記述しない
// 使用するファイルで include
#include "raygui.h"

void CountdownTimer::UpdateSetCount() {
    // カウントを、時、分、秒に変換
    int hours = timeLeft / 3600;
    int minutes = (timeLeft % 3600) / 60;
    int seconds = timeLeft % 60;

    // タイマーを、 00:00:00 の形に変換
    std::ostringstream stream;
    stream << std::setfill('0') << std::setw(2) << hours << ":" << std::setfill('0') << std::setw(2) << minutes << ":" << std::setfill('0')
           << std::setw(2) << seconds;

    // ostringstream -> string
    std::string formattedTime = stream.str();
    // string -> const char*
    const char* displayTime = formattedTime.c_str();

    DrawTimerDisplay(displayTime);
}

void CountdownTimer::DrawTimerDisplay(const char* displayTime) {
    // displayの枠線を描画
    DrawRectangleLinesEx(displayFrameRect, 2, GRAY);

    // 描画する文字列の幅と高さを取得
    Vector2 textSize = MeasureTextEx(GetFontDefault(), displayTime, displayTextSize, 2);

    // displayの中央に文字列を配置
    Vector2 textPosition = {displayFrameRect.x + (displayFrameRect.width - textSize.x) / 2,
                            displayFrameRect.y + (displayFrameRect.height - textSize.y) / 2};

    // 文字列を描画
    DrawTextEx(GetFontDefault(), displayTime, textPosition, displayTextSize, 2, YELLOW);
}

void CountdownTimer::DrawSetCountButton() {
    // ボタンの背景色を設定
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, SetCountBtnFill);
    // ボタンの枠線の色を設定
    GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, SetCountBtnStroke);
    // ボタンのテキスト色を設定
    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, SetCountBtnTextFll);
    // ボタンの文字位置を設定
    GuiSetStyle(BUTTON, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
    // ボタンの文字サイズを設定
    GuiSetStyle(DEFAULT, TEXT_SIZE, SetCountBtnTextSize);

    if (GuiButton(hourBtn, "Hr") && !running) {
        timeLeft += 3600;
        timeCount = timeLeft;
    }
    if (GuiButton(minuteBtn, "Min") && !running) {
        timeLeft += 60;
        timeCount = timeLeft;
    }
    if (GuiButton(secondBtn, "Sec") && !running) {
        timeLeft += 1;
        timeCount = timeLeft;
    }
}

void CountdownTimer::DrawControlButton() {
    // Start, Reset Button

    // ボタンの背景色を設定
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, SetControlBtnFill);
    // ボタンの枠線の色を設定
    GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, SetControlBtnStroke);
    // ボタンの文字位置を設定
    GuiSetStyle(BUTTON, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
    // ボタンの文字サイズを設定
    GuiSetStyle(DEFAULT, TEXT_SIZE, SetControlBtnTextSize);

    // start -> yellow, stop -> red
    const int btnTextColor = running ? SetStopBtnTextFill : SetStartBtnTextFill;

    // ボタンのテキスト色を設定
    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, btnTextColor);

    // start ボタンを描画
    if (GuiButton(startBtn, startText)) {
        if (running == false) {
            running = true;
            StopSound(sound);

            // GetTime() = InitWindow()されてからの経過時間
            startTime = GetTime();

            startText = "Stop";
        } else {
            running = false;
            // stop が押されたら、残り時間を再セット
            timeCount = timeLeft;
        }
    }

    // start ボタンが押されたままの状態
    if (running) {
        double currentTime = GetTime();

        // タイムを更新
        timeLeft = startTime + timeCount - currentTime;

        // timer end
        if (timeLeft < 0) {
            PlaySound(sound);

            running = false;
            timeLeft = 0;
        }
    } else {
        startText = "Start";
    }

    // reset button のテキスト色を設定
    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, SetResetBtnTextFill);

    // reset ボタンを描画
    if (GuiButton(resetBtn, "Reset") && !running) {
        StopSound(sound);
        timeLeft = 0;
        timeCount = 0;
    }
}