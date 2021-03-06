#pragma once

#include <Windows.h>
#include <math.h>
#include <vector>
#include <thread>
#include <mutex>

//Zet multithreading hier aan of uit
//#define MULTITHREADED
//#define DEBUG

typedef struct Grid {
	int TLX = 0;
	int TLY = 0;
	int BRX = 0;
	int BRY = 0;
};

class ScreenCalc
{
public:
	ScreenCalc(float Diago, UINT32 *DataSet, int Hres, int Vres, int BlockH, int BlockV,
		int boven, int onder, int links, int rechts, int Black);
	~ScreenCalc();
	void Bereken_Grid();

	void set_Gamma(float Gamma);
	void set_Brightness(int Brightness);
	void update();

	void SetOffset(int *Offset);
	void SetvOffset(int Offset);
	void SethOffset(int Offset);
	void set_data(UINT32 *dataset);

	int Calc_Aspect_ratio();


	UINT16 geefLeds();
	UINT8 *GeefLedPointer();

private:
	void Gemiddelde(UINT8 *Led, int TopLeftX, int TopLeftY, int BottomLeftY, int BottomRightX);
	void Calc_Top_border();
	void Calc_Side_border();
	void Bereken();


	float Hoogte;
	float Lengte;
	float K_P;

	int Hres, Vres;
	int BlockDepthHori;	//in procent
	int BlockDepthVert; //in procent
	int LedsBoven;
	int LedsOnder;
	int LedsLinks;
	int LedsRechts;
	int BlackLevel;
	int hborder = 0;
	int vborder = 0;
	int hOffset = 0;
	int	vOffset = 0;
	int brightness;
	UINT16 LedAantal;

	UINT32 *PixelData;
	UINT8 *LedData;	//multidimensio pointer
	UINT8 *OldLedData;	//PID

	Grid *Blok;

	int *Offset;

	//Gamma correction lookup table
	int *GammaE;

	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);


#ifdef MULTITHREADED
private:
	std::thread **threadPool;
	std::mutex *startMutexPool;
	std::mutex *readyMutexPool;
public:
	static void ThreadedBereken(UINT32 *ScreenData, Grid *Area, std::mutex *startmtx, std::mutex *readymtx);
#endif
};

