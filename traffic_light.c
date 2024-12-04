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
        case RED:
        case YELLOW:
        case GREEN:
    }
}

void display_state(TrafficLight *traffic_light) {
    print("State")
}


void simiulate_traffic_light(TrafficLight *traffic_light) {
    while (1) {
        display_state(traffic_light);
        sleep(5);
    }
}

int main()
{
    TrafficLight traffic_light;
    initialize_traffic_light(&traffic_light, )
    simiulate_traffic_light(&traffic_light);
    return 0;
}