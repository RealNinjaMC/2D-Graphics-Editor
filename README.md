# 2D Graphics Editor in C

A terminal-based 2D graphics editor built in C using only characters. The editor keeps the drawing in a fixed-size 2D character array, uses `_` for empty space, and uses `*` to draw shapes on the canvas.

This project was created as a mini project for practicing core C programming concepts such as arrays, structures, functions, input handling, and simple graphics algorithms.

## Overview

The program provides a small interactive editor where users can create and manage basic shapes on a text canvas. Instead of drawing directly once and losing track of the shape, each object is stored in an object list. When the picture changes, the canvas is cleared and rebuilt from the saved objects.

This approach makes delete and modify operations cleaner because old pixels are removed automatically during redraw.

## Features

- Draw lines, rectangles, circles, and triangles.
- Add multiple objects to the same picture.
- Delete existing objects by object number.
- Modify an existing object by re-entering its values.
- List all active objects in the drawing.
- Clear the complete picture.
- Display the canvas at any time.
- Ignore out-of-bounds pixels safely instead of crashing.

## How It Works

The editor uses a 25 x 60 canvas:

- `_` represents an empty cell.
- `*` represents a drawn pixel.
- `canvas[ROWS][COLS]` stores the visible picture.
- `GraphicObject objects[MAX_OBJECTS]` stores all shapes added by the user.

The main drawing flow is:

1. User adds, deletes, or modifies an object.
2. The program clears the canvas.
3. All active objects are drawn again.
4. The updated picture is displayed.

This keeps the visual canvas and object data consistent.

## Supported Shapes

| Shape | Input Values |
| --- | --- |
| Line | Start point and end point |
| Rectangle | Top-left point, width, and height |
| Circle | Center point and radius |
| Triangle | Three corner points |

## Project Structure

```text
.
├── main.c          # Main editor source code
├── test_editor.c   # Simple automated tests for drawing functions
├── README.md       # Project documentation
└── .gitignore      # Ignores generated build files
```

## Build

Use GCC to compile the editor:

```powershell
gcc main.c -o editor.exe
```

## Run

```powershell
.\editor.exe
```

After running, choose an option from the menu:

```text
1. Add object
2. Delete object
3. Modify object
4. List objects
5. Clear picture
6. Display picture
0. Exit
```

## Testing

The repository includes a small test program for the core drawing functions. These tests check that the canvas clears correctly and that each shape places expected `*` characters on the canvas.

Build and run the tests:

```powershell
gcc -Dmain=editor_main -c main.c -o main_test.o
gcc test_editor.c main_test.o -o test_editor.exe
.\test_editor.exe
```

Expected output:

```text
All editor tests passed.
```

## Notes

- This is a terminal graphics project, not a GUI application.
- Coordinates use `x` for column and `y` for row.
- The top-left corner of the canvas is `(0, 0)`.
- Generated files such as `.exe` and `.o` are ignored by Git.

## Learning Goals

This project demonstrates:

- 2D character arrays in C.
- Struct-based object storage.
- Function-based program design.
- Basic shape drawing algorithms.
- Rebuilding output from stored data.
- Simple automated testing for C functions.

## Project Note

This repository was made as a Mini Project for Semester 2, CSE-F.
