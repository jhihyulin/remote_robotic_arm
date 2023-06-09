# remote_robotic_arm

A simple remote-control robotic arm controlled by two joysticks and servo motors.

## BOM

| Materials | Quantity | Remarks |
| --- | --- | --- |
| Arduino Nano | 2 | |
| nRF24L01 | 2 | |
| SG90 Servo Motor | 5 | or any other servo motor
| Joystick | 2 | |
| 10kΩ Resistor | 2 | pull-up resistor for joystick button |
| 10kΩ Potentiometer | 2 | |
| Type-C socket | 2 | if your nano not Type-C interface |
| 100uF Capacitor | 2 | |
| Red LED | 1 | optional |
| 220Ω Resistor | 1 | optional with LED |
| Buzzer | 1 | optional |
| Popsicle Stick | | or any other strong material |
| Wires | | |
| Pin Headers | | |

## Circuit

### Controller
![](/control/control.svg)

### Receiver
![](/remote/remote.svg)

## Credits
> [Simple and Cheap Radio Control Making for RC Models. DIY RC](https://www.rcpano.net/2020/02/17/simple-and-cheap-radio-control-making-for-rc-models-diy-rc)
