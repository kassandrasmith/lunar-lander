# lunar-lander
Embedded Systems design game styled after the classic Lunar Lander game.

# Usage

Create a `Makedef` file and declare `ROOT` to be the path to Tiva Ware, TI's useful bundle of resources and libraries for working with launchpad. You may also specify a compiler prefix in this file by defining `PREFIX`.

```
ROOT = /Applications/arm/TivaWare
```

Run `make; make upload;` to build and flash the code to a connected board.
