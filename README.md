# Project Documentation: STM32 JSON Communication with FreeRTOS

## Project Overview
This project implements a communication system on an STM32 microcontroller capable of receiving and sending JSON messages. The messages are used to initialize, modify, or activate nodes such as sensors (temperature and light) and actuators (relay). The STM32 communicates via UART to a monitoring tool, allowing the user to send JSON commands and receive responses. The system operates under the FreeRTOS environment and leverages the cJSON library for JSON parsing and generation.

## System Requirements
- **Microcontroller:** STM32 (any variant supported by Proteus simulation)
- **Sensors:** Temperature and light sensors
- **Actuator:** Relay
- **Tools and Libraries:**
  - FreeRTOS
  - cJSON library
  - UART communication
  - Custom drivers for sensors, actuators, and UART
- **Development Environment:**
  - Eclipse IDE with GNU Arm Embedded Toolchain (or equivalent)
  - Proteus for circuit simulation

## Architecture and Design
### System Architecture
- **Nodes:**
  - **Sensor Nodes:** Read data from temperature and light sensors.
  - **Actuator Nodes:** Control a relay.
- **JSON Message Protocol:** Defines the commands and responses for communication.
- **RTOS Tasks:**
  - Task for UART communication (handling TX and RX buffers).
  - Tasks for managing sensor readings and actuator states.
- **Peripheral Drivers:** Custom drivers for UART, sensors, and actuators.

### JSON Message Format
#### Commands Sent to STM32:
- Enable Node: `{ "command": "ENA", "nodeID": <ID>, "data": NULL }`
- Disable Node: `{ "command": "DIS", "nodeID": <ID>, "data": NULL }`
- Activate Node: `{ "command": "ACT", "nodeID": <ID>, "data": <action> }`
- Status Request: `{ "command": "STA", "nodeID": <ID>, "data": NULL }`
- Set Duration: `{ "command": "DUR", "nodeID": <ID>, "data": <duration> }`

#### Responses from STM32:
- Sensor Reading: `{ "nodeType": "NS", "nodeID": <ID>, "data": <reading> }`
- Actuator Status: `{ "nodeType": "NA", "nodeID": <ID>, "data": <status> }`

### Task Flow
1. UART RX Task: Parses incoming JSON commands.
2. Sensor Node Tasks: Periodically read sensor data and send updates.
3. Actuator Node Task: Update actuator states based on commands.
4. UART TX Task: Sends JSON responses to the UART monitor.

## Functional Specifications
1. Enable or disable specific nodes via JSON commands.
2. Set sensor nodes to periodically send readings.
3. Control actuator nodes through commands.
4. Query the current status of any node.
5. Handle UART communication for JSON message parsing and generation.

## Setup and Installation
1. **Clone the Repository:**
   ```bash
   git clone <repository-url>
   ```
2. **Install Development Tools:**
   - Install keil uVision5,Eclips,STM32cub,Proutes IDE and set up the GNU Arm Embedded Toolchain.
   - Download and integrate FreeRTOS and cJSON libraries into the project.
3. **Open the Project:**
   - Import the project into Eclipse IDE.
4. **Compile and Flash:**
   - Build the project and flash the firmware to the STM32 microcontroller.
5. **Simulate Hardware:**
   - Open the Proteus simulation file and run the simulation.


### Bill of Materials (BOM)
| Component          | Quantity | Description               |
|--------------------|----------|---------------------------|
| STM32F103C8 MCU          | 1        | Microcontroller           |
| Temperature Sensor | 1        | LM35 sensor     |
| Light Sensor       | 1        | Tourch_LDR     |
| Relay Module       | 1        | Relay for actuator control|
| Resistors, NPN Transistor | Various | For circuit connections |
| UART Module        | 1        | UART interface for debug  |




