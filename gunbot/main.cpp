#include <Windows.h>
#include "main.h"
#include <regex>
#include <format>

SAMPFUNCS *SF = new SAMPFUNCS();
bool __stdcall onRecievePacket(stRakNetHookParams* param);
bool __stdcall onSendPacket(stRakNetHookParams* param);
bool __stdcall onRecvRpc(stRakNetHookParams* param);

DWORD keys[1000] = {
	1982416315,
	3905734190,
	4265428755,
	4272483793,
	2631983357,
	1611010807
};

BotStatus Bot;
int pathLenList[4] = { 17, 17, 43, 55 };

bool debugBot = false;
bool canLoad = false;

stFontInfo* pFont;

bool CALLBACK Present(CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride,
	CONST RGNDATA* pDirtyRegion)
{
	if (SUCCEEDED(SF->getRender()->BeginRender())) // если рендерер готов к рисованию
	{
		if (debugBot) {
			pFont->Print("BotStatus: ", D3DCOLOR_ARGB(255, 255, 255, 0), 20, 300, false);
			pFont->Print("PathProgress: ", D3DCOLOR_ARGB(255, 255, 255, 0), 20, 315, false);
			pFont->Print("PathLen: ", D3DCOLOR_ARGB(255, 255, 255, 0), 20, 330, false);

			pFont->Print(std::to_string((int)Bot.Status).c_str(), D3DCOLOR_ARGB(255, 255, 255, 0), 150, 300, false);
			pFont->Print(std::to_string((int)Bot.PathProgress).c_str(), D3DCOLOR_ARGB(255, 255, 255, 0), 150, 315, false);
			pFont->Print(std::to_string((int)Bot.PathLen).c_str(), D3DCOLOR_ARGB(255, 255, 255, 0), 150, 330, false);
		}
		// рисуем
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
				SF->getSAMP()->getChat()->AddChatMessage(-1, "[{7f6bff}Armory{6b8bff}Bot{FFFFFF}]: Успешно загружен.");
				SF->getSAMP()->getChat()->AddChatMessage(-1, "[{7f6bff}Armory{6b8bff}Bot{FFFFFF}]: Активация: {ff6b6b}/armbot");

				SF->getRender()->registerD3DCallback(eDirect3DDeviceMethods::D3DMETHOD_PRESENT, Present);
				pFont = SF->getRender()->CreateNewFont("Tahoma", 12, FCR_BORDER);

				SF->getRakNet()->registerRakNetCallback(RAKHOOK_TYPE_INCOMING_PACKET, onRecievePacket);
				SF->getRakNet()->registerRakNetCallback(RAKHOOK_TYPE_OUTCOMING_PACKET, onSendPacket);
				SF->getRakNet()->registerRakNetCallback(RAKHOOK_TYPE_INCOMING_RPC, onRecvRpc);

				SF->getSAMP()->registerChatCommand("armdebug", [](std::string arg) {
					debugBot = !debugBot;
				});

				SF->getSAMP()->registerChatCommand("armbot", [](std::string arg) {
					if (Bot.Status == NOPE) {
						Bot.Status = LOOKING_FOR_STANOK;
						Bot.Stanok = 0;
						Bot.LastAlt = 0;
						Bot.LastSend = 0;
						SF->getSAMP()->getChat()->AddChatMessage(-1, "[{7f6bff}Armory{6b8bff}Bot{FFFFFF}]: Активирован");
					}
					else {
						Bot.Status = NOPE;
						Bot.Stanok = 0;
						Bot.LastAlt = 0;
						Bot.LastSend = 0;
						SF->getSAMP()->getChat()->AddChatMessage(-1, "[{7f6bff}Armory{6b8bff}Bot{FFFFFF}]: Деактивирован");
					}
					});
			}
			else {
				std::string message = "У тебя нет привязки!\nТвой ключ: " + std::to_string(VSNumber);
				SF->getSAMP()->getChat()->AddChatMessage(-1, "[{7f6bff}Armory{6b8bff}Bot{FFFFFF}]: У тебя нет привязки! Твой ключ: %d", VSNumber);
				MessageBox(
					NULL,
					message.c_str(),
					"Оружейный бот!",
					MB_OK | //Да нет (кнопки)
					MB_DEFBUTTON1 | //Выделеная кнопка
					MB_ICONQUESTION | //Тип иконки
					MB_DEFAULT_DESKTOP_ONLY
				);
			}
		}
	}

	if (initialized) {
		if (Bot.Status != NOPE && canLoad) {

			if (Bot.SendingBuild) {
				if (Bot.LastSend == 0) {
					Bot.LastSend = GetTickCount() + 1000;
				}
				else {
					if ((GetTickCount() - 700) > Bot.LastSend) {
						if (Bot.BuildSended == 4) {
							Bot.LastSend = 0;
							Bot.SendingBuild = false;
						}
						else {
							Bot.LastSend = GetTickCount();
							SendBuild();
							Bot.BuildSended++;
						}
					}
				}
			}

			switch (Bot.Status) {

			case LOOKING_FOR_STANOK:
				{
					if (GetTickCount() - 1000 > Bot.SdachaTimer) {
						Bot.SdachaTimer = 0;
						if (findStanok(&Bot.Stanok)) {
							Bot.PathLen = pathLenList[Bot.Stanok];
							Bot.Status = LOOKING_FOR_NEAREST_POINT;
						}
					}
					break;
				}
			case LOOKING_FOR_NEAREST_POINT:
				{
					VECTOR NearestPoint = getNearestPathDot(Bot.Stanok, &Bot.PathProgress, pathLenList[Bot.Stanok]);
					if (NearestPoint.X != 0 && NearestPoint.Y != 0) {
						SF->getSAMP()->getChat()->AddChatMessage(-1, "[{7f6bff}Armory{6b8bff}Bot{FFFFFF}]: Точка: %d | Длина пути: %d | Станок: %d", Bot.PathProgress, Bot.PathLen, Bot.Stanok);
						Bot.Status = RUN_TO_STANOK;
					}
					break;
				}
			case RUN_TO_STANOK:
				{
					if (Bot.PathProgress - 1 != Bot.PathLen) {
						if (RunToPoint(Bot.Stanok, Bot.PathProgress, Bot.PathLen)) {
							Bot.PathProgress++;
						}
					}
					else {
						Bot.Status = WAIT_FOR_FREE;
						Bot.AltAttempts = 0;
						Bot.LastAlt = 0;
					}
					break;
				}
			case WAIT_FOR_FREE:
				{
					CVector* vect = PEDSELF->GetPosition();
					if (isStolSvoboden(vect->fX, vect->fY)) {
						if (GetTickCount() > Bot.LastAlt + 1000) {
							SendAlt();
							Bot.LastAlt = GetTickCount();
							Bot.AltAttempts++;
						}
					}
					if (Bot.AltAttempts > 10) {
						if (Bot.Status == WAIT_FOR_FREE) {
							Bot.Status = RUN_OT_STANOK_BACK;
							Bot.PathProgress = Bot.PathLen - 1;
						}
					}
					break;
				}
			case RUN_OT_STANOK_BACK:
				{
					if (Bot.PathProgress != -1) {
						if (RunToPoint(Bot.Stanok, Bot.PathProgress, Bot.PathLen)) {
							Bot.PathProgress--;
						}
					}
					else {
						Bot.Status = LOOKING_FOR_STANOK;
						Bot.AltAttempts = 0;
						Bot.SdachaAttempts = 0;
						Bot.Peresdacha = 0;
					}
					break;
				}
				case RUN_OT_STANOK:
				{
					if (Bot.PathProgress != -1) {
						if (RunToPoint(Bot.Stanok, Bot.PathProgress, Bot.PathLen)) {
							Bot.PathProgress--;
						}
					}
					else {
						Bot.Status = SDACHA_LOOT;
						Bot.AltAttempts = 0;
						Bot.SdachaAttempts = 0;
						Bot.Peresdacha = 0;
						Bot.LastAlt = GetTickCount();
					}
					break;
				}
			case SDACHA_LOOT:
				{
					if (GetTickCount() > Bot.LastAlt + 700) {

						CVector* vect = PEDSELF->GetPosition();
						float dist = CalcDist2d(vect->fX, vect->fY, -1602.5430908203, -629.56372070313);

						if (dist > 1.5 && Bot.AltAttempts != 0 && canLoad) {
							RunToCoord(-1602.5430908203, -629.56372070313);
						}
						else {
							SendAlt();
							Bot.LastAlt = GetTickCount();
							Bot.AltAttempts++;
						}
					}

					if (Bot.AltAttempts >= 5) {
						if (Bot.Peresdacha < 2) {
							Bot.Status = PERESDACHA_LOOT;
							Bot.Peresdacha++;

						}
						else {
							Bot.Status = LOOKING_FOR_STANOK;
							Bot.Peresdacha = 0;
							Bot.AltAttempts = 0;
							Bot.LastAlt = 0;
						}
					}
					break;
				}
			case PERESDACHA_LOOT:
				{
					if (RunToCoord(-1598.6810302734, -630.47320556641)) {
						Bot.Status = SDACHA_LOOT;
						Bot.AltAttempts = 0;
					}
					break;
				}
			}

			if (Bot.SendChat) {
				if (GetTickCount() - 3500 > Bot.StartSendChat && canLoad) {
					char* cstr = new char[Bot.ChatMessage.length() + 1];
					strcpy(cstr, Bot.ChatMessage.c_str());

					SF->getSAMP()->getPlayers()->localPlayerInfo.data->Say(cstr);

					Bot.SendChat = false;
					Bot.StartSendChat = 0;
					Bot.Status = NOPE;

					delete[] cstr;
				}
			}
		}
	}
}

bool __stdcall onRecievePacket(stRakNetHookParams* param)
{
	if (param->packetId == 215 && canLoad)
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

		if ((0 < length) && (length < 10000) && Bot.Status != NOPE) {
			char* dialogText = new char[length + 1];
			param->bitStream->Read(dialogText, length);
			dialogText[length] = '\0';
			std::string strdialogText(dialogText);
			if (strdialogText.find("WeaponAssembly") != std::string::npos) {
				Bot.Status = SENDING_BUILD;
				Bot.SendingBuild = true;
				Bot.BuildSended = 0;
				delete[] dialogText;
				return false;
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
					delete[] dialogText2;
					return false;
				}
				delete[] dialogText2;
			}
		}
	}

	return true;
}


bool __stdcall onRecvRpc(stRakNetHookParams* param) {
	if (param->packetId == ScriptRPCEnumeration::RPC_ScrClientMessage && canLoad) {
		UINT32 dColor;
		UINT32 dMessageLength;
		char Message[576];

		param->bitStream->ResetReadPointer();
		param->bitStream->Read(dColor);
		param->bitStream->Read(dMessageLength);
		param->bitStream->Read(Message, dMessageLength);

		std::string strdialogText(Message);
		if (Bot.Status != NOPE) {
			if (strdialogText.find("Администратор") != std::string::npos && strdialogText.find("подбросил Вас") != std::string::npos) {
				Bot.SendChat = true;
				Bot.StartSendChat = GetTickCount();
				srand((unsigned)dMessageLength);
				Bot.Status = NOPE;
				int i = i = (rand() % 3); +1;

				switch (i) {
				case 1:
					Bot.SendChat = true;
					Bot.StartSendChat = GetTickCount();
					Bot.ChatMessage = "ммм?";
					break;
				case 2:
					Bot.SendChat = true;
					Bot.StartSendChat = GetTickCount();
					Bot.ChatMessage = "что это";
					break;
				case 3:
					Bot.SendChat = true;
					Bot.StartSendChat = GetTickCount();
					Bot.ChatMessage = "/n тут ят ут";
					break;
				}
			}
			if (strdialogText.find("Администратор") != std::string::npos && strdialogText.find("для") != std::string::npos && strdialogText.find(":") != std::string::npos) {
				Bot.SendChat = true;
				Bot.StartSendChat = GetTickCount();
				srand((unsigned)dMessageLength);
				int i = i = (rand() % 6) + 1;
				switch (i) {
				case 1:
					Bot.SendChat = true;
					Bot.StartSendChat = GetTickCount();
					Bot.ChatMessage = "Да я тут";
					break;
				case 2:
					Bot.SendChat = true;
					Bot.StartSendChat = GetTickCount();
					Bot.ChatMessage = "ку, тут";
					break;
				case 3:
					Bot.SendChat = true;
					Bot.StartSendChat = GetTickCount();
					Bot.ChatMessage = "/n я тута";
					break;
				case 4:
					Bot.SendChat = true;
					Bot.StartSendChat = GetTickCount();
					Bot.ChatMessage = "/n тута";
					break;
				case 5:
					Bot.SendChat = true;
					Bot.StartSendChat = GetTickCount();
					Bot.ChatMessage = "ай эм да";
					break;
				case 6:
					Bot.SendChat = true;
					Bot.StartSendChat = GetTickCount();
					Bot.ChatMessage = "ну допустим тут";
					break;
				}
			}
			if (strdialogText.find("Администратор") != std::string::npos && (strdialogText.find("телепортировал Вас к себе") != std::string::npos || strdialogText.find("заморозил Вас") != std::string::npos)) {
				Bot.SendChat = true;
				Bot.StartSendChat = GetTickCount();
				srand((unsigned)dMessageLength);
				Bot.ChatMessage = "f";
			}

			if ((strdialogText.find("главный склад") != std::string::npos && strdialogText.find("положили изготовленный предмет") != std::string::npos) || (strdialogText.find("На складе недостаточно мест для произведенной продукции") != std::string::npos)) {
				Bot.Status = LOOKING_FOR_STANOK;
				Bot.SdachaTimer = GetTickCount();
			}

			if (strdialogText.find("Отнесите готовую продукцию на") != std::string::npos && strdialogText.find("главный склад") != std::string::npos && canLoad) {
				Bot.Status = RUN_OT_STANOK;
				Bot.PathProgress = Bot.PathLen - 1;
			}

			if (strdialogText.find("Вы успешно произвели") != std::string::npos && strdialogText.find("главный склад") != std::string::npos && canLoad) {
				Bot.Status = RUN_OT_STANOK;
				Bot.PathProgress = Bot.PathLen - 1;
			}
		}
	}

    return true;
}

bool __stdcall onSendPacket(stRakNetHookParams* param)
{
    return true;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReasonForCall, LPVOID lpReserved)
{
	if (dwReasonForCall == DLL_PROCESS_ATTACH)
		SF->initPlugin(mainloop, hModule);

	if (dwReasonForCall == DLL_PROCESS_DETACH) {
		delete SF;
	}
	return TRUE;
}
