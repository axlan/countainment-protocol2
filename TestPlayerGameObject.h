#pragma once

#include <SDL.h>

class TestPlayerGameObject
{
public:
	TestPlayerGameObject(const SDL_Rect & init_rect, const SDL_Color &color)
	{
		bound_box_ = init_rect;
		display_color_ = color;
	}

	void Move(const SDL_Point & new_loc)
	{
		bound_box_.x = new_loc.x;
		bound_box_.y = new_loc.y;
	}

	SDL_bool CheckBound(const SDL_Rect & check_rect) const
	{
		return SDL_HasIntersection(&check_rect, &bound_box_);
	}

	void SetSelect(bool selected)
	{
		selected_ = selected;
	}

	bool IsSelected() const
	{
		return selected_;
	}

	void Update()
	{

	}

	void Draw(SDL_Renderer* renderer) const
	{
		SDL_SetRenderDrawColor(renderer, display_color_.r, display_color_.g, display_color_.b, display_color_.a);
		SDL_RenderFillRect(renderer, &bound_box_);
		if (selected_)
		{
			SDL_SetRenderDrawColor(renderer,0, 0, 0, 255);
			SDL_RenderDrawRect(renderer,&bound_box_);
		}
	}

private:

	SDL_Color display_color_;
	SDL_Rect bound_box_;

	bool selected_ = false;
};
