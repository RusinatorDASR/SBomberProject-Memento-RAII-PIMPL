#include "SBomberImpl.h"

using namespace std; 

extern FileLogger logger;

SBomberImpl::SBomberImpl(bool _exitFlag, uint64_t _startTime, uint64_t _finishTime, uint16_t _deltaTime, uint64_t _passedTime, uint16_t _fps, uint16_t _bombsNumber, int16_t _score) 
	: exitFlag(_exitFlag), startTime(_startTime), finishTime(_finishTime), deltaTime(_deltaTime), passedTime(_passedTime), 
	fps(_fps), bombsNumber(_bombsNumber), score(_score) {}

SBomberImpl::~SBomberImpl() {}

void SBomberImpl::CheckPlaneAndLevelGUI()
{
	if (FindPlane()->GetX() > FindLevelGUI()->GetFinishX())
	{
		exitFlag = true;
	}
}

void SBomberImpl::CheckBombsAndGround()
{
	vector<Bomb*> vecBombs = FindAllBombs();
	Ground* pGround = FindGround();
	const double y = pGround->GetY();
	for (size_t i = 0; i < vecBombs.size(); i++)
	{
		if (vecBombs[i]->GetY() >= y) // Пересечение бомбы с землей
		{
			pGround->AddCrater(vecBombs[i]->GetX());
			CheckDestoyableObjects(vecBombs[i]);
			DeleteDynamicObj(vecBombs[i]);
		}
	}

}

void SBomberImpl::CheckDestoyableObjects(Bomb * pBomb)
{
	vector<DestroyableGroundObject*> vecDestoyableObjects = FindDestoyableGroundObjects();
	const double size = pBomb->GetWidth();
	const double size_2 = size / 2;
	for (size_t i = 0; i < vecDestoyableObjects.size(); i++)
	{
		const double x1 = pBomb->GetX() - size_2;
		const double x2 = x1 + size;
		if (vecDestoyableObjects[i]->isInside(x1, x2))
		{
			score += vecDestoyableObjects[i]->GetScore();
			DeleteStaticObj(vecDestoyableObjects[i]);
		}
	}
}

void SBomberImpl::DeleteDynamicObj(DynamicObject* pObj)
{
	auto it = vecDynamicObj.begin();
	for (; it != vecDynamicObj.end(); it++)
	{
		if (*it == pObj)
		{
			vecDynamicObj.erase(it);
			break;
		}
	}
}

void SBomberImpl::DeleteStaticObj(GameObject* pObj)
{
	auto it = vecStaticObj.begin();
	for (; it != vecStaticObj.end(); it++)
	{
		if (*it == pObj)
		{
			vecStaticObj.erase(it);
			break;
		}
	}
}

vector<DestroyableGroundObject*> SBomberImpl::FindDestoyableGroundObjects() const
{
	vector<DestroyableGroundObject*> vec;
	Tank* pTank;
	House* pHouse;
	for (size_t i = 0; i < vecStaticObj.size(); i++)
	{
		pTank = dynamic_cast<Tank*>(vecStaticObj[i]);
		if (pTank != nullptr)
		{
			vec.push_back(pTank);
			continue;
		}

		pHouse = dynamic_cast<House*>(vecStaticObj[i]);
		if (pHouse != nullptr)
		{
			vec.push_back(pHouse);
			continue;
		}
	}

	return vec;
}

Ground* SBomberImpl::FindGround() const
{
	Ground* pGround;

	for (size_t i = 0; i < vecStaticObj.size(); i++)
	{
		pGround = dynamic_cast<Ground *>(vecStaticObj[i]);
		if (pGround != nullptr)
		{
			return pGround;
		}
	}

	return nullptr;
}

vector<Bomb*> SBomberImpl::FindAllBombs() const
{
	vector<Bomb*> vecBombs;

	for (size_t i = 0; i < vecDynamicObj.size(); i++)
	{
		Bomb* pBomb = dynamic_cast<Bomb*>(vecDynamicObj[i]);
		if (pBomb != nullptr)
		{
			vecBombs.push_back(pBomb);
		}
	}

	return vecBombs;
}

Plane* SBomberImpl::FindPlane() const
{
	for (size_t i = 0; i < vecDynamicObj.size(); i++)
	{
		Plane* p = dynamic_cast<Plane*>(vecDynamicObj[i]);
		if (p != nullptr)
		{
			return p;
		}
	}

	return nullptr;
}

LevelGUI* SBomberImpl::FindLevelGUI() const
{
	for (size_t i = 0; i < vecStaticObj.size(); i++)
	{
		LevelGUI* p = dynamic_cast<LevelGUI*>(vecStaticObj[i]);
		if (p != nullptr)
		{
			return p;
		}
	}

	return nullptr;
}

void SBomberImpl::DropBomb()
{
	if (bombsNumber > 0)
	{
		logger.WriteToLog(string(__FUNCTION__) + " was invoked");

		Plane* pPlane = FindPlane();
		double x = pPlane->GetX() + 4;
		double y = pPlane->GetY() + 2;

		Bomb* pBomb = new Bomb;
		pBomb->SetDirection(0.3, 1);
		pBomb->SetSpeed(2);
		pBomb->SetPos(x, y);
		pBomb->SetWidth(SMALL_CRATER_SIZE);

		vecDynamicObj.push_back(pBomb);
		bombsNumber--;
		score -= Bomb::BombCost;
	}
}
