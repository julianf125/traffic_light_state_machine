#include <stdio.h>
#include <unistd.h>
#include "traffic_light.h"

void initialize_traffic_light(TrafficLight *traffic_light, unsigned int green_dur, unsigned int yellow_dur, unsigned int red_dur) {
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
    }
}

void display_state(TrafficLightState traffic_light_state) {
    const char *states[] = {"GREEN", "YELLOW", "RED"};
    printf("Traffic Light Color: %s\n", states[traffic_light_state]);
}

void simiulate_traffic_light(TrafficLight *traffic_light) {
    while (1) {
        display_state(traffic_light->current_state);
        update_light(traffic_light);
    }
}