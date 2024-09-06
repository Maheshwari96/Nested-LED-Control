// Pin definitions for the LEDs
#define INDIVIDUAL_LED_PIN 3  // Connect an LED to digital pin 3
#define GROUP_LED_PIN 5       // Connect another LED to digital pin 5

// Structure to hold individual LED settings
typedef struct {
    uint8_t state;        // 1 for ON, 0 for OFF
    uint8_t brightness;   // Brightness level (0-255)
} LEDSettings;

// Structure to hold group LED settings
typedef struct {
    LEDSettings singleLED;    // Individual LED settings
    uint8_t groupState;       // 1 for all ON, 0 for all OFF
    uint8_t groupBrightness;  // Collective brightness adjustment
} LEDGroup;

// Initialize the LED group with default values
void initLEDGroup(LEDGroup *group) {
    group->singleLED.state = 0;         // LED OFF
    group->singleLED.brightness = 0;    // Minimum brightness
    group->groupState = 0;              // Group OFF
    group->groupBrightness = 0;         // Minimum brightness for the group
}

// Update LED group and individual settings
void updateLEDGroupSettings(LEDGroup *group, uint8_t groupState, uint8_t groupBrightness, 
                            uint8_t state, uint8_t brightness) {
    group->groupState = groupState;          // Update group state
    group->groupBrightness = groupBrightness;// Update group brightness
    group->singleLED.state = state;          // Update individual LED state
    group->singleLED.brightness = brightness;// Update individual LED brightness

    // Set individual LED brightness (PWM on pin 3)
    analogWrite(INDIVIDUAL_LED_PIN, brightness);
    
    // Set group LED brightness (PWM on pin 5)
    analogWrite(GROUP_LED_PIN, groupBrightness);
}

// Display the current status (for debugging via serial monitor)
void displayLEDGroupStatus(const LEDGroup *group) {
    Serial.print("Group State: ");
    Serial.println(group->groupState ? "ON" : "OFF");
    
    Serial.print("Group Brightness: ");
    Serial.println(group->groupBrightness);
    
    Serial.print("Individual LED State: ");
    Serial.println(group->singleLED.state ? "ON" : "OFF");
    
    Serial.print("Individual LED Brightness: ");
    Serial.println(group->singleLED.brightness);
}

void setup() {
    // Initialize the pins as output
    pinMode(INDIVIDUAL_LED_PIN, OUTPUT);
    pinMode(GROUP_LED_PIN, OUTPUT);

    // Start Serial communication for debugging
    Serial.begin(9600);

    // Create and initialize the LED group
    LEDGroup group;
    initLEDGroup(&group);

    // Update the LED group and individual LED settings
    updateLEDGroupSettings(&group, 1, 150, 1, 200); // Example: Group ON, brightness 150, individual LED ON, brightness 200

    // Display the LED group status
    displayLEDGroupStatus(&group);
}

void loop() {
    // Code to control LEDs in real-time can be added here
}
