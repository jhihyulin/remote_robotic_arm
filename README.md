# remote_robotic_arm

⚠⚠⚠ IN PROGRESS ⚠⚠⚠

A simple remote-controlled robotic arm controlled by a joystick and servo motors.

## BOM

| Materials | Quantity | Remarks |
| --- | --- | --- |
| Arduino Nano | 2 | |
| nRF24L01 | 2 | |
| SG90 Servo Motor | 6 | or any other servo motor
| Joystick | 2 | |
| 10k Ohm Resistor | 2 | pull-up resistor for joystick button |
| 10k Ohm Potentiometer | 2 | |
| Type C socket | 2 | if your nano not Type-C interface |
| 100uF Capacitor | 2 | > 6.3V |
| popsicle stick | | or any other strong material |
| wires | | |
| pin headers | | |

## Circuit

### Controller
![](/control/control.svg)

### Receiver
![](/remote/remote.svg)

## Credits
> [Simple and Cheap Radio Control Making for RC Models. DIY RC](https://www.rcpano.net/2020/02/17/simple-and-cheap-radio-control-making-for-rc-models-diy-rc)
