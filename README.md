# gokhan_beyaz_25221304003_gomulu_s-stemler_v-ze_proje_STM32-ADC-DMA-PWM-Controller[main.c](https://github.com/user-attachments/files/26624825/main.c)
/* USER CODE BEGIN Header */
/**
  * @file           : main.c
  * @brief          : Gökhan Beyaz - Vize Projesi
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stdio.h>

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc;
DMA_HandleTypeDef hdma_adc;
TIM_HandleTypeDef htim1;
UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
uint32_t adc_deger = 0;
uint8_t sistem_aktif = 0;
char uart_mesaj[64];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_ADC_Init(void);
static void MX_TIM1_Init(void);
static void MX_USART1_UART_Init(void);

/**
  * @brief  The application entry point.
  */
int main(void)
{
  /* MCU Configuration */
  HAL_Init();
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init(); // DMA önce başlamalı
  MX_ADC_Init();
  MX_TIM1_Init();
  MX_USART1_UART_Init();

  /* USER CODE BEGIN 2 */
  /* PWM ve ADC-DMA Başlat */
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
  HAL_ADC_Start_DMA(&hadc, &adc_deger, 1);
  HAL_UART_Transmit(&huart1, (uint8_t*)"Sistem Yuklendi - Gokhan Beyaz\r\n", 32, 100);
  /* USER CODE END 2 */

  /* Infinite loop */
  while (1)
  {
    if(sistem_aktif == 1)
    {
        /* ADC (0-4095) -> PWM (0-999) Oranlama */
        uint32_t parlaklik = (adc_deger * 999) / 4095;
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, parlaklik);

        /* UART Bilgi Gönderimi */
        int len = sprintf(uart_mesaj, "AKTIF | ADC: %lu | PWM: %lu\r\n", adc_deger, parlaklik);
        HAL_UART_Transmit(&huart1, (uint8_t*)uart_mesaj, len, 100);
    }
    else
    {
        /* Sistem Kapalı */
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
        HAL_UART_Transmit(&huart1, (uint8_t*)"SISTEM KAPALI\r\n", 15, 100);
    }
    HAL_Delay(500);
  }
}

/* USER CODE BEGIN 4 */
/* Buton Kesmesi (PA1 için) */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == GPIO_PIN_1)
    {
        sistem_aktif = !sistem_aktif;
    }
}
/* USER CODE END 4 */

/**
  * @brief System Clock Configuration
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSI14;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSI14State = RCC_HSI14_ON;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0);

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);
}

static void MX_ADC_Init(void)
{
  ADC_ChannelConfTypeDef sConfig = {0};
  hadc.Instance = ADC1;
  hadc.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
  hadc.Init.Resolution = ADC_RESOLUTION_12B;
  hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc.Init.ScanConvMode = ADC_SCAN_DIRECTION_FORWARD;
  hadc.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc.Init.ContinuousConvMode = ENABLE;
  hadc.Init.DMAContinuousRequests = ENABLE;
  HAL_ADC_Init(&hadc);

  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  HAL_ADC_ConfigChannel(&hadc, &sConfig);
}

static void MX_TIM1_Init(void)
{
  TIM_OC_InitTypeDef sConfigOC = {0};
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 0;
  htim1.Init.Period = 999;
  HAL_TIM_PWM_Init(&htim1);

  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2);
  HAL_TIM_MspPostInit(&htim1);
}

static void MX_USART1_UART_Init(void)
{
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  HAL_UART_Init(&huart1);
}

static void MX_DMA_Init(void) 
{
  __HAL_RCC_DMA1_CLK_ENABLE();
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);
}

static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  __HAL_RCC_GPIOA_CLK_ENABLE();

  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  HAL_NVIC_SetPriority(EXTI0_1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_1_IRQn);
}

void Error_Handler(void) { while (1) {} }
