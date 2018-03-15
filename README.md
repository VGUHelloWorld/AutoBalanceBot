# AutoBalanceBot
An "Auto balancing robot" project using TM4C123G launchpad, MPU6050, L298N and DC encoder motors

Modules included:
-

1. MPU6050
  - I2C (2 pins: PA6, PA7)
  - DMP
  - Complementary filter
  - Kalman filter

2. Motors
  2.1 Motor control (L298N):
    - PWM speed control (2 pins: PB6, PB7)
    - Direction control (4 pins: PE1-PE4)
  2.2 Speed reading (Incremental encoders)
    - QEI (2 pins: PD6, PD7)

3. PID control

