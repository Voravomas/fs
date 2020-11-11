# Lab 7 FAT-16

## Team

 - [Samovarov Mykyta](https://github.com/voravomas)

## Prerequisites

 - **C++ compiler** - needs to support **C++17** standard
 - **CMake** 3.15+
 
Dependencies (such as development libraries) can be found in the [dependencies folder](./dependencies) in the form of the text files with package names for different package managers.

## Installing

1. Clone the project.
    ```bash
    git clone git@github.com:voravomas/fs.git
    ```
2. Install required packages.

   On Ubuntu:
   ```bash
   [[ -r dependencies/apt.txt ]] && sed 's/#.*//' dependencies/apt.txt | xargs sudo apt-get install -y
   ```
   On MacOS:
   ```bash
   [[ -r dependencies/homebrew.txt ]] && sed 's/#.*//' dependencies/homebrew.txt | xargs brew install
   ```
   Use Conan on Windows.
3. Build.
    ```bash
    cmake -Bbuild
    cmake --build build
    ```

## Usage

```bash
fs fat16.img
fs ../../a.img
```

This program reads FAT-16 image.
It reads characteristics of filesystem,
and each entry file in root directory.

Note: Please try it in wide opened terminal
for better visual look.
 
Lab is made without any additional tasks.

Help flags `-h`/`--help` support is available.
