//TODO add music
//TODO terrain generator
//TODO draw thrust
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/types.h>
#include "inc/tm4c123gh6pm.h"
#include <inc/hw_memmap.h>
#include "../inc/debugging_utilities.h"
#include "../inc/computations.h"
#include "../inc/buttons.h"
#include "../inc/LCD.h"
#include "../inc/initialization.h"
#include "../inc/main.h"
#include "../inc/images.h"
#include "driverlib/systick.h"
#include "driverlib/fpu.h"
#include "driverlib/interrupt.h"
//unused for now TODO delete them at the end
#include "../inc/sound.h"
//#include "driverlib/sysctl.h"
//#include "driverlib/gpio.h"
//#include "driverlib/timer.h"

#define FRAME_RATE 30
#define SOUND_RATE 1
#define BUTTON_RATE 10
#define GRAVITY 1.5f
//declare global variables
uint16_t score = 0;
uint16_t time = 0;
uint16_t seconds = 0;
uint16_t fuel = 3000;
char multiplier = 0;                //To be used to increase score according to where the lander lands
float yposit = 9;                   //initialize to topmost of landscape-oriented screen
float xposit = 64;                  //initialize to middle of landscape-oriented screen
float oldxposit = 64;               //position where the lander was previously, to clear
float oldyposit = 5;                //position where the lander was previously, to clear
float yvelocity;                    //can be negative if vertical position is increasing
float xvelocity;                    //negative value moves left, positive moves right
float xaccel;                       //acceleration in the x direction
float yaccel;                       //acceleration in the x direction
float thrusterAccel;                //acceleration when the thrusters are enabled
int16_t angle = 4;                  //4 points upwards, 0 leftwards, and 8 rightwards
int endGame = 0;                    //initialize game states
int startGame = 1;
int playGame = 0;
int16_t width;                      //width of lander
int16_t height;                     //height of lander
int storeTerrainY[WIDTH];

int main(void) {
    //Initializations board connections
    IntMasterDisable();         //Interrupts must be disabled here to prevent unwanted triggering
    DAC_Init();                 //Digital to analog converter for sounds.
    ButtonsInit();              //Allows for easier writing to handle button inputs
    PortE_Init();               //Initialize hardware off-board buttons
    PortF_Init();               //Initializes on-board buttons and LEDs for debugging
    screen_init();              //Initializes screen
    //Initialize interrupts
    FPULazyStackingEnable();
    sound_init(SOUND_RATE);               //Initializes interrupt (Timer 2A) used for sounds
    game_loop_init(FRAME_RATE);   //Initializes Systick interrupt to handle game loop
    button_Interrupt_Init(BUTTON_RATE);
    IntMasterEnable();          //end of initializations, enable interrupts
    start_screen();             // set screen to initial state
    // We need to stall here and wait for the interrupts to trigger at regular intervals.
    while(true);
}


void game_loop() {

    if (startGame) {
        startGame = 0;
        playGame = 1;
        endGame = 0;
        start_screen();
        check();
    }
    else if (playGame) {
        playGame = 1;
        startGame = 0;
        endGame = 0;
        update();
        check();
        render();
        tick();

    }
    else if (endGame) {
        playGame = 0;
        endGame = 1;
        startGame = 0;
        draw_terrain_chunk();
        tick();
    }
    if (endGame && buttonPushed()) {
        endGame = 0;
        playGame = 0;
        startGame = 1;
    }
    toggleLED(FRAME_RATE);      //Debugging heartbeat

}

//update location and time
void update(void) {
    float ttime = .07;                  //TODO set to refresh rate

    time++;

    yaccel = sinAngle(angle) * (-thrusterAccel) + GRAVITY;
    xaccel = cosAngle(angle) * thrusterAccel;

    yvelocity += yaccel * ttime;
    xvelocity += xaccel * ttime;

    yposit += yvelocity * ttime;
    xposit += xvelocity * -ttime;


    oldxposit = xposit;
    oldyposit += yposit + yvelocity * ttime;


}
//"check" the things that will kill you
void check(void) {
    //declare boolean
    bool outOfTime = seconds >= 240;
    bool collided = detect_collision();
    bool tooFast = yvelocity >= 2.0;
    bool crashed = collided && ((angle != 4) || tooFast);

    //check yposit
    if (crashed) {
        die(CRASHED);
    }
    if (collided && !crashed) {
        land();
    }
    //check time
    if (outOfTime) {
        die(OUTOFTIME);
    }
    if (xposit >= 128) {
        xposit = 0;
    }
    if (xposit <= 0) {
        xposit = 128;
    }
}

void render(void) {
    int16_t xoffset;                    //offset of lander
    int16_t yoffset;
    int16_t thrustXOffset;                    //offset of lander
    int16_t thrustYOffset;
    int16_t thrustWidth;
    int16_t thrustHeight;
    sprite sprite = *landerSprite[angle];
    thrust thrust = *thrustSprite[angle];
    write(score, fuel, seconds);

    if (time % FRAME_RATE == 0) {
        //write_time(seconds);
        seconds++;
    }

    write_velocities(xvelocity, yvelocity);
    write_angle(angle);

    width = sprite.width;
    height = sprite.height;
    xoffset = sprite.xoffset;
    yoffset = sprite.yoffset;
    const uint16_t *data = sprite.data;

    thrustWidth = thrust.width;
    thrustHeight = thrust.height;
    thrustXOffset = thrust.xoffset;
    thrustYOffset = thrust.yoffset;
    const uint16_t *thrustData = thrust.data;

    //Draw the lander
    draw_bitmap((int16_t) (xposit + xoffset), (int16_t) (yposit + yoffset) , data, width, height);

    draw_bitmap((int16_t) (oldxposit), (int16_t) (oldyposit - (oldyposit - yposit) - height - 2),
                black,
                26, 5);
    if (thrusterAccel == 2.5f) {
        draw_bitmap((int16_t) (xposit + thrustXOffset), (int16_t) (yposit + thrustYOffset), thrustData, thrustWidth,
                    thrustHeight);
    }
    else {
        draw_bitmap((int16_t) (xposit + thrustXOffset), (int16_t) (yposit + thrustYOffset), black,
                    thrustWidth,
                    thrustHeight);
    }


    //  draw_bitmap((int16_t) ((xposit + xoffset) + width), (int16_t) (oldyposit) , blue, 2, 10);
    //   draw_bitmap((int16_t) ((xposit + xoffset) + width), (int16_t) (oldyposit + 6 + height) , blue, 2, 10);
    //   draw_bitmap((int16_t) (xposit - 2 + xoffset), (int16_t) (oldyposit + 6 +  height) , black, 2, 10);
    // draw_bitmap(oldxposit - 5, oldyposit - 9, blue, 13, 5);

}

//Output some sort of death message
void die(DeathType_t deathtype) {
    //fill_background(BLACK);
    endGame = 1;
    playGame = 0;
    draw_string(6, 6, "You died!", (int16_t) WHITE);
    switch (deathtype) {
        case CRASHED:
            draw_string(1, 7, "Lost 20 fuel units.", (int16_t) WHITE);
            fuel -= 20;
            draw_string(3, 8, "Fuel left:", (int16_t) WHITE);
            draw_dec(14, 8, fuel);
            //draw_string(4, 8, "Current score:", (int16_t)WHITE);
            //write_score(score);
            break;
        case OUTOFTIME:
            draw_string(4, 8, "Out of time!", (int16_t) WHITE);
            //draw_string(4, 6, "Final score:", (int16_t)WHITE);
            //write_score(score);
            break;
    }

}

void land(void) {
    // fill_background(BLACK);
    endGame = 1;
    playGame = 0;
    oldxposit = 0;
    draw_string(6, 6, "You landed!", (int16_t) WHITE);
    if (fuel > 0) {
        draw_string(6, 7, "Fuel left:", (int16_t) WHITE);
        draw_dec(6, 8, fuel);
    }

}

void write(uint16_t score, uint16_t fuel, uint16_t seconds) {
    draw_string(0, 0, "s:", (int16_t) WHITE);
    draw_string(0, 1, "f:", (int16_t) WHITE);
    draw_string(0, 2, "t:", (int16_t) WHITE);
    draw_dec(2, 0, score);
    draw_dec(2, 1, fuel);
    //FIXME: The seconds doesn't draw a leading zero for the tens place.
    //This leads to strange behaviour at the start of a new minute
    //FIXME: Doesn't handle over 10 minutes
    uint8_t min = (uint8_t) (seconds / 60);
    draw_dec(2, 2, min);
    draw_string(3, 2, ":", (int16_t) WHITE);
    uint8_t sec = seconds - min * 60;
    if (sec < 10) {
        draw_dec(4, 2, 0);
        draw_dec(5, 2, sec);
    }
    else {
        draw_dec(4, 2, sec);
    }

}

void draw_terrain(void) {

    for (uint16_t i = 0; i < WIDTH; i++) {
        int16_t terrainy = 140;     //TODO Random number generator (+1, +0, -1)
        storeTerrainY[i] = terrainy;
        draw_pixel(i, terrainy, WHITE);
    }
}

bool detect_collision(void) {
    int newterrainy;
    for (int i = (int) xposit; i < xposit + 8; i++) {
        newterrainy = storeTerrainY[i];
        if (newterrainy <= yposit - 1) {
            return true;
        }
    }
    return false;
}

void start_screen(void) {
    xposit = 64;
    yposit = 9;
    oldxposit = 64;
    oldyposit = 5;
    xvelocity = 0;
    yvelocity = 0;
    xaccel = 0;
    yaccel = 0;
    fill_background(BLACK);
    draw_terrain();
}

uint16_t buttonPushed(void) {
    if (GPIOPinRead(GPIO_PORTE_BASE, 1 << 2)) {
        //Then there was a pin0 interrupt
        if (fuel != 0) {
            fuel--;             //using fuel
            thrusterAccel = 2.5f;
        }
        return true;
    }

    else if (GPIOPinRead(GPIO_PORTE_BASE, 1 << 0)) {
        //Then there was a pin1 interrupt
        angle--;
        if (angle <= 0) { angle = 0; }
        return true;
    }

    else if (GPIOPinRead(GPIO_PORTE_BASE, 1 << 1)) {
        //Then there was a pin2 interrupt
        angle++;
        if (angle >= 8) { angle = 8; }
        return true;
    }

    else {
        thrusterAccel = 0.0;
        return false;
    }
}

void draw_terrain_chunk(void) {
    for (int i = (int) xposit; i < xposit + 9; i++) {
        int16_t terrainy = 140; //FIXME reminder that there is another place the terrain generator needs to be
        storeTerrainY[i] = terrainy;
        draw_pixel(i, terrainy, WHITE);
    }
}
