/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpadenko <dpadenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 18:32:49 by dpadenko          #+#    #+#             */
/*   Updated: 2024/01/29 21:46:12 by dpadenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	isometric(int *x, int *y, int z)
{
   *x = (*x - *y) * cos(1);
   *y = (*x + *y) * sin(1) - z;
}

void set_bres_param(t_bres_param *params)
{
    params->dx = abs(params->x1 - params->x0);
    params->dy = -abs(params->y1 - params->y0);
	if (params->x0 < params->x1)
		params->sx = 1;
	else
		params->sx = -1;
	if (params->y0 < params->y1)
		params->sy = 1;
	else
		params->sy = -1;
	params->err = params->dx + params->dy;
}

void bresenham(t_bres_param *params, t_fdf *data)
{
	int z = data->z_matrix[(int)params->y0][(int)params->x0];
	int z1 = data->z_matrix[(int)params->y1][(int)params->x1];
	params->x0 *= data->zoom;
	params->y0 *= data->zoom;
	params->x1 *= data->zoom;
	params->y1 *= data->zoom;
	if (z != 0)
		data->color = 0xff00ff;
	else
		data->color = 0x00fffff;
	isometric(&params->x0 , &params->y0, z * data->zoom / 10);
	isometric(&params->x1, &params->y1, z1 * data->zoom / 10);
    set_bres_param(params);
	draw_bresenham(params, data);
}

void draw_bresenham(t_bres_param *params, t_fdf *data)
{
	int e2;

    while (1)
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, (params->x0 + 200), (params->y0 + 200), data->color);
        if (params->x1 == params->x0 && params->y1 == params->y0)
            break;
        e2 = params->err * 2;
        if (e2 <= params->dx)
		{
			if (params->y0 == params->y1)
				break;
            params->err += params->dx;
            params->y0 += params->sy;
        }
        if (e2 >= params->dy)
		{
			if (params->x0 == params->x1)
				break;
            params->err += params->dy;
            params->x0 += params->sx;
        }
    }
}


void	draw(t_fdf *data)
{
    int x;
    int y;
    t_bres_param params;

    y = -1;
    while (++y < data->height)
    {
        x = -1;
        while (++x <= data->width)
        {
            params.x0 = x;
            params.y0 = y;
			params.x1 = x+1;
            params.y1 = y;
            if (x < data->width)
               bresenham(&params, data);
			params.x0 = x;
            params.y0 = y;
			params.x1 = x;
            params.y1 = y+1;
            if (y < data->height - 1)
                bresenham(&params, data);
        }
    }
}