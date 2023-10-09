#include <Windows.h>
#include "main.h"
#include <regex>
#include <format>

SAMPFUNCS* SF = new SAMPFUNCS();
bool __stdcall onRecievePacket(stRakNetHookParams* param);
bool __stdcall onSendPacket(stRakNetHookParams* param);
bool __stdcall onRecvRpc(stRakNetHookParams* param);

BotStatus Bot;
int pathLenList[4] = { 17, 17, 43, 55 };

bool prostorabotaet = false;

bool debugBot = false;
bool canLoad = false;

#define sqr(x) (x) * (x)

bool napisaladmin = false;
DWORD TICKTIMEERR = 0;

float X = 0.0f, Y = 0.0f;
bool GoStatus = false;
bool work = false;
int workint = 0;



DWORD JDEMKDEZHE = 0;

struct
{
	bool active = false;
}gui;

struct
{
	bool active = false;
	bool player = false;
	bool vehicle = false;
	bool object = false;
	bool build = false;
} collision;

void CreateJump(BYTE* pAddress, DWORD dwJumpTo, DWORD dwLen)
{
	DWORD dwOldProtect, dwBkup, dwRelAddr;
	VirtualProtect(pAddress, dwLen, PAGE_EXECUTE_READWRITE, &dwOldProtect);
	dwRelAddr = (DWORD)(dwJumpTo - (DWORD)pAddress) - 5;
	*pAddress = 0xE9;
	*((DWORD*)(pAddress + 0x1)) = dwRelAddr;
	for (DWORD x = 0x5; x < dwLen; x++)*(pAddress + x) = 0x90;
	VirtualProtect(pAddress, dwLen, dwOldProtect, &dwBkup);
	return;
}

void WriteMemory(void* address, void* bytes, int byteSize)
{
	DWORD NewProtection;
	VirtualProtect(address, byteSize, PAGE_EXECUTE_READWRITE, &NewProtection);
	memcpy(address, bytes, byteSize);
	VirtualProtect(address, byteSize, NewProtection, &NewProtection);
}

bool CollisionCheck(object_base* obj1, object_base* obj2)
{
	return (obj2->nType == 3 || obj2->nType == 2) &&
		((obj1->nType == 2 && collision.vehicle) ||
			(obj1->nType == 3 && collision.player) ||
			(obj1->nType == 4 && collision.object));
}

void __declspec (naked) HOOK_PlayerCollision(void)
{
	static object_base* _obj1, * _obj2;
	static DWORD RETURN_ovrwr = 0x54CEFC, RETURN_process = 0x0054BCF4, RETURN_noProcessing = 0x54CF8D;
	__asm
	{
		jz hk_PlCol_process
		jmp RETURN_ovrwr
	}

hk_PlCol_process:
	__asm
	{
		pushad
		mov _obj2, esi // processing collision of *_info (esi)
		mov _obj1, edi // with *_info (edi)
	}

	// process collision if cheat not enabled
	if (!collision.active)
		goto hk_PlCol_processCol;

	// already crashed, if true
	if (_obj1 == nullptr || _obj2 == nullptr)
		goto hk_PlCol_noCol;

	// check for disable collision
	if (CollisionCheck(_obj1, _obj2))
		goto hk_PlCol_noCol;

	if (collision.build)
	{
		__asm popad;
		__asm jmp RETURN_ovrwr
	}

hk_PlCol_processCol:
	__asm popad
	__asm jmp RETURN_process

	hk_PlCol_noCol :
	__asm popad
	__asm jmp RETURN_noProcessing
}

void InstallNakedHooks(void) {
	CreateJump((BYTE*)0x0054BCEE, (DWORD)&HOOK_PlayerCollision, 6U);
}

void InstallCollisionHook(void) {
	CreateJump((BYTE*)0x0054BCEE, (DWORD)&HOOK_PlayerCollision, 6U);

}

void RemoveCollisionHook(void) {
	WriteMemory((void*)0x0054BCEE, (BYTE*)"\x0F\x85\x08\x12\x00\x00", 6U);
}

void __stdcall mainloop()
{
	static bool initialized = false;
	if (!initialized)
	{
		if (GAME && GAME->GetSystemState() == eSystemState::GS_PLAYING_GAME && SF->getSAMP()->IsInitialized())
		{
			initialized = true;
			canLoad = true;
			if (canLoad) {

				SF->getRakNet()->registerRakNetCallback(RAKHOOK_TYPE_INCOMING_PACKET, onRecievePacket);
				SF->getRakNet()->registerRakNetCallback(RAKHOOK_TYPE_OUTCOMING_PACKET, onSendPacket);
				SF->getRakNet()->registerRakNetCallback(RAKHOOK_TYPE_INCOMING_RPC, onRecvRpc);
				InstallCollisionHook();
				SF->getSAMP()->registerChatCommand("gunzavodbot", [](std::string arg) {
					if (Bot.Status == NOPE) {
						Bot.Status = LOOKING_FOR_STANOK;
						Bot.Stanok = 0;
						Bot.LastAlt = 0;
						Bot.LastSend = 0;
						collision.active = true;
						collision.player = true;
						prostorabotaet = true;
						SF->getSAMP()->getChat()->AddChatMessage(-1, "Вкл");
					}
					else {
						Bot.Status = NOPE;
						Bot.Stanok = 0;
						Bot.LastAlt = 0;
						Bot.LastSend = 0;
						collision.active = false;
						prostorabotaet = false;
						collision.player = false;
						SF->getSAMP()->getChat()->AddChatMessage(-1, "Выкл");
					}
					});
				SF->getSAMP()->registerChatCommand("dopustim_vipal_case_or_key", [](std::string arg) {
					X = -1599.0270;
					Y = -628.4521;
					GoStatus = true;
					Bot.Status = WWWAAAIIITTT;
					//JDEMKDEZHE = GetTickCount() + 2400000;
					JDEMKDEZHE = GetTickCount() + 10000;
				});
			}
		}
	}

	if (initialized) {
		if (Bot.Status != NOPE && canLoad && prostorabotaet) {
			if ((sqrt(sqr(Y - PEDSELF->GetPosition()->fY) + sqr(X - PEDSELF->GetPosition()->fX)) <= 3.5) && GoStatus == true) {
				cameraset(X, Y);
				SF->getGame()->emulateGTAKey(1, -128);
			}
			if ((sqrt(sqr(Y - PEDSELF->GetPosition()->fY) + sqr(X - PEDSELF->GetPosition()->fX)) > 3.5) && GoStatus == true) {
				cameraset(X, Y);
				SF->getGame()->emulateGTAKey(1, -128);
				SF->getGame()->emulateGTAKey(16, 255);
			}
			if ((sqrt(sqr(Y - PEDSELF->GetPosition()->fY) + sqr(X - PEDSELF->GetPosition()->fX)) <= 0.4) && GoStatus == true) {
				GoStatus = false;
			}
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
					if (GetTickCount() > Bot.LastAlt + 400) {
						SendAlt();
						Bot.LastAlt = GetTickCount();
						Bot.AltAttempts++;
					}
				}
				if (Bot.AltAttempts > 3) {
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
			case WWWAAAIIITTT:
			{
				if (!napisaladmin) {
					if (JDEMKDEZHE > 0 && GetTickCount() > JDEMKDEZHE)
					{
						JDEMKDEZHE = 0;
						SF->getSAMP()->getChat()->AddChatMessage(-1, "ПРОЖДАЛИ КД ИДЕМ ПАХАТЬ");
						Bot.Status = LOOKING_FOR_STANOK;
						Bot.SdachaTimer = GetTickCount();
					}
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
			if (napisaladmin && TICKTIMEERR > 0 && TICKTIMEERR < GetTickCount())
			{
				TICKTIMEERR = 0;
				Bot.Status = LOOKING_FOR_STANOK;
				napisaladmin = false;
				Bot.Stanok = 0;
				Bot.LastAlt = 0;
				Bot.LastSend = 0;
				SF->getGame()->emulateGTAKey(14, 255);
			}
		}
	}
}

bool __stdcall onRecievePacket(stRakNetHookParams* param)
{
	if (param->packetId == 215 && canLoad && prostorabotaet)
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
				if ((strdialogText2.find("хотите забрать его себе") != std::string::npos || strdialogText2.find("ключ") != std::string::npos || strdialogText2.find("кейс") != std::string::npos || strdialogText2.find("Ключ") != std::string::npos || strdialogText2.find("Кейс") != std::string::npos) && prostorabotaet) {
					SendDialog();
					X = -1599.0270;
					Y = -628.4521;
					GoStatus = true;
					Bot.Status = WWWAAAIIITTT;
					JDEMKDEZHE = GetTickCount() + 2580000;
					SF->getSAMP()->getChat()->AddChatMessage(-1, "БОТ забрал кейсик или ключик и убегает на покой");
					return false;
				}
				delete[] dialogText2;
			}
		}
	}

	return true;
}


bool __stdcall onRecvRpc(stRakNetHookParams* param) {
	if (param->packetId == ScriptRPCEnumeration::RPC_ScrClientMessage && canLoad && Bot.Status != NOPE && prostorabotaet) {
		UINT32 dColor;
		UINT32 dMessageLength;
		char Message[576];

		param->bitStream->ResetReadPointer();
		param->bitStream->Read(dColor);
		param->bitStream->Read(dMessageLength);
		param->bitStream->Read(Message, dMessageLength);

		std::string strdialogText(Message);
		if (Bot.Status != NOPE && prostorabotaet) {
			if (strdialogText.find("Администратор") != std::string::npos && strdialogText.find("для") != std::string::npos && strdialogText.find(":") != std::string::npos) {
				napisaladmin = true;
				Bot.Status = WWWAAAIIITTT;
				Bot.Stanok = 0;
				Bot.LastAlt = 0;
				Bot.LastSend = 0;
				TICKTIMEERR = GetTickCount() + 12000;
				SF->getSAMP()->getChat()->AddChatMessage(-1, "НАПИСАЛ АДМИН");
			}
			if (strdialogText.find("Администратор") != std::string::npos && strdialogText.find("подбросил") != std::string::npos && strdialogText.find("Вас") != std::string::npos) {
				napisaladmin = true;
				Bot.Status = WWWAAAIIITTT;
				Bot.Stanok = 0;
				Bot.LastAlt = 0;
				Bot.LastSend = 0;
				TICKTIMEERR = GetTickCount() + 6000;
				SF->getSAMP()->getChat()->AddChatMessage(-1, "СЛАПНУЛ АДМИН");
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
