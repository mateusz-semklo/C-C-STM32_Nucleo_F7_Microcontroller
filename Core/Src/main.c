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
#include "adc.h"
#include "dma.h"
#include "eth.h"
#include "tim.h"
#include "usart.h"
#include "usb_otg.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "arm_math.h"
#include "stdio.h"
#include "stdio_ext.h"
#include "stdlib.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
 #define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })


#define limit_H_ARR 11250
#define limit_H_current 500
#define limit_L 0
#define size 2000
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */


volatile float32_t Ialpha, Ibeta,e,out,priv,Ia,Ib,Ic, theta,sinVal,cosVal,pId,pIq;

volatile uint8_t trans,recive;
volatile int16_t pomiar[4], set_point;
volatile arm_pid_instance_f32 pid;

uint8_t allow=0;
uint16_t licz,i,a,b,c,d,f=0;


volatile char tablica[size][18];



/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance==TIM1)
		{
d++;

/**


        if((i+size)<(size+size))
         {
		    sprintf(tablica[i], "%.4f+j*%.4f\n", Ialpha, Ibeta);
		    i++;

         }
         **/

		}

}

void HAL_TIMEx_CommutCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance==TIM1)
	{


	}
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance==USART3)
	{
		HAL_UART_Receive_IT(&huart3, &recive, 1);
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin==GPIO_PIN_13)
	{
		 HAL_TIMEx_HallSensor_Start(&htim3);
		 HAL_TIM_Base_Start_IT(&htim1);
		 HAL_TIM_PWM_Start_IT(&htim1, TIM_CHANNEL_1);


	/**	HAL_TIMEx_HallSensor_Stop(&htim3);
		HAL_TIM_Base_Stop_IT(&htim1);
		HAL_TIM_PWM_Stop_IT(&htim1, TIM_CHANNEL_1);
		HAL_ADC_Stop_DMA(&hadc1);


		allow=1;
		**/


	}

}

void   HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{

				Ia=(pomiar[0]-3000) * 0.0044;
			    Ib=(pomiar[1]-3000) * 0.0044;
			    Ic=(pomiar[2]-3000) * 0.0044;
			    theta=((int16_t)(pomiar[3] * 0.0879));

f++;

			    arm_clarke_f32(Ia, Ib, &Ialpha, &Ibeta);
			    arm_sin_cos_f32(theta, &sinVal, &cosVal);
			    arm_park_f32(Ialpha, Ibeta, &pId, &pIq, sinVal, cosVal);

/**
				set_point=recive;
				priv=pid.state[2];
				e=set_point-current;
				out=arm_pid_f32(&pid, e);


				if(out>limit_H_current)
						{

							pid.state[2]=priv;
							out=limit_H_current;
						}

				if(out<limit_L)
						{
							pid.state[2]=priv;
							out=limit_L;

						}

**/

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
  MX_ETH_Init();
  MX_USART3_UART_Init();
  MX_USB_OTG_FS_PCD_Init();
  MX_TIM3_Init();
  MX_USART2_UART_Init();
  MX_ADC1_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */

  ////////konfiguracja USART ///////////
//  HAL_UART_Receive_IT(&huart3, &recive, 1);


  //////// konfiguracja Timer 1  ////////////
  // TIM1->ARR=limit_H_ARR/2;
 //  TIM1->PSC=0;
 //  TIM1->CCR1=5000;

   TIM1->ARR=0xFFFF;
<<<<<<< HEAD
<<<<<<< HEAD
   TIM1->PSC=500;
   TIM1->CCR1=50000;


=======
   TIM1->PSC=15000;
   TIM1->CCR1=20000;
>>>>>>> d9406d99c57890a9848312fd213f5ad332613b4d
=======
   TIM1->PSC=15000;
   TIM1->CCR1=20000;
>>>>>>> d9406d99c57890a9848312fd213f5ad332613b4d


  // HAL_TIMEx_ConfigCommutEvent_IT(&htim1,TIM_TS_ITR2, TIM_COMMUTATION_TRGI);


   //////// konfiguracja Timer 3  ////////////
    TIM3->ARR=0xFFFF;
    TIM3->PSC=500;
    TIM3->CCR2=2;



 /////////// inicjalizacja pid ////////////////
    pid.Kp=1;
    pid.Ki=5;
    pid.Kd=0;
    arm_pid_init_f32(&pid, 1);


    //////// konfiguracja ADC  ////////////
     HAL_ADC_Start_DMA(&hadc1,pomiar,4);


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6))
		  a=1;
	  else
		  a=0;

	  if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_7))
	  		  b=1;
	  else
		  b=0;

	  if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_8))
	  		  c=1;
	  else
		  c=0;


/**	  if(allow)
	  {

	  if(licz<size)
	  {
	if( HAL_OK== HAL_UART_Transmit_DMA(&huart3, tablica[licz], strlen(tablica[licz])))
	  licz++;

	  }

	  }
	  **/

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Configure LSE Drive Capability 
  */
  HAL_PWR_EnableBkUpAccess();
  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 216;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Activate the Over-Drive mode 
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART2|RCC_PERIPHCLK_USART3
                              |RCC_PERIPHCLK_CLK48;
  PeriphClkInitStruct.Usart2ClockSelection = RCC_USART2CLKSOURCE_SYSCLK;
  PeriphClkInitStruct.Usart3ClockSelection = RCC_USART3CLKSOURCE_SYSCLK;
  PeriphClkInitStruct.Clk48ClockSelection = RCC_CLK48SOURCE_PLL;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

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
