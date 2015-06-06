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

	std::vector<Tasma*> tasmy;

	void init()
	{
		//tasmaL = new Tasma(500, 50, 200, 1, 0);
		//tasmaR = new Tasma(400, 500, 400, 1, -0.6 );
		//tasmaS = new Tasma(700, 800, 300, 1, 0);
		tasmy.push_back( new Tasma(500, 50, 200, 1, 0) );
		tasmy.push_back(new Tasma(400, 500, 400, 1, -0.6));
		tasmy.push_back(new Tasma(700, 800, 300, 1, 0));
		kolo = new Figura(400, 400);
		kwadrat = new Figura(300, 200);
	}

	void draw(HDC hdc)
	{
		//tasmaL->draw(hdc);
		//tasmaR->draw(hdc);
		//tasmaS->draw(hdc);
		for (std::vector<Tasma*>::iterator it = tasmy.begin(); it != tasmy.end(); it++)
		{
			(*it)->draw(hdc);
		}

		kolo->draw(hdc);
		kwadrat->draw(hdc);
	}

	void update()
	{

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

	Figura::Figura(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	void Figura::draw(HDC hdc)
	{
		srand(time(NULL));
		int t = rand() % 2;
		Graphics graphics(hdc);
		if (t == 0)
		{
			SolidBrush      solidbrush(Color(255, 0, 0, 255));
			graphics.FillEllipse(&solidbrush, 0, 0, 30, 30);
		}
		else
		{
			SolidBrush      solidbrush(Color(155,155,155, 155));
			graphics.FillEllipse(&solidbrush, 0, 0, 60, 60);
		}
		
	}

	void Selektor::add(Figura* fig)
	{
		if (fig->getType() == Figura::SQUARE){
			reverse = true;
		}
	}

	//void Selektor::remove(Figura* fig ) // jezeli nie ma juz zadnch kwadratow to reverse = false;

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
}