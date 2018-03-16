# AutoBalanceBot
An "Auto balancing robot" project using TM4C123G launchpad, MPU6050, L298N and DC encoder motors

## Coding convention
1. Variable name:
   - Starting character -> Non-capital (ex: mySpeed)
2. Function name:
   - Starting character -> capital (ex: SpeedCalc)
3. Constant name:
   - All letters -> capital (ex: SET_SPEED)
4. File name:
   - All letters -> capital (ex: I2C.h, MPU6050.c) (except main.c & include.h)
5. Commenting:
   - Function: [link1](http://www.edparrish.net/common/cppdoc.html#functioncomment), [link2](https://www.drupal.org/project/drupal/issues/711918).

## Modules included:
1. MPU6050
  - I2C (2 pins: PA6, PA7)
  - DMP
  - Complementary filter
  - Kalman filter

2. Motors
   - Motor control (L298N):
     - PWM speed control (2 pins: PB6, PB7)
     - Direction control (4 pins: PE1-PE4)
   - Speed reading (Incremental encoders)
     - QEI (2 pins: PD6, PD7)

3. PID control

