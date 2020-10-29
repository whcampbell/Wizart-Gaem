# Wizart Gaem

## Table of Contents
+ [About](#about)
+ [Getting Started](#getting_started)
+ [Usage](#usage)

## About <a name = "about"></a>
Wizart Gaem is a 2d top down rogue lite action game where the player takes the role of a wizard battling off hordes of monsters in a procedurally generated map.

## Getting Started <a name = "getting_started"></a>
Pull the project to a folder of your choice, then follow the system installation instructions for your OS

### Prerequisites

Windows:
You will need the following to compile wizart-gaem on your system (eventually a release will be available which should run natively on windows or mac)
 1. MinGW
 2. g++ compiler version 9.2.0+
 3. a linux shell (git bash works)
 
 Mac:
 You will need the following to compile wizart-gaem on your system (eventually a release will be available which should run natively on windows or mac)
 1. XCode version 11.0+
 2. g++ compiler version 9.2.0+

### Installing

Windows
1. Navigate to the build/build_win directory
2. Open your linux shell of choice
3. run mingw32-make
4. run the generated game.exe file

Mac
1. Navigate to the build/build_mac directory
2. Open your command shell of choice
3. run make
4. run the generated game file

## Usage <a name = "usage"></a>

The game is built on the knapsack++ engine. the relevant files for this can be found in the root headers folder, as well as src/engine.
