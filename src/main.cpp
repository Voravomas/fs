#include <iostream>
#include <boost/program_options.hpp>
#include <fstream>

#include "../header/structs.h"
#include "../header/helper.h"
#include "../header/printer.h"


namespace po = boost::program_options;

int main(int ac, char *av[]) {
    std::string img_path;
    std::vector<std::string> str_files;
    std::string desc_str = std::string("Description:\n\tThis program allows to read FAT-16 image info");
    //configuring positional arguments
    try{
        po::options_description desc(desc_str);
        desc.add_options()
                ("help,h", "Produce help message")
                ("input-file", po::value< std::vector<std::string> >(), "Enter path to image")
                ;

        po::positional_options_description p;
        p.add("input-file", -1);

        po::variables_map vm;
        po::store(po::command_line_parser(ac, av).
                options(desc).positional(p).run(), vm);
        po::notify(vm);

        if (vm.count("help")) {
            std::cout << desc << "\n";
            return 0;
        }

        if (vm.count("input-file")){
            str_files = vm["input-file"].as<std::vector<std::string> >();
        }
    }
    catch (std::exception& e) {
        std::string tempStr = std::string("Error: ") + e.what();
        perror(tempStr.c_str());
        return 1;
    }

    // error handling for user's argv
    if (str_files.empty()){
        std::cerr << "Error: No Image path included!" << std::endl;
        exit(1);
    } else if (str_files.size() == 1){
        img_path = str_files[0];
        if (!ends_with(img_path, ".img")){
            std::cerr <<"Error: Path should ends with '.img'" << std::endl;
            exit(1);
        }
    } else if (str_files.size() > 1){
        std::cerr <<"Error: Only one argument is allowed!" << std::endl;
        exit(1);
    }

    //read image and fill structure
    Fat16BootSector bs{};
    std::fstream in;
    in.open(img_path, std::fstream::in | std::fstream::binary);
    if (in.fail()){
        std::cerr << "Error: Unable to open file" << std::endl;
        exit(1);
    }

    in.read((char*)&bs, sizeof(Fat16BootSector));
    if (!in.is_open()){
        std::cerr << "Error: Unable to read file" << std::endl;
        in.close();
        exit(1);
    }


    //calculating name of image
    int temp_idx = (img_path.rfind('/') != -1) ? static_cast<int>(img_path.rfind('/') + 1) : 0;
    std::string img_name = img_path.substr(temp_idx, img_path.size());

    //print main info
    printer_img_char(&img_name, &bs);


    //calculating offset, number of dir entries and doing offset
    int offset = (bs.reserved_sectors + bs.fat_size_sectors * static_cast<unsigned short>(bs.number_of_fats))
            * bs.sector_size;
    in.seekg(offset);

    //printing meta info
    printer_meta_info(&bs, &in);

    in.close();
    if (in.fail()){
        std::cerr << "Error: Unable to close file" << std::endl;
        exit(1);
    }
    return 0;
}
