/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpadenko <dpadenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 18:32:49 by dpadenko          #+#    #+#             */
/*   Updated: 2024/01/31 22:13:58 by dpadenko         ###   ########.fr       */
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

	isometric(&params->x0 , &params->y0, z * data->zoom / 10);
	isometric(&params->x1, &params->y1, z1 * data->zoom / 10);
    set_bres_param(params);
    printf("%d\n", data->color_delta);
        printf("%f\n", sqrt((params->y1 - params->ystart)*(params->y1 - params->ystart) + (params->x1 - params->xstart)*(params->x1 - params->xstart)));
        printf("y1:%d\n",params->y1);
        printf("ystart:%d\n",params->ystart);
        printf("x1:%d\n",params->x1);
        printf("xstart:%d\n",params->xstart);
	draw_bresenham(params, data, z, z1);
    printf("%d\n", data->color_delta);
        printf("%f\n", sqrt((params->y1 - params->ystart)*(params->y1 - params->ystart) + (params->x1 - params->xstart)*(params->x1 - params->xstart)));
        printf("y1:%d\n",params->y1);
        printf("ystart:%d\n",params->ystart);
        printf("x1:%d\n",params->x1);
        printf("xstart:%d\n",params->xstart);
}

void draw_bresenham(t_bres_param *params, t_fdf *data, int z, int z1)
{
	int e2;


    while (1)
	{
        //if (params->x0 <= data->win_width - data->x_shift && params->x0 >= -data->x_shift && params->y0 <= data->win_height - data->y_shift && params->y0 >= -data->y_shift)
        if (params->x0 + data->x_shift < data->win_width && params->x0 + data->x_shift > 0
            && params->y0 + data->y_shift < data->win_height && params->y0 + data->y_shift > 0)
            my_mlx_pixel_put(&data->image, (params->x0 + data->x_shift), (params->y0 + data->y_shift), data->color);
        if (params->x0 == params->x1 && params->y0 == params->y1)
            break;
        e2 = params->err * 2;
        if (e2 <= params->dx)
		{
			if (params->y0 == params->y1)
				break;
            params->err += params->dx;
            params->y0 += params->sy;
           // if (z1 != 0 && z == 0)
           //     data->color += data->color_delta / sqrt((params->y1 - params->ystart)*(params->y1 - params->ystart) + (params->x1 - params->xstart)*(params->x1 - params->xstart));
           // if (z1 == 0 && z != 0 && params->y1 != params->y0)
           //     data->color -= data->color_delta / sqrt((params->y1 - params->ystart)*(params->y1 - params->ystart) + (params->x1 - params->xstart)*(params->x1 - params->xstart));
        }
        if (e2 >= params->dy)
		{
			if (params->x0 == params->x1)
				break;
            params->err += params->dy;
            params->x0 += params->sx;
          //  if (z1 != 0 && z == 0)
          //      data->color += data->color_delta / (params->x1 - params->xstart);
          //  if (z1 == 0 && z != 0 && params->x1 != params->x0)
          //      data->color -= data->color_delta / (params->x1 - params->xstart);
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
        data->color = c.color;
    }
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
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->image.img, 0, 0);
}