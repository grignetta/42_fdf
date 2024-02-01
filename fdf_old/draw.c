/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpadenko <dpadenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 18:32:49 by dpadenko          #+#    #+#             */
/*   Updated: 2024/02/01 19:01:29 by dpadenko         ###   ########.fr       */
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

union color
{
    int color;
    char values[4];
};

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
	if (z != 0)
		data->color = 0xff00ff;
	else
		data->color = 0x0fffff;
    data->color_delta = 0xff00ff - 0x0fffff;
    if (data->isometric == 1)
	{
        isometric(&params->x0 , &params->y0, z, data);
	    isometric(&params->x1, &params->y1, z1, data);
    }
    set_bres_param(params);
	draw_bresenham(params, data, z, z1);
}

void draw_bresenham(t_bres_param *params, t_fdf *data, int z, int z1)
{
	int e2;


    while (1)
	{
        if (params->x0 + data->x_shift < data->win_width && params->x0 + data->x_shift > 0
            && params->y0 + data->y_shift + data->legend_offset < data->win_height && params->y0 + data->y_shift + data->legend_offset > 0)
            my_mlx_pixel_put(&data->image, (params->x0 + data->x_shift), (params->y0 + data->y_shift + data->legend_offset), data->color);
        if (params->x0 == params->x1 && params->y0 == params->y1)
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
        union color c;
        c.color = data->color;

        if (z1 != 0 && z == 0)
        {
            c.values[1] += -0xff / sqrt((params->y1 - params->ystart)*(params->y1 - params->ystart) + (params->x1 - params->xstart)*(params->x1 - params->xstart)) * 2;
            c.values[2] += 0xf0 / sqrt((params->y1 - params->ystart)*(params->y1 - params->ystart) + (params->x1 - params->xstart)*(params->x1 - params->xstart)) * 2;
        }
        if (z1 == 0 && z != 0 && params->y1 != params->y0)
        {
            c.values[1] += 0xff / (sqrt((params->y1 - params->ystart)*(params->y1 - params->ystart) + (params->x1 - params->xstart)*(params->x1 - params->xstart)) * 0.8f);
            c.values[2] += -0xf0 / (sqrt((params->y1 - params->ystart)*(params->y1 - params->ystart) + (params->x1 - params->xstart)*(params->x1 - params->xstart)) * 0.8f);
        }
        /*
        if (z1 != 0 && z == 0)
            data->color -= data->color_delta / sqrt((params->y1 - params->ystart)*(params->y1 - params->ystart) + (params->x1 - params->xstart)*(params->x1 - params->xstart));
        if (z1 == 0 && z != 0 && params->y1 != params->y0)
            data->color -= data->color_delta / (sqrt((params->y1 - params->ystart)*(params->y1 - params->ystart) + (params->x1 - params->xstart)*(params->x1 - params->xstart)));*/
        data->color = c.color;
    }
}
/*
void draw_bresenham(t_bres_param *params, t_fdf *data, int z, int z1)
{
    // Pre-compute the total distance for color interpolation
    float totalDistance = sqrt((params->x1 - params->x0) * (params->x1 - params->x0) + (params->y1 - params->y0) * (params->y1 - params->y0));

    // Start and end colors
    int startColor = data->color; // Initial color
    int endColor = (z != 0) ? 0xff00ff : 0x0fffff; // Determine the end color based on your condition

    // Decompose start and end colors into their components
    int startR = (startColor >> 16) & 0xFF;
    int startG = (startColor >> 8) & 0xFF;
    int startB = startColor & 0xFF;

    int endR = (endColor >> 16) & 0xFF;
    int endG = (endColor >> 8) & 0xFF;
    int endB = endColor & 0xFF;

    // Calculate color component differences
    int diffR = endR - startR;
    int diffG = endG - startG;
    int diffB = endB - startB;

    int dx = abs(params->x1 - params->x0), sx = params->x0 < params->x1 ? 1 : -1;
    int dy = -abs(params->y1 - params->y0), sy = params->y0 < params->y1 ? 1 : -1;
    int err = dx + dy, e2;

    while (true) // Replace the for loop with a while loop
    {
        // Calculate current distance
        float currentDistance = sqrt((params->x0 - params->xstart) * (params->x0 - params->xstart) + (params->y0 - params->ystart) * (params->y0 - params->ystart));
        // Calculate interpolation factor (0.0 to 1.0)
        float t = 0;
        if (totalDistance > 0) {
            t = currentDistance / totalDistance;
        }

        // Interpolate color components
        int currentR = round(startR + t * diffR);
        int currentG = round(startG + t * diffG);
        int currentB = round(startB + t * diffB);


        // Clamp color components to the range 0-255
currentR = max(0, min(255, currentR));
currentG = max(0, min(255, currentG));
currentB = max(0, min(255, currentB));
        // Combine components back into an integer color


        int currentColor = (currentR << 16) | (currentG << 8) | currentB;

        // Draw the pixel with the interpolated color
        if (params->x0 + data->x_shift < data->win_width && params->x0 + data->x_shift > 0 &&
            params->y0 + data->y_shift < data->win_height && params->y0 + data->y_shift > 0) {
            my_mlx_pixel_put(&data->image, (params->x0 + data->x_shift), (params->y0 + data->y_shift), currentColor);
        }

        if (params->x0 == params->x1 && params->y0 == params->y1) break;

        e2 = 2 * err;
        if (e2 >= dy) {
            err += dy;
            params->x0 += sx;
        }
        if (e2 <= dx) {
            err += dx;
            params->y0 += sy;
        }
    }
}
*/


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
            //if (params.x1 == data->width)
            //    break;
            params.y1 = y;
            if (x < data->width)
               bresenham(&params, data);
			params.x0 = x;
            params.y0 = y;
			params.x1 = x;
            params.y1 = y+1;
            //if (y+1 == data->height)
            //     break;
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

void draw_rectangle(t_fdf *data, int x0, int y0, int width, int height, int color)
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