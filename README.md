# Team-Treadless
Team members: Beatriz de Castro Diez, Can Yang, David Östberg, Leo Zuckerman

(Goal Sprint 1: Input Handler.)

(Goal Sprint 2: CAN reader and Input Handler.)

(Goal Sprint 3: Have the whole chain of communication from input handler to dashboard and have some functionalities on the UI.)

(Goal Sprint 4: Finalizing the features of the engine emulator. Prepare the final demo.)

# User manual

This repo includes three executables/binaries. And they are executed by one CMake.

Create a build folder: mkdir build

Go into build folder: cd build

Generate build files for the environment: cmake ..

Build executables and libraries: make

Run input handler(/Team-Treadless/build/App/InputHandler): ./inputHandler

Run emulator(/Team-Treadless/build/App/Emulator): ./emulator

Run avic(/Team-Treadless/build/App/Emulator): ./avic -c vcan1


s to start the engin, o to turn on the engin, g/d/p/r for gear leverl, 8 for acceleration and 2 for deceleration.

## Working area
| Applications  | Team member         |
| ------------- |:-------------:|
| Input Handler | Can Yang |
| CAN Reader    | David Östberg      |
| Emulator | Beatriz de Castro Diez, Leo Zuckerman |

## Project description
One executable receiving  user input transmitting CAN messages.
One executable with at least two thread:
- One reading  CAN data
- Emulation

One executable for the dashboard user interface.

keyboard input -> Input handler --vcan0--> CAN reader | Emulator --vcan1--> Dashboard

Two communiation chanel are used: vcan0 and vcan1.

## Input Hander
Keyboard mapping:

S- Start

O- stop

P- Gear in Park

R- Gear in Reverse

N- Gear in Neutral

D- Gear in Drive

8 (with numlock) - Acceleration

2 (with numlock) - Deceleration


Input handler is sending the CAN frame with ignition status, Gear state and padle status to the CAN reader.
Ignition status, Gear state and padle status are captured by keyboard input as user operation.
Each CAN frame is three valid data and there are 5 reserved space for future needs.(Current design)

## CAN reader

CAN reader takes the raw data from input handler and convert to readable data.

The log format:

len 8 byte, id: 1, data: 00 00 00 00 00 00 00 00

Ignition: 0

Gear: 0

Throttle: 0


## User cases
Case  0: Enginer is off. No Ignition [0,0,0]

Case 1: Engine ON. Ignition  [1,0,0]

	Case 1.1: Parking - default - no throttle [1,0,0] Speed == 0, rmp != 0
	Case 1.2: Neutral - no throttle (==P)  [1,2,0]  Speed == 0, rmp != 0
	(Throttle != 0 && Speed !=0)
		Case 1.3.1: Gear 1 - reverse && drive  [1,1,!=0] && [1,3,!=0]
		Case 1.3.2: Gear > 1 - Drive [1,3,!=0]
	(Throttle == 0 && Speed > 0) hard stop

## Emulator Functions

Max speed = 300 km/h
Idle = 800 rpm

throttleRatio = maxSpeed / maxThrottle

speed = throttle * throttleRatio

|  Gear  | Speed (km/h) |      RMP      |
| ------ |:------------:|:-------------:|
|    N   |      0       |     0 -  800  |
|    1   |    0 -  60   |   800 - 4500  |
|    2   |   61 -  80   |  3136 - 4500  |
|    3   |   81 - 118   |  3109 - 4500  |
|    4   |  119 - 170   |  3147 - 4500  |
|    5   |  171 - 200   |  3780 - 4500  |
|    6   |  200 - 300   |  3000 - 4500  |

