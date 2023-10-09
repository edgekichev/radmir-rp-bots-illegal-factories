#include "main.h"

int SortPacket[45] = {215, 2, 0, 0, 0, 0, 0, 25, 0, 0, 0, 70, 111, 111, 100, 83, 111, 114, 116, 95, 79, 110, 83, 101, 108, 101, 99, 116, 67, 97, 116, 101, 103, 111, 114, 121, 2, 0, 0, 0, 100, 1, 0, 0, 0};
int AltPacket[41] =  { 215, 2, 0, 0, 0, 0, 0, 21, 0, 0, 0, 79, 110, 80, 108, 97, 121, 101, 114, 67, 108, 105, 101, 110, 116, 83, 105, 100, 101, 75, 101, 121, 2, 0, 0, 0, 100, 18, 0, 0, 0};
int DialogResponse[51] = { 215, 2, 0,0,0,0,0,16,0,0,0,79,110,68,105,97,108,111,103,82,101,115,112,111,110,115,101,8,0,0,0,100,0,0,0,0,100,1,0,0,0,100,255,255,255,255,115,0,0,0,0 };


void SendTable(int group)
{
	BitStream MyPacket;
	for (int i = 0; i < 45; i++) {
		if (i == 41) {	
			MyPacket.Write((BYTE) group);
		}
		else {
			MyPacket.Write((BYTE)SortPacket[i]);
		}
	}

	SF->getRakNet()->SendPacket(&MyPacket);
}


void SendDialog() {
	BitStream MyPacket;
	for (int i = 0; i < 45; i++) {
		MyPacket.Write((BYTE)DialogResponse[i]);
	}

	SF->getRakNet()->SendPacket(&MyPacket);
}



void SendAlt() {
	BitStream MyPacket;
	for (int i = 0; i < 45; i++) {
		MyPacket.Write((BYTE)AltPacket[i]);
	}

	SF->getRakNet()->SendPacket(&MyPacket);
}

float distanceR(int x1, int y1, int x2, int y2)
{
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);
}

bool isStolSvoboden(float X, float Y) {
	float Dist;
	float MinDist = 10000;

	float newX, newY;
	std::string labelString;
	for (int i = 0; i < SAMP_MAX_3DTEXTS; i++)
	{
		if (SF->getSAMP()->getNetGame()->pools->textLabelPool->iIsListed[i] != 1)
			continue;
		std::string strdialogText(SF->getSAMP()->getNetGame()->pools->textLabelPool->textLabel[i].text);
		if (strdialogText.find("Сортировка продукции") != std::string::npos) {
			float labelposX = SF->getSAMP()->getNetGame()->pools->textLabelPool->textLabel[i].position[0];
			float labelposY = SF->getSAMP()->getNetGame()->pools->textLabelPool->textLabel[i].position[1];

			CVector* vect = PEDSELF->GetPosition();

			Dist = distanceR(X, Y, labelposX, labelposY);

			if (Dist < MinDist) {
				newX = labelposX;
				newY = labelposY;
				MinDist = Dist;
				labelString = strdialogText;
			}
		}
	}
	return (labelString.find("Свободно") != std::string::npos);
}