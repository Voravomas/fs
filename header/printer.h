#ifndef FS_PRINTER_H
#define FS_PRINTER_H

#include <iostream>
#include <vector>
#include <fstream>
#include <boost/format.hpp>

#include "structs.h"
#include "helper.h"

void printer_img_char(const std::string* img_name, const Fat16BootSector* bs);

void printer_meta_info(const Fat16BootSector* bs, std::fstream* in);

#endif //FS_PRINTER_H
