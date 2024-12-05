#include <stdio.h>
#include "traffic_light.h"

int main()
{
    // Initialize instance of TrafficLight
    TrafficLight traffic_light;
    initialize_traffic_light(&traffic_light, GREEN_DURATION, YELLOW_DURATION, RED_DURATION);

    // Begin traffic light simulation
    printf("Simulating Traffic Light\n");
    simulate_traffic_light(&traffic_light);
    return 0;
}
