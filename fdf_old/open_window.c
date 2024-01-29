/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpadenko <dpadenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 20:47:33 by dpadenko          #+#    #+#             */
/*   Updated: 2023/12/13 20:19:42 by dpadenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
//not filled in circle
/*
void	my_mlx_pixel_put_circle(t_data *data, int centerX, int centerY, int radius, int color)
{
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y)
    {
        my_mlx_pixel_put(data, centerX + x, centerY + y, color);
        my_mlx_pixel_put(data, centerX + y, centerY + x, color);
        my_mlx_pixel_put(data, centerX - y, centerY + x, color);
        my_mlx_pixel_put(data, centerX - x, centerY + y, color);
        my_mlx_pixel_put(data, centerX - x, centerY - y, color);
        my_mlx_pixel_put(data, centerX - y, centerY - x, color);
        my_mlx_pixel_put(data, centerX + y, centerY - x, color);
        my_mlx_pixel_put(data, centerX + x, centerY - y, color);

        if (err <= 0)
        {
            y += 1;
            err += 2*y + 1;
        }

        if (err > 0)
        {
            x -= 1;
            err -= 2*x + 1;
        }
    }
}
*/

void	my_mlx_pixel_put_line(t_data *data, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0);
    int sy = y0 < y1 ? 1 : -1;
    int err = dx + dy;
    int e2;

    while (1)
    {
        my_mlx_pixel_put(data, x0, y0, color);
        if (x0 == x1 && y0 == y1)
            break;
        e2 = 2 * err;
        if (e2 >= dy)
        {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}
// Square
/*
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    int	i;
    int	j;

    i = 0;
    while (i < 50) // change the size of the square here
    {
        j = 0;
        while (j < 50) // change the size of the square here
        {
            char	*dst;

            dst = data->addr + ((y + i) * data->line_length + (x + j) * (data->bits_per_pixel / 8));
            *(unsigned int*)dst = color;
            j++;
        }
        i++;
    }
}
*/

void	my_mlx_pixel_put_filled_circle(t_data *data, int centerX, int centerY, int radius, int startColor, int endColor)
{
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y)
    {
		for (int i = -x; i <= x; i++)
        {
            double distance = sqrt((i * i) + (y * y));
            int color = startColor + (int)((endColor - startColor) * (distance / radius));
            my_mlx_pixel_put(data, centerX + i, centerY + y, color);
            my_mlx_pixel_put(data, centerX + i, centerY - y, color);
        }

        for (int i = -y; i <= y; i++)
        {
            double distance = sqrt((i * i) + (x * x));
            int color = startColor + (int)((endColor - startColor) * (distance / radius));
            my_mlx_pixel_put(data, centerX + i, centerY + x, color);
            my_mlx_pixel_put(data, centerX + i, centerY - x, color);
        }

        if (err <= 0)
        {
            y += 1;
            err += 2*y + 1;
        }

        if (err > 0)
        {
            x -= 1;
            err -= 2*x + 1;
        }
    }
}

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

int	close(int keycode, t_vars *vars)
{
	printf("Keycode: %d\n", keycode);
    if (keycode == 65307) // 53 is the keycode for the ESC key
    {
        mlx_destroy_window(vars->mlx, vars->win);
        exit(0); // exit the program
    }
    return (0);
}
/*
int main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	my_mlx_pixel_put_filled_circle(&img, 960, 540, 100, 0x00FF0000, 0x0000FF00); // draws a filled red circle with a radius of 100 at the position (960, 540)
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
*/

int main(void)
{
    t_vars	vars;
    t_data	img;

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world");
    img.img = mlx_new_image(vars.mlx, 1920, 1080);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
    my_mlx_pixel_put_filled_circle(&img, 960, 540, 100, 0x00FF0000, 0x0000FF00); // draws a filled red circle with a radius of 100 at the position (960, 540)
    mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
    mlx_hook(vars.win, 2, 1L<<0, close, &vars);
    mlx_loop(vars.mlx);
}
