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

int main(void)
{
    test_clear_canvas_uses_underscores();
    test_line_draws_start_and_end();
    test_rectangle_draws_corners();
    test_triangle_draws_vertices();
    test_circle_draws_cardinal_points();
    printf("All editor tests passed.\n");
    return 0;
}
