#pragma once

// ##############################################################################################
// MCU Select:

#include "mcu_select.h"

/*
    If there is not exist mcu_select.h at beside of this header file, Create it and put this bellow following content. 
    Then select your desired MCU that want work with.
*/
// ----------------------------------------------------------------
// mcu_select.h file:

// Define the target MCU family here
// Uncomment the desired MCU family definition below:

// #define STM32F1
// #define STM32F4
// #define STM32H7

// ----------------------------------------------------------------

// ##############################################################################################
// Include libraries:

#if defined(STM32F1)
#include "stm32f1xx_hal.h"
#elif defined(STM32F4)
#include "stm32f4xx_hal.h"
#elif defined(STM32H7)
#include "stm32h7xx_hal.h"
#endif

// ##############################################################
// Buzzer class:

/**
 @class BuzzerAlarm
 @brief Buzzer class for manage alaram sounds.
 @note - Maximum output speed GPIO config is LOW.
 @note - GPIO mode is output push-pull.
*/
class Buzzer
{
  public:

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

  private:

    /**
     * @struct ParametersStructure
     * @brief Parameters structure
     */
    struct ParametersStructure
    {
        /// @brief GPIO port for buzzer pin.
        GPIO_TypeDef* GPIO_PORT;

        /**
         * @brief GPIO pin number for buzzer. 
         * @note It shoude be GPIO_PIN_0, GPIO_PIN_1, ...
         *  */
        uint16_t GPIO_PIN;

        /// @brief Active mode of buzzer control. 0: Active low, 1: Active high.
        uint8_t ACTIVE_MODE;
    }parameters;

    /// @brief The time update for buzzer triggering in non blocking mode.
    uint32_t _T;

    /// @brief GPIO_PinState value for LED turn on state.
    GPIO_PinState _on;

    /// @brief GPIO_PinState value for LED turn off state.
    GPIO_PinState _off;

    /// @brief Counter for trig buzzer in non blocking mode.
    uint8_t _trigCounter;

    /// @brief The flag for trig buzzer state in non blocking mode.
    bool _trigFlag;

    /// @brief The delay of time for one trig buzzer in non blocking mode. [ms]
    uint16_t _trigDelay;

    /// @brief The number of trig buzzer in non blocking mode.
    uint8_t _trigNumber;

    /// @brief The flag for LED.init() is succeeded or not.
    bool _initFlag;

    /**
     * @brief Enable RCC GPIO PORT for certain port.
     * @return true if successful.
     */
    bool RCC_GPIO_CLK_ENABLE(GPIO_TypeDef *GPIO_PORT);
};


