#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <inc/hw_memmap.h>
#include <sys/types.h>
#include "../inc/buttons.h"
#include "../inc/LCD.h"
#include "../inc/initialization.h"
#include "../inc/main.h"
#include "../inc/images.h"
#include "driverlib/systick.h"
#include "driverlib/fpu.h"
#include "driverlib/interrupt.h"
#include "../inc/debugging_utilities.h"
#include "../inc/computations.h"
#include "inc/tm4c123gh6pm.h"
//unused for now TODO delete them at the end
#include "../inc/sound.h"
//#include "driverlib/sysctl.h"
//#include "driverlib/gpio.h"
//#include "driverlib/timer.h"

#define FRAME_RATE 30
#define SOUND_RATE 1
#define GRAVITY 1.5f
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
int16_t angle = 4;                  //4 points upwards, 0 leftwards, and 8 rightwards
float accel;                        //negative value causes increase in vertical position

float xaccel;
float yaccel;
float thrusterAccel;

int endGame = 0;
int startGame = 1;
int playGame = 0;
float oldxposit;
float oldyposit;
int16_t width;
int16_t height;
int16_t xoffset;
int16_t yoffset;
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
    IntMasterEnable();          //end of initializations, enable interrupts

    start_screen();             // set screen to initial state

    // We need to stall here and wait for the interrupts to trigger at regular intervals.
    while(true);
}

bool buttonPressed;
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
        process_input();
        update();
        check();
        render();
        tick();

    }
    else if (endGame) {
        playGame = 0;
        endGame = 1;
        startGame = 0;
        process_input();
        tick();
        // ttime = 0;

    }
    if (endGame && buttonPressed) {
        endGame = 0;
        playGame = 0;
        startGame = 1;
    }

    toggleLED(FRAME_RATE);      //Debugging heartbeat

}

bool jetButtonPressed;
void process_input(void) {

    jetButtonPressed = GPIOPinRead(GPIO_PORTE_BASE, 1 << 2);
    bool rightButtonPressed = GPIOPinRead(GPIO_PORTE_BASE, 1 << 1);
    bool leftButtonPressed = GPIOPinRead(GPIO_PORTE_BASE, 1 << 0);
    bool noFuel = fuel == 0;
    buttonPressed = jetButtonPressed || rightButtonPressed || leftButtonPressed;

    #define ONBOARDBUTTONS
#ifdef ONBOARDBUTTONS
    uint8_t buttonState = ButtonsPoll(0, 0);
    leftButtonPressed = (buttonState & ALL_BUTTONS) == LEFT_BUTTON;
    rightButtonPressed = (buttonState & ALL_BUTTONS) == RIGHT_BUTTON;
#endif

    if (!noFuel && jetButtonPressed) {
        fuel--;             //using fuel
        thrusterAccel = 2.5f;
    } else {
        thrusterAccel = 0.0;
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
    if (angle <= 0) {
        angle = 0;
    }
    if (angle >= 8) {
        angle = 8;
    }
}
//update location and time

void update(void) {
    time++;

    yaccel = sinAngle(angle) * (-thrusterAccel) + GRAVITY;
    xaccel = cosAngle(angle) * thrusterAccel;

    yvelocity += yaccel * ttime;
    xvelocity += xaccel * ttime;


    yposit += yvelocity * ttime;
    xposit += xvelocity * ttime;

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
    sprite sprite = *landerSprite[angle];
    write(score, fuel, seconds);

    if (time % FRAME_RATE == 0) {
        //write_time(seconds);
        seconds++;
    }

    write_velocities(xvelocity, yvelocity);
    write_angle(angle);
    oldxposit = xposit;
    oldyposit = yposit;
    width = sprite.width;
    height = sprite.height;
    xoffset = sprite.xoffset;
    yoffset = sprite.yoffset;
    const uint16_t *data = sprite.data;

    //Draw the legs of the lander
    draw_bitmap((int16_t) (xposit + xoffset), (int16_t) (yposit + yoffset) , data, width, height);



    //  draw_bitmap((int16_t) ((xposit + xoffset) + width), (int16_t) (oldyposit) , black, 2, 10);
    //   draw_bitmap((int16_t) ((xposit + xoffset) + width), (int16_t) (oldyposit + 6 + height) , black, 2, 10);
    //   draw_bitmap((int16_t) (xposit - 2 + xoffset), (int16_t) (oldyposit + 6 +  height) , black, 2, 10);
    draw_bitmap(oldxposit - 5, oldyposit - 9, black, 13, 5);
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
        if (yposit + height >= newterrainy) {
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

void buttonPushed(void) {
    if (GPIOIntStatus(GPIO_PORTF_BASE, false) & GPIO_PIN_4) {
        // PF4 was interrupt cause
        printf("Button Down\n");
        GPIOIntRegister(GPIO_PORTF_BASE,
                        buttonReleased);   // Register our handler function for port F
        GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_4,
                       GPIO_RISING_EDGE);          // Configure PF4 for rising edge trigger
        GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_4);  // Clear interrupt flag
    }
}

void buttonReleased(void) {
    if (GPIOIntStatus(GPIO_PORTF_BASE, false) & GPIO_PIN_4) {
        // PF4 was interrupt cause
        printf("Button Up\n");
        GPIOIntRegister(GPIO_PORTF_BASE, buttonPushed); // Register our handler function for port F
        GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_4,
                       GPIO_FALLING_EDGE);         // Configure PF4 for falling edge trigger
        GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_4);  // Clear interrupt flag
    }

}