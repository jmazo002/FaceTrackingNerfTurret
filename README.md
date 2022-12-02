# Face Tracking Nerf Turret

Creator: [Justin Mazon](https://github.com/JustintheBox)

Demo Link w/ explaination: https://www.youtube.com/watch?v=0kSbqZipghE&ab_channel=JustinMazon

## Project Description
  * Fully automated nerf gun turret that will fire upon face detection using OpenCV. 
  * Languages/tools/technologies used:
    * C++
    * Python
    * OpenCV
    * Arduino UNO
    * Git/Github for VCS and productivity management
<img src="https://user-images.githubusercontent.com/83481452/205171275-f0455999-c66c-449a-a853-1e997c5dd0c6.jpg" width="500" height="500">

https://user-images.githubusercontent.com/83481452/205170020-60f8b6ae-90d7-4aab-88c6-258fce4be335.mp4

## Manual Mode
 - User controls Nerf Turret using joystick only (indicated by the blue LED)
 - Left on the joystick moves the nerf turret left on the x-plane
 - Left on the joystick moves the nerf turret left on the x-plane
 - Right on the joystick moves the nerf turret right on the x-plane
 - Down on the joystick moves the nerf turret up on the y-plane
 - Up on the joystick moves the nerf turret down on the y-plane
 - A press of the joystick button shoots the nerf gun
 
 ## Wireless Mode
 - User controls Nerf Turret using IR receiver and remote only (indicated by the yellow LED)
 - Left on the remote moves the nerf turret left on the x-plane
 - Left on the remote moves the nerf turret left on the x-plane
 - Right on the remote moves the nerf turret right on the x-plane
 - Down on the remote moves the nerf turret up on the y-plane
 - Up on the remote moves the nerf turret down on the y-plane
 - A press of the middle button shoots the nerf gun
 
 ##  Automatic Mode
 - No user control instead nerf gun points at face from webcam video (indicated by the white LED)
 - Arduino recievers coordinates from Python script on laptop
 - If face x is greater than middle then move arduino to the right
 - If face x is less than middle then move arduino to the left
 - If face y is greater than middle then move arduino down
 - If face y is less than middle then move arduino up
 - If face coordinates is within 50 pixels of the middle of video for at least 1.5 seconds, then shoot
    
## Hardware Components
* Computing
  * Laptop (for automatic mode only)
  * Elegoo UNO R3 microcontroller
* Analog Inputs
  * Logitech Webcam
  * IR Receiver and Remote
  * Joystick
  * Potentiometer
* Digital Outputs
  * (x2) MG996R Servo Motors
  * (x3) LEDs
  * 5V Relay

<img src="https://user-images.githubusercontent.com/83481452/205171283-12a78e34-b119-4305-b275-7c2ba47f16b5.jpg" width="500" height="500">
<img src="https://user-images.githubusercontent.com/83481452/205171288-a5a0afc5-5ddf-4baf-8820-95db6873afeb.jpg" width="800" height="500">


