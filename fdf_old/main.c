/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpadenko <dpadenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 12:49:25 by dpadenko          #+#    #+#             */
/*   Updated: 2024/02/02 22:38:01 by dpadenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void init_data(t_fdf *data)
{
	data->zoom = 10;
	data->z_zoom = 8;
	data->angle = 0.523598;
	data->isometric = 0;
	data->x_shift = 0;
	data->y_shift = 0;
	data->win_width = 1000;
	data->win_height = 1000;
	data->legend_offset = 90;
	data->black = 1;
}

void clear_window(t_fdf *data)
{
	int x;
	int y;

	x = 0;
	while (x < data->win_width)
	{
		y = 0;
		while (y < data->win_height)
			my_mlx_pixel_put(&data->image, x, y++, 0);
		x++;
	}
}

void	key_event(int keycode, t_fdf *data)
{
	if (keycode == 65364)
		data->y_shift += 10;
	if (keycode == 65362)
		data->y_shift += -10;
	if (keycode == 65361)
		data->x_shift += -10;
	if (keycode == 65363)
		data->x_shift += 10;
	if (keycode == 105)
		data->zoom +=5;
	if (keycode == 111)
		data->zoom -=5;
	if (keycode == 117)
		data->z_zoom += 0.5;
	if (keycode == 100)
		data->z_zoom -= 0.5;
	if (keycode == 115)
		data->isometric = !data->isometric;
	if (keycode == 97)
		data->angle += 0.1;
	if (keycode == 99)
		data->black = !data->black;
}

int mouse_event(int button, int x, int y, t_fdf *data)
{
	(void)x;
    (void)y;

    if (button == 4)
        data->zoom += 5;
    else if (button == 5)
            data->zoom -= 5;
	clear_window(data);
	draw(data);
    return (0);
}

int close_event(t_fdf *data)
{
		mlx_destroy_image(data->mlx_ptr, data->image.img);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		free_matrix(data->z_matrix);
		free(data);
		exit(1);
    return (0);
}
/*
int	main(int argc, char **argv)
{
	if (argc > 1)
	{
		t_fdf *data;

	data = (t_fdf*)malloc(sizeof(t_fdf));
	if (read_file(argv[1], data))
		return (1);
	init_data (data);
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return (free_matrix(data->z_matrix), free(data), 1);
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->win_width,
	data->win_height, "FDF");
	if (data->win_ptr == NULL)
		return (mlx_destroy_display(data->mlx_ptr),
		free_matrix(data->z_matrix), free(data), 1);
	data->image.img = mlx_new_image(data->mlx_ptr,
	data->win_height, data->win_width);
	if (data->image.img == NULL)
		return (free(data->win_ptr), mlx_destroy_display(data->mlx_ptr),
		free_matrix(data->z_matrix),
		free(data), 1);
	data->image.addr = mlx_get_data_addr(data->image.img,
	&data->image.bits_per_pixel, &data->image.line_length, &data->image.endian);
	if (data->image.addr == NULL)
		return (free(data->image.img), free(data->win_ptr),
		mlx_destroy_display(data->mlx_ptr), free_matrix(data->z_matrix),
		free(data), 1);
	draw(data);
	mlx_mouse_hook(data->win_ptr, mouse_event, data);
	mlx_hook(data->win_ptr, 2, 1L<<0, handle_input, data);
	mlx_hook(data->win_ptr, 17, 0, close_event, data);
	mlx_loop(data->mlx_ptr);
	}
}
*/
t_fdf *initialize_data(char *filename)
{
    t_fdf *data = (t_fdf*)malloc(sizeof(t_fdf));
    if (read_file(filename, data))
        return NULL;
    init_data(data);
    return data;
}

int initialize_graphics(t_fdf *data)
{
    data->mlx_ptr = mlx_init();
    if (data->mlx_ptr == NULL)
        return 1;
    data->win_ptr = mlx_new_window(data->mlx_ptr,
									data->win_width,
									data->win_height,
									"FDF");
    if (data->win_ptr == NULL)
        return 1;
    return 0;
}

int initialize_image(t_fdf *data)
{
    data->image.img = mlx_new_image(data->mlx_ptr,
                                    data->win_height,
									data->win_width);
    if (data->image.img == NULL)
        return 1;
    data->image.addr = mlx_get_data_addr(data->image.img,
                                         &data->image.bits_per_pixel,
										 &data->image.line_length,
										 &data->image.endian);
    if (data->image.addr == NULL)
        return 1;
    return 0;
}

int	main(int argc, char **argv)
{
    if (argc > 1)
    {
        t_fdf *data = initialize_data(argv[1]);
        if (data == NULL)
            return 1;
        if (initialize_graphics(data))
            return (free_matrix(data->z_matrix), free(data), 1);
        if (initialize_image(data))
            return (free(data->win_ptr), mlx_destroy_display(data->mlx_ptr),
                    free_matrix(data->z_matrix), free(data), 1);
        draw(data);
        mlx_mouse_hook(data->win_ptr, mouse_event, data);
        mlx_hook(data->win_ptr, 2, 1, handle_input, data);
        mlx_hook(data->win_ptr, 17, 0, close_event, data);
        mlx_loop(data->mlx_ptr);
    }
}
