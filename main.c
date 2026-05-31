#define ROWS 25
#define COLS 60

char canvas[ROWS][COLS];

void clearCanvas()
{
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) { 
            canvas[i][j] = '_';
        }
    }
}

void displayCanvas()
{
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%c", canvas[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    clearCanvas();

    printf("2D Graphics Editor\n\n");
    displayCanvas();

    return 0;
}