#ifndef FS_HELPER_H
#define FS_HELPER_H

#include <iostream>
#include <vector>
#include <cmath>

#include "structs.h"

void get_attribute(const int* attr, std::string* res);

void dt_converter(const unsigned short* time, const unsigned short* date, std::string* res);

void get_file_name(unsigned char* name, unsigned char* ext, std::string* f_name);

bool ends_with(std::string const & value, std::string const & ending);

#endif //FS_HELPER_H
