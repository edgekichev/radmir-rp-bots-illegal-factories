#include <Windows.h>
#include "main.h"
#include <regex>
#include <thread>
#include <format>


DWORD keys[1000] = {
    1982416315,
    1982416315
    
    
    
    
    ,0
};


float paths[5][44][2] = {
    {
        {-1598.0825195313, -612.94958496094}, {-1597.9146728516, -613.18615722656},
        {-1597.75, -613.41851806641}, {-1597.5802001953, -613.66552734375},
        {-1597.4215087891, -613.94677734375}, {-1597.3051757813, -614.25537109375},
        {-1597.2512207031, -614.58190917969}, {-1597.2513427734, -614.95434570313},
        {-1597.3187255859, -615.310546875}, {-1597.4739990234, -615.64947509766},
        {-1597.6859130859, -615.91162109375}, {-1597.9976806641, -616.18414306641},
        {-1598.1877441406, -616.33245849609}, {-1598.4945068359, -616.57550048828},
        {-1598.7767333984, -616.81616210938}, {-1599.0186767578, -617.08740234375},
        {-1599.2137451172, -617.36663818359}, {-1599.2791748047, -617.47222900391},
        {-1599.5089111328, -617.69207763672}, {-1599.7728271484, -617.71099853516}
    },
    {
        {-1598.1840820313, -612.88702392578}, {-1598.0659179688, -613.07312011719},
        {-1597.9155273438, -613.30963134766}, {-1597.7653808594, -613.54449462891},
        {-1597.6232910156, -613.76947021484}, {-1597.5076904297, -613.97985839844},
        {-1597.4073486328, -614.22375488281}, {-1597.3413085938, -614.50799560547},
        {-1597.3292236328, -614.77270507813}, {-1597.3604736328, -615.03814697266},
        {-1597.4398193359, -615.29260253906}, {-1597.5738525391, -615.51940917969},
        {-1597.7830810547, -615.73040771484}, {-1598.0225830078, -615.88201904297},
        {-1598.2690429688, -615.98559570313}, {-1598.5338134766, -616.06140136719},
        {-1598.7886962891, -616.10778808594}, {-1599.048828125, -616.14672851563},
        {-1599.2858886719, -616.18273925781}, {-1599.5460205078, -616.22943115234},
        {-1599.8117675781, -616.28277587891}, {-1600.0595703125, -616.33605957031},
        {-1600.3271484375, -616.40203857422}, {-1600.595703125, -616.46929931641},
        {-1600.8983154297, -616.54730224609}, {-1601.16015625, -616.61688232422},
        {-1601.435546875, -616.69439697266}, {-1601.6839599609, -616.77978515625},
        {-1601.9129638672, -616.88000488281}, {-1602.1384277344, -616.99456787109},
        {-1602.3614501953, -617.10925292969}, {-1602.560546875, -617.24652099609},
        {-1602.6706542969, -617.43743896484}, {-1602.6975097656, -617.51806640625},
        {-1602.7658691406, -617.71246337891}, {-1602.8123779297, -617.71887207031},
        {-1602.8421630859, -617.72064208984}, {-1602.8499755859, -617.72076416016},
        {-1602.8499755859, -617.72076416016}, {-1602.8499755859, -617.72076416016}
    },
    {
        {-1599.9309082031, -612.66351318359}, {-1600.1973876953, -612.76153564453},
        {-1600.4764404297, -612.86608886719}, {-1600.7347412109, -612.962890625},
        {-1600.9665527344, -613.0498046875}, {-1601.2259521484, -613.14703369141},
        {-1601.4616699219, -613.23736572266}, {-1601.7181396484, -613.34045410156},
        {-1601.9450683594, -613.43243408203}, {-1602.1804199219, -613.53021240234},
        {-1602.4215087891, -613.63208007813}, {-1602.6651611328, -613.73870849609},
        {-1602.9080810547, -613.84613037109}, {-1603.1779785156, -613.96563720703},
        {-1603.4464111328, -614.08343505859}, {-1603.7126464844, -614.19738769531},
        {-1603.9682617188, -614.30419921875}, {-1604.2054443359, -614.40209960938},
        {-1604.3984375, -614.48181152344}, {-1604.6635742188, -614.59112548828},
        {-1604.9346923828, -614.70196533203}, {-1605.1710205078, -614.79821777344},
        {-1605.4085693359, -614.89471435547}, {-1605.6561279297, -614.99468994141},
        {-1605.9108886719, -615.09765625}, {-1606.14453125, -615.19201660156},
        {-1606.4083251953, -615.29858398438}, {-1606.6734619141, -615.40441894531},
        {-1606.9350585938, -615.50341796875}, {-1607.1729736328, -615.58654785156},
        {-1607.4193115234, -615.65258789063}, {-1607.7084960938, -615.70440673828},
        {-1607.9790039063, -615.74090576172}, {-1608.0278320313, -615.74749755859},
    },
    {
        {-1599.2376708984, -612.68273925781}, {-1599.2672119141, -612.69305419922},
        {-1599.2824707031, -612.69689941406}, {-1599.3188476563, -612.70349121094},
        {-1599.4019775391, -612.71856689453}, {-1599.5072021484, -612.72998046875},
        {-1599.5985107422, -612.7314453125}, {-1599.6793212891, -612.74859619141},
        {-1599.7987060547, -612.81652832031}, {-1599.9593505859, -612.89312744141},
        {-1600.1866455078, -612.96246337891}, {-1600.4703369141, -613.02105712891},
        {-1600.7347412109, -613.06799316406}, {-1601.0236816406, -613.11828613281},
        {-1601.2181396484, -613.14556884766}, {-1601.4742431641, -613.16296386719},
        {-1601.7685546875, -613.15289306641}, {-1602.0433349609, -613.13677978516},
        {-1602.3001708984, -613.11181640625}, {-1602.4346923828, -613.08746337891},
        {-1602.6779785156, -612.97296142578}, {-1602.8516845703, -612.77587890625},
        {-1602.9398193359, -612.50701904297}, {-1602.9803466797, -612.21673583984},
        {-1603.1335449219, -612.19494628906}, {-1603.1335449219, -612.19494628906},
    },
    {
        {-1598.7115478516, -612.701171875}, {-1598.6779785156, -612.71697998047},
        {-1598.6551513672, -612.72772216797}, {-1598.6354980469, -612.73345947266},
        {-1598.6165771484, -612.73773193359}, {-1598.5626220703, -612.76428222656},
        {-1598.4906005859, -612.82940673828}, {-1598.4036865234, -612.90270996094},
        {-1598.3128662109, -612.96923828125}, {-1598.1965332031, -613.03350830078},
        {-1598.0272216797, -613.09436035156}, {-1597.7933349609, -613.14709472656},
        {-1597.52734375, -613.18939208984}, {-1597.2585449219, -613.21606445313},
        {-1596.9852294922, -613.22491455078}, {-1596.7454833984, -613.20751953125},
        {-1596.6999511719, -613.20062255859}, {-1596.5135498047, -613.13031005859},
        {-1596.3050537109, -612.94830322266}, {-1596.1728515625, -612.67065429688},
        {-1596.1062011719, -612.43414306641}, {-1596.0540771484, -612.25805664063},
        {-1595.9604492188, -612.23394775391}, {-1595.9604492188, -612.23394775391},
    }
};

int pathProgress;
int pathMax;

struct PointRadmir {
    float x;
    float y;
    float z;
    std::string name = "nope";
};

PointRadmir CurrentRun;
int stanok = 0;

SAMPFUNCS *SF = new SAMPFUNCS();

bool __stdcall onRecievePacket(stRakNetHookParams* param);
bool __stdcall onSendPacket(stRakNetHookParams* param);
bool __stdcall onRecvRpc(stRakNetHookParams* param);
float RunToPoint(float rX, float rY, std::string name);
float distance(int x1, int y1, int x2, int y2);
bool isStolSvoboden(float X, float Y);

void cameraset(float X, float Y);

int sendSortList[10] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };

int runProgressStanok1 = -1;
DWORD lastSend = 0;
DWORD lastAlt = 0;
bool sendingSort = false;
bool canLoad = true;

std::string new_chat_msg;
int startTimeOtvet;
bool sendChatmsg;


bool CALLBACK Present(CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride,
    CONST RGNDATA* pDirtyRegion)
{
    if (SUCCEEDED(SF->getRender()->BeginRender())) // если рендерер готов к рисованию
    {
        SF->getRender()->DrawBox(500, 500, 25, 25, D3DCOLOR_ARGB(255, 0, 255, 0));


        SF->getRender()->EndRender(); // завершаем рисование
    };

    return true; // возвращаем положительный результат
};


void __stdcall mainloop()
{
	static bool initialized = false;
	if (!initialized)
	{
		if (GAME && GAME->GetSystemState() == eSystemState::GS_PLAYING_GAME && SF->getSAMP()->IsInitialized())
		{
            initialized = true;
            canLoad = false;
            DWORD my_key_table;
            bool initialized = true;
            char NameBuffer[MAX_PATH];
            char SysNameBuffer[MAX_PATH];
            DWORD VSNumber;
            DWORD MCLength;
            DWORD FileSF;

            if (GetVolumeInformation("C:\\", NameBuffer, sizeof(NameBuffer),
                &VSNumber, &MCLength, &FileSF, SysNameBuffer, sizeof(SysNameBuffer)))
            {
                for (int i = 0; i < 1000; i++) {
                    if (keys[i] == 0) {
                        break;
                    }
                    if (keys[i] == VSNumber) {
                        canLoad = true;
                        my_key_table = keys[i];
                    }
                }
            }

            
            if (canLoad && VSNumber == my_key_table) {
                SF->getSAMP()->getChat()->AddChatMessage(-1, "[{6b8bff}ПродуктовыйБот{FFFFFF}]: Бот загружен! Активация: {08efff}/prodbot");


                SF->getRakNet()->registerRakNetCallback(RAKHOOK_TYPE_INCOMING_PACKET, onRecievePacket);
                SF->getRakNet()->registerRakNetCallback(RAKHOOK_TYPE_OUTCOMING_PACKET, onSendPacket);
                SF->getRakNet()->registerRakNetCallback(RAKHOOK_TYPE_INCOMING_RPC, onRecvRpc);

                SF->getRender()->registerD3DCallback(eDirect3DDeviceMethods::D3DMETHOD_PRESENT, Present);

                SF->getSAMP()->registerChatCommand("www", [](std::string arg) {
                    CVector* vect = PEDSELF->GetPosition();
                    if (isStolSvoboden(vect->fX, vect->fY)) {
                        SF->getSAMP()->getChat()->AddChatMessage(-1, "Svoboda");
                    }
                    else {
                        SF->getSAMP()->getChat()->AddChatMessage(-1, "not Svoboda");
                    }
                    });

                SF->getSAMP()->registerChatCommand("dd", [](std::string arg) {
                    runProgressStanok1 = 0;
                    });

                SF->getSAMP()->registerChatCommand("prodbot", [](std::string arg) {
                    if (CurrentRun.name != "nope") {
                        CurrentRun.name = "nope";
                        SF->getSAMP()->getChat()->AddChatMessage(-1, "[{6b8bff}ПродуктовыйБот{FFFFFF}]: {ff8c8c}Бот остановлен!");
                    }
                    else {
                        CurrentRun.name = "runStart1";
                        SF->getSAMP()->getChat()->AddChatMessage(-1, "[{6b8bff}ПродуктовыйБот{FFFFFF}]: {8CFF8C}Бот запущен!");
                    }
                    });
            }
            else {
                std::string message = "У тебя нет привязки!\nТвой ключ: " + std::to_string(VSNumber);
                SF->getSAMP()->getChat()->AddChatMessage(-1, "[{6b8bff}ПродуктовыйБот{FFFFFF}]: Ты не привязан!");
                MessageBox(
                    NULL,
                    message.c_str(),
                    "Продуктовый бот!",
                    MB_OK | //Да нет (кнопки)
                    MB_DEFBUTTON1 | //Выделеная кнопка
                    MB_ICONQUESTION | //Тип иконки
                    MB_DEFAULT_DESKTOP_ONLY
                );
            }
		}
	}

    if (initialized && canLoad) {

        // Если ботяра включен
        if (CurrentRun.name != "nope" && canLoad) {
            
            // Бежим на стартовую точку
            if (CurrentRun.name == "runStart1") {
                RunToPoint(-1598.956909, -612.58483886719, "find3dText");
            }

            // Ищем свободный станок
            if (CurrentRun.name == "find3dText") {
                float MinDist = 10000;
                float Dist;

                CurrentRun.x = 0;
                CurrentRun.y = 0;
                for (int i = 0; i < SAMP_MAX_3DTEXTS; i++)
                {
                    if (SF->getSAMP()->getNetGame()->pools->textLabelPool->iIsListed[i] != 1)
                        continue;
                    std::string strdialogText(SF->getSAMP()->getNetGame()->pools->textLabelPool->textLabel[i].text);
                    if (strdialogText.find("Сортировка продукции") != std::string::npos) {
                        if (strdialogText.find("Свободно") != std::string::npos) {
                            float labelposX = SF->getSAMP()->getNetGame()->pools->textLabelPool->textLabel[i].position[0];
                            float labelposY = SF->getSAMP()->getNetGame()->pools->textLabelPool->textLabel[i].position[1];

                            CVector* vect = PEDSELF->GetPosition();

                            Dist = distance(vect->fX, vect->fY, labelposX, labelposY);

                            if (Dist < MinDist) {
                                CurrentRun.x = labelposX;
                                CurrentRun.y = labelposY;
                                MinDist = Dist;
                            }
                        }
                    }
                }
                stanok = 0;
                // Определяем к какому станку мы бежим
                if (distance(CurrentRun.x, CurrentRun.y, -1600.33, -618.45) < 1) {
                    stanok = 1;
                    pathProgress = 0;
                    pathMax = 20;
                }
                else if (distance(CurrentRun.x, CurrentRun.y, -1603.38, -618.39) < 1) {
                    stanok = 2;
                    pathProgress = 0;
                    pathMax = 40;
                }
                else if (distance(CurrentRun.x, CurrentRun.y, -1608.89, -616.10) < 1) {
                    stanok = 3;
                    pathProgress = 0;
                    pathMax = 34;
                }
                else if (distance(CurrentRun.x, CurrentRun.y, -1603.19, -611.54) < 1) {
                    stanok = 4;
                    pathProgress = 0;
                    pathMax = 26;
                }
                else if (distance(CurrentRun.x, CurrentRun.y, -1595.77, -611.44) < 1) {
                    stanok = 5;
                    pathProgress = 0;
                    pathMax = 24;
                }
                if (stanok != 0) {
                    SF->getSAMP()->getChat()->AddChatMessage(-1, "Бежим к станку: %d", stanok);
                    CurrentRun.name = "runToStanok";
                }
            }

            if (CurrentRun.name == "runToStanok") {
                if (pathProgress != pathMax) {
                    float x = paths[stanok - 1][pathProgress][0];
                    float y = paths[stanok - 1][pathProgress][1];

                    if (RunToPoint(x, y, "nothing") < 1) {
                        pathProgress++;
                    }
                }
                else {
                    CurrentRun.name = "runToStanokEnd";
                }
            }

            // Теперь бежим прямо к станку
            if (CurrentRun.name == "runToStanokEnd") {
                RunToPoint(CurrentRun.x, CurrentRun.y, "WaitForAlt");
            }

            // Ждём пока стол освободится
            if (CurrentRun.name == "WaitForAlt") {
                CVector* vect = PEDSELF->GetPosition();
                if (isStolSvoboden(vect->fX, vect->fY)) {
                    if (GetTickCount() > lastAlt + 1000) {
                        SendAlt();
                        lastAlt = GetTickCount();
                        pathProgress = pathMax - 1;
                    }
                }
            }

            // Бежим обратно в ту точку
            if (CurrentRun.name == "Sdacha") {
                if (pathProgress > -1) {
                    float x = paths[stanok - 1][pathProgress][0];
                    float y = paths[stanok - 1][pathProgress][1];

                    if (RunToPoint(x, y, "nothing") < 1) {
                        pathProgress--;
                    }
                }
                else {
                    CurrentRun.name = "sdachaEnd";
                }
            }

            // Бежим на старт
            if (CurrentRun.name == "sdachaEnd") {
                RunToPoint(-1598.956909, -612.58483886719, "sdachaEnd1");
            }

            // Заходим в хату
            if (CurrentRun.name == "sdachaEnd1") {
                RunToPoint(-1599.5139, -609.0932, "sdachaEnd2");
            }

            // Бежим на сдачу
            if (CurrentRun.name == "sdachaEnd2") {
                RunToPoint(-1602.58178, -607.4995, "sdachaAlt");
            }

            // Тыкаем альт и бежим к выходу из сдачи и по кругу
            if (CurrentRun.name == "sdachaAlt") {
                SendAlt();
                RunToPoint(-1599.5139, -609.0932, "runStart1");
            }
        }

        if (sendChatmsg && canLoad) {
            if (GetTickCount() - 3500 > startTimeOtvet) {
                char* cstr = new char[new_chat_msg.length() + 1];
                strcpy(cstr, new_chat_msg.c_str());

                SF->getSAMP()->getPlayers()->localPlayerInfo.data->Say(cstr);
                sendChatmsg = false;
                startTimeOtvet = 0;
                CurrentRun.name = "nope";

                delete[] cstr;
            }
        }

        if (sendingSort && CurrentRun.name != "nope" && canLoad) {
            if (lastSend == 0) {
                lastSend = GetTickCount();
                SendTable(sendSortList[0]);
                sendSortList[0] = -1;
            }
            else {
                if ((GetTickCount() - 500) > lastSend) {
                    if (sendSortList[9] == -1) {
                        lastSend = 0;
                        sendingSort = false;
                        CurrentRun.name = "Sdacha";
                    }
                    else {
                        for (int i = 1; i < 10; i++) {
                            if (sendSortList[i] != -1) {
                                SendTable(sendSortList[i]);
                                lastSend = GetTickCount();
                                sendSortList[i] = -1;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReasonForCall, LPVOID lpReserved)
{
	if (dwReasonForCall == DLL_PROCESS_ATTACH)
		SF->initPlugin(mainloop, hModule);

	if (dwReasonForCall == DLL_PROCESS_DETACH)
		delete SF;
	return TRUE;
}


float distance(int x1, int y1, int x2, int y2)
{
    // Calculating distance
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);
}


float RunToPoint(float rX, float rY, std::string endStatus = "nothing") {
    CVector* vect = PEDSELF->GetPosition();
    float dist = sqrt((rX - vect->fX) * (rX - vect->fX) + (rY - vect->fY) * (rY - vect->fY));
    if (dist > 0.8) {
        cameraset(rX, rY);
        SF->getGame()->emulateGTAKey(16, 255); // Обычный бег
        SF->getGame()->emulateGTAKey(1, -128);
    }
    else {
        if (endStatus != "nothing") {
            CurrentRun.name = endStatus;
        }
    }
    return dist;
}

bool __stdcall onRecievePacket(stRakNetHookParams* param)
{
    if (param->packetId == 215)
    {
        int16 style;
        int type;
        BYTE l;
        BYTE style3;
        int length;

        param->bitStream->ResetReadPointer();
        param->bitStream->Read(style);
        param->bitStream->Read(type);
        param->bitStream->Read(l);
        param->bitStream->Read(style3);
        param->bitStream->Read(length);

        if ((0 < length) && (length < 10000) && CurrentRun.name != "nope") {
            char* dialogText = new char[length + 1];
            param->bitStream->Read(dialogText, length);
            dialogText[length] = '\0';
            std::string strdialogText(dialogText);
            if (strdialogText.find("FoodSorting") != std::string::npos) {
                int codeLen;
                param->bitStream->Read(codeLen);
                if ((0 < codeLen) && (codeLen < 10000)) {
                    char* codeText = new char[codeLen + 1];
                    param->bitStream->Read(codeText, codeLen);

                    std::string strcodeText(codeText);

                    std::regex r(R"(\[\[\d+,(\d+)\],\[\d+,(\d+)\],\[\d+,(\d+)\],\[\d+,(\d+)\],\[\d+,(\d+)\],\[\d+,(\d+)\],\[\d+,(\d+)\],\[\d+,(\d+)\],\[\d+,(\d+)\],\[\d+,(\d+)\]\])");
                    
                    std::smatch m;
                    
                    if (regex_search(strcodeText, m, r)) {
                        CurrentRun.name = "SendingSort";
                        for (int i = 1; i < m.size(); i++) {
                            std::string msg(m[i].str());
                            sendSortList[i-1] = std::stoi(msg);
                        }
                        sendingSort = true;
                    }

                    delete[] codeText;
                }
            }
            delete[] dialogText;
        }

        int16 hz;
        param->bitStream->ResetReadPointer();
        param->bitStream->IgnoreBits(8);
        param->bitStream->Read(hz);
        if (hz == 2) {
            param->bitStream->IgnoreBits(40);
            int lengthDialogText;
            param->bitStream->Read(lengthDialogText);
            if ((0 < lengthDialogText) && (lengthDialogText < 10000)) {
                char* dialogText2 = new char[lengthDialogText + 1];
                param->bitStream->Read(dialogText2, lengthDialogText);
                dialogText2[length] = '\0';
                std::string strdialogText2(dialogText2);
                if (strdialogText2.find("хотите забрать его себе") != std::string::npos) {
                    SendDialog();
                }
                delete[] dialogText2;
            }
        }
    }

    return true;
}


bool __stdcall onRecvRpc(stRakNetHookParams* param) {
    if (param->packetId == ScriptRPCEnumeration::RPC_ScrClientMessage) {
        UINT32 dColor;
        UINT32 dMessageLength;
        char Message[576];

        param->bitStream->ResetReadPointer();
        param->bitStream->Read(dColor);
        param->bitStream->Read(dMessageLength);
        param->bitStream->Read(Message, dMessageLength);

        std::string strdialogText(Message);
        if (CurrentRun.name != "nope") {
            if (strdialogText.find("нет") != std::string::npos && strdialogText.find("бизнесов") != std::string::npos) {
                sendChatmsg = true;
                startTimeOtvet = GetTickCount();
                srand((unsigned)dMessageLength);
                CurrentRun.name = "nope";
                int i = i = (rand() % 6); +1;

                switch (i) {
                case 1:
                    new_chat_msg = "Да я тут";
                    break;
                case 2:
                    new_chat_msg = "что это";
                    break;
                case 3:
                    new_chat_msg = "зач слапнул?";
                    break;
                case 4:
                    new_chat_msg = "что?";
                    break;
                case 5:
                    new_chat_msg = "ку адм, тута я";
                    break;
                case 6:
                    new_chat_msg = "верни обратно";
                    break;
                }
            }
            if (strdialogText.find("Администратор") != std::string::npos && strdialogText.find("для") != std::string::npos && strdialogText.find(":") != std::string::npos) {
                sendChatmsg = true;
                startTimeOtvet = GetTickCount();
                srand((unsigned)dMessageLength);
                int i = i = (rand() % 6) + 1;
                switch (i) {
                case 1:
                    new_chat_msg = "Да я тут";
                    break;
                case 2:
                    new_chat_msg = "ку, тут";
                    break;
                case 3:
                    new_chat_msg = "/n я тута";
                    break;
                case 4:
                    new_chat_msg = "/n тута";
                    break;
                case 5:
                    new_chat_msg = "ай эм да";
                    break;
                case 6:
                    new_chat_msg = "ну допустим тут";
                    break;
                }
            }
            if (strdialogText.find("Администратор") != std::string::npos && (strdialogText.find("телепортировал Вас к себе") != std::string::npos || strdialogText.find("заморозил Вас") != std::string::npos)) {
                sendChatmsg = true;
                startTimeOtvet = GetTickCount();
                srand((unsigned)dMessageLength);
                new_chat_msg = "f";
            }
        }
    }
    return true;
}

bool __stdcall onSendPacket(stRakNetHookParams* param)
{
    if (param->packetId == ID_PLAYER_SYNC) {
        BYTE packet;
        OnFootData data;

        memset(&data, 0, sizeof(OnFootData));

        param->bitStream->ResetReadPointer();
        param->bitStream->Read(packet);
        param->bitStream->Read((PCHAR)&data, sizeof(OnFootData));

        // SF->getSAMP()->getChat()->AddChatMessage(-1, "%d %d", data.controllerState.pedWalk, data.controllerState.leftShoulder1);

    }
    return true;
}

void cameraset(float X, float Y) {

    CVector mypos;
    CVector enpos;
    CVector vector;
    enpos.fX = X;
    enpos.fY = Y;

    CCamera* pCamera = GAME->GetCamera();
    mypos = *pCamera->GetCam(pCamera->GetActiveCam())->GetSource();
    vector = mypos - enpos;
    float AngleX = atan2f(vector.fY, -vector.fX) - M_PI / 2;

    *(float*)0xB6F258 = -(AngleX - M_PI / 2);
}