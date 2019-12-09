#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include <iostream>

using namespace std;
 
int main() {
	char in;
	in = _getch();
	while (in != 'q') {
		cout << "hai digitato " << in << endl;
		in = _getch();
	}
}
