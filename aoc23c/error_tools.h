// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

#ifndef ERROR_TOOLS_H
#define ERROR_TOOLS_H

extern const int INVALID_DAY;  // Invalid Advent of Code day number

/**
 * @brief Return a string description of the error code, including custom-defined error codes.
 *
 * @param code the error code, >= 1.
 * @return a string description of the error code.
 */
const char * custom_error_message(int code);

/**
 * @brief Exits the application if the global errno is non-zero.
 *
 * If the global errno is zero, this function does nothing. If the global errno is non-zero, then it prints the given
 * error message followed the error string for the set errno, then exists the application.
 *
 * @param message the error message to print if global errno is non-zero
 */
void exit_if_errno_set(const char * message);

#endif //ERROR_TOOLS_H
