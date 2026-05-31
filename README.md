# 2D Graphics Editor

Mini project in C that draws shapes on a 25 x 60 character canvas.

## Features

- Draw line, rectangle, circle, and triangle using `*`.
- Keep empty space as `_`.
- Add, delete, modify, list, and clear objects.
- Store picture in a 2D character array.
- Redraw from saved objects after every change.

## Build

```powershell
gcc main.c -o editor.exe
```

## Run

```powershell
.\editor.exe
```

## Test

```powershell
gcc -Dmain=editor_main -c main.c -o main_test.o
gcc test_editor.c main_test.o -o test_editor.exe
.\test_editor.exe
```
