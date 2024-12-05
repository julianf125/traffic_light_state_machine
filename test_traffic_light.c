#include <assert.h> // For assert function
#include <stdio.h>
#include <pthread.h> // For threads
#include <unistd.h> // For sleep function
#include "traffic_light.h" // File to be tested

// Valid and invalid TrafficLight instances to test on
TrafficLight test_light_valid;
TrafficLight test_light_invalid;

// Valid state durations for GREEN, YELLOW, and RED
unsigned int green_dur = 2;
unsigned int yellow_dur = 1;
unsigned int red_dur_valid = 3;

// Invalid RED state duration
unsigned int red_dur_invalid = 0;

// Helper function to perform a test using assert() and handle output to console
void assert_and_print(const char *test_name, int condition) {
    printf("   Testing %s: ", test_name);
    assert(condition);
    printf("PASSED\n");
}

/*
* This function tests the initialize_traffic_light() function
*
* Initializes test_light_valid using the provided valid state durations
* Then tests whether the current state and state durations have been initialized to the correct values
*
* Also initializes test_light_invalid with an invalid state duration
* Tests whether initial state has been correctly set to FLASH_RED (error state)
*/
void test_initialization() {
    printf("----- Testing initialize_traffic_light() -----\n");

    // Initialize light with valid state durations
    initialize_traffic_light(&test_light_valid, green_dur, yellow_dur, red_dur_valid);

    // Check that initial state and state durations have been correctly set
    assert_and_print("valid state initialization", test_light_valid.current_state == RED);
    assert_and_print("green duration initialization", test_light_valid.green_duration == green_dur);
    assert_and_print("yellow duration initialization", test_light_valid.yellow_duration == yellow_dur);
    assert_and_print("red duration initialization", test_light_valid.red_duration == red_dur_valid);

    // Initialize light with one invalid state duration
    initialize_traffic_light(&test_light_invalid, green_dur, yellow_dur, red_dur_invalid); 
    printf("\n");

    // Check that light has been initialized with initial state FLASH_RED
    assert_and_print("invalid state initialization", test_light_invalid.current_state == FLASH_RED);

    printf("--- All initialization tests passed ---\n\n");
}

/*
* This function tests update_light() to ensure correct state transitions
*
* Uses test_light_valid, which has been intialized during the previous test and is in RED state
* Calls update_light() 3 times and ensures that the correct state transitions have occurred:
*   1. RED -> GREEN
*   2. GREEN -> YELLOW
*   3. YELLOW -> RED
*/
void test_state_transitions() {
    printf("----- Testing update_light() -----\n");
    
    // test_light_valid begins in RED state
    update_light(&test_light_valid);  // Transition RED -> GREEN
    // Check if light is in GREEN state
    assert_and_print("RED -> GREEN transition", test_light_valid.current_state == GREEN);

    update_light(&test_light_valid);  // Transition GREEN -> YELLOW
    // Check if light is in YELLOW state
    assert_and_print("GREEN -> YELLOW transition", test_light_valid.current_state == YELLOW);

    update_light(&test_light_valid);  // Transition YELLOW -> RED
    // Check if light is in RED state
    assert_and_print("YELLOW -> RED transition", test_light_valid.current_state == RED);

    printf("--- All update tests passed ---");
}

/*
* Function to test the outputs of display_state()
*
* Calls display_state() on each of the 4 possible states (GREEN, YELLOW, RED, FLASH_RED)
* Then displays both the expected and actual values displayed
*/
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

     printf("--- All display tests completed ---");
}

/*
* Function to be ran in the thread started in test_flashing_red_light()
* Calls the handle_flash_red() function to verify correct behavior in FLASH_RED state
*/
void* run_flash_red_thread() {
    handle_flash_red(&test_light_invalid); // Display FLASH_RED state behavior
    return NULL;
}

/*
* Function to verify correct behavior in FLASH_RED state
* Displays expected output and flashes light red to display actual output
* Timing behavior must be confirmed visually
*
* Runs handle_flash_red() function in a thread
* Thread is necessary because handle_flash_red() enters a loop that is only terminated
*    when the provided TrafficLight instance is switched to a state other than FLASH_RED
*/
void test_flashing_red_light() {
    printf("\n\n----- Testing handle_flash_red() (Confirm output visually) -----\n");

    pthread_t thread;  // Thread to handle light operation
    int flashing_time = 3;  // Flashing red light timeout

    // Display expected output
    printf("* EXPECTED:\n");
    printf("FLASH_RED: Light ON\n");
    printf("FLASH_RED: Light OFF\n");
    printf("FLASH_RED: Light ON\n");
    printf("FLASH_RED: Light OFF\n");

    // Display the actual output
    printf("* ACTUAL:\n");

    // Start the thread running the flashing red light function
    if (pthread_create(&thread, NULL, run_flash_red_thread, NULL) != 0) {
        // Handle thread creation errors
        printf("Error: Failed to create thread\n");
        return;
    }

    // Wait for the timeout
    sleep(flashing_time);

    // Stop flashing red light
    test_light_invalid.current_state = RED;

    // Wait for the thread to terminate
    if (pthread_join(thread, NULL) != 0) {
        // Handle thread termination errors
        printf("Error: Failed to join thread\n");
    }

    printf("--- All FLASH_RED tests completed ---");
}

/*
* Function to verify the routine operation of the traffic light system
* 
* First displays expected output
* Then updates light and displays state to show actual output
*
* Output timing correctness must be confirmed visually
*/
void test_normal_operation() {
    printf("\n\n----- Testing routine operation (confirm output visually) -----\n");

    // Start light in initial state (RED)
    test_light_valid.current_state = RED;

    // Display expected output
    printf("* EXPECTED:\n");
    printf("Traffic Light State: RED\n");
    printf("Traffic Light State: GREEN\n");
    printf("Traffic Light State: YELLOW\n");
    printf("Traffic Light State: RED\n");

    // Cycle through all possible state updates to display actual output
    printf("* ACTUAL:\n");
    for (int i = 0; i < 4; i++) {
        display_state(test_light_valid.current_state);  // Display the current state
        update_light(&test_light_valid);  // Transition to the next state
    }

    printf("--- Routine operation test completed ---\n");
}

// Run all tests
int main() {
    printf("\n===== Begin Testing =====\n\n");

    test_initialization();  // Test traffic light initialization function
    test_state_transitions();  // Test state update function
    test_display_state();  // Test function used to display the current state of the light
    test_flashing_red_light();  // Test light behavior in FLASH_RED state
    test_normal_operation();  // Test light behavior during routine operation

    printf("\n===== Testing Completed =====\n\n");
    return 0;
}