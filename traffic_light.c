#include <stdio.h>
#include <unistd.h>
#include "traffic_light.h"

void initialize_traffic_light(TrafficLight *traffic_light, unsigned int green_dur, unsigned int yellow_dur, unsigned int red_dur) {
    if (red_dur == 0 || green_dur == 0 || yellow_dur == 0) {
        printf("Error: Invalid light durations provided; entering error state");
        traffic_light->current_state = FLASH_RED;
        return;
    }

    traffic_light->current_state = RED;
    traffic_light->green_duration = green_dur;
    traffic_light->yellow_duration = yellow_dur;
    traffic_light->red_duration = red_dur;
}

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
        default:  // Error is detected
            traffic_light->current_state = FLASH_RED;  // Handle error by entering FLASH RED state
            printf(", ON");  // Turn red light on
            fflush(stdout);  // Ensure output is displayed immediately
            sleep(1);  // Remain on for 1 second
            printf("\nTraffic Light State: FLASH RED, OFF");  // Turn red light off
            fflush(stdout);  // Ensure output is displayed immediately
            sleep(1); // Remain off for 1 second
            break;
    }
}

void display_state(TrafficLightState traffic_light_state) {
    const char *states[] = {"GREEN", "YELLOW", "RED", "FLASH_RED"};  // Constant character array to hold possible states
    printf("\nTraffic Light State: %s", states[traffic_light_state]);  // Print state
    fflush(stdout);  // Ensure output is displayed immediately
}

void simiulate_traffic_light(TrafficLight *traffic_light) {
    while (1) {
        display_state(traffic_light->current_state);
        update_light(traffic_light);
    }
}