# 🕵️‍♂️ Thief vs Police - C Maze Game

A terminal-based maze game developed in C where the player (Thief) tries to escape while avoiding the Police. Features intelligent enemy movement using the Manhattan Distance algorithm.

## 🎮 Features
* **Grid-Based Gameplay:** 16x16 maze layout with walls and obstacles.
* **Two Difficulty Levels:**
    * **Easy:** Police moves randomly.
    * **Hard:** Police uses **Manhattan Distance** algorithm to track and chase the player efficiently.
* **Cross-Platform:** Works on both Windows and macOS/Linux.
* **Interactive Controls:** Simple WASD movement.

## 🚀 How to Run

### Prerequisites
You need a C compiler (GCC) installed on your system.

### Compilation
Open your terminal/command prompt and run:
```bash
gcc game.c -o game
