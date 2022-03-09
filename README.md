<div align="center">
 <h1> Maze </h1>
 <img src="https://img.shields.io/badge/Language--lightgrey?style=for-the-badge&logo=C" alt="Python">
</div>

A maze solvers that solves given maze defined as a 2D array where the blocks are represented as `0` and open path is represented by ` `. `S` represents the starting point and `E` represents the ending point. The solution path is displayed using `X`. The flow of program to reach the ending point can be stored in a text file.

Example:
Let the given maze be:
<div align="center">

```
+-------------+
| S 0 0 0 0   |
|         0   |
|   0 0   0   |
|         0 0 |
|   0 0   0   |
|     0     E |
+-------------+
```
</div>

This will be passed as:
```c
{{'S', '0', '0', '0', '0', ' '},
 {' ', ' ', ' ', ' ', '0', ' '},
 {' ', '0', '0', ' ', '0', ' '},
 {' ', ' ', ' ', ' ', '0', '0'},
 {' ', '0', '0', ' ', '0', ' '},
 {' ', ' ', '0', ' ', ' ', 'E'}};
```
The solution will be displayed as:
<div align="center">

```
+-------------+
| S 0 0 0 0   |
| X       0   |
| X 0 0   0   |
| X X X X 0 0 |
|   0 0 X 0   |
|     0 X X E |
+-------------+
```
</div>
