/*
 * userApp.c
 *
 *  Created on: Sep 18, 2024
 *      Author: G00397054@atu.ie
 */

#include "userApp.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

extern UART_HandleTypeDef huart1;
static void task1(void * pvParameters);
static void task2(void * pvParameters);


int _write(int file, char *ptr, int len) {
	HAL_UART_Transmit(&huart1, (uint8_t *)ptr, len, HAL_MAX_DELAY);
	return len;
}

void userApp(){
	printf("First RTOS Lab\r\n");
	if(xTaskCreate(task1, "Task 1", 100, NULL, 2, NULL)== pdPASS){
		printf("Task 1 created\r\n");
	}
	else{
		printf("ERROR: Failed to create task 1\r\n\n");
		while(1);
	}
	vTaskStartScheduler();
	while(1){

	}
}

static void task1(void * pvParameters){
	uint8_t x;
	printf("Task 1 Running...\r\n");
	while(1){
		printf("Task 1 Running...\r\n");
		for(x=0; x<10; x++){
			HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
		    vTaskDelay(pdMS_TO_TICKS(1000));
		}
		//Create task 2
		if(xTaskCreate(task2, "Task 2", 100, NULL, 1, NULL)== pdPASS){
				printf("Task 2 created\r\n");
		}
		else{
			printf("ERROR: Failed to create task 2\r\n\n");
			while(1);
		}

		//Suspend task 1
		vTaskSuspend(NULL);

	}
}

static void task2(void * pvParameters){
	uint8_t x;
	printf("Task 2 Running...\r\n");
	while(1){
		HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
		vTaskDelay(pdMS_TO_TICKS(200));
	}
}
