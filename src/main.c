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
#include "../inc/random.h"
#include "driverlib/systick.h"
#include "driverlib/fpu.h"
#include "driverlib/interrupt.h"
#include "../inc/game_state.h"


#define FRAME_RATE 30
#define SOUND_RATE 1
#define BUTTON_RATE 10
#define GRAVITY 1.5f


//declare global variables
GameState state = {.fuel = 3000,
                      .score = 0,
                      .time = 0,
                      .xaccel = 0,
                      .yaccel = 0,
                      .yposit = 9,           //initialize to topmost of landscape-oriented screen
                      .xposit = 64,                  //initialize to middle of landscape-oriented screen
                      .xvelocity = 0,
                      .yvelocity = 0,
                      .heading = SOUTH};
uint16_t seconds = 0;

char multiplier = 0;                //To be used to increase score according to where the lander lands

float oldxposit = 64;               //position where the lander was previously, to clear
float oldyposit = 5;                //position where the lander was previously, to clear

float thrusterAccel;                //acceleration when the thrusters are enabled

int endGame = 0;                    //initialize game states
int startGame = 1;
int playGame = 0;
int16_t width;                      //width of lander
int16_t height;                     //height of lander
uint16_t terrain[WIDTH];

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

    generate_terrain((uint16_t *)&terrain, (uint16_t)WIDTH);
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

    state.time++;

    state.yaccel = sinAngle(state.heading) * (-thrusterAccel) + GRAVITY;
    state.xaccel = cosAngle(state.heading) * thrusterAccel;

    state.yvelocity += state.yaccel * ttime;
    state.xvelocity += state.xaccel * ttime;

    state.yposit += state.yvelocity * ttime;
    state.xposit += state.xvelocity * -ttime;


    oldxposit = state.xposit;
    oldyposit += state.yposit + state.yvelocity * ttime;


}
//"check" the things that will kill you
void check(void) {
    //declare boolean
    bool outOfTime = seconds >= 240;
    bool collided = detect_collision();
    bool tooFast = state.yvelocity >= 2.0;
    bool crashed = collided && ((state.heading != SOUTH) || tooFast);

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
    if (state.xposit >= 128) {
        state.xposit = 0;
    }
    if (state.xposit <= 0) {
        state.xposit = 128;
    }
}

void render(void) {
    int16_t xoffset;                    //offset of lander
    int16_t yoffset;
    int16_t thrustXOffset;                    //offset of lander
    int16_t thrustYOffset;
    int16_t thrustWidth;
    int16_t thrustHeight;
    sprite sprite = *landerSprite[state.heading];
    thrust thrust = *thrustSprite[state.heading];
    write(state.score, state.fuel, seconds);

    if (state.time % FRAME_RATE == 0) {
        //write_time(seconds);
        seconds++;
    }

    write_velocities(state.xvelocity, state.yvelocity);
    write_angle(state.heading);

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
    draw_bitmap((int16_t) (state.xposit + xoffset), (int16_t) (state.yposit + yoffset) , data, width, height);

    draw_bitmap((int16_t) (oldxposit), (int16_t) (oldyposit - (oldyposit - state.yposit) - height - 2),
                black,
                26, 5);
    if (thrusterAccel == 2.5f) {
        draw_bitmap((int16_t) (state.xposit + thrustXOffset), (int16_t) (state.yposit + thrustYOffset), thrustData, thrustWidth,
                    thrustHeight);
    }
    else {
        draw_bitmap((int16_t) (state.xposit + thrustXOffset), (int16_t) (state.yposit + thrustYOffset), black,
                    thrustWidth,
                    (int16_t) (thrustHeight - 2));
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
            state.fuel -= 20;
            draw_string(3, 8, "Fuel left:", (int16_t) WHITE);
            draw_dec(14, 8, state.fuel);
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
    if (state.fuel > 0) {
        draw_string(6, 7, "Fuel left:", (int16_t) WHITE);
        draw_dec(6, 8, state.fuel);
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
        draw_pixel(i, terrain[i], WHITE);
    }
}

bool detect_collision(void) {
    int newterrainy;
    for (int i = (int) state.xposit; i < state.xposit + 8; i++) {
        newterrainy = terrain[i];
        if (newterrainy <= state.yposit - 1) {
            return true;
        }
    }
    return false;
}

void start_screen(void) {
    state.xposit = 64;
    state.yposit = 9;
    oldxposit = 64;
    oldyposit = 5;
    state.xvelocity = 0;
    state.yvelocity = 0;
    state.xaccel = 0;
    state.yaccel = 0;
    fill_background(BLACK);
    draw_terrain();
}

uint16_t buttonPushed(void) {
    if (GPIOPinRead(GPIO_PORTE_BASE, 1 << 2)) {
        //Then there was a pin0 interrupt
        if (state.fuel != 0) {
            state.fuel--;             //using fuel
            thrusterAccel = 2.5f;
        }
        return true;
    }

    else if (GPIOPinRead(GPIO_PORTE_BASE, 1 << 0)) {
        //Then there was a pin1 interrupt
        state.heading--;
        if (state.heading <= WEST) { state.heading = WEST; }
        return true;
    }

    else if (GPIOPinRead(GPIO_PORTE_BASE, 1 << 1)) {
        //Then there was a pin2 interrupt
        state.heading++;
        if (state.heading >= EAST) { state.heading = EAST; }
        return true;
    }

    else {
        thrusterAccel = 0.0;
        return false;
    }
}

void draw_terrain_chunk(void) {
    for (uint16_t i = state.xposit; i < state.xposit + 9; i++) {
        draw_pixel(i, terrain[i], WHITE);
    }
}

void generate_terrain(uint16_t *container, uint16_t size){
    // The number of terrain features
    uint8_t features = rand() % 6 + 4;
    int feature_type[10];
    for (int i = 0; i < features; i++){
        feature_type[i] = (rand() % 5) - 3;
        //Verify that there's at least one flat area
    }

    int terrain_cursor = 0;
    uint16_t terrain_level = 120;
    for (int i = 0; i < features; i++) {
        const int incline = feature_type[i];
        const uint16_t length = rand() % 30 + 15;
        // Ensure that the minimum length is enough space for the lander to land
        for (int j = 0; j < length; j++) {
            if (terrain_cursor > size){
                goto done;
            }
            terrain_level += incline;
            container[terrain_cursor] = terrain_level;
            terrain_cursor++;
        }
    }
    done:
    return;

}