# Optogenetics Project

## Overview

This project involves developing a system for optogenetic stimulation and data collection in a research lab setting. The project consists of two main components:

1. **Arduino-based Control System**: Controls the optogenetic stimulation and collects data from the experiment.
2. **Graphical User Interface (GUI)**: Provides an interface for researchers to interact with the system, visualize data, and control the experiment.

## Arduino Sketch: GUI_recieve_char_arry.ino

The Arduino sketch `GUI_recieve_char_arry.ino` is responsible for receiving and processing character arrays from the GUI to control the optogenetic system.

### Functionality:
- Receives data from a computer or external device via serial communication.
- Processes the received character arrays to control various outputs like LEDs or other stimulation devices.
- Provides real-time feedback to the GUI for monitoring purposes.

### Key Features:
- Real-time communication with GUI.
- Efficient handling of serial data to ensure smooth experiment operation.

## How to Use

### Prerequisites
- **Hardware**: Arduino board (e.g., Arduino Uno or similar), optogenetic stimulation setup.
- **Software**: Arduino IDE.

### Uploading the Sketch
1. Open `GUI_recieve_char_arry.ino` in the Arduino IDE.
2. Connect your Arduino board and select the correct port.
3. Click **Upload** to upload the sketch to your Arduino.

### Running the GUI
1. After uploading the sketch, launch the GUI software (provide details about the GUI part).
2. The Arduino will communicate with the GUI via serial, allowing you to control the optogenetic setup in real-time.

## Project Structure

- **/GUI_recieve_char_arry.ino**: Arduino sketch controlling the optogenetic system.
- **/GUI**: Folder containing the GUI files (insert file paths if applicable).
- **/docs**: Documentation and user manual for the project.

## Future Work

- Improve the GUI for enhanced data visualization.
- Integrate additional sensors for real-time feedback.
- Create frequency and independent well functionality


