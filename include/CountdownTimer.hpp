#pragma once

#include <iomanip>
#include <sstream>
#include <string>

#include "App.hpp"

class CountdownTimer {
   private:

    Rectangle displayFrameRect = {30, 50, 260, 200};

    const int displayTextSize = 60;

    // raygui button style
    Rectangle hourBtn = {30, 280, 80, 40};
    Rectangle minuteBtn = {120, 280, 80, 40};
    Rectangle secondBtn = {210, 280, 80, 40};
    Rectangle startBtn = {30, 350, 110, 60};
    Rectangle resetBtn = {180, 350, 110, 60};

    // set count button style
    const int SetCountBtnFill = 0x959595ff;
    const int SetCountBtnStroke = 0x12487fff;
    const int SetCountBtnTextFll = 0xffff00ff;

    const int SetCountBtnTextSize = 20;

    // start, reset button style
    const int SetControlBtnFill = 0x12487fff;
    const int SetControlBtnStroke = 0x959595ff;

    const int SetStartBtnTextFill = 0xffff00ff;
    const int SetStopBtnTextFill = 0xff0000ff;
    const int SetResetBtnTextFill = 0x00ff00ff;

    const int SetControlBtnTextSize = 20;

    double startTime;

    // ê›íËéûä‘
    int timeCount = 0;

    // écÇËéûä‘
    int timeLeft = 0;

    bool running = false;

    const char* startText = "Start";
    void DrawTimerDisplay(const char* displayTime);

   public:
    // music file ÇéÊÇËçûÇﬁ
    Sound sound = LoadSound("../assets/sound.wav");

    void UpdateSetCount();
    void DrawSetCountButton();
    void DrawControlButton();
};