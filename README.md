# FaceTrackingNerfTurret

Creator: [Justin Mazon](https://github.com/JustintheBox)

## Project Description
 > * We all like gaming, and chess is a great game. It has a low skill floor and a very high skill ceiling: each piece is governed by simple rules, but their interactions come together to form a timeless experience with unrivaled depth.
  * What languages/tools/technologies do you plan to use? (This list may change over the course of the project):
    * C++
    * Git/Github for VCS and productivity management
    * Grid GUI
  * What will be the input/output of your project? What are the features that the project provides?
    * Input: The piece a player would like to use, the program will provide valid positions for that piece to move to
    * Output: The piece will move to the new position, the opponent's chess piece will react appropriately (if taken)
  * Features:
    * Graphical representation of board and pieces
    * Board updates in real time to reflect game-state
    * 2-player support, with potential of a CPU opponent for single-player
    * King, Queen, Bishop, Knight, Rook, Pawn, all programmed with their appropriate behaviors

## Phase II Class Diagram
 > ![Screenshot 2022-02-08 221550](https://user-images.githubusercontent.com/97067245/153135246-06b265cf-1af4-41b9-9b78-fa3437d49dbb.png)
 > Classes/Modules:
 > * Player
 >   * 2 players
 >   * Both players begin the game with the appropriate number of each piece
 >   * A player can only control their own pieces
 >   * A player can only move pieces during their turn
 >   * Each turn, players will choose a specific chess piece and a new location to move it to 
 > * Chess Piece
 >   * Each chess piece can move locations and capture other enemies. 
 >   * Each type of piece is a subtype: (Pawn, Bishop, Rook, Knight, King, Queen)
 >   * Each piece has a function that defines its appropriate attack/move behavior
 >     * Pawns can only move forward or in a diagonal direction if trying to capture an enemy
 >     * Bishops move diagonally
 >     * Knights move in an L direction and can jump over other pieces
 >     * Rooks can move horizontally and vertically
 >     * Kings can move in any direction one squuare at a time
 >     * Queens can move in any direction (vertically, horizontally, diagonally) so players will choose how she moves.
 >   * A piece may only perform valid moves (a piece should not be able to behave in unexpected ways)
 >    * We will check to see if the new position chosen is valid depending on how a piece moves.
 >    * Some chess pieces will have special moves and abilities like jumping, promotion, and castle.
 > * Chessboard
 >   * 8x8 grid of squares each of which can hold a chess piece 
 >   * Each square can contain only one piece at a time
 >    * New positions will be checked to see if a chess piece has already claimed that spot. If an enemy has claimed the spot, then it will be captured. If it is an ally, then player must choose a new location 
 > * Win/Exit Condition
 >   * The game ends when:
 >     * Either player's king is taken signifying checkmate 
 
 > ## Phase III
 > <img width="652" alt="Screen Shot 2022-02-23 at 3 20 44 PM" src="https://user-images.githubusercontent.com/97190825/155426126-9d4d2b4f-ec54-4f99-bc89-3316ea6072c7.png">

> For this new uml diagram, we implemented the strategy design pattern and the mediator design pattern.
>  * Strategy Pattern: We chose the strategy pattern because of how applicable it was to the behavioral relationship between the abstract piece class and its chess piece subclasses as each chess piece subclass will implement their own version of a function that the piece parent class contains. We are using this pattern to create the validMove function which ensures that the movements of each piece on the board are valid to that particular chess piece and do not break the established rules of the game. Using the strategy design pattern helps us write better code because we can have a more simplified implementation of how movement will be conducted in the game. Since general movement from one square to another will be done through the square class, we can use each chess piece subclass to just validate whether the movment is valid for that specific piece or not and as such, we only have to worry about how each subclass will implement their own version of the function.  

>  * Mediator Pattern: We chose the Mediator design pattern because it best shows the the general gameplay loop of our chess game through the relationsip between the two player objects, the gameboard, and the square class which functions as a mediator. We are using this design pattern to implement how the players interact with the board. Essentially, each player takes turns moving pieces with the help of the square class which is the mediator since it reflects the changes made by each player on the board by showing which squares have pieces and which do not. Using this design pattern improves our code because we can use the square class as a way to manage the complexity that comes with both players interacting with the board while using the player classes as input and output which is much simpler to design.    
 
 
 ## Final Class Diagram
 <img width="763" alt="Screen Shot 2022-03-09 at 5 18 32 PM" src="https://user-images.githubusercontent.com/97190825/157569193-7ec5cbc3-522c-4cbe-8219-8b5689498f69.png">
 
 >  * Changes:
 >  * We decided to get rid of the player class objects since it was easier to use main.cpp and the gameboard object to handle the turn based system and how players move their chess pieces
 >  * We moved several of the special chess moves over to the gameboard object since its easier to acess the actual board and check that the conditions of these special moves were met

 ## Screenshots
 Game initialized:
 
 ![chess 00](https://user-images.githubusercontent.com/97067245/157372701-473d2a9a-3afa-4cf5-83ba-6a63824f1f32.png)
 
 A few turns in:
 
 ![chess 01](https://user-images.githubusercontent.com/97067245/157372745-1b957fd2-31a6-4703-a351-c0dbecdd31c3.png)
 
 White commited REGICIDE:
 
 ![chess 02](https://user-images.githubusercontent.com/97067245/157372798-022f25ff-675f-48ec-9743-56ed5840a890.png)
 
 ## Installation/Usage
 * System Requirements:
   * Intended for use with Windows (7+):
   * Install folder needs to contain:
     * regicide.exe (simply run this to start the game)
     * assets/
     * SDL2.dll
 * Usage Instructions
   * Run “regicide.exe”
     * One instance of regicide.exe = one Chess game
   * 2 Players
     * Player 1 = White
       * Blue cursor glow
     * Player 2 = Black
       * Orange cursor glow
     * White ALWAYS goes first
   * Turns alternate back and forth after each player makes a move
   * Click on a piece to select it
     * It will glow green while selected, click it again to deselect it
     * With a piece selected, click on the desired destination tile to move to/attack
     * Pieces can only perform their standard moves/attacks
     * A player’s turn only passes when they perform a valid move
   * The game ends when either player’s King is killed, at which point the game no longer be interacted with
   * User can close the game at any time by X’ing out the window


 

