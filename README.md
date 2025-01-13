# Buzzer Library for STM32

- This library can be used for active buzzer sound management.  
- The main class is Buzzer. 
- The buzzer sounds can be control in blocking or non-blocking mode.

-------------------------------------------------------------------------------------------

# Public Member Functions for Buzzer class

```cpp
/**
 @brief Default constructor.
    @param activeMode: This is the GPIO output value when the LED state is on. Default is active high.
    @note - The init() method is needed after this to apply the settings on the hardware.
    @note - Maximum output speed GPIO config is LOW.
    @note - GPIO mode is output push-pull.
*/
Buzzer(GPIO_TypeDef* gpioPort, uint16_t gpioPin, uint8_t activeMode = 1);

/**
 @brief Apply the settings to the hardware. Start the Buzzer action.
    @return true if successful.
*/
bool init(void);

/**
 * @brief Clean setting on hardware. Stop  Buzzer action. 
 */
void clean(void);

/**
 * @brief Trig the Buzzer.
 * @param duration: is the duration time for toggle Buzzer.
 * @param number: is the number of toggling in certain duration time.
 * @param blockingMode: is the trig mode for blocking mode enable/disable. Default value is true that means triggering is in blocking mode.
 * @note - Total time duration for toggle operation is: (duration)
 */
void trig(uint16_t duration, uint8_t number, bool blockingMode = true);

/**
 * @brief Return triggering status in non blocking mode.
 * @return - true if triggering proccess is not finished.
 * @return - false if triggering proccess is finished.
 *  */ 
bool isTriggering(void) {return _trigFlag;};

/**
 * @brief Update triggering status in non blocking mode.
 */
void trigUpdate(void);

// ------------------------------------------------------------------
// Special sounds for buzzer:

/// @brief Alarm for finished initial and configurations something.
void soundInit(bool blockingMode = true);

/// @brief Alarm for stop something action for operations. 
void soundStop(bool blockingMode = true);

/// @brief Alarm type_1 for warning happening.
void soundWarning_1(void);

/// @brief Alarm type_2 for warning happening.
void soundWarning_2(void);

/// @brief Alarm type_3 for warning happening.
void soundWarning_3(void);

// -----------------------------------------------------------------
// ON/OFF buzzer sound:

/// @brief turn on sound.
void on(void);

/// @brief turn off sound.
void off(void);

/// @brief Toggle the LED.
void toggle(void);

```