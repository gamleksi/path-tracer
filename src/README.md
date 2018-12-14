## Getting started

Make sure you have [openCV](https://www.opencv.org) installed in your $PATH
* MacOS ```brew install opencv``` ```brew install libomp``` ```brew install sfml``` ```brew install boost```
* Ubuntu 18.04: Aalto University Paniikki computers have needed software already installed

Project uses Cmake for compiling. ```CMakeLists.txt``` file can be found from the ```/src```. Use it to compile. Project has tests written with gtest. Those can be found from the ```/tests``` folder.


### Run main

1. ```cd /src```
2. ```cmake .```
3. ```make path_tracer```
4. ```./path_tracer```

## Example commands

*create a "cornell box" with lights
```./path_tracer -s 1000 -f cornell.png```

*create a random scene with day light and hundreds of spheres
```./path_tracer -r 1 -o 500 -s 200 -f randomnew.png```

*both will take a while to render due to a high anti-aliasing sample rate

### Run tests

#### TESTS ARE OUTDATED

1. ```cd /src```
2. ```cmake .```
3. Build all ```make```
4. Example: Run vector tests ```./tests/vector_tests/./vector_test ```
