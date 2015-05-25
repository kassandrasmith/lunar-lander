# lunar-lander
Embedded systems design game styled after the classic [Lunar Lander](https://en.wikipedia.org/wiki/Lunar_Lander_(1979_video_game)).

# Usage

Create a `Makedef` file and declare `TWROOT` to be the path to Tiva Ware, TI's useful bundle of resources and libraries for working with launchpad. You may also specify a compiler prefix in this file by defining `PREFIX`.

```
ROOT = /Applications/arm/TivaWare
```

Run `make; make upload;` to build and flash the code to a connected board.
