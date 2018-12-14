
## Getting started

Make sure you have [openCV](https://www.opencv.org) installed in your $PATH
* MacOS ```brew install opencv``` ```brew install libomp``` ```brew install sfml``` ```brew install boost```
* Ubuntu 18.04: ```sudo apt update && sudo apt install python3-opencv```

Project uses Cmake for compiling. ```CMakeLists.txt``` file can be found from the ```/src```. Use it to compile. Project has tests written with gtest. Those can be found from the ```/tests``` folder.


### Run main

1. ```cd /src```
2. ```cmake .```
3. ```make path_tracer```
4. ```./path_tracer```


### Run tests

1. ```cd /src```
2. ```cmake .```
3. Build all ```make```
4. Run tests ```./tests/vector_tests/./vector_test ```
