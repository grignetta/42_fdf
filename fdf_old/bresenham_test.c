#include <stdio.h>
#include <stdlib.h>
/*
// function for line generation
void bresenham(int x1, int y1, int x2, int y2)
{
    int m_new = 2 * (y2 - y1);
    int slope_error_new = m_new - (x2 - x1);
    int x = x1, y = y1;

    while (x <= x2) {
        printf("(%d,%d)\n", x, y);

        // Add slope to increment angle formed
        slope_error_new += m_new;

        // Slope error reached limit, time to
        // increment y and update slope error.
        if (slope_error_new >= 0) {
            y++;
            slope_error_new -= 2 * (x2 - x1);
        }
        x++;
    }
}*/

void bresenham(int x1, int y1, int x2, int y2)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int sx, sy;

    if (x1 < x2) {
        sx = 1;
    } else {
        sx = -1;
    }

    if (y1 < y2) {
        sy = 1;
    } else {
        sy = -1;
    }

    int err = (dx > dy ? dx : -dy) / 2;
    int e2;

    while (1) {
        printf("(%d,%d)\n", x1, y1);

        if (x1 == x2 && y1 == y2)
            break;

        e2 = err;
        if (e2 > -dx) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dy) {
            err += dx;
            y1 += sy;
        }
    }
}

int main() {
    // Example usage
    int x1 = 0, y1 = 0, x2 = 4, y2 = 3;
    bresenham(x1, y1, x2, y2);
    return 0;
}