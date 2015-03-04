#pragma once

#include <SDL.h>

#include <math.h>

class TestPlayerGameObject
{
public:
	TestPlayerGameObject(const SDL_Rect & init_rect, const SDL_Color &color,double velocity)
	{
		bound_box_ = init_rect;
		display_color_ = color;
		x = init_rect.x;
		y = init_rect.y;
		xTarget = x;
		yTarget = y;
		this->velocity = velocity;
	}

	void Move(const SDL_Point & new_loc)
	{
		xTarget = new_loc.x;
		yTarget = new_loc.y;
	}

	SDL_bool CheckBound(const SDL_Rect & check_rect) const
	{
		return SDL_HasIntersection(&check_rect, &bound_box_);
	}

	void SetSelect(SDL_bool selected)
	{
		selected_ = selected;
	}

	SDL_bool IsSelected() const
	{
		return selected_;
	}

	void Update()
	{
		if (xTarget != x || yTarget != y)
		{
			double diffY = (yTarget-y);
			double diffX = (xTarget-x);

			double diffTotal = abs(diffY) + abs(diffX);

			if (diffTotal < velocity)
			{
				x = xTarget;
				y = yTarget;
			}
			else
			{
				double velX = velocity * diffX / diffTotal;
				double velY = velocity * diffY / diffTotal;

				x += velX;
				y += velY;
			}

			

			bound_box_.x = static_cast<int>(round(x));
			bound_box_.y = static_cast<int>(round(y));
		}
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

	double velocity;

	SDL_Color display_color_;
	SDL_Rect bound_box_;
	
	double x, y;
	double xTarget, yTarget;

	SDL_bool selected_ = SDL_FALSE;
};
