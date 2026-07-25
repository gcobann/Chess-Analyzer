# ♟️ Chess-Analyzer

This project is a C++ application that analyzes the movement capability of queens and their interaction with obstacles on a dynamically generated chess board. It was developed to improve my competencies in **algorithm building**, **dynamic memory management**, and **file systems (I/O)** during my software engineering education.

## 🚀 Features

* **Dynamic Board Generation:** In every run, a board with random dimensions between 5x5 and 30x30 is generated.
* **Obstacle System:** Obstacles (X) randomly placed on the board realistically restrict the movement paths of the queens.
* **8-Way Movement Analysis:** All possible squares, including horizontal, vertical, and diagonal, are scanned for each queen.
* **File-Based Reporting:** 
  * Raw board data is saved to the `input.txt` file.
  * Detailed analysis results and the visualized board report are presented in the `output.txt` file.

## 🛠️ Technical Details

* **Memory Management:** 2D dynamic arrays were used, and appropriate `delete[]` operations were applied to prevent memory leaks.
* **Data Structures:** Custom `struct` structures were used for coordinate management.
* **Algorithm:** A direction-based scanning algorithm that tracks the movement paths of the queens until they hit an obstacle or the board boundary was developed.

## 💻 How to Run?

1. Clone the repo.
2. Open the project with **Visual Studio 2026**.
3. Compile and run the project.
4. You can generate a new board via the menu and examine the analysis results through the terminal/file.

## 📊 Sample Output View

```text
CHESS BOARD
Q - Queens
X - Obstacles
0 - Empty/Unreachable Cell
+ - Movable Area
---------------------------
| Q  +  +  X  0 |
| +  +  0  0  0 |
| +  0  +  0  0 |
| X  0  0  Q  + |
| 0  0  0  +  + |
---------------------------
```
