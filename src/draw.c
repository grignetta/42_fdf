/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpadenko <dpadenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 18:32:49 by dpadenko          #+#    #+#             */
/*   Updated: 2024/02/03 14:11:30 by dpadenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw(t_fdf *data)
{
	draw_lines(data);
	mlx_put_image_to_window(data->mlx_ptr,
		data->win_ptr,
		data->image.img,
		0, 0);
	draw_rectangle(data, data->legend_offset, 6710886);
	legend(data);
}

void	draw_lines(t_fdf *data)
{
	int				x;
	int				y;
	t_bres_param	params;

	y = -1;
	while (++y < data->height)
	{
		x = -1;
		while (++x <= data->width)
		{
			params.x0 = x;
			params.y0 = y;
			params.x1 = x + 1;
			params.y1 = y;
			if (x < data->width)
				bresenham(&params, data);
			params.x0 = x;
			params.y0 = y;
			params.x1 = x;
			params.y1 = y + 1;
			if (y < data->height - 1)
				bresenham(&params, data);
		}
	}
}

void	bresenham(t_bres_param *params, t_fdf *data)
{
	int	z;
	int	z1;

	z = data->z_matrix[(int)params->y0][(int)params->x0];
	z1 = data->z_matrix[(int)params->y1][(int)params->x1];
	z *= data->z_zoom;
	z1 *= data->z_zoom;
	params->x0 *= data->zoom;
	params->y0 *= data->zoom;
	params->x1 *= data->zoom;
	params->y1 *= data->zoom;
	set_color (data, z);
	if (data->isometric == 1)
	{
		isometric(&params->x0, &params->y0, z, data);
		isometric(&params->x1, &params->y1, z1, data);
	}
	set_bres_param(params);
	draw_bresenham(params, data, z, z1);
}

void	set_bres_param(t_bres_param *params)
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
	params->xstart = params->x0;
	params->ystart = params->y0;
}

void	draw_bresenham(t_bres_param *params, t_fdf *data, int z, int z1)
{
	int	e2;

	while (1)
	{
		if (params->x0 + data->x_shift < data->win_width
			&& params->x0 + data->x_shift > 0
			&& params->y0 + data->y_shift + data->legend_offset
			< data->win_height && params->y0 + data->y_shift
			+ data->legend_offset > 0)
			my_mlx_pixel_put(&data->image, (params->x0 + data->x_shift),
				(params->y0 + data->y_shift + data->legend_offset),
				data->color);
		if (params->x0 == params->x1 && params->y0 == params->y1)
			break ;
		e2 = params->err * 2;
		update_params(params, e2);
		update_color(params, data, z, z1);
	}
}
