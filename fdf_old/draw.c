/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpadenko <dpadenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 18:32:49 by dpadenko          #+#    #+#             */
/*   Updated: 2024/02/02 22:10:23 by dpadenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	isometric(int *x, int *y, int z, t_fdf *data)
{
   *x = (*x - *y) * cos(data->angle);
   *y = (*x + *y) * sin(data->angle) - z;
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
    params->xstart = params->x0;
    params->ystart = params->y0;
}

void set_color(t_fdf *data, int z)
{
    if (data->black == 0)
    {
        if (z != 0)
		    data->color = 0xff00ff;
	    else
		    data->color = 0x0fffff;
    }
    else if (data->black == 1)
    {
        if (z != 0)
		    data->color = 0xffffff;
	    else
		    data->color = 0x444444;
    }
    return ;
}

void set_color2(t_fdf *data, int z)
{
    if (z != 0)
		data->color = 0xff00ff;
	else
		data->color = 0x0fffff;
}

void bresenham(t_bres_param *params, t_fdf *data)
{
	int z = data->z_matrix[(int)params->y0][(int)params->x0];
	int z1 = data->z_matrix[(int)params->y1][(int)params->x1];
    z *= data->z_zoom;
    z1 *= data->z_zoom;
	params->x0 *= data->zoom;
	params->y0 *= data->zoom;
	params->x1 *= data->zoom;
	params->y1 *= data->zoom;
    set_color (data, z);
    if (data->isometric == 1)
	{
        isometric(&params->x0 , &params->y0, z, data);
	    isometric(&params->x1, &params->y1, z1, data);
    }
    set_bres_param(params);
	draw_bresenham(params, data, z, z1);
}

double distance (double x0, double y0, double x1, double y1)
{
    return (sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0)));
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
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
        while (++x <=data->width)
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
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->image.img, 0, 0);
    draw_rectangle(data, 0, 0, data->win_width, 90, 6710886);
    legend(data);
}

void    legend(t_fdf *data)
{
    char    *legend;

    legend = "MOVE: UP, DOWN, LEFT, RIGHT";
    mlx_string_put(data->mlx_ptr, data->win_ptr, 10, 20, 0xffffff, legend);
	legend = "ZOOM-IN: I    ZOOM-OUT: O";
	mlx_string_put(data->mlx_ptr, data->win_ptr, 10, 35, 0xffffff, legend);
	legend = "Z UP: U       Z DOWN: D";
	mlx_string_put(data->mlx_ptr, data->win_ptr, 10, 50, 0xffffff, legend);
	legend = "ISOMETRIC: S";
	mlx_string_put(data->mlx_ptr, data->win_ptr, 10, 65, 0xffffff, legend);
    legend = "ANGLE: A";
	mlx_string_put(data->mlx_ptr, data->win_ptr, 10, 80, 0xffffff, legend);
}

void draw_rectangle(t_fdf *data, int x0, int y0, int width, int height,
                    int color)
{
    int x, y;

    y = y0 - 1;
    while (++y < y0 + height)
    {
        x = x0 - 1;
        while (++x < x0 + width)
        {
            my_mlx_pixel_put(&data->image, x, y, color);
        }
    }
}


void update_params(t_bres_param *params, int e2)
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

void update_color(t_bres_param *params, t_fdf *data, int z, int z1)
{
    union color c;
    double current_distance;
    double full_distance;

    current_distance = distance(params->xstart, params->ystart, params->x0,
    params->y0);
    full_distance = sqrt((params->y1 - params->ystart)*
    (params->y1 - params->ystart) + (params->x1 - params->xstart)*
    (params->x1 - params->xstart));
    current_distance /= full_distance;
    c.color = data->color;
    if (data->black == 0)
        not_black_color(&c, z, z1, current_distance);
    else
        black_color(&c, z, z1, current_distance);
    data->color = c.color;
}

void not_black_color(union color *c, int z, int z1, double current_distance)
{
    if (z1 != 0 && z == 0)
    {
        c->values[1] = 0x00 - 0xff * current_distance;
        c->values[2] = 0xff + 0xf0 * current_distance;
    }
    if (z1 == 0 && z != 0)
    {
        c->values[1] = 0x00 + 0xff * current_distance;
        c->values[2] = 0xff - 0xf0 * current_distance;
    }
}

void black_color(union color *c, int z, int z1, double current_distance)
{
    if (z1 != 0 && z == 0)
    {
        c->values[0] = 0x44 + 0xbb * current_distance;
        c->values[1] = 0x44 + 0xbb * current_distance;
        c->values[2] = 0x44 + 0xbb * current_distance;
    }
    if (z1 == 0 && z != 0)
    {
        c->values[0] = 0xff - 0xbb * current_distance;
        c->values[1] = 0xff - 0xbb * current_distance;
        c->values[2] = 0xff - 0xbb * current_distance;
    }
}

void draw_bresenham(t_bres_param *params, t_fdf *data, int z, int z1)
{
    int e2;

    while (1)
    {
        if (params->x0 + data->x_shift < data->win_width &&
        params->x0 + data->x_shift > 0 &&
        params->y0 + data->y_shift + data->legend_offset < data->win_height &&
        params->y0 + data->y_shift + data->legend_offset > 0)
            my_mlx_pixel_put(&data->image, (params->x0 + data->x_shift),
            (params->y0 + data->y_shift + data->legend_offset), data->color);
        if (params->x0 == params->x1 && params->y0 == params->y1)
            break;
        e2 = params->err * 2;
        update_params(params, e2);
        update_color(params, data, z, z1);
    }
}