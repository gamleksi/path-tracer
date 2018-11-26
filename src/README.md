# Path Tracer

## Getting started

Make sure you have [openCV](https://www.opencv.org) installed in your $PATH
* MacOS ```brew install opencv```
* Ubuntu ```apt-get install opencv```

Project uses cmake for compiling. ```CMakeLists.txt``` file can be found from the root. Use it to compile. Project has tests written with gtest. Those can be found from the ```/tests``` folder.


### Run project

1. ```cd /src```
2. ```cmake .```
3. ```make path_tracer```
4. ```./path_tracer```