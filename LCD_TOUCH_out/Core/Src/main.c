/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi2;
SPI_HandleTypeDef hspi3;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI2_Init(void);
static void MX_SPI3_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/*
//1. Write Command to LCD
void ILI9488_SendCommand(uint8_t com)
{
	//*(__IO uint8_t *)(0x60000000) = com;
	uint8_t tmpCmd = com;
	//Set DC HIGH for COMMAND mode
	//HAL_GPIO_WritePin(tftDC_GPIO, tftDC_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_RESET);
	//Put CS LOW
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, GPIO_PIN_RESET); //CHIP SELECT
	//Write byte using SPI
	HAL_SPI_Transmit(&hspi2, &tmpCmd, 1, 1);
	//SendByte(tmpCmd);
	//WaitLastData();
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, GPIO_PIN_SET);
	HAL_Delay(1);
	//Bring CS HIGH
	//HAL_GPIO_WritePin(tftCS_GPIO, tftCS_PIN, GPIO_PIN_SET);
}

//2. Write data to LCD
void ILI9488_SendData(uint8_t data)
{
	//*(__IO uint8_t *)(0x60000000) = com;
	uint8_t tmpCmd = data;
	//Set DC HIGH for COMMAND mode
	//HAL_GPIO_WritePin(tftDC_GPIO, tftDC_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_SET);
	//Put CS LOW
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, GPIO_PIN_RESET); //CHIP SELECT
	//Write byte using SPI
	HAL_SPI_Transmit(&hspi2, &tmpCmd, 1, 1);
	//SendByte(tmpCmd);
	//WaitLastData();
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, GPIO_PIN_SET);
	//Bring CS HIGH
	//HAL_GPIO_WritePin(tftCS_GPIO, tftCS_PIN, GPIO_PIN_SET);
}
*/
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
	int16_t x;
	int16_t y;

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
  MX_SPI2_Init();
  MX_SPI3_Init();
  /* USER CODE BEGIN 2 */
/*
  //RESET LCD
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET);
	HAL_Delay(50);

  //BEGIN INIT CODE (ngl don't know whats happening here but hope it works lel)
  	ILI9488_SendCommand(0XF7);
	ILI9488_SendData(0xA9);
	ILI9488_SendData(0x51);
	ILI9488_SendData(0x2C);
	ILI9488_SendData(0x82);
	ILI9488_SendCommand(0xC0);
	ILI9488_SendData(0x11);
	ILI9488_SendData(0x09);
	ILI9488_SendCommand(0xC1);
	ILI9488_SendData(0x41);
	ILI9488_SendCommand(0XC5);
	ILI9488_SendData(0x00);
	ILI9488_SendData(0x0A);
	ILI9488_SendData(0x80);
	ILI9488_SendCommand(0xB1);
	ILI9488_SendData(0xB0);
	ILI9488_SendData(0x11);
	ILI9488_SendCommand(0xB4);
	ILI9488_SendData(0x02);
	ILI9488_SendCommand(0xB6);
	ILI9488_SendData(0x02);
	ILI9488_SendData(0x42);
	ILI9488_SendCommand(0xB7);
	ILI9488_SendData(0xc6);
	ILI9488_SendCommand(0xBE);
	ILI9488_SendData(0x00);
	ILI9488_SendData(0x04);
	ILI9488_SendCommand(0xE9);
	ILI9488_SendData(0x00);
	ILI9488_SendCommand(0x36);
	ILI9488_SendData((1<<3)|(0<<7)|(1<<6)|(1<<5));
	ILI9488_SendCommand(0x3A);
	ILI9488_SendData(0x66);
	ILI9488_SendCommand(0xE0);
	ILI9488_SendData(0x00);
	ILI9488_SendData(0x07);
	ILI9488_SendData(0x10);
	ILI9488_SendData(0x09);
	ILI9488_SendData(0x17);
	ILI9488_SendData(0x0B);
	ILI9488_SendData(0x41);
	ILI9488_SendData(0x89);
	ILI9488_SendData(0x4B);
	ILI9488_SendData(0x0A);
	ILI9488_SendData(0x0C);
	ILI9488_SendData(0x0E);
	ILI9488_SendData(0x18);
	ILI9488_SendData(0x1B);
	ILI9488_SendData(0x0F);
	ILI9488_SendCommand(0XE1);
	ILI9488_SendData(0x00);
	ILI9488_SendData(0x17);
	ILI9488_SendData(0x1A);
	ILI9488_SendData(0x04);
	ILI9488_SendData(0x0E);
	ILI9488_SendData(0x06);
	ILI9488_SendData(0x2F);
	ILI9488_SendData(0x45);
	ILI9488_SendData(0x43);
	ILI9488_SendData(0x02);
	ILI9488_SendData(0x0A);
	ILI9488_SendData(0x09);
	ILI9488_SendData(0x32);
	ILI9488_SendData(0x36);
	ILI9488_SendData(0x0F);
	ILI9488_SendCommand(0x11);
	HAL_Delay(120);
	ILI9488_SendCommand(0x29);
	ILI9488_SendCommand(0x36);
	ILI9488_SendData((1<<3)|(0<<6)|(0<<7));//BGR==1,MY==0,MX==0,MV==0\

  	//SET DIRECTION [HORIZONTAL]
	ILI9488_SendCommand(0x2A); //set window size. x direction. In this case, we're taking the entire display.
	ILI9488_SendData(0>>8);
	ILI9488_SendData(0x00FF&0);
	ILI9488_SendData(479>>8);
	ILI9488_SendData(0x00FF&479>>8);

	ILI9488_SendCommand(0x2B); //set window size. y direction. In this case, we're taking the entire display.
	ILI9488_SendData(0>>8);
	ILI9488_SendData(0x00FF&0);
	ILI9488_SendData(479>>8);
	ILI9488_SendData(0x00FF&479	);

	ILI9488_SendCommand(0x2C); //display ram prep command

	//START WRITING WHITE SCREEN:
	unsigned int i,m;
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, GPIO_PIN_RESET); //LCD CHIP SELECT
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET); //SET LCD TO RESET

	for(i=0;i<319;i++)
		{
	    for(m=0;m<479;m++)
	    {
				ILI9488_SendData((0x07FF>>8)&0xF8);//RED
				ILI9488_SendData((0x07FF>>3)&0xFC);//GREEN
				ILI9488_SendData(0x07FF<<3);//BLUE
			}
		}
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, GPIO_PIN_SET); //LCD CHIP SELECT
*/
  ILI9488_Init();
HAL_Delay(1000);
setRotation(1);
fillScreen(ILI9488_WHITE);

   uint16_t touchX = 0, touchY = 0;


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	//
	  /*fillScreen(ILI9488_NAVY);
	  HAL_Delay(300);
	   	    	    fillScreen(ILI9488_BLUE);
	   	   	  HAL_Delay(300);
	   	    	    fillScreen(ILI9488_DARKGREEN);
	   	   	  HAL_Delay(300);
	   	    	    fillScreen(ILI9488_MAROON);
	   	   	  HAL_Delay(300);
	   	    	    fillScreen(ILI9488_PURPLE);
	   	   	  HAL_Delay(300);
	   	    	    fillScreen(ILI9488_OLIVE);
	   	   	  HAL_Delay(300);
	   	    	    fillScreen(ILI9488_LIGHTGREY);
	   	   	  HAL_Delay(300);
	   	    	    fillScreen(ILI9488_GREEN);
	   	   	  HAL_Delay(300);
	   	    	  fillScreen(ILI9488_NAVY);
	   	 	  HAL_Delay(300);
	   	    	    	    fillScreen(ILI9488_BLUE);
	   	    	   	  HAL_Delay(300);
	   	    	    	    fillScreen(ILI9488_DARKGREEN);
	   	    	   	  HAL_Delay(300);
	   	    	    	    fillScreen(ILI9488_MAROON);
	   	    	   	  HAL_Delay(300);
	   	    	    	    fillScreen(ILI9488_PURPLE);
	   	    	   	  HAL_Delay(300);
	   	    	    	    fillScreen(ILI9488_OLIVE);
	   	    	   	  HAL_Delay(300);
	   	    	    	    fillScreen(ILI9488_LIGHTGREY);
	   	    	   	  HAL_Delay(300);
	   	    	    	    fillScreen(ILI9488_GREEN);
	   	    	   	  HAL_Delay(300);
	   	    	    	  fillScreen(ILI9488_NAVY);
	   	    	 	  HAL_Delay(300);
	   	    	    	    	    fillScreen(ILI9488_BLUE);
	   	    	    	   	  HAL_Delay(300);
	   	    	    	    	    fillScreen(ILI9488_DARKGREEN);
	   	    	    	   	  HAL_Delay(300);
	   	    	    	    	    fillScreen(ILI9488_MAROON);
	   	    	    	   	  HAL_Delay(300);
	   	    	    	    	    fillScreen(ILI9488_PURPLE);
	   	    	    	   	  HAL_Delay(300);
	   	    	    	    	    fillScreen(ILI9488_OLIVE);
	   	    	    	   	  HAL_Delay(300);
	   	    	    	    	    fillScreen(ILI9488_LIGHTGREY);
	   	    	    	   	  HAL_Delay(300);
	   	    	    	    	    fillScreen(ILI9488_GREEN);
	   	    	    	   	  HAL_Delay(300);
	   	    	    fillRect(0, 10, 480, 10, ILI9488_BLUE);
	   	   	  HAL_Delay(300);
	   	    	    fillRect(0, 40, 480, 10, ILI9488_DARKGREEN);
	   	   	  HAL_Delay(300);
	   	    	    fillRect(0, 60, 480, 10, ILI9488_MAROON);
	   	   	  HAL_Delay(300);
	   	    	    fillRect(0, 80, 480, 10, ILI9488_PURPLE);
	   	   	  HAL_Delay(300);
	   	    	    fillRect(0, 100, 480, 10, ILI9488_OLIVE);
	   	   	  HAL_Delay(300);
	   	    	    fillRect(0, 120, 480, 10, ILI9488_LIGHTGREY);
	   	   	  HAL_Delay(300);
	   	    	    fillRect(0, 140, 480, 10, ILI9488_BLUE);
	   	   	  HAL_Delay(300);
	   	    	    fillRect(460, 220, 20, 100, ILI9488_BLUE);
	   	   	  HAL_Delay(300);*/


	  char buf[20];
	  char buf1[20];
	  	  //LCD_Font(25, 25, buf1, _Open_Sans_Bold_24  , 1, ILI9488_WHITE);
	  	  //void LCD_Font(uint16_t x, uint16_t y, const char *text, const GFXfont *p_font,
      //uint8_t size, uint32_t color24) {
	  	  //void ILI9488_printText(char text[], int16_t x, int16_t y, uint16_t color, uint16_t bg, uint8_t size)
	  	  ILI9488_printText(buf1, 25, 25, ILI9488_WHITE, ILI9488_WHITE, 1);
	  	  touchX = getX();
	  	  touchY = getY();
	  	  sprintf(buf,"x=%3d y=%3d",touchX,touchY);
	  	  sprintf(buf1,"x=%3d y=%3d",touchX,touchY);
	  	  //LCD_Font(25, 25, buf, _Open_Sans_Bold_24  , 1, ILI9488_BLACK);
	  	  ILI9488_printText(buf1, 25, 25, ILI9488_BLACK, ILI9488_BLACK, 1);
	  	  fillRect(touchX, touchY,5,5, ILI9488_RED);
	  	  //HAL_Delay(1000);




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

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 60;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 7;
  hspi2.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi2.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * @brief SPI3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI3_Init(void)
{

  /* USER CODE BEGIN SPI3_Init 0 */

  /* USER CODE END SPI3_Init 0 */

  /* USER CODE BEGIN SPI3_Init 1 */

  /* USER CODE END SPI3_Init 1 */
  /* SPI3 parameter configuration*/
  hspi3.Instance = SPI3;
  hspi3.Init.Mode = SPI_MODE_MASTER;
  hspi3.Init.Direction = SPI_DIRECTION_2LINES;
  hspi3.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi3.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi3.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi3.Init.NSS = SPI_NSS_SOFT;
  hspi3.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
  hspi3.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi3.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi3.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi3.Init.CRCPolynomial = 7;
  hspi3.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi3.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI3_Init 2 */

  /* USER CODE END SPI3_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(NSS_GPIO_Port, NSS_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, TFT_CS_Pin|TFT_DC_Pin|TFT_RST_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : NSS_Pin */
  GPIO_InitStruct.Pin = NSS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(NSS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : TFT_CS_Pin TFT_DC_Pin TFT_RST_Pin */
  GPIO_InitStruct.Pin = TFT_CS_Pin|TFT_DC_Pin|TFT_RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
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
  __disable_irq();
  while (1)
  {
  }
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */