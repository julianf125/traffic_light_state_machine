#include <stdio.h>
#include "traffic_light.h"

int main()
{
    TrafficLight traffic_light;
    initialize_traffic_light(&traffic_light, GREEN_DURATION, YELLOW_DURATION, RED_DURATION);

    printf("Simulating Traffic Light");
    simiulate_traffic_light(&traffic_light);
    return 0;
}
