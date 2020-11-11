#ifndef FS_STRUCTS_H
#define FS_STRUCTS_H

#include <iostream>

//! number to do logical AND with file's attributes
//! to define whether it is a sub directory
const int dir_num = 10000;

const int filename_size = 8;
const int ext_size = 3;

#pragma pack(push, 1)

//! struct for each entry in root directory
struct myFat16DirEntry{
    unsigned char filename[filename_size];
    unsigned char ext[ext_size];
    unsigned char attributes;
    unsigned char reserved[10];
    unsigned short time;
    unsigned short date;
    unsigned short first_cluster;
    int size;
};

//! https://codeandlife.com/2012/04/02/simple-fat-and-sd-tutorial-part-1/
//! struct for boot sector
struct Fat16BootSector{
    unsigned char jmp[3];
    unsigned char oem[8];
    unsigned short sector_size;
    unsigned char sectors_per_cluster;
    unsigned short reserved_sectors;
    unsigned char number_of_fats;
    unsigned short root_dir_entries;
    unsigned short total_sectors_short; // if zero, later field is used
    unsigned char media_descriptor;
    unsigned short fat_size_sectors;
    unsigned short sectors_per_track;
    unsigned short number_of_heads;
    unsigned long hidden_sectors;
    unsigned long total_sectors_long;

    unsigned char drive_number;
    unsigned char current_head;
    unsigned char boot_signature;
    unsigned long volume_id;
    char volume_label[11];
    char fs_type[8];
    char boot_code[448];
    unsigned short boot_sector_signature;
};

#pragma pack(pop)


#endif //FS_STRUCTS_H
