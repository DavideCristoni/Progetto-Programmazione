#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <stdlib.h>

int main() {
	FILE* f;
	f=fopen("ciao.txt", "a"); //prevede che il file esista
	fprintf(f, "%d", 10);
	fclose(f);

}
