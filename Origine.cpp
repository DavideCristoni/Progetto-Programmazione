#include <iostream>
#include <windows.h>
using namespace std;
int main() {
    HWND console = GetConsoleWindow();
    RECT ConsoleRect;
    GetWindowRect(console, &ConsoleRect);

    MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 1000, 400, TRUE);

    system("pause");
}

bool f(start, end) {
    int modulo;
    modulo = ((double)(end - start) / (double)clock_per_sec) * 10000;
    if (modulo % 1000 == 0) return true;
    else return false;
}