#include "tasma.h"

#include <cmath>
#include <vector>
#include <ctime>
#include <cstdlib>

namespace proj
{
	Tasma* tasmaL;
	Tasma* tasmaR;
	Tasma* tasmaS;
	Figura* kolo;
	Figura* kwadrat;
	int value = 0;
	std::vector<Tasma*> tasmy;
	std::list<Figura*> figury;

	void init()
	{
		tasmy.push_back(new Tasma(600, 0, 200, 1, 0) );
		tasmy.push_back(new Selektor(250, 560, 320, 1, -0.3));
		tasmy.push_back(new Tasma(700, 800, 300, 1, 0));
	}

	void draw(HDC hdc)
	{
		for (std::vector<Tasma*>::iterator it = tasmy.begin(); it != tasmy.end(); it++)
		{
			(*it)->draw(hdc);
		}

		for (std::list<Figura*>::iterator it = figury.begin(); it != figury.end(); it++)
		{
			(*it)->draw(hdc);
		}
	}

	void update()
	{
		value++;
		if (value % 15 == 0)
		{
			int rodzaj = rand() % 2;
			Figura* fig = new Figura(50, 50, rodzaj);
			figury.push_back(fig);
		}

		std::list< std::list<Figura*>::iterator > toremove;

		for (std::list<Figura*>::iterator it = figury.begin(); it != figury.end(); it++)
		{
			Figura* fig = *it;
			fig->update();
			if (fig->getY() > 1000)				//Jesli wyjdzie poza zakres
				toremove.push_back(it);
		}

		for (std::list< std::list< Figura* >::iterator >::iterator it = toremove.begin(); it != toremove.end(); it++)
		{
			figury.erase(*it);
		}
	}
	
	void quit()
	{
		delete tasmaL;
		delete tasmaR;
		delete tasmaS;
	}

	Tasma::Tasma()
	{
		len = 0;
		x = 0;
		y = 0;
		dx = 0;
		dy = 0;
	}

	Tasma::Tasma(float len, float x, float y, float dx, float dy)
	{
		this->len = len;
		setDirection(dx, dy);
		this->x = x;
		this->y = y;
	}
	
	void Tasma::draw(HDC hdc)
	{
		Graphics graphics(hdc);
		Pen      pen(Color(255, 0, 0, 255));
		graphics.DrawLine(&pen, x, y, x + dx*len, y + dy*len);
	}

	void Tasma::setDirection(float angle)
	{
		dx = cos(angle);
		dy = sin(angle);
	}

	void Tasma::setDirection(float x, float y)
	{
		float l = sqrt(x*x + y*y);
		dx = x / l;
		dy = y / l;
	}

	void Tasma::add(Figura* fig)
	{
		figury.push_back(fig);
	}

	void Tasma::remove(Figura* fig)
	{
		figury.remove(fig);
	}

	bool Tasma::collides(float tx, float ty)
	{
		float fy = dy / dx * (tx - x) + y;   // y=f(x) dla tasmy SELEKTOR
			if (tx > x && tx < (x + dx*len) &&
				ty > fy && ty < (fy + 1*SPEED + 1) )
				return true;
		return false;
	}

	Figura::Figura(float x, float y, int type)
	{
		this->x = x;
		this->y = y;
		this->pod = NULL;
		this->type = type;
	}

	void Figura::update()
	{
		float nextX, nextY;
		Tasma* starepod = pod;
		pod = NULL;

		for (std::vector<Tasma*>::iterator it = tasmy.begin(); it != tasmy.end(); it++)
		{
			if ((*it)->collides(x, y))
			{
				pod = (*it);
				break;
			}
		}

		if (!starepod && pod)
			pod->add(this);
		if (!pod && starepod)
			starepod->remove(this);
		if (!pod)
		{
			nextX = x ;
			nextY = y + 1*SPEED;
		}
		else{
			nextX = x + pod->getDx()*SPEED;
			nextY = y + pod->getDy()*SPEED;
		}

		//sprawdzanie kolizji
		x = nextX;
		y = nextY;
	
	}

	Selektor::Selektor(float len, float x, float y, float dx, float dy)
	{
		this->len = len;
		setDirection(dx, dy);
		this->x = x;
		this->y = y;
	}

	void Figura::draw(HDC hdc)
	{
		Graphics graphics(hdc);
		if (type == 0)
		{
			SolidBrush      solidbrush(Color(255, 0, 0, 255));
			graphics.FillEllipse(&solidbrush, int(x)-15, int(y)-30, 30, 30);
		}
		else
		{
			SolidBrush      solidbrush(Color(255, 255, 0, 0));
			graphics.FillRectangle(&solidbrush, int(x)-15, int(y)-30, 30, 30);
		}
		
	}

	void Selektor::draw(HDC hdc)
	{
		Graphics graphics(hdc);
		Pen      pen(Color(255, 0, 0, 255));
		graphics.DrawLine(&pen, x, y, x + dx*len, y + dy*len);
	}

	void Selektor::add(Figura* fig)
	{
		if (fig->getType() == Figura::SQUARE)
		{
			reverse = true;
		}
		if ((fig->getType() != Figura::SQUARE))
			reverse = false;
	}

	void Selektor::remove(Figura* fig) 
	{
		if (reverse && fig->getType() == Figura::SQUARE)
			reverse = false;
	}

	int Figura::getType()
	{
		return type;
	}

	float Selektor::getDx()
	{
		if (reverse)
			return -dx;
		return dx;
	}

	float Selektor::getDy()
	{
		if (reverse)
			return -dy;
		return dy;
	}

	float Tasma::getDx()
	{
		return dx;
	}

	float Tasma::getDy()
	{
		return dy;
	}

	float Tasma::getLength()
	{
		return len;
	}

	float Tasma::getX()
	{
		return x;
	}

	float Tasma::getY()
	{
		return y;
	}

	float Figura::getY()
	{
		return y;
	}
}