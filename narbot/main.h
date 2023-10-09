#pragma once

#include "SAMPFUNCS_API.h"
#include "game_api.h"

void SendBuild0();
void SendBuild1();
void SendBuild2();
void SendBuild3();
void SendBuild4();
void SendAlt();
void SendDialog();
bool findStanok(int* stanok);
VECTOR getNearestPathDot(int stanok, int* pathProg, int pathLen);
bool RunToPoint(int Stanok, int PathProgress, int PathLength);
bool RunToCoord(float rX, float rY);
bool isStolSvoboden(float X, float Y);
void cameraset(float X, float Y);
float CalcDist2d(float x1, float y1, float x2, float y2);

enum StatusList {
    NOPE = 0,
    LOOKING_FOR_STANOK,
    LOOKING_FOR_NEAREST_POINT,
    RUN_TO_STANOK,
    WAIT_FOR_FREE,
    RUN_OT_STANOK,
    SDACHA_LOOT,
    PERESDACHA_LOOT,
    RUN_OT_STANOK_BACK,
    SENDING_BUILD
};

struct BotStatus {
    int PathLen = 0;
    int PathProgress = 0;

    bool SendingBuild = false;
    int Peresdacha = 0;
    int SdachaAttempts = 0;
    int AltAttempts = 0;
    int BuildSended;

    DWORD LastAlt = 0;
    DWORD SdachaTimer = 0;
    DWORD LastSend = 0;

    int Stanok = 0;

    StatusList Status = NOPE;

    bool SendChat = false;
    DWORD StartSendChat = 0;
    std::string ChatMessage = "";
};

extern SAMPFUNCS *SF;
