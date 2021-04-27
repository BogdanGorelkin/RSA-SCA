/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/

//RSA
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
//#define V_30 1.43f
//#define Avg_Slope 0.0043f
//#define VDDA 3.3f

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */


/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc;
DMA_HandleTypeDef hdma_adc;

TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_usart2_rx;

/* USER CODE BEGIN PV */

//int16_t TS_ADC_DATA = 0;
//float Vsense, Temperature;
uint32_t tempDMA[2300] = {0};



/* USER CODE END PV */
uint64_t d = 2668186619;
uint64_t n = 4002689923;
//uint64_t cipher, decrypt;
//uint32_t msg;

//===========================
//======= private key =======
//===========================
//p = 10007;
//q = 399989;
//n=4002689923;
//e = 3;
//d=2668186619;
//unsigned int x[679] = {117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,};
//unsigned int x[100] = {117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,/*seven begin*/166375/*seven end*/,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649,117649};//0 in this array you need put your encrypted data
unsigned int xOne = 117649;
unsigned int xSeven = 166375;

unsigned short MSG[2500] = {0};

short i = -1;
unsigned short j = 2500;
short k=10;
/* for message "FFFFFFFFFF"
unsigned int x[10] = {343000,343000,343000,343000,343000,343000,343000,343000,343000,343000};
unsigned short MSG[10] = {0};
short k=10;
short i = -1;
unsigned short j = 10*250;
*/
/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_ADC_Init(void);
static void MX_TIM3_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */
int powMod(unsigned long long a, unsigned long long b, unsigned long long n) {
        long long x = 1, y = a;

        while (b > 0) {
                if (b % 2 == 1)
                        x = (x%n * y) % n;
                y = (y%n * y) % n; // (a*b) mod n = (a*(b mod n) mod n)
                b /= 2;
        }

        return x % n;
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC_Init();
  MX_TIM3_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
//start the timer
	HAL_TIM_Base_Start(&htim3);
//start ADC as DMA
 
 	HAL_ADC_Start_DMA(&hadc, tempDMA, 2300);  
 

	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	    while (j)
    {
        i++;
        j--;
        if (i==k)
					MSG[i] = powMod(xSeven, d, n);
//           i = 0;
//						HAL_Delay(10);
				else
//============= decrypt ===============
        MSG[i] = powMod(xOne, d, n);

//calculate msg (-dependent) Block chipper
//        MSG[i]=decrypt;
/*        if (i==0)
            msg = decrypt;
            else if (decrypt>MSG[i-1])
                msg = (decrypt-MSG[i-1])%n;
                else
                    msg = (decrypt+n-MSG[i-1])%n;
*/
//print decrypted ASCII symbol
//        printf(",%u", msg);
//print decrypted symbol
//        printf(",%c", msg);
		if (j==0)
		{
			HAL_ADC_Stop_DMA(&hadc);


				uint8_t tempUART[5] = {0};
				
				
//sent temperature by UART				
				for (unsigned short z=0; z<2300; z++)
				{
				sprintf(tempUART, "%lu\n" , tempDMA[z]);
				HAL_UART_Transmit(&huart2,tempUART, 5,100);
				if (tempDMA[z]==0)
					return 0;
				}
			}
			
//		HAL_ADC_Start(&hadc);
//		tempConvert(int z, tempDMAvar)
/*		for(int z	= 0;z<100;z++){
			HAL_Delay(500);
		tempArray[z] = tempDMA[0];  
		}
			if(HAL_ADC_PollForConversion(&hadc, 100) == HAL_OK)
		{
			TS_ADC_DATA = HAL_ADC_GetValue(&hadc);
			Vsense = (float) TS_ADC_DATA/4095*VDDA;
			Temperature = (V_30-Vsense)/Avg_Slope+30;

		}
*/

    }

    /* USER CODE END WHILE */
	
    /* USER CODE BEGIN 3 */
//		HAL_UART_Transmit(&huart2,tempDMA, strlen(tempDMA),1);


	}

  /* USER CODE END 3 */

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSI14;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSI14State = RCC_HSI14_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.HSI14CalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC_Init(void)
{

  /* USER CODE BEGIN ADC_Init 0 */

  /* USER CODE END ADC_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC_Init 1 */

  /* USER CODE END ADC_Init 1 */
  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion) 
  */
  hadc.Instance = ADC1;
  hadc.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc.Init.Resolution = ADC_RESOLUTION_12B;
  hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc.Init.ScanConvMode = ADC_SCAN_DIRECTION_FORWARD;
  hadc.Init.EOCSelection = ADC_EOC_SEQ_CONV;
  hadc.Init.LowPowerAutoWait = DISABLE;
  hadc.Init.LowPowerAutoPowerOff = DISABLE;
  hadc.Init.ContinuousConvMode = DISABLE;
  hadc.Init.DiscontinuousConvMode = DISABLE;
  hadc.Init.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T3_TRGO;
  hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_RISING;
  hadc.Init.DMAContinuousRequests = ENABLE;
  hadc.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  if (HAL_ADC_Init(&hadc) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel to be converted. 
  */
  sConfig.Channel = ADC_CHANNEL_TEMPSENSOR;
  sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
  sConfig.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC_Init 2 */

  /* USER CODE END ADC_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 4800;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 100;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/** 
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void) 
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);
  /* DMA1_Channel4_5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel4_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel4_5_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PA5 */
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hadc);

  /* NOTE : This function should not be modified. When the callback is needed,
            function HAL_ADC_ConvCpltCallback must be implemented in the user file.
   */
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
