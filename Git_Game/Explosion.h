#pragma once
#include "Explosive_Ball.h"

//------------------------------------------------------------------------------------------------------------
class AExplosion
{
protected:
	AExplosion();

	void Start_Explosion(RECT &area_rect);

	bool Act_On_Explosion();

	void Draw_Explosion(HDC hdc, RECT & paint_area);

private:

	vector<AExplosive_Ball> Explosive_Balls;
	static const int Explosive_Balls_Count = 20;

};
//------------------------------------------------------------------------------------------------------------

