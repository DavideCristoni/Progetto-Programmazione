#define _CRT_SECURE_NO_WARNINGS_

#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <stdlib.h>

using namespace std;

struct mappa {
	char map[15];
	int pos = 7;
};

int main() {
	mappa m;
	for (int i = 0; i < 5; i++)
		m.map[i] = ' ';
	m.map[m.pos] = 'A';
	char in;
	in = _getch();
	while (in != 'q') {
		if (in == 'a') {
			m.map[m.pos] = ' ';
			if (m.pos != 0)
				m.pos--;
			m.map[m.pos] = 'A';
		}
		else if (in == 'd') {
			m.map[m.pos] = ' ';
			if (m.pos != 14)
				m.pos++;
			m.map[m.pos] = 'A';
		}
		cout << m.map << endl;
		cout << in << endl;
		in = _getch();
		system("clear");
		
	}
}