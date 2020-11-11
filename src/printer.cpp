#include "../header/printer.h"

//! function that prints characteristics about image
void printer_img_char(const std::string* img_name, const Fat16BootSector* bs){
    std::vector<std::string> img_char = {"IMG NAME",
                                         "SECTOR SIZE",
                                         "NUM SECTORS",
                                         "NUM FAT",
                                         "SIZE FAT (sectors)",
                                         "SIZE FAT   (bytes)",
                                         "ROOT DIR  (number)",
                                         "ROOT DIR   (bytes)",
                                         "RESERVED SECT",
                                         "SIGNATURE"
    };
    std::vector<std::string> char_in_str = {*img_name,
                                            std::to_string(bs->sector_size),
                                            std::to_string(static_cast<unsigned>(bs->sectors_per_cluster)),
                                            std::to_string(static_cast<unsigned>(bs->number_of_fats)),
                                            std::to_string(bs->fat_size_sectors),
                                            std::to_string(bs->fat_size_sectors * bs->sector_size),
                                            std::to_string(bs->root_dir_entries),
                                            std::to_string(bs->root_dir_entries * bs->sector_size),
                                            std::to_string(bs->reserved_sectors),
                                            std::to_string(bs->boot_sector_signature)
    };

    for (auto i = 0; i < img_char.size(); i++){
        std::cout << boost::format("%20i: %20i") % img_char[i] % char_in_str[i] << std::endl;
    }
    std::cout << std::endl;
}

//! function that prints meta-information about each file entry in root dir
void printer_meta_info(const Fat16BootSector* bs, std::fstream* in){
    //printing head of table (of root dir entries)
    std::string boost_form = "%15i %10i %10i %22i %10i %40i\n";
    std::cout << boost::format(boost_form) % "NAME" % "SIZE" % "ISDIR" % "DATE&TIME"
                 % "CLUSTER" % "ATTRIBUTES" << std::endl;

    //iterating over dir entries, printing them
    int iter = static_cast<int>(bs->root_dir_entries);
    for (auto i = 0; i < iter; i++){
        myFat16DirEntry fe{};
        in->read((char *)&fe, sizeof(myFat16DirEntry));
        std::string f_name;

        //format filename and extension
        get_file_name(fe.filename, fe.ext, &f_name);

        if (f_name.empty()){
            continue;
        }

        std::string attrs;
        int attr_copy = fe.attributes;
        get_attribute(&attr_copy, &attrs);
        attrs = attrs.substr(0, attrs.size() - 1);
        std::string is_subdir = ((attr_copy & dir_num) != 0) ? "SUBDIR" : "-";

        // formatting date and time
        std::string date_time;
        dt_converter(&fe.time, &fe.date, &date_time);

        // printing each file entry
        std::cout << boost::format(boost_form) % f_name % fe.size % is_subdir % date_time % fe.first_cluster % attrs;
    }
}
