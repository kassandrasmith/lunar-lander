#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <inc/hw_memmap.h>
#include "inc/hw_ints.h"
#include "inc/tm4c123gh6pm.h"
#include "../inc/buttons.h"
#include "../inc/LCD.h"
#include "../inc/initialization.h"
#include "../inc/main.h"
#include "../inc/images.h"
#include "driverlib/systick.h"
#include "driverlib/fpu.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "../inc/debugging_utilities.h"
#include "../inc/computations.h"
#include "../inc/sound.h"

#define FRAME_RATE 30
#define SOUND_RATE 4

//declare global variables
uint16_t score = 0;
uint16_t time = 0;
uint16_t seconds = 0;
uint16_t fuel = 3000;
char multiplier = 0;                //To be used to increase score according to where the lander lands
float ttime = .07;                  //TODO set to refresh rate
float yvelocity;                    //can be negative if vertical position is increasing
float xvelocity;                    //negative value moves left, positive moves right
float yposit = 9;                   //initialize to topmost of landscape-oriented screen
float xposit = 64;                  //initialize to middle of landscape-oriented screen
uint16_t angle = 4;                  //4 points upwards, 0 leftwards, and 8 rightwards
float accel;                        //negative value causes increase in vertical position
int endGame = 0;
int startGame = 1;
int playGame = 0;
float oldxposit;
float oldyposit;
int16_t width;
int16_t height;
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
    sysTick_init(FRAME_RATE);   //Initializes Systick interrupt to handle game loop
    IntMasterEnable();          //end of initializations, enable interrupts

    start_screen();             // set screen to initial state

    // We need to stall here and wait for the interrupts to trigger at regular intervals.
    while(true);
}

bool buttonPressed;
void game_loop() {
    if (startGame) {
        start_screen();
        check();
        startGame = 0;
        playGame = 1;
    }
    else if (playGame) {
        process_input();
        update();
        check();
        render();
        tick();
        toggleLED(FRAME_RATE);      //Debugging heartbeat

    }
    else if (endGame) {
        process_input();
        check();
        tick();
        toggleLED(FRAME_RATE);      //Debugging heartbeat

        if (buttonPressed) {
            endGame = 0;
            playGame = 1;
            start_screen();
        }
    }
    SysTickDisable();

    if (endGame) { IntDisable(INT_TIMER2A); }
    else { IntEnable(INT_TIMER2A); }
}

bool jetButtonPressed;
void process_input(void) {

    jetButtonPressed = GPIOPinRead(GPIO_PORTE_BASE, 1 << 2);
    bool rightButtonPressed = GPIOPinRead(GPIO_PORTE_BASE, 1 << 1);
    bool leftButtonPressed = GPIOPinRead(GPIO_PORTE_BASE, 1 << 0);
    bool noFuel = fuel == 0;
    buttonPressed = jetButtonPressed || rightButtonPressed || leftButtonPressed;

#ifdef ONBOARDBUTTONS
    uint8_t buttonState = ButtonsPoll(0, 0);
    leftButtonPressed = (buttonState & ALL_BUTTONS) == LEFT_BUTTON;
    rightButtonPressed = (buttonState & ALL_BUTTONS) == RIGHT_BUTTON;
#endif

    if (!noFuel & jetButtonPressed) {
        accel = -1.5;    //negative accelaration forces lander opposite gravity
        fuel--;             //using fuel
    }
    if (noFuel | !jetButtonPressed) {
        accel = 1.0;
    }
    if (leftButtonPressed) {
        angle--;
    }
    if (rightButtonPressed) {
        angle++;
    }
    if (angle <= -1) {
        angle = 0;
    }
    if (angle >= 9) {
        angle = 8;
    }
}
//update location and time
float haccel;
void update(void) {
    time++;

    float vaccel = sinAngle(angle) * accel;
    if (jetButtonPressed) {
        haccel = cosAngle(angle) * accel;
    }
    else {
        haccel = 0;
    }

    yvelocity += (vaccel * ttime);
    xvelocity += (haccel * ttime);

    yposit += (yvelocity * ttime);
    xposit += (xvelocity * ttime);
}
//"check" the things that will kill you
void check(void) {
    //declare boolean
    bool outOfTime = seconds >= 240;
    bool collided = detect_collision();
    bool tooFast = yvelocity >= -1;
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
    sprite sprite = *landerSprites[angle];
    write_score(score);
    if (time % FRAME_RATE == 0) {
        write_time(seconds);
        seconds++;
    }
    write_fuel(fuel);
    write_velocities(xvelocity, yvelocity);
    write_angle(angle);
    oldxposit = xposit;
    oldyposit = yposit;
    width = sprite.width;
    height = sprite.height;
    const uint16_t *data = sprite.data;
    //TODO add other landers and other angle cases
    draw_bitmap((int16_t) xposit, (int16_t) yposit, data, width, height);
    refresh();
}

//Output some sort of death message
void die(DeathType_t deathtype) {
    //fill_background(BLACK);
    xvelocity = 0;
    yvelocity = 0;
    draw_string(5, 6, "You died!", (int16_t) WHITE);
    switch (deathtype) {
        case CRASHED:
            draw_string(1, 8, "Lost 20 fuel units.", (int16_t) WHITE);
            fuel -= 20;
            //draw_string(4, 6, "Fuel left:", (int16_t)WHITE);
            //write_fuel(fuel);
            //draw_string(4, 8, "Current score:", (int16_t)WHITE);
            //write_score(score);
            break;
        case OUTOFTIME:
            draw_string(4, 8, "Out of time!", (int16_t) WHITE);
            //draw_string(4, 6, "Final score:", (int16_t)WHITE);
            //write_score(score);
            break;
    }
    endGame = 1;
}

void land(void) {
    // fill_background(BLACK);
    xvelocity = 0;
    yvelocity = 0;
    oldxposit = 0;
    draw_string(6, 6, "You landed!", (int16_t) WHITE);
    if (fuel > 0) {
        draw_string(6, 7, "Fuel remaining:", (int16_t) WHITE);
        write_fuel(fuel);
    }
    endGame = 1;
}

void write_score(uint16_t score) {
    draw_string(0, 0, "s:", (int16_t) WHITE);
    draw_dec(2, 0, score);
}

void write_fuel(uint16_t inFuel) {
    draw_string(0, 1, "f:", (int16_t) WHITE);
    draw_dec(2, 1, inFuel);
}


void write_time(uint16_t seconds) {
    //FIXME: The seconds doesn't draw a leading zero for the tens place.
    //This leads to strange behaviour at the start of a new minute
    draw_string(0, 2, "t:", (int16_t) WHITE);

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
        int16_t terrainy = 140;
        storeTerrainY[i] = terrainy;
        draw_pixel(i, terrainy, WHITE);
    }
}

void refresh(void) {
    draw_bitmap(oldxposit - 5, oldyposit - 8, black, 13, 3);
    draw_bitmap(oldxposit - 2, oldyposit, black, 1, height + 2);
    draw_bitmap(oldxposit + 10, oldyposit, black, 1, height + 2);
}

int newterrainy;
bool detect_collision(void) {
    for (int i = 0; i < WIDTH; i++) {
        newterrainy = storeTerrainY[i];
        if ((xposit >= i - 5) && (xposit <= i + 5) && (yposit >= newterrainy)) {
            return true;
        }
    }
    return false;
}

void start_screen(void) {
    xposit = 64;
    yposit = 9;
    fill_background(BLACK);
    draw_terrain();
}
