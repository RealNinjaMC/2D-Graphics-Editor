#include <assert.h>
#include <stdio.h>

#define ROWS 25
#define COLS 60

extern char canvas[ROWS][COLS];

void clearCanvas(void);
void drawLine(int x1, int y1, int x2, int y2);
void drawRectangle(int x, int y, int width, int height);
void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3);
void drawCircle(int cx, int cy, int radius);
int isInsideCanvas(int x, int y);
int parseInt(const char *text, int *value);

static void test_parse_int_accepts_clean_numbers(void)
{
    int value = 0;

    assert(parseInt("42\n", &value) == 1);
    assert(value == 42);
    assert(parseInt("   -7  \n", &value) == 1);
    assert(value == -7);
}

static void test_parse_int_rejects_invalid_input(void)
{
    int value = 99;

    assert(parseInt("12abc\n", &value) == 0);
    assert(value == 99);
    assert(parseInt("abc\n", &value) == 0);
    assert(parseInt("\n", &value) == 0);
    assert(parseInt("999999999999999999999999\n", &value) == 0);
    assert(parseInt("5 6\n", &value) == 0);
}

static void test_clear_canvas_uses_underscores(void)
{
    clearCanvas();
    assert(canvas[0][0] == '_');
    assert(canvas[ROWS - 1][COLS - 1] == '_');
}

static void test_line_draws_start_and_end(void)
{
    clearCanvas();
    drawLine(1, 1, 5, 1);
    assert(canvas[1][1] == '*');
    assert(canvas[1][5] == '*');
}

static void test_rectangle_draws_corners(void)
{
    clearCanvas();
    drawRectangle(2, 3, 6, 4);
    assert(canvas[3][2] == '*');
    assert(canvas[3][7] == '*');
    assert(canvas[6][2] == '*');
    assert(canvas[6][7] == '*');
}

static void test_triangle_draws_vertices(void)
{
    clearCanvas();
    drawTriangle(10, 2, 6, 8, 14, 8);
    assert(canvas[2][10] == '*');
    assert(canvas[8][6] == '*');
    assert(canvas[8][14] == '*');
}

static void test_circle_draws_cardinal_points(void)
{
    clearCanvas();
    drawCircle(20, 10, 4);
    assert(canvas[10][24] == '*');
    assert(canvas[10][16] == '*');
    assert(canvas[14][20] == '*');
    assert(canvas[6][20] == '*');
}

static void test_canvas_bounds_are_checked(void)
{
    assert(isInsideCanvas(0, 0) == 1);
    assert(isInsideCanvas(COLS - 1, ROWS - 1) == 1);
    assert(isInsideCanvas(-1, 0) == 0);
    assert(isInsideCanvas(0, -1) == 0);
    assert(isInsideCanvas(COLS, 0) == 0);
    assert(isInsideCanvas(0, ROWS) == 0);
}

int main(void)
{
    test_parse_int_accepts_clean_numbers();
    test_parse_int_rejects_invalid_input();
    test_clear_canvas_uses_underscores();
    test_line_draws_start_and_end();
    test_rectangle_draws_corners();
    test_triangle_draws_vertices();
    test_circle_draws_cardinal_points();
    test_canvas_bounds_are_checked();
    printf("All editor tests passed.\n");
    return 0;
}
