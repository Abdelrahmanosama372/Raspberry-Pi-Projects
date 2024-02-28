# MQTT_LED_Control

MQTT_LED_Control is a project that allows you to control the state of an LED on your Raspberry Pi from your laptop using MQTT (Message Queuing Telemetry Transport) protocol. You can publish the state of the LED from your laptop to switch it on or off remotely.

## Setup

1. Install MQTT broker on your Laptop (e.g., Mosquitto).

2. Ensure your Raspberry Pi and laptop are connected to the same network.

3. Clone this repository to your laptop:

    ```bash
    git clone https://github.com/Abdelrahmanosama372/MQTT_LED_Control.git
    ```

4. Install the necessary MQTT client library on your laptop (e.g., paho.mqtt.cpp).

## Usage

1. Start the MQTT broker on your Laptop.

2. compile and execute the `main.cpp` code on your laptop to publish the state of the LED:

    ```bash
    g++ publisher.cpp -lpaho-mqttpp3 -lpaho-mqtt3as -o publisher
    ./publisher
    ```
3. enter the led state `on || off` on the terminal to be published and `quit` to close the communication

4. The LED on your Raspberry Pi will switch on or off based on the state published by the publisher code.

## Configuration

- Modify the MQTT broker address in the `raspberryPi_client/subscriber.hpp` code to match your setup.
- Modify the led brightness file in raspberryPi_client/subscriber.cpp to match your setup.

## Contributing

Contributions are welcome! If you have any ideas for improvement or bug fixes, feel free to open an issue or submit a pull request.

