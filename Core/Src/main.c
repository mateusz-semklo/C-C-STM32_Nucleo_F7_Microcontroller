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
#define ilosc_probek 12
#define limit_probek_pradu 10
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */


volatile float32_t Ialpha, Ibeta,e,out,priv,Ia,Ib,Ic, theta_mech,theta_el,sinVal,cosVal,pId,pIq;
volatile float32_t okres_COM,speed, sum_speed, average_speed, speed_tab[ilosc_probek];

volatile uint8_t trans,recive,limit_c,allow_c;
volatile int16_t pomiar[4], set_point,pomiar_zero[3],pomiar_zero1[3];
volatile arm_pid_instance_f32 pid;

uint8_t allow=0;
uint8_t f,g=0;
uint8_t d=(ilosc_probek-1);
uint16_t licz,i,a,b,c,z;;



volatile char tablica[size][18];



/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance==TIM1)
		{


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
	   /// TIM3 CLK 80 MHz, PSC =499,  80MGz/(PSC+1)*(TIM1->CCR1+1)
		/// 80 000 000/ 500 = 160 000 Hz
		/// T 1/160000 = 0,000000625
		okres_COM=	0.00000625 * TIM3->CCR1;
		// speed = 60 * 1/(12*okres_COM) [obr/min]
		speed=5 / okres_COM;

		speed_tab[0]=okres_COM;

		while (d>0)
		{
			speed_tab[d]=speed_tab[d-1];
			d--;
		}
		d=(ilosc_probek-1);

		if(g<ilosc_probek)
			g++;

		else
			g=ilosc_probek;



		f=0;
		while(f<g)
		{
			sum_speed=sum_speed + speed_tab[f];
			f++;

		}

		average_speed= 5 / (sum_speed/(f+1));

		sum_speed=0;

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

				if(limit_c<limit_probek_pradu)
				{
					pomiar_zero[0]+=pomiar[0];
					pomiar_zero[1]+=pomiar[1];
					pomiar_zero[2]+=pomiar[2];
					limit_c++;


				}

				else
				{
					pomiar_zero1[0]=pomiar_zero[0]/limit_c;
					pomiar_zero1[1]=pomiar_zero[1]/limit_c;
					pomiar_zero1[2]=pomiar_zero[2]/limit_c;
					allow_c=1;



				}

				if(allow_c>0)
				{

				Ia=(pomiar[0]-pomiar_zero1[0]) * 0.0044;  // 2.5 v / 3.6 v x 4095 = 2843
			    Ib=(pomiar[1]-pomiar_zero1[0]) * 0.0044;  // 3.3/4095 * 1/0.185 [v/a] == 0,00435 A
			    Ic=(pomiar[2]-pomiar_zero1[0]) * 0.0044;
			    theta_mech=((int16_t)(pomiar[3] * 0.0879));
			    theta_el=theta_mech*2;


			    arm_clarke_f32(Ia, Ib, &Ialpha, &Ibeta);
			    arm_sin_cos_f32(theta_el, &sinVal, &cosVal);
			    arm_park_f32(Ialpha, Ibeta, &pId, &pIq, sinVal, cosVal);

				}

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
   TIM1->ARR=0xFFFE;
   TIM1->PSC=100;
   TIM1->CCR1=43000;
   HAL_TIM_Base_Start_IT(&htim1);
   HAL_TIM_PWM_Start_IT(&htim1, TIM_CHANNEL_1);
   HAL_TIMEx_ConfigCommutEvent_IT(&htim1,TIM_TS_ITR2, TIM_COMMUTATION_TRGI);


   //////// konfiguracja Timer 3  ////////////
    TIM3->ARR=0xFFFE;
    TIM3->PSC=499;
    TIM3->CCR2=1;
    TIM3->CCR4=1;
    HAL_TIMEx_HallSensor_Start(&htim3);
    //HAL_TIM_Base_Start(&htim3);
    //HAL_TIM_OC_Start(&htim3, TIM_CHANNEL_4);



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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 160;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART2|RCC_PERIPHCLK_USART3
                              |RCC_PERIPHCLK_CLK48;
  PeriphClkInitStruct.PLLSAI.PLLSAIN = 192;
  PeriphClkInitStruct.PLLSAI.PLLSAIR = 2;
  PeriphClkInitStruct.PLLSAI.PLLSAIQ = 2;
  PeriphClkInitStruct.PLLSAI.PLLSAIP = RCC_PLLSAIP_DIV8;
  PeriphClkInitStruct.PLLSAIDivQ = 1;
  PeriphClkInitStruct.PLLSAIDivR = RCC_PLLSAIDIVR_2;
  PeriphClkInitStruct.Usart2ClockSelection = RCC_USART2CLKSOURCE_SYSCLK;
  PeriphClkInitStruct.Usart3ClockSelection = RCC_USART3CLKSOURCE_SYSCLK;
  PeriphClkInitStruct.Clk48ClockSelection = RCC_CLK48SOURCE_PLLSAIP;
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
