/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpadenko <dpadenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 18:32:49 by dpadenko          #+#    #+#             */
/*   Updated: 2023/12/19 20:20:03 by dpadenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	find_max(float a, float b)
{
	if (a >= b)
		return (a);
	else
		return (b);
}

float abs_dif(float x, float y)
{
	float	dif;
	dif = x - y;
	if (dif >= 0)
		return(dif);
	return(-dif);
}

void	isometric(float *x, float *y, int z)
{
	float old_x = *x;
    float old_y = *y;
    *x = (old_x - old_y) * cos(0.8);
    *y = (old_x + old_y) * sin(0.8) - z;
   // *x = (*x - *y) * cos(0.8);
   // *y = (*x + *y) * sin(0.8) - z;
}

//void	bresenham(t_draw_fdf params)

void	bresenham(float x, float y, float x1, float y1, t_fdf *data)
{
	float x_step;
	float y_step;
	int max;
	int z;
	int z1;

	z = data->z_matrix[(int)y][(int)x];
	z1 = data->z_matrix[(int)y1][(int)x1];
	x *= data->zoom;
	x1 *= data->zoom;
	y *= data->zoom;
	y1 *= data->zoom;
	if (z != 0)
		data->color = 0xff00ff;
	else
		data->color = 0x00fffff;
	isometric(&x, &y, z);
	isometric(&x1, &y1, z1);
	x_step = abs_dif(x1, x);
	y_step = abs_dif(y1, y);
	max = find_max(x_step, y_step);
	x_step = x_step / max;
	y_step = y_step / max;

	while (((int)x) - ((int)x1) || ((int)y) - ((int)y1))
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, data->color);
		x += x_step;
		y += y_step;
	}
}

void	draw(t_fdf *data)
{
	int x;
	int y;

	y = 0;
	while(y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			if (x < data->width - 1)
				bresenham(x, y, x + 1, y, data);
			if (y < data->height - 1)
				bresenham(x, y, x, y + 1, data);
			x++;
		}
		y++;
	}
}