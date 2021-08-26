# 2048 for curses

A 2048 written using curses (ncurses, or any modern curses library).

**Example:**

![sample](https://user-images.githubusercontent.com/41715288/130339024-c968314e-2827-4399-b42c-98c507148409.png)
![gif-sample](https://user-images.githubusercontent.com/41715288/130892098-862cb649-b989-4aad-88a7-e330f85681e7.gif)

## How to play

Use the arrow keys to move the squares under game's grid,
the objective is to sum squares with same value.

You lose when there is no legal move.

## Installing

Clone the repositore (with submodules)

> git clone --recurse-submodules https://github.com/1chard/2048.git

Then, build it and run it

> cmake .

> make

> ./2048curses or 2048curses
