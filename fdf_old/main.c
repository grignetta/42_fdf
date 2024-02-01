/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpadenko <dpadenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 12:49:25 by dpadenko          #+#    #+#             */
/*   Updated: 2024/02/01 19:22:24 by dpadenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	deal_key(int key, void *data)
{
	printf("%d", key);
	return (0);
}

void init_data(t_fdf *data)
{
	data->zoom = 30;
	data->z_zoom = 4;
	data->angle = 0.523598;
	data->isometric = 0;
	data->x_shift = 100;
	data->y_shift = 100;
	data->win_width = 1000;
	data->win_height = 1000;
	data->legend_offset = 90;
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
		data->z_zoom += 1;
	if (keycode == 100)
		data->z_zoom -= 1;
	if (keycode == 115)
	{
		if (data->isometric == 1)
			data->isometric = 0;
		else if (data->isometric == 0)
			data->isometric = 1;
	}
	if (keycode == 97)
		data->angle += 0.1;
}

int	handle_input(int keycode, t_fdf *data)
{
	if (keycode == 65362 || keycode == 65364 || keycode == 65361 ||
		keycode == 65363 || keycode == 99 || keycode == 97 || keycode == 105 ||
		keycode == 111 || keycode == 117 || keycode == 100 || keycode == 115)
	{
		key_event(keycode, data);
		clear_window(data);
		draw(data);
	}
	if (keycode == 65307) // 53 is the keycode for the ESC key
	{
		printf("The %d key (ESC) has been pressed\n\n", keycode);
		mlx_destroy_image(data->mlx_ptr, data->image.img);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		free_matrix(data->z_matrix);
		free(data);
		exit(1);
	}
	printf("The %d key has been pressed\n\n", keycode);
	return(0);
}

int	main(int argc, char **argv)
{
	t_fdf *data;

	data = (t_fdf*)malloc(sizeof(t_fdf));
	if (read_file(argv[1], data))
		return (1);
	init_data (data);
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return (free_matrix(data->z_matrix), free(data), 1);
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->win_width, data->win_height, "FDF");
	if (data->win_ptr == NULL)
		return (mlx_destroy_display(data->mlx_ptr), free_matrix(data->z_matrix), free(data), 1);
	data->image.img = mlx_new_image(data->mlx_ptr, data->win_height, data->win_width);
	if (data->image.img == NULL)
		return (free(data->win_ptr), mlx_destroy_display(data->mlx_ptr), free_matrix(data->z_matrix),
		free(data), 1);
	data->image.addr = mlx_get_data_addr(data->image.img, &data->image.bits_per_pixel, &data->image.line_length, &data->image.endian);
	if (data->image.addr == NULL)
		return (free(data->image.img), free(data->win_ptr), mlx_destroy_display(data->mlx_ptr), free_matrix(data->z_matrix), free(data), 1);
	draw(data);
	mlx_hook(data->win_ptr, 2, 1L<<0, handle_input, data);
	//mlx_key_hook(data->win_ptr, handle_input, data);
	mlx_loop(data->mlx_ptr);
}