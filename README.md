Required Elements
1.ESP32 Boards: Two ESP32 development boards are required. One such example is the ESP32 DevKit V1.
2.Microphones: Two electret microphone modules, such as the MAX4466 series, are needed. These are going to record audio.
3. Speaker: To output the voice data that has been communicated, a speaker will be attached to the second ESP32 board.
4. Bluetooth Communication Modules: Bluetooth modules are usually included into ESP32 boards. Make sure they are correctly configured and activated.
5.Power Supply: Make sure the ESP32 boards and accessories have access to a reliable power source. Depending on your configuration, this could be a USB connection or batteries.

Hardware Attachments

Microphone Connection: Attach the microphone to the ESP32-A. Three pins are normally present on the MAX4466 module: VCC, GND, and OUT.
- Attach the microphone's VCC to an ESP32-A output pin that is either 3.3V or 5V.
- Attach the microphone's GND to the ESP32-A's ground pin (GND).
- Attach the microphone's OUT pin to the ESP32-A's analog input pin (A0, for example).

Bluetooth Setup: - Make use of the ESP32's integrated Bluetooth module.
- Configure the Bluetooth Low Energy (BLE) service to be advertised by the ESP32-A. This entails setting up a BLE server with the ability to transmit microphone data and initializing the BLE stack.

Power: - Make sure there is enough current for the microphone and the ESP32 by powering the ESP32-A with a reliable power source.

 Connection of the Speaker: - Attach the speaker to the ESP32-B.
- Generally, a PWM pin or the output of a digital-to-analog converter (DAC) can be used to control speakers. Make sure the selected method can drive your speaker.
- Attach the positive terminal of the speaker to the ESP32-B's DAC or PWM pin (such as the DAC pin or any other pin that can handle PWM, such GPIO25).
- Attach the negative terminal of the speaker to an ESP32-B ground pin (GND).

Bluetooth Setup: - Configure the ESP32-B to function as a BLE client in order to establish a connection with ESP32-A. - Establish a connection with the stated BLE service and feature of ESP32-A in order to obtain microphone data.

Power: - Use an appropriate power source, much as the ESP32-A, to power the ESP32-B.

Software Synopsis

ESP32 (ESP32-A) sender: - Turn on Bluetooth and broadcast a- Take in analog information from the mic.
- Send ESP32-B microphone data over Bluetooth.

ESP32 Receiver (ESP32-B) - Turn on Bluetooth and establish a connection to the BLE service that ESP32-A has advertised.
- Use Bluetooth to receive microphone data from the ESP32-A.
- Handle incoming data (speech filtering implementation is optional).
Provide the speaker with processed data output.

Remarks

- voice Filtering: Machine learning models or signal processing techniques are used to construct a filter that transmits human voice alone. Further processing of the ESP32-B's received microphone data is necessary for this phase.

- Testing and Debugging: During development, use serial communication (Serial.print commands) to track data flow and debug issues.

You may use two ESP32 boards with Bluetooth communication to set up a real-time speech transfer system by following these instructions and making the necessary connections. Changes can be required depending on particular ESP32 board models and
