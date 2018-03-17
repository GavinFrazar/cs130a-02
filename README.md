# Author: Gavin Frazar

# How to build and run
* Place the `hotels-small` [dataset](https://d1b10bmlvqabco.cloudfront.net/attach/jci7j807fm83p0/jci7jv21n1g43x/jdg6r506m433/hotelssmall.tar.gz)in the build/ directory. From terminal cd into build/ and type:
* `cd build`
* `make`
* `./main`

Part 2 of the project can be found in `Part02-Complexity.md`

If for whatever reason the Makefile provided does not work and you have CMake installed, you can generate a working Makefile by:
* `cd build`
* `cmake ../`
* `make`
* `./main`
