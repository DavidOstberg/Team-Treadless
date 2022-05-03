# Team-Treadless
Team members: Beatriz de Castro Diez, Can Yang, David Östberg, Leo Zuckerman
(Goal Sprint 2: CAN reader and Input Handler.)
## Working area
| Applications  | Team member         |
| ------------- |:-------------:|
| Input Handler | Can Yang |
| CAN Reader    | David Östberg      |
| Emulator | Beatriz de Castro Diez, Leo Zuckerman |

## Project description
One executable receiving  user input transmitting CAN messages.
one executable with at least two thread:
- one reading  CAN data
- emulation


## User cases


## Emulation Functions

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
