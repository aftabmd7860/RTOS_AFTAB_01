
#include<stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/FreeRTOSConfig.h>
#include<freertos/task.h>
#include<freertos/queue.h>


TaskHandle_t task1Handle, task2Handle, task3Handle, task4Handle, task5Handle;
QueueHandle_t queueHanlde;
UBaseType_t QueueLength = 10;
UBaseType_t ItemSize = sizeof(int);

BaseType_t retQueueSend, retQueueReceive;
void Task1(void * parameter) 
{
    printf("Inside %s():\n", __FUNCTION__);

    // Block for 1000ms
    const TickType_t xDelay = 1000 / portTICK_PERIOD_MS;

    // For parameter
    configASSERT(((uint32_t *)parameter) == NULL);

    for(;;) 
    {
        printf("Task1 : running...\n");
        // To provide delay
        vTaskDelay(xDelay);
    }

    // To delete task
    vTaskDelete(task1Handle);
}

void Task2(void * parameter) 
{
    printf("Inside %s():\n", __FUNCTION__);

    // Block for 2000ms
    const TickType_t xDelay = 2000 / portTICK_PERIOD_MS;
    // For parameter
    configASSERT(((uint32_t *)parameter) == NULL);

    for(;;) 
    {
        printf("Task2 : running...\n");
        vTaskDelay(xDelay);
    }

    // To delete task
    vTaskDelete(task2Handle);
}

void Task3(void * parameter) 
{
    printf("Inside %s():\n", __FUNCTION__);

    // Block for 5000ms
    const TickType_t xDelay = 5000 / portTICK_PERIOD_MS;

    // For parameter
    configASSERT(((uint32_t *)parameter) == NULL);

    for(;;) 
    {
        printf("Task3 : running....\n");
        // To provide delay
        vTaskDelay(xDelay);
    }

    // To delete task
    vTaskDelete(task3Handle);
}

void Task4(void * parameter) 
{
    int num = 0;

    printf("Inside %s():\n", __FUNCTION__);

    // For parameter
    configASSERT(((uint32_t *)parameter) == NULL);

    for(;;) 
    {
        retQueueSend = xQueueSend(queueHanlde, (const void *)&num, pdMS_TO_TICKS(1000));
        if(retQueueSend == errQUEUE_FULL) {
            perror("error in QueueSend : ");
            exit(EXIT_FAILURE);
        }
        else if(retQueueSend == pdTRUE) {
            printf("Data sent : success\n");
            printf("Task-4 sent : data : %d\n", num);
            num++;
            vTaskDelay(pdMS_TO_TICKS(2000));
        }
    }

    // To delete task
    vTaskDelete(task4Handle);
}

void Task5(void * parameter) 
{
    int num = 0;

    printf("Inside %s():\n", __FUNCTION__);

    // For parameter
    configASSERT(((uint32_t *)parameter) == NULL);

    for(;;) 
    {
        retQueueReceive = xQueueReceive(queueHanlde, &num, portMAX_DELAY);
        if(retQueueReceive == pdFALSE) {
            perror("error in Message Queue Receive: \n");
            exit(EXIT_FAILURE);
        }
        else if (retQueueReceive == pdTRUE) {
            printf("Data receive : success\n");
            printf("Task-5 received : data : %d\n", num);
            vTaskDelay(pdMS_TO_TICKS(2000));
        }
    }

    // To delete task
    vTaskDelete(task5Handle);
}




void app_main()
{
    BaseType_t task1Return, task2Return, task3Return, task4Return, task5Return;

    printf("Inside %s() function:\n", __FUNCTION__);

    
    queueHanlde = xQueueCreate(QueueLength,ItemSize);
    if(queueHanlde == NULL) {
        perror("error in Message Queue : ");
        exit(EXIT_FAILURE);
    }
    printf("Message Queue : Created\n");


    
    task1Return = xTaskCreate(Task1, "Task1", 2048, NULL, 5, &task1Handle);
    if(task1Return != pdPASS) {
        perror("error in task1 ");
        exit(EXIT_FAILURE);
    }
    printf("Task1 : created\n");

    task2Return = xTaskCreate(Task2, "Task2", 2048, NULL, 6, &task2Handle);
    if(task2Return != pdPASS) {
        perror("error in task2 ");
        exit(EXIT_FAILURE);
    }
    printf("Task2 : created\n");

    task3Return = xTaskCreate(Task3, "Task3", 2048, NULL, 7, &task3Handle);
    if(task3Return != pdPASS) {
        perror("error in task3 ");
        exit(EXIT_FAILURE);
    }
    printf("Task3 : created\n");

    task4Return = xTaskCreate(Task4, "Task4", 2048, NULL, 8, &task4Handle);
    if(task4Return != pdPASS) {
        perror("error in task4 ");
        exit(EXIT_FAILURE);
    }
    printf("Task4 : created\n");

    task5Return = xTaskCreate(Task5, "Task5", 2048, NULL, 9, &task5Handle);
    if(task5Return != pdPASS) {
        perror("error in task5 ");
        exit(EXIT_FAILURE);
    }
    printf("Task5 : created\n");

}