#include "oggetto.h"
#include <iostream>

using namespace std;

	oggetto::oggetto(int type, int x, int y, int offx, int offy, int score, const int battery, const char txtr[10][10], bool disappear)
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
	}
	void oggetto::stampa()
	{
		cout << "posx: " << posx << ", globaly: " << globaly << ", score: " << score << ", battery: " << battery << " texture:" << endl;
		for (int i = 0; i < offsetY; i++) {
			for (int j = 0; j < offsetX; j++)
				cout << texture[i][j];
			cout << endl;
		}
		/*
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
		}*/
	}
	void oggetto::effect(int& score, int& battery)
	{
		if (enable) {
			score = score - this->score;
			battery = battery + this->battery;
			enable = false;
		}
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
