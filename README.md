# PlayStation Vita port of Plumbers Don't Wear Ties - SDL2 (https://github.com/MaikelChan/PlumbersDontWearTies-SDL)

## Description 
Plumbers Don't Wear Ties is an adult-oriented "romantic comedy" visual novel/dating sim developed by United Pixtures and published by Kirin Entertainment for the 3DO Interactive Multiplayer. Although the game did have a DOS version, it had very limited distribution and was published by United Pixtures itself. The game stars Edward J. Foster and Jeanne Basone as John and Jane, respectively; two people who are being pressured by their respective parents to go out and find a spouse. The player's task is to get John and Jane together. 

## Install
Install PlumbersDontWearTies.vpk to your Vita.

Plumbers Don't Wear Ties requires the original data files from the PC version of the game.

Copy all the folders included in the PC version (SC1, SC2, SC3...), and GAME.BIN and SHOWTIME.EXE files into "ux0:data/PlumbersDontWearTies".

## Controls
- △ - Select first option in a choice selection screen
- □ - Select second option in a choice selection screen
- × - Select third option in a choice selection screen
- SELECT - Exit the game
- D-Pad right - Advance to the next picture

Thank you very much to MaikelChan for making the original implementation, I started this port to learn a bit about how the Vita works and to have some fun in the meantime.

# Plumbers Don't Wear Ties - SDL2 - Original README

This project is my own implementation of the game `Plumbers Don't Wear Ties` written from scratch, that is, the original program has not been decompiled or reverse-engineered. However, the game still needs the assets from the original PC version to run. The only thing that has been reverse-engineered is the `GAME.BIN` file, done by [Daniel Marschall](https://misc.daniel-marschall.de/spiele/plumbers/?page=pc_gamebin), which contains information about the scenes, background images, sounds and sequences of events.

This game is infamous for being considered one of the worst games ever made. The 3DO version is much more known (relatively speaking), but there was also a very rare Windows version released in 1993. Due to being 16bit, it can't be run on modern PCs.

This is the current state of the project:

- It has been tested and works fine on Windows and Linux.
- It could still contain some small bugs here and there that I haven't catched up yet.
- It can be played with a keyboard or an XInput compatible controller.
- Rendering, audio and input are implemented with SDL2.
- Window can be resized to any arbitrary dimensions and set to borderless fullscreen.
- It is possible to advance to the next picture to progress quickly through the game.

## How to build

You will need [CMake](https://cmake.org) to build the project.

### Windows with Microsoft Visual C++ Compiler

1. Download the latest version of [SDL2 development library (Visual C++ 32/64-bit)](https://www.libsdl.org/download-2.0.php).
2. Download the latest version of [SDL2_ttf development library (Visual C++ 32/64-bit)](https://www.libsdl.org/projects/SDL_ttf/).
3. Create a `SDL2` folder at the root of the project.
4. Place the `lib` and `include` folders of both libraries into the `SDL2` folder.
5. Configure and build with CMake. After a successful build, the game will appear in the `bin` folder along with a `Data` folder and a `Font.ttf` inside.

### Ubuntu and other Debian based Linux distros

1. Install the required dependencies: `sudo apt install build-essential cmake libsdl2-dev libsdl2-ttf-dev`.
2. Configure and build with CMake. After a successful build, the game will appear in the `bin` folder along with a `Data` folder and a `Font.ttf` inside.

## How to run

1. Put all the assets and folders of the original PC version of the game into the `Data` folder that is located along with the game's executable.

## How to play

| Keyboard    | Controller | Action                                            |
|-------------|------------|---------------------------------------------------|
| 1           | X          | Select first option in a choice selection screen  |
| 2           | Y          | Select second option in a choice selection screen |
| 3           | B          | Select third option in a choice selection screen  |
| Right Arrow | DPad Right | Advance to the next picture                       |
| Alt+Enter   | Start      | Toggle fullscreen                                 |
| Esc         | Back       | Exit the game                                     |

## Screenshots

<p align="center">
  <img title="Plumbers Don't Wear Ties screenshot" src="/screenshot00.png">
  <img title="Plumbers Don't Wear Ties screenshot" src="/screenshot01.png">
  <img title="Plumbers Don't Wear Ties screenshot" src="/screenshot02.png">
  <img title="Plumbers Don't Wear Ties screenshot" src="/screenshot03.png">
  <img title="Plumbers Don't Wear Ties screenshot" src="/screenshot04.png">
</p>
