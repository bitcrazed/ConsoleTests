// ConsoleTests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    DWORD dwOriginalMode, dwMode;

    cout << "Getting Current Console Mode ... ";
    if (GetConsoleMode(hConsole, &dwOriginalMode))
    {
        cout << "Success: Original Console Mode is 0x" << hex << dwOriginalMode << endl;

        cout << "Enabling VT Processing Mode ... ";
        dwMode = dwOriginalMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        if (SetConsoleMode(hConsole, dwMode))
        {
            cout << "\x1b[93m"; // Bright yellow
            cout << "Success: Enabled VT Processing mode";
            cout << "\x1b[0m" << endl;

            cout << "Double-checking console mode ... ";
            if (GetConsoleMode(hConsole, &dwMode))
            {
                if (dwMode && ENABLE_VIRTUAL_TERMINAL_PROCESSING)
                {
                    cout << "\x1b[92m"; // Bright green
                    cout << "Success: Updated Console Mode to 0x" << hex << dwMode;
                    cout << "\x1b[0m" << endl;
                }
                else
                {
                    cout << "Fail: VT Processing requested, but not granted";
                }
            }
        }
        else
        {
            cout << "Fail: Could not enable VT Processing Mode 0x" << ENABLE_VIRTUAL_TERMINAL_PROCESSING << endl;
        }

        // Reset console mode before we exit.
        cout << "Resetting Console Mode to 0x" << hex << dwOriginalMode << endl;
        SetConsoleMode(hConsole, dwOriginalMode);
    }
    else
    {
        cout << "Error: Couldn't get Console mode!" << endl;
    }

    cout << endl;

    return 0;
}

