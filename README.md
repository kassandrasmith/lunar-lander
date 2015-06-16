# Lunar Lander
Embedded systems design game styled after the classic [Lunar Lander](https://en.wikipedia.org/wiki/Lunar_Lander_(1979_video_game)).

## Usage

# Hardware I/O connections

Buttons| Pin
-------|-----
jet button | PE0
left button | PE1
right button | PE2

DAC Resistor Value | Pin
-----------------|----------
32*R | PB0
16*R | PB1
8*R | PB2
4*R |
2*R | PB4
1*R | PB
ST7735 Screen | Pin
------|-----------------
Backlight | +3.3 V
MISO | unconnected
SCK  | PA2
MOSI | PA5
TFT_CS | PA3 (SSI0Fss)
CARD_CS | unconnected
Data/Command | PA6
RESET | PA7
VCC | +3.3 V
Gnd | ground

### Software

Create a `Makedefs` file and declare `TWROOT` to be the path to Tiva Ware, TI's useful bundle of resources and libraries for working with launchpad. You may also specify a compiler prefix in this file by defining `PREFIX`.

```
TWROOT = /Applications/arm/TivaWare
```

Lines number 1576-1580 in the provided ST7735.c file are unecessary and will prevent you from building. You should delete them or comment them out.

Run `make; make upload;` to build and flash the code to a connected board.

