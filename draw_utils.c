/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpadenko <dpadenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 12:52:34 by dpadenko          #+#    #+#             */
/*   Updated: 2024/02/03 14:34:47 by dpadenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	isometric(int *x, int *y, int z, t_fdf *data)
{
	*x = (*x - *y) * cos(data->angle);
	*y = (*x + *y) * sin(data->angle) - z;
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	legend(t_fdf *data)
{
	char	*legend;

	legend = "MOVE: UP, DOWN, LEFT, RIGHT";
	mlx_string_put(data->mlx_ptr, data->win_ptr, 10, 20, 0xffffff, legend);
	legend = "ZOOM-IN: I or SCROLL-UP";
	mlx_string_put(data->mlx_ptr, data->win_ptr, 10, 35, 0xffffff, legend);
	legend = "ZOOM-OUT: O or SCROLL-DOWN";
	mlx_string_put(data->mlx_ptr, data->win_ptr, 10, 50, 0xffffff, legend);
	legend = "Z UP: U       Z DOWN: D";
	mlx_string_put(data->mlx_ptr, data->win_ptr, 10, 65, 0xffffff, legend);
	legend = "ISOMETRIC: S";
	mlx_string_put(data->mlx_ptr, data->win_ptr, 10, 80, 0xffffff, legend);
	legend = "ANGLE: A";
	mlx_string_put(data->mlx_ptr, data->win_ptr, 10, 95, 0xffffff, legend);
	legend = "EXIT: ESC";
	mlx_string_put(data->mlx_ptr, data->win_ptr, 10, 110, 0xffffff, legend);
}

void	draw_rectangle(t_fdf *data, int height, int color)
{
	int	x0;
	int	y0;
	int	x;
	int	y;

	x0 = 0;
	y0 = 0;
	y = y0 - 1;
	while (++y < y0 + height)
	{
		x = x0 - 1;
		while (++x < x0 + data->win_width)
		{
			my_mlx_pixel_put(&data->image, x, y, color);
		}
	}
}

void	update_params(t_bres_param *params, int e2)
{
	if (e2 <= params->dx)
	{
		if (params->y0 != params->y1)
		{
			params->err += params->dx;
			params->y0 += params->sy;
		}
	}
	if (e2 >= params->dy)
	{
		if (params->x0 != params->x1)
		{
			params->err += params->dy;
			params->x0 += params->sx;
		}
	}
}
