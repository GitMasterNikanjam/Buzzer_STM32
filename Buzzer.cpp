
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

bool Buzzer::init(void)
{
  #ifdef GPIOA
  if(parameters.GPIO_PORT == GPIOA)
  {
      __HAL_RCC_GPIOA_CLK_ENABLE();
  }
  #endif
  #ifdef GPIOB
  else if (parameters.GPIO_PORT == GPIOB)
  {
      __HAL_RCC_GPIOB_CLK_ENABLE();
  }
  #endif
  #ifdef GPIOC
  else if (parameters.GPIO_PORT == GPIOC)
  {
      __HAL_RCC_GPIOC_CLK_ENABLE();
  }
  #endif
  #ifdef GPIOD
  else if (parameters.GPIO_PORT == GPIOD)
  {
      __HAL_RCC_GPIOD_CLK_ENABLE();
  }
  #endif
  #ifdef GPIOE
  else if (parameters.GPIO_PORT == GPIOE)
  {
      __HAL_RCC_GPIOE_CLK_ENABLE();
  }
  #endif
  #ifdef GPIOF
  else if (parameters.GPIO_PORT == GPIOF)
  {
      __HAL_RCC_GPIOF_CLK_ENABLE();
  }
  #endif
  #ifdef GPIOG
  else if (parameters.GPIO_PORT == GPIOG)
  {
      __HAL_RCC_GPIOG_CLK_ENABLE();
  }
  #endif
  #ifdef GPIOH
  else if (parameters.GPIO_PORT == GPIOH)
  {
      __HAL_RCC_GPIOH_CLK_ENABLE();
  }
  #endif
  #ifdef GPIOI
  else if (parameters.GPIO_PORT == GPIOI)
  {
      __HAL_RCC_GPIOI_CLK_ENABLE();
  }
  #endif

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

void Buzzer::toggle(void)
{
    HAL_GPIO_TogglePin(parameters.GPIO_PORT, parameters.GPIO_PIN);
}

void Buzzer::clean(void)
{
    off();

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    /*Configure GPIO pin */
    GPIO_InitStruct.Pin = parameters.GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(parameters.GPIO_PORT, &GPIO_InitStruct);
}

void Buzzer::soundInit(bool blockingMode)
{
  trig(2000, 1, blockingMode);
}

void Buzzer::soundStop(bool blockingMode)
{
  trig(200, 2, blockingMode);
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

void Buzzer::trig(uint16_t period, uint8_t number, bool blockingMode)
{
    if( (period == 0) || (number == 0) )
    {
        _T = 0;
        _trigFlag = false;
        off();
    }

    if(blockingMode == true)
    {
        for(int i=1; i<=number; i++)
        {
            on();
            HAL_Delay(period/2);
            off();
            HAL_Delay(period/2);
        }
    }
    else
    {
        _trigNumber = number;
        _trigPeriod = period;
        _T = HAL_GetTick();
        _trigCounter = 0;
        _trigFlag = true;
        on();
    }
}

void Buzzer::trigUpdate(void)
{
    uint32_t time = HAL_GetTick();

    if( (_trigFlag == false) || (time <= _T) )
    {
        return;
    }

    uint32_t hp = _trigPeriod/2;
    
    if( (time - _T) >= hp)
    {
        ++_trigCounter;
        if(_trigCounter >= (2* _trigNumber) )
        {
            _trigFlag = false;
            off();
            return;
        }
        toggle();
        _T = time;   
    }
}