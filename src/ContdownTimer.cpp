#include "CountdownTimer.hpp"

// raygui.h  �́A�����ɖ����Ƃ��߁I.hpp�ɋL�q���Ȃ�
// �g�p����t�@�C���� include
#include "raygui.h"

void CountdownTimer::UpdateSetCount() {
    // �J�E���g���A���A���A�b�ɕϊ�
    int hours = timeLeft / 3600;
    int minutes = (timeLeft % 3600) / 60;
    int seconds = timeLeft % 60;

    // �^�C�}�[���A 00:00:00 �̌`�ɕϊ�
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
    // display�̘g����`��
    DrawRectangleLinesEx(displayFrameRect, 2, GRAY);

    // �`�悷�镶����̕��ƍ������擾
    Vector2 textSize = MeasureTextEx(GetFontDefault(), displayTime, displayTextSize, 2);

    // display�̒����ɕ������z�u
    Vector2 textPosition = {displayFrameRect.x + (displayFrameRect.width - textSize.x) / 2,
                            displayFrameRect.y + (displayFrameRect.height - textSize.y) / 2};

    // �������`��
    DrawTextEx(GetFontDefault(), displayTime, textPosition, displayTextSize, 2, YELLOW);
}

void CountdownTimer::DrawSetCountButton() {
    // �{�^���̔w�i�F��ݒ�
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, SetCountBtnFill);
    // �{�^���̘g���̐F��ݒ�
    GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, SetCountBtnStroke);
    // �{�^���̃e�L�X�g�F��ݒ�
    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, SetCountBtnTextFll);
    // �{�^���̕����ʒu��ݒ�
    GuiSetStyle(BUTTON, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
    // �{�^���̕����T�C�Y��ݒ�
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

    // �{�^���̔w�i�F��ݒ�
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, SetControlBtnFill);
    // �{�^���̘g���̐F��ݒ�
    GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, SetControlBtnStroke);
    // �{�^���̕����ʒu��ݒ�
    GuiSetStyle(BUTTON, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
    // �{�^���̕����T�C�Y��ݒ�
    GuiSetStyle(DEFAULT, TEXT_SIZE, SetControlBtnTextSize);

    // start -> yellow, stop -> red
    const int btnTextColor = running ? SetStopBtnTextFill : SetStartBtnTextFill;

    // �{�^���̃e�L�X�g�F��ݒ�
    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, btnTextColor);

    // start �{�^����`��
    if (GuiButton(startBtn, startText)) {
        if (running == false) {
            running = true;
            StopSound(sound);

            // GetTime() = InitWindow()����Ă���̌o�ߎ���
            startTime = GetTime();

            startText = "Stop";
        } else {
            running = false;
            // stop �������ꂽ��A�c�莞�Ԃ��ăZ�b�g
            timeCount = timeLeft;
        }
    }

    // start �{�^���������ꂽ�܂܂̏��
    if (running) {
        double currentTime = GetTime();

        // �^�C�����X�V
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

    // reset button �̃e�L�X�g�F��ݒ�
    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, SetResetBtnTextFill);

    // reset �{�^����`��
    if (GuiButton(resetBtn, "Reset") && !running) {
        StopSound(sound);
        timeLeft = 0;
        timeCount = 0;
    }
}