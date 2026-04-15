/*
 * PROJE: STM32 ADC-DMA-PWM Kontrol Sistemi
 * ÖĞRENCİ: Gökhan Beyaz
 * AÇIKLAMA: PA0 pininden potansiyometre verisi okunur, 
 * PB3 pinindeki (Nucleo Green LED) parlaklık kontrol edilir
 * ve UART üzerinden eş zamanlı durum raporu basılır.
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "stm32l0xx_hal.h"

// Donanım Tanımlamaları
#define LED_PIN        GPIO_PIN_3
#define LED_PORT       GPIOB

ADC_HandleTypeDef hadc;
UART_HandleTypeDef huart2;
uint32_t adc_deger = 0;

// Fonksiyon Prototipleri
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC_Init(void);
static void MX_USART2_UART_Init(void);

int main(void) {
    // HAL Kütüphanesini ve Çevresel Birimleri Başlat
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_ADC_Init();
    MX_USART2_UART_Init();

    // ADC modülünü aktifleştir
    HAL_ADC_Start(&hadc);

    while (1) {
        // Potansiyometre değerini ADC üzerinden oku
        if (HAL_ADC_PollForConversion(&hadc, 10) == HAL_OK) {
            adc_deger = HAL_ADC_GetValue(&hadc);
        }

        // --- Terminal Raporlama Sistemi ---
        if (adc_deger >= 3000) {
            printf("Sensor: %lu | Durum: KRITIK\r\n", adc_deger);
        } else if (adc_deger >= 1000) {
            printf("Sensor: %lu | Durum: UYARI\r\n", adc_deger);
        } else {
            printf("Sensor: %lu | Durum: NORMAL\r\n", adc_deger);
        }

        // --- LED Kontrol Mantığı ---
        // Eşik değerine göre PB3 pinindeki yeşil LED'i kontrol eder
        if (adc_deger > 1000) {
            HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_SET);   // LED AÇIK
        } else {
            HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_RESET); // LED KAPALI
        }

        HAL_Delay(250); // Simülasyon kararlılığı için bekleme
    }
}

// ADC Yapılandırması (Potansiyometre - PA0)
static void MX_ADC_Init(void) {
    hadc.Instance = ADC1;
    hadc.Init.Resolution = ADC_RESOLUTION_12B;
    hadc.Init.ContinuousConvMode = ENABLE;
    HAL_ADC_Init(&hadc);

    ADC_ChannelConfTypeDef sCh = {0};
    sCh.Channel = ADC_CHANNEL_0;
    sCh.Rank = ADC_RANK_CHANNEL_NUMBER;
    HAL_ADC_ConfigChannel(&hadc, &sCh);
}

// UART Yapılandırması (Terminal İletişimi - 115200 Baud)
static void MX_USART2_UART_Init(void) {
    huart2.Instance = USART2;
    huart2.Init.BaudRate = 115200;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    HAL_UART_Init(&huart2);
}

// printf fonksiyonunun UART üzerinden çalışmasını sağlar
int _write(int file, char *ptr, int len) {
    HAL_UART_Transmit(&huart2, (uint8_t*)ptr, len, HAL_MAX_DELAY);
    return len;
}

// GPIO Yapılandırması (PB3 LED Çıkışı)
static void MX_GPIO_Init(void) {
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = LED_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LED_PORT, &GPIO_InitStruct);
}

void SystemClock_Config(void) {
    // Wokwi ortamı için varsayılan saat ayarları
}
