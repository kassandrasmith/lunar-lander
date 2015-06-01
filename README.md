# Lunar Lander
Embedded systems design game styled after the classic [Lunar Lander](https://en.wikipedia.org/wiki/Lunar_Lander_(1979_video_game)).

## Usage

### Hardware

Slide pot:
Slide pot pin 1 connected to ground
Slide pot pin 2 connected to PE2/AIN1
Slide pot pin 3 connected to +3.3V
*Buttons:
jet button connected to PE0
left button connected to PE1
right button connected to PE2
*DAC:
32*R resistor DAC bit 0 on PB0
16*R resistor DAC bit 1 on PB1
8*R resistor DAC bit 2 on PB2
4*R resistor DAC bit 3 on PB3
2*R resistor DAC bit 4 on PB4
1*R resistor DAC bit 5 on PB5
*ST7735 Screen connections:
Backlight (pin 10) connected to +3.3 V
MISO (pin 9) unconnected
SCK (pin 8) connected to PA2 (SSI0Clk)
MOSI (pin 7) connected to PA5 (SSI0Tx)
TFT_CS (pin 6) connected to PA3 (SSI0Fss)
CARD_CS (pin 5) unconnected
Data/Command (pin 4) connected to PA6 (GPIO), high for data, low for command
RESET (pin 3) connected to PA7 (GPIO)
VCC (pin 2) connected to +3.3 V
Gnd (pin 1) connected to ground

### Software

Create a `Makedefs` file and declare `TWROOT` to be the path to Tiva Ware, TI's useful bundle of resources and libraries for working with launchpad. You may also specify a compiler prefix in this file by defining `PREFIX`.

```
TWROOT = /Applications/arm/TivaWare
```

Run `make; make upload;` to build and flash the code to a connected board.

# Hardware I/O connections
*Slide pot:
Slide pot pin 1 connected to ground
Slide pot pin 2 connected to PE2/AIN1
Slide pot pin 3 connected to +3.3V
*Buttons:
jet button connected to PE0
left button connected to PE1
right button connected to PE2
*DAC:
32*R resistor DAC bit 0 on PB0
16*R resistor DAC bit 1 on PB1
8*R resistor DAC bit 2 on PB2
4*R resistor DAC bit 3 on PB3
2*R resistor DAC bit 4 on PB4
1*R resistor DAC bit 5 on PB5
*ST7735 Screen connections:
Backlight (pin 10) connected to +3.3 V
MISO (pin 9) unconnected
SCK (pin 8) connected to PA2 (SSI0Clk)
MOSI (pin 7) connected to PA5 (SSI0Tx)
TFT_CS (pin 6) connected to PA3 (SSI0Fss)
CARD_CS (pin 5) unconnected
Data/Command (pin 4) connected to PA6 (GPIO), high for data, low for command
RESET (pin 3) connected to PA7 (GPIO)
VCC (pin 2) connected to +3.3 V
Gnd (pin 1) connected to ground
