# lunar-lander
Embedded Systems design game styled after the classic Lunar Lander game.

# Usage

Create a `Makedef` file and declare `ROOT` to be the path to Tiva Ware, TI's useful bundle of resources and libraries for working with launchpad.

```
ROOT = /Applications/arm/TivaWare
```

Run `make; make upload; make clean` to build and flash the code to a connected board.
