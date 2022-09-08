
#include <conio.h>
#include <windows.h>
#include <stdint.h>
#include <time.h> 

#include <string>
#include <iostream>
#include <fstream>
#include <chrono>


#include "MyTools.h"

using namespace std;

namespace MyTools {

    ofstream logOut;

    //=============================================================================================

    void ClrScr()
    {
        system("cls");
    }

    void __fastcall GotoXY(double x, double y)
    {
        const COORD cc = { short(x), short(y) };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cc);
    }

    uint16_t GetMaxX()
    {
        HANDLE hWndConsole;
        if (hWndConsole = GetStdHandle(-12))
        {
            CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
            if (GetConsoleScreenBufferInfo(hWndConsole, &consoleInfo))
            {
                return consoleInfo.srWindow.Right;
                int height = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top + 1;
            }
        }

        return 0;
    }

    uint16_t GetMaxY()
    {
        HANDLE hWndConsole;
        if (hWndConsole = GetStdHandle(-12))
        {
            CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
            if (GetConsoleScreenBufferInfo(hWndConsole, &consoleInfo))
            {
                return consoleInfo.srWindow.Bottom;
            }
        }

        return 0;
    }

    void SetColor(ConsoleColor color)
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, color); // color =  (WORD)((BackgroundColor << 4) | TextColor))
    }

    //=============================================================================================



    //=============================================================================================


} // namespace MyTools