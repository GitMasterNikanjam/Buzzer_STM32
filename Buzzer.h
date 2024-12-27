#pragma once

// ##############################################################################################
// Define the target MCU family here

#define STM32F1
// #define STM32F4
// #define STM32H7

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
*/
class Buzzer
{
  public:

    /**
     @brief Default constructor.
    */
    Buzzer(GPIO_TypeDef* gpioPort, uint16_t gpioPin, uint8_t activeMode = 1);

    /**
     @brief Initial object. start digital GPIO ouput mode. Check parameters.
     @return true if successed.
    */
    bool begin(void);

    // ------------------------------------------------------------------
    // Special sounds for buzzer:

    /// @brief Alarm for finished initial and configurations something.
    void soundInit(void);

    /// @brief Alarm for stop something action for operations. 
    void soundStop(void);
    
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

  private:

    /**
     * @struct ParametersStructure
     * @brief Parameters structure
     */
    struct ParametersStructure
    {
        GPIO_TypeDef* GPIO_PORT;

        uint16_t GPIO_PIN;

        uint8_t ACTIVE_MODE;
    }parameters;

    /// @brief GPIO_PinState value for LED turn on state.
    GPIO_PinState _on;

    /// @brief GPIO_PinState value for LED turn off state.
    GPIO_PinState _off;

};


