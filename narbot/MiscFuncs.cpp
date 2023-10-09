#include "main.h"
#include <vector>

int BuildPacket[43] = { 215, 2, 0, 0, 0, 0, 0, 28, 0, 0, 0, 87, 101, 97, 112, 111, 110, 65, 115, 115, 101, 109, 98, 95, 79, 110, 74, 111, 105, 110, 67, 111, 109, 112, 111, 110, 101, 110, 116, 0, 0, 0, 0 };
int AltPacket[41] = { 215, 2, 0, 0, 0, 0, 0, 21, 0, 0, 0, 79, 110, 80, 108, 97, 121, 101, 114, 67, 108, 105, 101, 110, 116, 83, 105, 100, 101, 75, 101, 121, 2, 0, 0, 0, 100, 18, 0, 0, 0 };
int DialogResponse[51] = { 215, 2, 0,0,0,0,0,16,0,0,0,79,110,68,105,97,108,111,103,82,101,115,112,111,110,115,101,8,0,0,0,100,0,0,0,0,100,1,0,0,0,100,255,255,255,255,115,0,0,0,0 };

int ebalmatbnomer[39] = { 215, 2, 0, 0, 0, 0, 0, 24, 0, 0, 0, 67, 111, 111, 107, 68, 114, 117, 103, 115, 95, 79, 110, 67, 111, 109, 112, 108, 101, 116, 101, 84, 97, 115, 107, 0, 0, 0, 0, };
int ebalmatbnomerone[45] = {215, 2, 0, 0, 0, 0, 0, 20, 0, 0, 0, 67, 111, 111, 107, 68, 114, 117, 103, 115, 95, 79, 110, 73, 116, 101, 109, 77, 111, 118, 101, 4, 0, 0, 0, 100, 0, 0, 0, 0, 100, 1, 0, 0, 0};
int ebalmatbnomertwo[45] = {215, 2, 0, 0, 0, 0, 0, 20, 0, 0, 0, 67, 111, 111, 107, 68, 114, 117, 103, 115, 95, 79, 110, 73, 116, 101, 109, 77, 111, 118, 101, 4, 0, 0, 0, 100, 2, 0, 0, 0, 100, 2, 0, 0, 0};
int ebalmatbnomerthree[45] = {215, 2, 0, 0, 0, 0, 0, 20, 0, 0, 0, 67, 111, 111, 107, 68, 114, 117, 103, 115, 95, 79, 110, 73, 116, 101, 109, 77, 111, 118, 101, 4, 0, 0, 0, 100, 2, 0, 0, 0, 100, 3, 0, 0, 0};
int ebalmatbnomerfour[45] = {215, 2, 0, 0, 0, 0, 0, 20, 0, 0, 0, 67, 111, 111, 107, 68, 114, 117, 103, 115, 95, 79, 110, 73, 116, 101, 109, 77, 111, 118, 101, 4, 0, 0, 0, 100, 1, 0, 0, 0, 100, 2, 0, 0, 0};

float paths[4][100][2] =
{
	{ // 30
		{-1602.5906982422, -585.451293945310}, { -1602.1475830078, -585.85614013672},
		{ -1601.8736572266, -586.13079833984}, { -1601.6623535156, -586.33508300781},
		{ -1601.4425048828, -586.54516601563}, { -1601.2225341797, -586.75531005859},
		{ -1601.0034179688, -586.96484375000}, { -1600.9189453125, -587.04547119141},
		{ -1600.6945800781, -587.25976562500},
		{ -1600.2244873047, -587.70758056641}, { -1599.998046875, -587.922790527340},
		{ -1599.8797607422, -588.03515625000}, { -1599.7097167969, -588.30474853516},
		{ -1599.6447753906, -588.61260986328}, { -1599.5612792969, -588.92041015625},
		{ -1599.462890625, -589.223999023440}, { -1599.3642578125, -589.48931884766},
		{ -1599.2524414063, -589.74249267578}, { -1599.1331787109, -589.96942138672},
		{ -1598.9790039063, -590.20825195313}, { -1598.8081054688, -590.42248535156},
		{ -1598.6300048828, -590.60131835938}, { -1598.4405517578, -590.75909423828},
		{ -1598.2189941406, -590.90789794922}, { -1597.9870605469, -591.02886962891},
		{ -1597.6964111328, -591.14111328125}, { -1597.0096435547, -591.20959472656},
		{ -1596.6241455078, -590.90405273438}, { -1595.9831542969, -590.29693603516},
		{ -1595.9831542969, -590.29693603516}
	},
	{ // 34
		{ -1602.5909423828, -585.3473510742}, { -1602.2593994141, -585.6464233398},
		{ -1601.9825439453, -585.9194335937}, { -1601.8259277344, -586.0751342773},
		{ -1601.6452636719, -586.2565307617}, { -1601.4412841797, -586.4615478515},
		{ -1601.2414550781, -586.6657714843}, { -1601.0705566406, -586.8541259765},
		{ -1600.9068603516, -587.0554809570}, { -1600.7048339844, -587.3074951171},
		{ -1600.5201416016, -587.5380249023}, { -1600.3330078125, -587.7715454101},
		{ -1600.1325683594, -588.0216674804},
		{ -1599.6707763672, -588.5903930664}, { -1599.5491943359, -588.7382812500},
		{ -1599.3394775391, -588.9932861328}, { -1599.1121826172, -589.2684326171},
		{ -1598.8674316406, -589.5590820312}, { -1598.6302490234, -589.8322753906},
		{ -1598.3927001953, -590.0998535156}, { -1597.9442138672, -590.5667724609},
		{ -1597.7322998047, -590.7677612304}, { -1597.4832763672, -590.9940185546},
		{ -1597.2390136719, -591.2088623046}, { -1597.0096435547, -591.4060668945},
		{ -1596.7762451172, -591.6030883789}, { -1596.5574951172, -591.7832641601},
		{ -1596.3437500000, -591.9541625976}, { -1596.1160888672, -592.1274414062},
		{ -1595.8471679688, -592.3134155273}, { -1595.6538085938, -592.4356689453},
		{ -1595.3963623047, -592.5828247070}, { -1594.9600830078, -592.9431152343},
		{ -1594.9600830078, -592.9431152343}
	},
	{ // 34
		{ -1602.6623535156, -585.41619873047}, { -1602.1917724609, -585.89428710938},
		{ -1602.0712890625, -586.01782226563}, { -1601.9047851563, -586.19744873047},
		{ -1601.6999511719, -586.41503906250}, { -1601.5010986328, -586.62536621094},
		{ -1601.3291015625, -586.80725097656}, { -1601.1130371094, -587.03576660156},
		{ -1601.0728759766, -587.07824707031}, { -1600.9241943359, -587.23553466797},
		{ -1600.6401367188, -587.41461181641}, { -1600.3919677734, -587.59497070313},
		{ -1600.2126464844, -587.78265380859}, 
		{ -1599.9560546875, -587.94549560547}, { -1599.7349853516, -588.10174560547},
		{ -1599.5599365234, -588.34552001953}, { -1599.4190673828, -588.61700439453},
		{ -1599.3281250000, -588.89166259766}, { -1599.2766113281, -589.16827392578},
		{ -1599.2629394531, -589.44116210938}, { -1599.3457031250, -589.97174072266},
		{ -1599.4316406250, -590.23455810547}, { -1599.5406494141, -590.46875000000},
		{ -1599.6888427734, -590.68377685547}, { -1599.8919677734, -590.87475585938},
		{ -1600.1121826172, -590.99627685547}, { -1600.3968505859, -591.06762695313},
		{ -1600.6710205078, -591.07135009766}, { -1600.8967285156, -590.96405029297},
		{ -1601.1605224609, -590.87792968750}, { -1601.3914794922, -590.77539062500},
		{ -1601.5952148438, -590.63604736328}, { -1606.5920410000, -590.29589840000},
		{ -1606.5920410000, -590.29589840000}
	},
	{ // 34
		{ -1602.6623535156, -585.41619873047}, { -1602.1917724609, -585.89428710938},
		{ -1602.0712890625, -586.01782226563}, { -1601.9047851563, -586.19744873047},
		{ -1601.6999511719, -586.41503906250}, { -1601.5010986328, -586.62536621094},
		{ -1601.3291015625, -586.80725097656}, { -1601.1130371094, -587.03576660156},
		{ -1601.0728759766, -587.07824707031}, { -1600.9241943359, -587.23553466797},
		{ -1600.6401367188, -587.41461181641}, { -1600.3919677734, -587.59497070313},
		{ -1600.2126464844, -587.78265380859}, { -1600.0070800781, -587.92376708984},
		{ -1599.9560546875, -587.94549560547},
		{ -1599.5599365234, -588.34552001953}, { -1599.4190673828, -588.61700439453},
		{ -1599.3281250000, -588.89166259766}, { -1599.2766113281, -589.16827392578},
		{ -1599.2629394531, -589.44116210938}, { -1599.3457031250, -589.97174072266},
		{ -1599.4316406250, -590.23455810547}, { -1599.5406494141, -590.46875000000},
		{ -1599.6888427734, -590.68377685547}, { -1599.8919677734, -590.87475585938},
		{ -1600.1121826172, -590.99627685547}, { -1600.3968505859, -591.06762695313},
		{ -1600.6710205078, -591.07135009766}, { -1600.8967285156, -590.96405029297},
		{ -1601.1605224609, -590.87792968750}, { -1601.3914794922, -590.77539062500},
		{ -1601.5952148438, -590.63604736328}, { -1604.1994628900, -590.38873290000},
		{ -1604.1994628900, -590.38873290000}
	}
};



float CalcDist2d(float x1, float y1, float x2, float y2)
{
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);
}

void SendBuild4() // похуй + похуй ( да насрал, ну и что )
{
	BitStream MyPacket;
	for (int i = 0; i < 45; i++) {
		MyPacket.Write((BYTE)ebalmatbnomerfour[i]);
	}

	SF->getRakNet()->SendPacket(&MyPacket);
}

void SendBuild3() // похуй + похуй
{
	BitStream MyPacket;
	for (int i = 0; i < 45; i++) {
		MyPacket.Write((BYTE)ebalmatbnomerthree[i]);
	}

	SF->getRakNet()->SendPacket(&MyPacket);
}

void SendBuild2() // похуй + похуй
{
	BitStream MyPacket;
	for (int i = 0; i < 45; i++) {
		MyPacket.Write((BYTE)ebalmatbnomertwo[i]);
	}

	SF->getRakNet()->SendPacket(&MyPacket);
}

void SendBuild1() // похуй + похуй
{
	BitStream MyPacket;
	for (int i = 0; i < 45; i++) {
		MyPacket.Write((BYTE)ebalmatbnomerone[i]);
	}

	SF->getRakNet()->SendPacket(&MyPacket);
}

void SendBuild0() // похуй + похуй
{
	BitStream MyPacket;
	for (int i = 0; i < 45; i++) {
		MyPacket.Write((BYTE)ebalmatbnomer[i]);
	}

	SF->getRakNet()->SendPacket(&MyPacket);
}


void SendDialog() {
	BitStream MyPacket;
	for (int i = 0; i < 51; i++) {
		MyPacket.Write((BYTE)DialogResponse[i]);
	}

	SF->getRakNet()->SendPacket(&MyPacket);
}


void SendAlt() {
	BitStream MyPacket;
	for (int i = 0; i < 41; i++) {
		MyPacket.Write((BYTE)AltPacket[i]);
	}

	SF->getRakNet()->SendPacket(&MyPacket);
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
		if (strdialogText.find("Изготовление наркотиков") != std::string::npos) {
			float labelposX = SF->getSAMP()->getNetGame()->pools->textLabelPool->textLabel[i].position[0];
			float labelposY = SF->getSAMP()->getNetGame()->pools->textLabelPool->textLabel[i].position[1];

			Dist = CalcDist2d(X, Y, labelposX, labelposY);

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

bool findStanok(int *stanok) {

	float MinDist = 10000;
	float Dist;


	float cX = 0;
	float cY = 0;
	
	CVector* vect = PEDSELF->GetPosition();
	for (int i = 0; i < SAMP_MAX_3DTEXTS; i++) {
		if (SF->getSAMP()->getNetGame()->pools->textLabelPool->iIsListed[i] != 1)
			continue;
		std::string labelText(SF->getSAMP()->getNetGame()->pools->textLabelPool->textLabel[i].text);

		if (labelText.find("Изготовление наркотиков") != std::string::npos && labelText.find("Свободно") != std::string::npos)
		{
			float labelX = SF->getSAMP()->getNetGame()->pools->textLabelPool->textLabel[i].position[0];
			float labelY = SF->getSAMP()->getNetGame()->pools->textLabelPool->textLabel[i].position[1];

			Dist = sqrt(pow(labelX - vect->fX, 2) + pow(labelY - vect->fY, 2) * 1.0);

			if (Dist < MinDist) {
				cX = labelX;
				cY = labelY;
				MinDist = Dist;
			}
		}
	
	}

	if (MinDist == 10000)
		return false;
	if (CalcDist2d(cX, cY, -1595.9831542969, -590.29693603516) < 1) {
		*stanok = 0;
	}
	else if (CalcDist2d(cX, cY, -1594.9600830078, -592.9431152343) < 1) {
		*stanok = 1;
	}
	else if (CalcDist2d(cX, cY, -1606.5920410, -590.2958984) < 1) {
		*stanok = 2;
	}
	else if (CalcDist2d(cX, cY, -1604.1849365234, -590.29779052734) < 1) {
		*stanok = 3;
	}
	*stanok = (rand() % static_cast<int>(2));
	return true;
}


VECTOR getNearestPathDot(int stanok, int *pathProg, int pathLen) 
{
	VECTOR pathDot = { paths[stanok][0][0], paths[stanok][0][1], 0 };
	CVector* vect = PEDSELF->GetPosition();
	float MinDist = 10000;
	float Dist = CalcDist2d(vect->fX, vect->fY, paths[stanok][0][0], paths[stanok][0][1]);

	*pathProg = 0;

	for (int i = 1; i < pathLen; i++) {
		Dist = CalcDist2d(vect->fX, vect->fY, paths[stanok][i][0], paths[stanok][i][1]);
		if (Dist < MinDist) {
			MinDist = Dist;
			pathDot.X = paths[stanok][i][0];
			pathDot.Y = paths[stanok][i][1];
			*pathProg = i;
		}
	}
	return pathDot;
}


bool RunToPoint(int stanok, int pathprog, int PathLen) {
	CVector* vect = PEDSELF->GetPosition();
	float rX = paths[stanok][pathprog][0];
	float rY = paths[stanok][pathprog][1];

	float dist = sqrt((rX - vect->fX) * (rX - vect->fX) + (rY - vect->fY) * (rY - vect->fY));
	cameraset(rX, rY);
	SF->getGame()->emulateGTAKey(1, -128);
	if (pathprog < (3 * PathLen / 4) && pathprog > (PathLen / 4)) {
		SF->getGame()->emulateGTAKey(16, 255);
	}
	return dist < 0.7;
}


bool RunToCoord(float rX, float rY) {
	CVector* vect = PEDSELF->GetPosition();

	float dist = sqrt((rX - vect->fX) * (rX - vect->fX) + (rY - vect->fY) * (rY - vect->fY));
	cameraset(rX, rY);
	SF->getGame()->emulateGTAKey(1, -128);
	if (dist < 1.5 && dist > 0.8) {
		SF->getGame()->emulateGTAKey(16, 255);
	}
	else if (dist < 0.8) {
		SF->getGame()->emulateGTAKey(21, 255);
	}
	return dist < 0.7;
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