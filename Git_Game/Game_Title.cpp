#include "Game_Title.h"

//AsGame_Title
const double AsGame_Title::Low_Y_Pos = 135.0;
//------------------------------------------------------------------------------------------------------------
AsGame_Title::~AsGame_Title()
{
	for (auto* title : Title_Letters)
		delete title;

	Title_Letters.erase(Title_Letters.begin(), Title_Letters.end());
}
//------------------------------------------------------------------------------------------------------------
AsGame_Title::AsGame_Title()
	: Game_Title_State(EGame_Title_State::Idle), Start_Tick(0), Destroy_Index(0)
{
}
//------------------------------------------------------------------------------------------------------------
void AsGame_Title::Act()
{
	int current_tick;
	double y_pos;
	double ratio;

	if (Game_Title_State == EGame_Title_State::Idle || Game_Title_State == EGame_Title_State::Finished)
		return;

	current_tick = AsConfig::Current_Timer_Tick - Start_Tick;

	switch (Game_Title_State)
	{
	case EGame_Title_State::Game_Over_Descent:
	case EGame_Title_State::Game_Won_Descent:
		if (current_tick < Descent_Timeout)
			ratio = (double)current_tick / (double)Descent_Timeout;
		else
		{
			ratio = 1.0;

			if (Game_Title_State == EGame_Title_State::Game_Over_Descent)
				Game_Title_State = EGame_Title_State::Game_Over_Show;
			else
				Game_Title_State = EGame_Title_State::Game_Won_Animate;

			Start_Tick = AsConfig::Current_Timer_Tick;
		}

		y_pos = Low_Y_Pos * ratio;

		for (auto *title : Title_Letters)
			title->Y_Pos = y_pos;

		Prev_Title_Rect = Title_Rect;

		Title_Rect.top = (int)(y_pos * AsConfig::D_Global_Scale);
		Title_Rect.bottom = Title_Rect.top + Height * AsConfig::Global_Scale;

		AsTools::Invalidate_Rect(Title_Rect);
		AsTools::Invalidate_Rect(Prev_Title_Rect);
		break;

	case EGame_Title_State::Game_Over_Show:
		if (current_tick > Game_Over_Showing_Timeout)
		{
			Game_Title_State = EGame_Title_State::Game_Over_Destroy;
			Start_Tick = AsConfig::Current_Timer_Tick;
		}
		break;

	case EGame_Title_State::Game_Over_Destroy:
		Destroy_Letters(current_tick);
		break;

	case EGame_Title_State::Game_Won_Animate:
		if (current_tick < Game_Won_Animate_Timeout)
			Animate_Game_Won();
		else
			Game_Title_State = EGame_Title_State::Finished;
		break;
	}
}
//------------------------------------------------------------------------------------------------------------
void AsGame_Title::Destroy_Letters(int current_tick)
{
	bool all_letters_are_finished, can_finish;

	can_finish = false;

	if (Destroy_Index == - 1 || current_tick % Destroy_Delay == 0)
	{
		++Destroy_Index;

		if (Destroy_Index >= 0 && Destroy_Index < (int)Title_Letters.size())
			Title_Letters[Destroy_Index]->Destroy();
		else
			can_finish = true;
	}

	all_letters_are_finished = true;

	for (auto *letter : Title_Letters)
	{
		letter->Act();

		all_letters_are_finished &= letter->Is_Finished();
	}

	if (can_finish && all_letters_are_finished)
		Game_Title_State = EGame_Title_State::Finished;
}
//------------------------------------------------------------------------------------------------------------
void AsGame_Title::Animate_Game_Won()
{
	unsigned char r, g, b;
	int letter_index;
	AFinal_Letter *letter;

	letter_index = AsTools::Rand(Title_Letters.size());

	letter = Title_Letters[letter_index];

	r = AsTools::Rand(256);
	g = AsTools::Rand(256);
	b = AsTools::Rand(256);

	letter->Set_Color(r, g, b);
}
//------------------------------------------------------------------------------------------------------------
void AsGame_Title::Clear(HDC hdc, RECT& paint_area)
{
	RECT intersection_rect;

	if (Game_Title_State == EGame_Title_State::Idle || Game_Title_State == EGame_Title_State::Finished)
		return;

	if (!IntersectRect(&intersection_rect, &paint_area, &Prev_Title_Rect))
		return;

	AsTools::Rect(hdc, Prev_Title_Rect, AsConfig::BG_Color);

}
//------------------------------------------------------------------------------------------------------------

void AsGame_Title::Draw(HDC hdc, RECT& paint_area)
{
	RECT intersection_rect;

	if (Game_Title_State == EGame_Title_State::Idle || Game_Title_State == EGame_Title_State::Finished)
		return;

	if (!IntersectRect(&intersection_rect, &paint_area, &Title_Rect))
		return;


	for (auto* title : Title_Letters)
		title->Draw(hdc, paint_area);
}
//------------------------------------------------------------------------------------------------------------
bool AsGame_Title::Is_Finished()
{
	return false;
}
//------------------------------------------------------------------------------------------------------------
void AsGame_Title::Show(bool game_over)
{
	double title_x, title_end_x;
	double title_y = 0.0;

	if (game_over)
	{
		title_x = 31.0;

		Title_Letters.push_back(new AFinal_Letter(title_x, title_y, L'�'));
		Title_Letters.push_back(new AFinal_Letter(title_x + 13.0, title_y, L'�'));
		Title_Letters.push_back(new AFinal_Letter(title_x + 29.0, title_y, L'�'));
		Title_Letters.push_back(new AFinal_Letter(title_x + 45.0, title_y, L'�'));
		Title_Letters.push_back(new AFinal_Letter(title_x + 59.0, title_y, L'�'));
		Title_Letters.push_back(new AFinal_Letter(title_x + 80.0, title_y, L'�'));
		Title_Letters.push_back(new AFinal_Letter(title_x + 96.0, title_y, L'�'));
		Title_Letters.push_back(new AFinal_Letter(title_x + 109.0, title_y, L'�'));
		Title_Letters.push_back(new AFinal_Letter(title_x + 121.0, title_y, L'�'));

		Game_Title_State = EGame_Title_State::Game_Over_Descent;
	}
	else
	{
		title_x = 54.0;

		Title_Letters.push_back(new AFinal_Letter(title_x, title_y, L'�'));
		Title_Letters.push_back(new AFinal_Letter(title_x + 16.0, title_y, L'�'));
		Title_Letters.push_back(new AFinal_Letter(title_x + 33.0, title_y, L'�'));
		Title_Letters.push_back(new AFinal_Letter(title_x + 46.0, title_y, L'�'));
		Title_Letters.push_back(new AFinal_Letter(title_x + 59.0, title_y, L'�'));
		Title_Letters.push_back(new AFinal_Letter(title_x + 75.0, title_y, L'�'));
		Title_Letters.push_back(new AFinal_Letter(title_x + 89.0, title_y, L'!'));
		Title_Letters.push_back(new AFinal_Letter(title_x + 94.0, title_y, L'!'));
		Title_Letters.push_back(new AFinal_Letter(title_x + 99.0, title_y, L'!'));

		Game_Title_State = EGame_Title_State::Game_Won_Descent;
	}

	title_end_x = Title_Letters[Title_Letters.size() - 1]->X_Pos + 16;

	Title_Rect.left = (int)(title_x * AsConfig::D_Global_Scale);
	Title_Rect.top = (int)(title_y * AsConfig::D_Global_Scale);
	Title_Rect.right = Title_Rect.left + (int)(title_end_x * AsConfig::D_Global_Scale);
	Title_Rect.bottom = Title_Rect.top + Height * AsConfig::Global_Scale;

	Start_Tick = AsConfig::Current_Timer_Tick;
	Destroy_Index = -1;

	AsTools::Invalidate_Rect(Title_Rect);
}
//------------------------------------------------------------------------------------------------------------
bool AsGame_Title::Is_Visible()
{
	if (Game_Title_State != EGame_Title_State::Idle)
		return true;
	else
		return false;
}
//------------------------------------------------------------------------------------------------------------