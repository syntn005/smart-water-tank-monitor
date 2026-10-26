
# Smart Water Tank Level Monitoring and Overflow Prevention

An Arduino-based project that monitors water levels and demonstrates
automatic pump control and overflow alerts using an HC-SR04 ultrasonic
sensor, LEDs, and a buzzer.

## Features

- 120 cm tank-height configuration
- Ultrasonic distance calculation
- Automatic pump control logic
- Pump ON at or below 20%
- Pump OFF at or above 90%
- Green and red level indicators
- Buzzer alarm at or above 90%
- Simulation mode for automatic filling and draining
- Serial Monitor output

## Components

- Arduino Uno
- HC-SR04 ultrasonic sensor
- Three LEDs with 220-ohm resistors
- Piezo buzzer
- Breadboard and jumper wires

For a physical pump, a suitable relay or MOSFET driver and a separate
power supply are also required.

## Wiring

| Component | Arduino connection |
|---|---|
| HC-SR04 VCC | 5V |
| HC-SR04 GND | GND |
| HC-SR04 TRIG | D9 |
| HC-SR04 ECHO | D10 |
| Pump indicator LED | D5 |
| Green LED | D6 |
| Red LED | D7 |
| Buzzer positive | D8 |
| LED cathodes and buzzer negative | GND |

Connect each LED through a 220-ohm resistor.

## How It Works

The HC-SR04 measures the time taken by an ultrasonic pulse to travel
to the water surface and return.

Distance is calculated using:

    distance = duration * 0.0343 / 2.0

Water level is calculated using:

    waterLevel = tankHeight - distance

The water-level percentage is:

    percentage = (waterLevel / tankHeight) * 100

The configured tank height is 120 cm. This value should match the
actual distance from the sensor's measuring face to the tank bottom.

## Pump Control

- At 20% or below, the pump status LED turns ON.
- At 90% or above, the pump status LED turns OFF.
- The red LED turns ON at 80%.
- The buzzer sounds at 90% or above.
- Between the pump thresholds, the previous pump state is maintained.

## Simulation and Real Hardware

The project supports two operating modes, selected using
`simulationMode` in the Arduino code.

### Simulation mode

Set:

    const bool simulationMode = true;

The program simulates water filling while the pump is ON and water
usage while the pump is OFF. It calculates a virtual sensor distance
from the simulated water level and applies the ultrasonic distance
formula.

This mode demonstrates the control logic in Tinkercad. The virtual
distance is calculated in software; it is not a measurement from the
physical ultrasonic sensor.

### Actual sensor mode

Set:

    const bool simulationMode = false;

The program triggers the HC-SR04, measures the echo duration, and
calculates the actual distance and water level. Water movement is
physical in this mode; the program does not artificially change the
water level.

Tinkercad does not automatically connect a software water-filling
simulation to the HC-SR04's virtual target.

## Running the Project

1. Open the circuit in Tinkercad or connect the physical components.
2. Open the Arduino code editor.
3. Copy `smart_water_tank.ino` into the editor.
4. Start the simulation or upload the sketch to the Arduino Uno.
5. Open the Serial Monitor at 9600 baud.
6. Observe the water-level percentage, distance, pump status, LEDs,
   and buzzer.

## Safety Notes

The pump indicator LED does not operate a physical pump. A real pump
must be connected through a suitable driver and power supply.

Keep electronics away from water. Use an independent overflow safeguard
and test the complete setup before unattended operation.

## Technology

- Arduino C++
- Ultrasonic sensing
- Embedded systems
- Tinkercad Circuits
