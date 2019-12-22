# Breakout

## Game Link

https://youtu.be/gsnn-xdFtl0
https://youtu.be/XFjIObBHblA

## Game description

  Breakout is an arcade game. In this game the player is represented by a paddle with a ball that jumps in a direction and his purpose is to destroy all the bricks to pass the level and eventually finish the game. While moving forward, the player will encounter various patterns. The difficulty will get higher with the level.

## Requirements

### Hardware

  For this project the hardware elements needed are : an 8x8 LED matrix used to display the game, an LCD used to view game menu, a joystick used for in-game movement and LCD control, a potentiometer used for LCD contrast, a button used to start or stop the LCD, a MAX7219 Driver, resistors and wires.
  
### Game specifications

* The score is the sum of the scores obtained at each level before you lose all of your lives.
* After each level the speed of the ball will increase and the size of the paddle will lower.
* We will have 3 levels with different patterns. The player starts with 3 lives and after he misses the ball he will lose 1 life.
* The highscore will be saved in EEPROM.

  The matrix will display an X after the game is over.
  This game like many others has it's own story.
  In a world where people's lives were controlled by computers through chips implanted in their brains, a guy named Keanu wakes up in a morning through a dream, unusual thing for these inhuman beings. From that moment his life changes radically because, a series of images appear in his mind, images that present not only him as a human, with his family and friends, but also the moment when everything was taken away from him, the moment when he became what he is now, a robot in a human body.
  Initially he doesn't lend much importance to this dream, but when he goes to work the boss comes to give him a new project and then he realizes that this man was his father from that dream. When he looked around, he noticed that many of the co-workers were people from that dream, but they, like him, didn't know about their previous lives.
  Therefore, Keanu realizes the cruel truth behind this new life and intends to free everyone from this cursed, controlled life by returning their memories. He starts to work in the dark, at a perfect plan that will restore everything to normal. After months of work, in which everything seemed impossible, he begins the operation in the evening, at the central tower, where he manages to infiltrate. Everything seemed to work perfectly, until he connects to the main chip, and reaches a virtual tunnel blocked by bricks. He has to clear the path if he wants to save the humanity.
  **It's your turn to help Keanu and save the day!**

### Documentation

  The player controls the paddle with the joystick, using the X axis. Specifying a direction, left or right, will make the player to move to that side and catch the ball and throw it and try to break the bricks. If he didn't catch the ball, will lose 1 life. If he loses all lives he will receive a message and will have an option to restart the game. If he ends all the levels he will receive from the one and olny, Keanu this message "You're breathtaking!". 

  The elements of hardware used for this game are : 
* a MAX7219 Driver
* Resistors
* Wires
* LCD Display
* 8x8 LED matrix
* Button
* Potentiometer
* Joystick

### LCD Display

* Play game - this option will start the game and will show on the screen the score and the lives of the player.
* HighScore - this option will display the highscore
* StartingLevel - this option will let you to choose the level from which will you play.
* LCDSettings - this option will let you to choose the contrast and the light for the LCD.
* Info - this option will show the credits.
  
  During the game we will display the lives and the score of the player.
  We can save the name of the player for a better understanding of the HighScore information.
  After the game finishes we will display the message "You're breathtaking!' if you complete all the levels and the message "Wake up samurai. We have a city to save." if you lose the game. If you make a highscore you will get this message "You are good, but not like Keanu".
  After these, we will get the second screen  where we will display a button for restart, another one for the initial menu and the score of the player.

## Schematic

  This is an example of how the pattern of the level can look.

![Schema](https://user-images.githubusercontent.com/49250412/70389462-43363100-19c8-11ea-9925-2c882e720dac.PNG)
