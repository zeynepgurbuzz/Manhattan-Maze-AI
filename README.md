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

```

### Execution

**On macOS / Linux:**

```bash
./game

```

**On Windows:**

```bash
game.exe

```

## 🕹️ Controls

* `W`: Move Up
* `A`: Move Left
* `S`: Move Down
* `D`: Move Right

## 🧠 Algorithm: Manhattan Distance

In Hard Mode, the police calculate the distance to the thief using the formula:|x2 - x1| + |y2 - y1|
It then chooses the move that minimizes this distance to trap the player.

## 📝 License

This project is open source and available under the [MIT License](https://www.google.com/search?q=LICENSE).
