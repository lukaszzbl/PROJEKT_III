

#ifndef __proj_H
#define __proj_H

#include "stdafx.h"

#include <list>

namespace proj
{
	void init();
	void draw(HDC);
	void update();
	void quit();

	class Figura
	{
	private:
		float x, y;
		int type;
	public:

		enum 
		{
			CIRCLE,
			SQUARE,
		};

		Figura();
		Figura(float x, float y);
		void update();
		void draw(HDC);
		int getType();
		float getX();
		float getY();
	};

	class Tasma
	{
	protected:
		float len, x, y;
		float dx, dy;
		std::list<Figura*> figury;
	public:
		Tasma();
		Tasma(float len, float x, float y, float dx, float dy);
		void draw(HDC);
		float getX();
		float getY();
		virtual float getDx();
		virtual float getDy();
		void setDirection(float angle);
		void setDirection(float x, float y);
		virtual void add(Figura* fig);
		virtual void remove(Figura* fig);
	};

	class Selektor : public Tasma
	{
		bool reverse;
		virtual float getDx();
		virtual float getDy();
		virtual void add(Figura* fig);
		virtual void remove(Figura* fig);
	};

}

#endif