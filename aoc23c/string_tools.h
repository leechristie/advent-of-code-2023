//
// Created by Lee A. Christie on 03/08/2024.
//

#ifndef STRING_TOOLS_H
#define STRING_TOOLS_H

#include <stdio.h>

/**
 * @brief Reads a single line from the given file as a C string.
 *
 * @param file the text file to read
 * @return the read string, or NULL if EOF or an error allocating memory
 * @exception ENOMEM if unable to allocate memory
 */
char * read_line(FILE * file);

#endif //STRING_TOOLS_H
