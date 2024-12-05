#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H

// Default durations of green, yellow, and red lights
#define GREEN_DURATION 6
#define YELLOW_DURATION 2
#define RED_DURATION 6

/// Enum that represents the potential states of the traffic light
typedef enum {
    GREEN,  // Light is green
    YELLOW,  // Light is yellow
    RED,  // Light is red
    FLASH_RED  // Ligth is flashing red (error state)
} TrafficLightState;

/// Struct that represents the traffic light
typedef struct {
    TrafficLightState current_state;  // Current state of the light
    unsigned int green_duration;  // Time green light remains on (seconds)
    unsigned int yellow_duration;  // Time yellow light remains on (seconds)
    unsigned int red_duration;  // Time red light stays on (seconds)
} TrafficLight;

/// @brief: Initializes the traffic light
/// @param traffic_light: Pointer to instance of TrafficLight 
/// @param green_dur: Duration of the green light in seconds
/// @param yellow_dur: Duration of the yellow light in seconds
/// @param red_dur: Duration of the red light in seconds
void initialize_traffic_light(TrafficLight *traffic_light, unsigned int green_dur, unsigned int yellow_dur, unsigned int red_dur);

/// @brief: Updates the traffic light to the next state 
/// @param traffic_light: Pointer to instance of traffic light 
void update_light(TrafficLight *traffic_light);

/// @brief: Flashes the red light 5 times; represents error state
/// @param traffic_light: Pointer to instance of traffic light
void handle_flash_red(TrafficLight *traffic_light);

/// @brief: Prints the current state of the traffic light
/// @param traffic_light: Pointer to instance of TrafficLight
void display_state(TrafficLightState traffic_light_state);

/// @brief: Simulates operation of the traffic light
/// @param traffic_light: Pointer to instance of TrafficLight
void simulate_traffic_light(TrafficLight *traffic_light);

#endif