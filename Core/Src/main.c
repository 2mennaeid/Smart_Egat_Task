
#include "main.h"
#include "config.h"
#include "cmsis_os.h"
#include "cJSON.h"
#include "TemperatureSensor.h"
#include "LDRSensor.h"
#include "Relay.h"

// Define Node IDs
#define TEMP_SENSOR_ID 0x80
#define LIGHT_SENSOR_ID 0x81
#define RELAY_ACTUATOR_ID 0x50

// UART Handler
extern UART_HandleTypeDef huart1;

// CMSIS-RTOS Task IDs
osThreadId uartTaskHandle;
osThreadId sensorTaskHandle;
osThreadId actuatorTaskHandle;

void uartTask(void const *argument);
void sensorTask(void const *argument);

uint32_t temp_sensor_data = 0;
uint32_t light_sensor_data = 0;
uint8_t relay_status = 0;

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    ADC1_Init();
    USART1_UART_Init();
    Relay_Init();
    LM35_Init();
    LDR_Init();

    /* Create Tasks using CMSIS-RTOS */
    osThreadDef(uartTask, uartTask, osPriorityNormal, 1, 256);
    osThreadDef(sensorTask, sensorTask, osPriorityNormal, 1, 256);

    uartTaskHandle = osThreadCreate(osThread(uartTask), NULL);
    sensorTaskHandle = osThreadCreate(osThread(sensorTask), NULL);

    /* Start Scheduler */
    osKernelStart();

    while (1)
    {
    }
}

void uartTask(void const *argument) {
    char rx_buffer[100];
    cJSON *root, *command, *nodeID, *data;

    for (;;) {
        receiveJSON(rx_buffer, sizeof(rx_buffer));

        root = cJSON_Parse(rx_buffer);
        if (root == NULL) {
            sendJSON("{\"error\":\"Invalid JSON\"}");
            continue;
        }

        command = cJSON_GetObjectItem(root, "command");
        nodeID = cJSON_GetObjectItem(root, "nodeID");
        data = cJSON_GetObjectItem(root, "data");

        if (command != NULL && nodeID != NULL) {
            int node_id = nodeID->valueint;
            if (strcmp(command->valuestring, "ENA") == 0) {
                if (node_id == TEMP_SENSOR_ID) {
                    temp_sensor_data = LM35_ReadTemperature();
                    sendJSON("{\"nodeType\":\"NS\",\"nodeID\":0x80,\"data\":\"DONE\"}");
                } else if (node_id == LIGHT_SENSOR_ID) {
                    light_sensor_data = LDR_ReadValue();
                    sendJSON("{\"nodeType\":\"NS\",\"nodeID\":0x81,\"data\":\"DONE\"}");
                } else if (node_id == RELAY_ACTUATOR_ID) {
                    Relay_SetState(1); // Turn on the relay
                    sendJSON("{\"nodeType\":\"NA\",\"nodeID\":0x50,\"data\":\"DONE\"}");
                }
            } else if (strcmp(command->valuestring, "ACT") == 0) {
                if (node_id == RELAY_ACTUATOR_ID) {
                    uint8_t relay_action = data->valueint;
                    Relay_SetState(relay_action);
                    sendJSON("{\"nodeType\":\"NA\",\"nodeID\":0x50,\"data\":\"DONE\"}");
                }
            } else if (strcmp(command->valuestring, "STA") == 0) {
                if (node_id == RELAY_ACTUATOR_ID) {
                    char relay_status_msg[50];
                    sprintf(relay_status_msg, "{\"nodeType\":\"NA\",\"nodeID\":0x50,\"data\":\"%d\"}", relay_status);
                    sendJSON(relay_status_msg);
                }
            } else if (strcmp(command->valuestring, "DUR") == 0) {
                // Implement logic for setting sensor reporting duration
                sendJSON("{\"nodeType\":\"NS\",\"nodeID\":0x80,\"data\":\"DONE\"}");
            }
        }
        cJSON_Delete(root);
        osDelay(100);  // Use CMSIS-RTOS osDelay
    }
}

void sensorTask(void const *argument) {
    for (;;) {
        char temp_msg[50];
        sprintf(temp_msg, "{\"nodeType\":\"NS\",\"nodeID\":0x80,\"data\":\"%d\"}", temp_sensor_data);
        sendJSON(temp_msg);

        char light_msg[50];
        sprintf(light_msg, "{\"nodeType\":\"NS\",\"nodeID\":0x81,\"data\":\"%d\"}", light_sensor_data);
        sendJSON(light_msg);

        osDelay(5000); // 5 seconds delay
    }
}
