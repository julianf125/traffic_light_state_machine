#include <assert.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "traffic_light.h" // Include file to be tested

TrafficLight test_light_valid;
TrafficLight test_light_invalid;
unsigned int green_dur = 2;
unsigned int yellow_dur = 1;
unsigned int red_dur_valid = 3;
unsigned int red_dur_invalid = 0;

void assert_and_print(const char *test_name, int condition) {
    printf("   Testing %s: ", test_name);
    assert(condition);
    printf("PASSED\n");
}

void test_initialization() {
    printf("----- Testing initialize_traffic_light() -----\n");

    initialize_traffic_light(&test_light_valid, green_dur, yellow_dur, red_dur_valid);

    assert_and_print("valid state initialization", test_light_valid.current_state == RED);
    assert_and_print("green duration initialization", test_light_valid.green_duration == green_dur);
    assert_and_print("yellow duration initialization", test_light_valid.yellow_duration == yellow_dur);
    assert_and_print("red duration initialization", test_light_valid.red_duration == red_dur_valid);

    initialize_traffic_light(&test_light_invalid, green_dur, yellow_dur, red_dur_invalid); 
    printf("\n");
    assert_and_print("invalid state initialization", test_light_invalid.current_state == FLASH_RED);

    printf("All tests passed\n\n");
}

void test_state_transitions() {
    printf("----- Testing update_light() -----\n");

    update_light(&test_light_valid);
    assert_and_print("RED -> GREEN transition", test_light_valid.current_state == GREEN);

    update_light(&test_light_valid);
    assert_and_print("GREEN -> YELLOW transition", test_light_valid.current_state == YELLOW);

    update_light(&test_light_valid);
    assert_and_print("YELLOW -> RED transition", test_light_valid.current_state == RED);

    printf("All tests passed");
}

void test_display_state() {
     printf("\n\n----- Testing display_state() (confirm output visually) -----\n");

     // Testing GREEN output
     printf("   Testing output in GREEN state:\n");
     printf("      Expected: Traffic Light State: GREEN\n        Actual: ");  // Display expected output
     display_state(GREEN);  // Show actual output

     // Testing YELLOW output
     printf("   Testing output in YELLOW state:\n");
     printf("      Expected: Traffic Light State: YELLOW\n        Actual: ");  // Display expected output
     display_state(YELLOW);  // Show actual output

     // Testing RED output
     printf("   Testing output in RED state:\n");
     printf("      Expected: Traffic Light State: RED\n        Actual: ");  // Display expected output
     display_state(RED);  // Show actual output

     // Testing FLASH_RED output
     printf("   Testing output in FLASH_RED state:\n");
     printf("      Expected: Traffic Light State: FLASH_RED\n        Actual: ");  // Display expected output
     display_state(FLASH_RED);  // Show actual output

     printf("All display tests completed");
}

void* run_flash_red_thread() {
    handle_flash_red(&test_light_invalid);
    return NULL;
}

void test_flashing_red_light() {
    printf("\n\n----- Testing handle_flash_red() (Confirm output visually) -----\n");
    pthread_t thread;
    int flashing_time = 5;  // Flashing red light timeout

    // Start the thread running the flashing red light function
    if (pthread_create(&thread, NULL, run_flash_red_thread, NULL) != 0) {
        printf("Error: Failed to create thread\n");
        return;
    }

    // Wait for the timeout
    sleep(flashing_time);

    // Stop flashing red light
    test_light_invalid.current_state = RED;

    // Wait for the thread to terminate
    if (pthread_join(thread, NULL) != 0) {
        printf("Error: Failed to join thread\n");
    }

    printf("All FLASH_RED tests completed");
}

void test_normal_operation() {
    printf("\n\n----- Testing routine operation (confirm output visually) -----");

    test_light_valid.current_state = RED;

    for (int i = 0; i < 5; i++) {
        display_state(test_light_valid.current_state);
        update_light(&test_light_valid);
    }

    printf("Routine operation test completed\n");
}

int main() {
    printf("===== Begin Testing =====\n\n");

    test_initialization();
    test_state_transitions();
    test_display_state();
    test_flashing_red_light();
    test_normal_operation();
    return 0;
}