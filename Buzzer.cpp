
// ################################################################################
// Include libraries:

#include "Buzzer.h"

// ################################################################################
// BuzzerAlarm class:

Buzzer::Buzzer(GPIO_TypeDef* gpioPort, uint16_t gpioPin, uint8_t activeMode)
{
    parameters.GPIO_PORT = gpioPort;
    parameters.GPIO_PIN = gpioPin;
    parameters.ACTIVE_MODE = activeMode;

    if(parameters.ACTIVE_MODE == 0)
    {
        _on = GPIO_PIN_RESET;
        _off = GPIO_PIN_SET;
    }
    else
    {
        _on = GPIO_PIN_SET;
        _off = GPIO_PIN_RESET;
    }
}

bool Buzzer::begin(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /*Configure GPIO pin */
    GPIO_InitStruct.Pin = parameters.GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(parameters.GPIO_PORT, &GPIO_InitStruct);

    /*Configure GPIO pin Output Level */
    off();

    return true;
}

void Buzzer::on(void)
{
  HAL_GPIO_WritePin(parameters.GPIO_PORT, parameters.GPIO_PIN, _on);
}

void Buzzer::off(void)
{
  HAL_GPIO_WritePin(parameters.GPIO_PORT, parameters.GPIO_PIN, _off);
}

void Buzzer::soundInit(void)
{
  on();
  HAL_Delay(1000);
  off();
  HAL_Delay(100);
}

void Buzzer::soundStop(void)
{
  for(uint8_t i=1;i<=2;i++)
  {
  on();
  HAL_Delay(100);
  off();
  HAL_Delay(100);
  }
}

void Buzzer::soundWarning_1(void)
{
  for(int j=1; j<=10; j++)
  {
    for(uint8_t i=1;i<=20;i++)
    {
      on();
      HAL_Delay(5);
      off();
      HAL_Delay(5);  
    }
    HAL_Delay(200);
  }
}
    
void Buzzer::soundWarning_2(void)
{
  on();
  HAL_Delay(100);
  off();
  HAL_Delay(100);
}

void Buzzer::soundWarning_3(void)
{
  for(uint8_t i=1;i<=10;i++)
  {
    
    on();
    HAL_Delay(25);
    off();
    HAL_Delay(25);  
  }
}