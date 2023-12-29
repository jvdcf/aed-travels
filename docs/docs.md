As part of the second project of the Algorithms and Data Structures course, was proposed a system that provides
effective assistance to users who wish to explore and plan travels. 

This project was carried out by students from group 23: 
 - Duarte Souto Assunção (up202208319@up.pt) 
 - Guilherme Duarte Silva Matos (up202208755@up.pt)
 - João Vítor da Costa Ferreira (up202208393@up.pt)

---

# Getting Started

The project was developed in C++ and uses the CMake tool to compile the source code and this documentation.

### Using the shell script
1. Make sure that the dependencies are installed:
    - **rlwrap**
    - CMake
    - Make
    - g++
    - ...
2. Execute the script `run.sh` (located in the directory of the project) in the terminal.

> **Note:** The script assumes that the csv files are in the folder `dataset/` and their names were not changed.  
> Feel free to change the script to suit your needs.

### Using the terminal

```
cmake -DCMAKE_BUILD_TYPE=Release CMakeLists.txt
make -j$(nproc)
./fins -ap airports.csv -al airlines.csv -f flights.csv
```

> **Warning:** Don't forget to **change the location of the csv files in the terminal commands**.  
> The commands above assume that the csv files are in the same directory as the executable.

> **Note:** Each flag indicates a file that must be passed as an argument to the program.
> - `-ap`: Airports csv file
> - `-al`: Airlines csv file
> - `-f`: Flights csv file

### Using CLion

1. Open the project folder in CLion.
2. Create a CMake profile with the build type set to `Release`.
3. Select the configuration `fins` already created.  
   _or_  
   Create a new configuration with the correct program arguments and working directory.  
   For example:
    - Program arguments: `-ap airports.csv -al airlines.csv -f flights.csv`
    - Working directory: `$ProjectFileDir$`
4. Run the configuration.

---

# Notes

- Some commands might take a while to execute in the build type `Debug`. Confirm that the build type is set to `Release`
  before running the program.
- The terminal embedded in CLion can behave a bit differently than the system's terminal.
  If possible, use the system's terminal to run the program.
- This program is tested for Linux only. As such, it only takes Linux-compatible CSV files on Linux. It might work on
  Windows, but that is untested.
