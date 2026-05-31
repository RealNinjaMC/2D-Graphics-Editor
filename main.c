#include <stdio.h>
#include <stdlib.h>

#define ROWS 25
#define COLS 60
#define MAX_OBJECTS 50

#define SHAPE_LINE 1
#define SHAPE_RECTANGLE 2
#define SHAPE_CIRCLE 3
#define SHAPE_TRIANGLE 4

typedef struct {
    int active;
    int type;
    int x1;
    int y1;
    int x2;
    int y2;
    int x3;
    int y3;
    int width;
    int height;
    int radius;
} GraphicObject;

char canvas[ROWS][COLS];
GraphicObject objects[MAX_OBJECTS];
int objectCount = 0;

static void clearInput(void)
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
}

static int readInt(const char *prompt)
{
    int value;

    while (1) {
        printf("%s", prompt);
        if (scanf("%d", &value) == 1) {
            return value;
        }
        printf("Please enter a number.\n");
        clearInput();
    }
}

static void putPixel(int x, int y)
{
    /* Out of canvas points are ignored, so weird input cannot crash drawing. */
    if (x >= 0 && x < COLS && y >= 0 && y < ROWS) {
        canvas[y][x] = '*';
    }
}

void clearCanvas(void)
{
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            canvas[row][col] = '_';
        }
    }
}

void displayCanvas(void)
{
    printf("\n");
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            printf("%c", canvas[row][col]);
        }
        printf("\n");
    }
}

void drawLine(int x1, int y1, int x2, int y2)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int stepX = (x1 < x2) ? 1 : -1;
    int stepY = (y1 < y2) ? 1 : -1;
    int error = dx - dy;

    while (1) {
        putPixel(x1, y1);
        if (x1 == x2 && y1 == y2) {
            break;
        }

        int doubleError = 2 * error;
        if (doubleError > -dy) {
            error -= dy;
            x1 += stepX;
        }
        if (doubleError < dx) {
            error += dx;
            y1 += stepY;
        }
    }
}

void drawRectangle(int x, int y, int width, int height)
{
    if (width <= 0 || height <= 0) {
        return;
    }

    int right = x + width - 1;
    int bottom = y + height - 1;

    drawLine(x, y, right, y);
    drawLine(x, bottom, right, bottom);
    drawLine(x, y, x, bottom);
    drawLine(right, y, right, bottom);
}

static void drawCirclePoints(int cx, int cy, int x, int y)
{
    putPixel(cx + x, cy + y);
    putPixel(cx - x, cy + y);
    putPixel(cx + x, cy - y);
    putPixel(cx - x, cy - y);
    putPixel(cx + y, cy + x);
    putPixel(cx - y, cy + x);
    putPixel(cx + y, cy - x);
    putPixel(cx - y, cy - x);
}

void drawCircle(int cx, int cy, int radius)
{
    if (radius < 0) {
        return;
    }

    int x = radius;
    int y = 0;
    int error = 1 - x;

    while (x >= y) {
        drawCirclePoints(cx, cy, x, y);
        y++;

        if (error < 0) {
            error += 2 * y + 1;
        } else {
            x--;
            error += 2 * (y - x) + 1;
        }
    }
}

void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3)
{
    drawLine(x1, y1, x2, y2);
    drawLine(x2, y2, x3, y3);
    drawLine(x3, y3, x1, y1);
}

static const char *shapeName(int type)
{
    switch (type) {
    case SHAPE_LINE:
        return "Line";
    case SHAPE_RECTANGLE:
        return "Rectangle";
    case SHAPE_CIRCLE:
        return "Circle";
    case SHAPE_TRIANGLE:
        return "Triangle";
    default:
        return "Unknown";
    }
}

static void drawObject(const GraphicObject *object)
{
    switch (object->type) {
    case SHAPE_LINE:
        drawLine(object->x1, object->y1, object->x2, object->y2);
        break;
    case SHAPE_RECTANGLE:
        drawRectangle(object->x1, object->y1, object->width, object->height);
        break;
    case SHAPE_CIRCLE:
        drawCircle(object->x1, object->y1, object->radius);
        break;
    case SHAPE_TRIANGLE:
        drawTriangle(object->x1, object->y1, object->x2, object->y2,
                     object->x3, object->y3);
        break;
    }
}

void redrawCanvas(void)
{
    /* Redraw from object list, so delete and modify remove old pixels cleanly. */
    clearCanvas();
    for (int i = 0; i < objectCount; i++) {
        if (objects[i].active) {
            drawObject(&objects[i]);
        }
    }
}

static int findFreeSlot(void)
{
    for (int i = 0; i < MAX_OBJECTS; i++) {
        if (!objects[i].active) {
            return i;
        }
    }
    return -1;
}

static void readObjectData(GraphicObject *object, int type)
{
    /* Same storage is used for all shapes; unused values stay zero. */
    object->active = 1;
    object->type = type;
    object->x1 = 0;
    object->y1 = 0;
    object->x2 = 0;
    object->y2 = 0;
    object->x3 = 0;
    object->y3 = 0;
    object->width = 0;
    object->height = 0;
    object->radius = 0;

    if (type == SHAPE_LINE) {
        object->x1 = readInt("Start x: ");
        object->y1 = readInt("Start y: ");
        object->x2 = readInt("End x: ");
        object->y2 = readInt("End y: ");
    } else if (type == SHAPE_RECTANGLE) {
        object->x1 = readInt("Left x: ");
        object->y1 = readInt("Top y: ");
        object->width = readInt("Width: ");
        object->height = readInt("Height: ");
    } else if (type == SHAPE_CIRCLE) {
        object->x1 = readInt("Center x: ");
        object->y1 = readInt("Center y: ");
        object->radius = readInt("Radius: ");
    } else if (type == SHAPE_TRIANGLE) {
        object->x1 = readInt("Point 1 x: ");
        object->y1 = readInt("Point 1 y: ");
        object->x2 = readInt("Point 2 x: ");
        object->y2 = readInt("Point 2 y: ");
        object->x3 = readInt("Point 3 x: ");
        object->y3 = readInt("Point 3 y: ");
    }
}

void listObjects(void)
{
    int found = 0;

    printf("\nObjects:\n");
    for (int i = 0; i < objectCount; i++) {
        if (objects[i].active) {
            printf("%d. %s\n", i + 1, shapeName(objects[i].type));
            found = 1;
        }
    }

    if (!found) {
        printf("No objects yet.\n");
    }
}

void addObject(void)
{
    int slot = findFreeSlot();

    if (slot == -1) {
        printf("Object list is full.\n");
        return;
    }

    printf("\nChoose shape\n");
    printf("1. Line\n");
    printf("2. Rectangle\n");
    printf("3. Circle\n");
    printf("4. Triangle\n");

    int type = readInt("Shape number: ");
    if (type < SHAPE_LINE || type > SHAPE_TRIANGLE) {
        printf("Invalid shape.\n");
        return;
    }

    readObjectData(&objects[slot], type);
    if (slot >= objectCount) {
        objectCount = slot + 1;
    }

    redrawCanvas();
    printf("Object added.\n");
}

void deleteObject(void)
{
    listObjects();

    int choice = readInt("Delete object number: ");
    if (choice < 1 || choice > objectCount || !objects[choice - 1].active) {
        printf("Invalid object number.\n");
        return;
    }

    objects[choice - 1].active = 0;
    redrawCanvas();
    printf("Object deleted.\n");
}

void modifyObject(void)
{
    listObjects();

    int choice = readInt("Modify object number: ");
    if (choice < 1 || choice > objectCount || !objects[choice - 1].active) {
        printf("Invalid object number.\n");
        return;
    }

    printf("Re-enter details for this %s.\n", shapeName(objects[choice - 1].type));
    readObjectData(&objects[choice - 1], objects[choice - 1].type);
    redrawCanvas();
    printf("Object modified.\n");
}

static void clearAllObjects(void)
{
    for (int i = 0; i < MAX_OBJECTS; i++) {
        objects[i].active = 0;
    }
    objectCount = 0;
    clearCanvas();
    printf("Picture cleared.\n");
}

static void showMenu(void)
{
    printf("\n2D Graphics Editor\n");
    printf("1. Add object\n");
    printf("2. Delete object\n");
    printf("3. Modify object\n");
    printf("4. List objects\n");
    printf("5. Clear picture\n");
    printf("6. Display picture\n");
    printf("0. Exit\n");
}

int main(void)
{
    int choice;

    clearCanvas();

    while (1) {
        displayCanvas();
        showMenu();
        choice = readInt("Choice: ");

        if (choice == 1) {
            addObject();
        } else if (choice == 2) {
            deleteObject();
        } else if (choice == 3) {
            modifyObject();
        } else if (choice == 4) {
            listObjects();
        } else if (choice == 5) {
            clearAllObjects();
        } else if (choice == 6) {
            displayCanvas();
        } else if (choice == 0) {
            printf("Goodbye.\n");
            break;
        } else {
            printf("Invalid choice.\n");
        }
    }

    return 0;
}
