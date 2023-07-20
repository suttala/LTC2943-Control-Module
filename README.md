# ChipControl - A LTC2943 Control Module
![GitHub last commit](https://img.shields.io/github/last-commit/suttala/LTC2943-Control-Module)

### Introduction
The ChipControl API, provides access to some key features of the LTC2943 Battery Gas Gauge.

Overview of the LTC2943 device from its datasheet:
> The LTC2943 is a battery gas gauge designed for use
> with multicell batteries with terminal voltages from 3.6V
> to 20V. It measures battery charge and discharge, battery
> voltage, current and its own temperature.
### Dependencies
* CMake & Make
* GCC

### Build & Run
Run these commands to build and execute the example provided in `main.c`
1. `mkdir build && cd build`
2. `cmake .. && make`
3. `./ChipControl`

### Features
* Retrieve the current ADC mode
* Change the ADC mode
* Check for temperature alerts
* Assign the charge high and low tresholds
* Check if the charge level is within the assigned tresholds

### Tools
* Code editor : Visual Studio Code
* Version control : Git, hosted in GitHub
* OS : Ubuntu 20.04
* Build system : CMake

### Reference material
* [LTC2943 Datasheet](https://www.analog.com/media/en/technical-documentation/data-sheets/2943fa.pdf)
* The Device Driver API provided in `LTC2943.h`

### Example
An example of how the ChipControl API may be used can be found in `main.c`. In this example, first, the ADC mode is fetched and printed (0x00 = SLEEP).
Then, the ADC mode is set to 0xC0 = AUTO. Finally the ADC mode is fetched again to make sure the mode is now changed.

**NOTE:** In order to build & test the API in this example, I created a "dummy" version of the assumed LTC2943 Driver program that can be found from `LTC2943.h` & `LTC2943.c`.
As such, these are only meant for debugging and testing the API.

### Mutex Design
Mutex handling is a noteworthy topic. The implementation is assuming that the provided LTC2948 Driver API handles mutexes, so that the ChipControl-module doesn't need to concern itself with this. Also, if the ChipControl-module is being used in several threads on higher levels, using mutexes there has to be considered as well. Otherwise the LTC2943 Read and Write operations done in different services of the ChipControl-module may become mixed up.