# "Pseudo-endless Simon" - CS50 Final Project (2023)

#### Video Demo: [Watch the project demo here](https://youtu.be/7UwS4w6dhZY?si=QWqQyInxGT6QXB5y)

#### Description:
The "Pseudo-endless Simon" game is an adaptation of the classic Simon game. In this game, players don't win after a certain number of rounds but instead continue playing until they make a mistake or fail to make a choice within a specified (in the code) time limit.

"The device creates a series of tones and lights and requires a user to repeat the sequence. If the user succeeds, the series becomes progressively longer and more complex. Once the user fails or the time limit runs out, the game is over." (--> source [Wikipedia: Simon (game)](https://en.wikipedia.org/wiki/Simon_(game)))

## Features:
- **Simon Game Mechanics:** The core mechanics of Simon are retained, where the game presents a sequence of colors or tones that the player must replicate.

- **Pseudo-Endless Gameplay:** The game doesn't have a fixed number of rounds. Instead, it continues indefinitely until the player makes a mistake or fails to respond within the time limit.

- **Mistake Detection:** The system accurately detects when a player makes a mistake in replicating the sequence, leading to the end of the game.

- **Time Limit:** To add an extra challenge, players must respond within a specific time limit for each turn. Failure to do so results in a mistake.

## Components Used:
- ELEGOO UNO R3 Board
- LEDs for different colors
- Buttons for player input
- Buzzer for audio feedback
- Solderless Breadboard
- Thinkpad T430 and necessary cables

## Setup Instructions:
1. **Install Arduino IDE:** Make sure you have the Arduino IDE installed on your computer.

2. **Connect Components:** Connect the LEDs, buttons, buzzer, and timing mechanism to the Arduino board according to the code specifications (or change the macros if needed). Connect your board to the computer.

3. **Upload Code:** Upload the provided Arduino code to the board using the Arduino IDE. Make sure you select the correct board in the IDE.

4. **Play!** Press any button to start!

## The code:
All the code is contained in the "simon.ino" file, which should be executed from the Arduino IDE. The code starts with macros for the pin numbers and some constant variables, for ease of access and modification should the wiring and settings be different in future implementations. Then, the color datatype is defined as a struct, in order to initialize the colors for each led light: blue, green, yellow, and red. I decided to make structs because then it is easier and more readable to access each element with its corresponding note and button. The notes chosen are almost arbitrary values within the buzzer's sound capabilities - I Just wanted them to be evenly separated and clearly distinguishable from one another.

The setup function is pretty straightforward.

The main loop calls for several custom functions for readability and simplification. The random seed is chosen after the user presses a button to start a game and not during setup, in order to make the sequence variable. In previous iterations, when the seed was set during setup, the sequence the device generated was the same every time.

## Future Improvements:
- Implement difficulty levels to increase the challenge as the game progresses.
- Include additional features such as customizable game modes or easter eggs (e.g: play a song if button is pressed long enough).
- Soldering it and turning the game into a console!

Feel free to contribute to the project and make it even more engaging!

