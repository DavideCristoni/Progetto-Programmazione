#include "oggetto.h"
#include "header.h"
#include <cstring>

using namespace std;

	oggetto::oggetto(int type, int x, int y, int offx, int offy, int score, const double battery, const char txtr[10][10], bool disappear)
	{
		this->type = type;
		posx = x;
		globaly = y;
		posy = 0;
		offsetX = offx;
		offsetY = offy;
		this->score = score;
		this->battery = battery;
		enable = true;
		disappearOnContact = disappear;
		for (int i = 0; i < 10; i++)
			strcpy(texture[i], txtr[i]);
	}
	
	void oggetto::move()
	{
		posy++;
		abilita();
	}
	
	void oggetto::stampa()
	{
		int i;
		int j = 0;
			if(!disappearOnContact || enable){
			attron(COLOR_PAIR(type));
				for(i = offsetY - 1; i >= 0; i --)
				{
					while(j < 10  && texture[i][j] != ' ')
					{
						mvprintw(posy - i, posx + j, "%c", texture[i][j]);
						j++;
					}
					j = 0;
				}
		attroff(COLOR_PAIR(type));
		}
	}
	
	bool oggetto::effect(int& score, double& battery, player *p)
	{
		if (enable) {
			score = score - this->score;
			battery = battery + this->battery;
			if (battery > 100)
			{
				battery = 100;
			}
			enable = false;

			if(type == 5)
			{
				int a;
				a = rand() % 4 + 1;
				char d = 'w';
				if(a == 1) d = 'w';
				if(a == 1) d = 's';
				if(a == 1) d = 'd';
				if(a == 1) d = 'a';

				for(int i = 0; i < 7; i++)
				{
					p->move(d, COLS, LINES);
				}
			}
            if(type == 2)
			{
				return true;
			}
		
		}
        return false;
	}
	
	int oggetto::getPosX()
	{
		return posx;
	}

	int oggetto::getGloalY()
	{
		return globaly;
	}

	int oggetto::getType()
	{
		return type;
	}

	int oggetto::getPosY()
	{
		return posy;
	}

	int oggetto::getOffsetx() 
	{ 
		return offsetX; 
	}

	int oggetto::getOffsety() 
	{ 
		return offsetY; 
	}

	void oggetto::reset(){
		posy=0;
		enable=true;
	}


	void oggetto::abilita()
	{
		if(type == 3)
		{
			int molt = (rand() % 3) - 1;
			if(posx <= 2)
			{
				molt = 1;
			}
			else if(posx >= ((COLS - OFFSET_MENU) - 5))
			{
				molt = -1;
			}
			posx = posx + molt;	
		}
	} 