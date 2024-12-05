#include <stdio.h>
#include <unistd.h>
#include "traffic_light.h"

/*
* Initializes an instance of TrafficLight

* Checks duration inputs for validity
- If invalid, light enters FLASH_RED error state
- If valid, light enters RED (default) state and light durations are set
*/
void initialize_traffic_light(TrafficLight *traffic_light, unsigned int green_dur, unsigned int yellow_dur, unsigned int red_dur) {
    if (red_dur == 0 || green_dur == 0 || yellow_dur == 0) {  // Check for invalid light durations
        printf("Error: Invalid light durations provided; entering FLASH_RED state");  // Display error message
        traffic_light->current_state = FLASH_RED;  // traffic_light enters error state
        return;
    }

    // If durations are valid
    traffic_light->current_state = RED;  // Set light to default state of RED
    traffic_light->green_duration = green_dur;  // Set duration of green light
    traffic_light->yellow_duration = yellow_dur;  // Set duration of yellow light
    traffic_light->red_duration = red_dur;  // Set duration of red light
}

/*
* Updates the traffic light to the next state:
- GREEN -> YELLOW
- YELLOW -> RED
- RED -> GREEN
* Remains in state for specified duration for each color

* If the light is flashing red, it toggles the red light on and off in 1-second intervals 
* No transitions occur if the light is in the FLASH_RED state
*/
void update_light(TrafficLight *traffic_light) {
    switch (traffic_light->current_state) {
        case GREEN:  // If light is green
            sleep(traffic_light->green_duration);  // Leave on for duration of green light
            traffic_light->current_state = YELLOW;  // Then turn light to yellow
            break;
        case YELLOW:  // If light is yellow
            sleep(traffic_light->yellow_duration);  // Leave on for duration of yellow light
            traffic_light->current_state = RED;  // Then turn light to red
            break;
        case RED:  // If light is red
            sleep(traffic_light->red_duration);  // Leave on for duration of red light
            traffic_light->current_state = GREEN;  // Then turn light green
            break;
        default:  // Error is detected, light is in FLASH_RED state
            handle_flash_red(traffic_light);  // Flash red light in accordance with FLASH_RED state
            break;
    }
}

void handle_flash_red(TrafficLight *traffic_light) {
    while (traffic_light->current_state == FLASH_RED) {  // Flash red while in FLASH_RED state
        printf("FLASH_RED: Light ON\n");  // Turn red light on
        fflush(stdout);  // Ensure output is displayed immediately
        sleep(1);  // Remain on for 1 second
        printf("FLASH_RED: Light OFF\n");  // Turn red light off
        fflush(stdout);  // Ensure output is displayed immediately
        sleep(1);  // Remain off for 1 second
    }
}

/*
* Displays current state of traffic light
*/
void display_state(TrafficLightState traffic_light_state) {
    const char *states[] = {"GREEN", "YELLOW", "RED", "FLASH_RED"};  // Constant character array to hold possible states
    printf("Traffic Light State: %s\n", states[traffic_light_state]);  // Print state
    fflush(stdout);  // Ensure output is displayed immediately
}

/*
* Runs traffic light simulation
* Displays state after each state update
*/
void simulate_traffic_light(TrafficLight *traffic_light) {
    while (1) {  // Run indefinitely
        display_state(traffic_light->current_state);  // Display current state of traffic light
        update_light(traffic_light);  // Update the state of the traffic light
    }
}