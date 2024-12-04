#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H

#define GREEN_DURATION 6
#define YELLOW_DURATION 3
#define RED_DURATION 6

typedef enum {
    RED,
    GREEN,
    YELLOW
} TrafficLightState;

typedef struct {
    TrafficLightState current_state;
    unsigned int green_duration;
    unsigned int yellow_duration;
    unsigned int red_duration;
} TrafficLight;

void initialize_traffic_light(TrafficLight *traffic_light, unsigned int green_dur, unsigned int yellow_dur, unsigned int red_dur);
void update_light(TrafficLight *traffic_light);
void display_state(TrafficLight *traffic_light);
void simiulate_traffic_light(TrafficLight *traffic_light);

#endif