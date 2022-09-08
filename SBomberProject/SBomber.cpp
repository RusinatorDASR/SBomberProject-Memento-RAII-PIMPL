
#include <conio.h>
#include <windows.h>

#include "MyTools.h"
#include "Bomb.h"
#include "Ground.h"
#include "Tank.h"
#include "House.h"
#include "SBomberImpl.h"

extern FileLogger logger("log.txt");

using namespace std;
using namespace MyTools;



SBomber::SBomber()
    : bomberImpl(new SBomberImpl(false, 0, 0, 0, 0, 0, 10, 0))
	
{
    logger.WriteToLog(string(__FUNCTION__) + " was invoked");

    Plane* p = new Plane;
    p->SetDirection(1, 0.1);
    p->SetSpeed(4);
    p->SetPos(5, 10);
    bomberImpl->vecDynamicObj.push_back(p);

    LevelGUI* pGUI = new LevelGUI;
    pGUI->SetParam(bomberImpl->passedTime, bomberImpl->fps, bomberImpl->bombsNumber, bomberImpl->score);
    const uint16_t maxX = GetMaxX();
    const uint16_t maxY = GetMaxY(); 
    const uint16_t offset = 3;
    const uint16_t width = maxX - 7;
    pGUI->SetPos(offset, offset);
    pGUI->SetWidth(width);
    pGUI->SetHeight(maxY - 4);
    pGUI->SetFinishX(offset + width - 4);
	bomberImpl->vecStaticObj.push_back(pGUI);

    Ground* pGr = new Ground;
    const uint16_t groundY = maxY - 5;
    pGr->SetPos(offset + 1, groundY);
    pGr->SetWidth(width - 2);
	bomberImpl->vecStaticObj.push_back(pGr);

    Tank* pTank = new Tank;
    pTank->SetWidth(13);
    pTank->SetPos(30, groundY - 1);
	bomberImpl->vecStaticObj.push_back(pTank);

    pTank = new Tank;
    pTank->SetWidth(13);
    pTank->SetPos(50, groundY - 1);
	bomberImpl->vecStaticObj.push_back(pTank);

    House * pHouse = new House;
    pHouse->SetWidth(13);
    pHouse->SetPos(80, groundY - 1);
	bomberImpl->vecStaticObj.push_back(pHouse);

    /*
    Bomb* pBomb = new Bomb;
    pBomb->SetDirection(0.3, 1);
    pBomb->SetSpeed(2);
    pBomb->SetPos(51, 5);
    pBomb->SetSize(SMALL_CRATER_SIZE);
    vecDynamicObj.push_back(pBomb);
    */
}

SBomber::~SBomber()
{
    for (size_t i = 0; i < bomberImpl->vecDynamicObj.size(); i++)
    {
        if (bomberImpl->vecDynamicObj[i] != nullptr)
        {
            delete bomberImpl->vecDynamicObj[i];
        }
    }

    for (size_t i = 0; i < bomberImpl->vecStaticObj.size(); i++)
    {
        if (bomberImpl->vecStaticObj[i] != nullptr)
        {
            delete bomberImpl->vecStaticObj[i];
        }
    }
	delete bomberImpl;
}

bool SBomber::GetExitFlag() const { return bomberImpl->exitFlag; }

void SBomber::MoveObjects()
{
    logger.WriteToLog(string(__FUNCTION__) + " was invoked");

    for (size_t i = 0; i < bomberImpl->vecDynamicObj.size(); i++)
    {
        if (bomberImpl->vecDynamicObj[i] != nullptr)
        {
			bomberImpl->vecDynamicObj[i]->Move(bomberImpl->deltaTime);
        }
    }
};

void SBomber::CheckObjects()
{
    logger.WriteToLog(string(__FUNCTION__) + " was invoked");

	bomberImpl->CheckPlaneAndLevelGUI();
	bomberImpl->CheckBombsAndGround();
};




void SBomber::ProcessKBHit()
{
    int c = _getch();

    if (c == 224)
    {
        c = _getch();
    }

    logger.WriteToLog(string(__FUNCTION__) + " was invoked. key = ", c);

    switch (c) {

    case 27: // esc
		bomberImpl->exitFlag = true;
        break;

    case 72: // up
		bomberImpl->FindPlane()->ChangePlaneY(-0.25);
        break;

    case 80: // down
		bomberImpl->FindPlane()->ChangePlaneY(0.25);
        break;

    case 'b':
		bomberImpl->DropBomb();
        break;

    case 'B':
		bomberImpl->DropBomb();
        break;

    default:
        break;
    }
}

void SBomber::DrawFrame()
{
    logger.WriteToLog(string(__FUNCTION__) + " was invoked");

    for (size_t i = 0; i < bomberImpl->vecDynamicObj.size(); i++)
    {
        if (bomberImpl->vecDynamicObj[i] != nullptr)
        {
			bomberImpl->vecDynamicObj[i]->Draw();
        }
    }

    for (size_t i = 0; i < bomberImpl->vecStaticObj.size(); i++)
    {
        if (bomberImpl->vecStaticObj[i] != nullptr)
        {
			bomberImpl->vecStaticObj[i]->Draw();
        }
    }

    GotoXY(0, 0);
	bomberImpl->fps++;

	bomberImpl->FindLevelGUI()->SetParam(bomberImpl->passedTime, bomberImpl->fps, bomberImpl->bombsNumber, bomberImpl->score);
}

void SBomber::TimeStart()
{
    logger.WriteToLog(string(__FUNCTION__) + " was invoked");
	bomberImpl->startTime = GetTickCount64();
}

void SBomber::TimeFinish()
{
	bomberImpl->finishTime = GetTickCount64();
	bomberImpl->deltaTime = uint16_t(bomberImpl->finishTime - bomberImpl->startTime);
	(bomberImpl->passedTime) += (bomberImpl->deltaTime);

    logger.WriteToLog(string(__FUNCTION__) + " deltaTime = ", (int)(bomberImpl->deltaTime));
}

