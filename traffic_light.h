#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H

#define GREEN_DURATION 6
#define YELLOW_DURATION 3
#define RED_DURATION 6

/// @brief 
/// @
typedef enum {
    GREEN,
    YELLOW,
    RED
} TrafficLightState;

/// @brief 
typedef struct {
    TrafficLightState current_state;
    unsigned int green_duration;
    unsigned int yellow_duration;
    unsigned int red_duration;
} TrafficLight;

/// @brief: 
/// @param traffic_light:  
/// @param green_dur: 
/// @param yellow_dur: 
/// @param red_dur: 
void initialize_traffic_light(TrafficLight *traffic_light, unsigned int green_dur, unsigned int yellow_dur, unsigned int red_dur);

/// @brief 
/// @param traffic_light 
void update_light(TrafficLight *traffic_light);

/// @brief 
/// @param traffic_light 
void display_state(TrafficLightState traffic_light_state);

/// @brief
/// @param traffic_light
void simiulate_traffic_light(TrafficLight *traffic_light);

#endif