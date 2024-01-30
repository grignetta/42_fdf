/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpadenko <dpadenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 12:49:25 by dpadenko          #+#    #+#             */
/*   Updated: 2024/01/30 21:53:40 by dpadenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	deal_key(int key, void *data)
{
	printf("%d", key);
	return (0);
}

int	handle_input(int keycode, t_fdf *data)
{
	if (keycode == 65307) // 53 is the keycode for the ESC key
	{
		printf("The %d key (ESC) has been pressed\n\n", keycode);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		exit(1);
	}
	printf("The %d key has been pressed\n\n", keycode);
	return(0);
}

void init_data(t_fdf *data)
{
	data->zoom = 30;
	data->z_zoom = 1;
	data->angle = 0.523598;
	data->isometric = 1;
	data->x_shift = 100;
	data->y_shift = 100;
	data->win_width = 1000;
	data->win_height = 1000;

	data->img_side = 1000; //maybe not needed!
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
		return (free(data), 1);
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->win_width, data->win_height, "FDF");
	if (data->win_ptr == NULL)
		return (mlx_destroy_display(data->mlx_ptr), free(data), 1);
	data->image.img = mlx_new_image(data->mlx_ptr, data->img_side, data->img_side);
	if (data->image.img == NULL)
		return (free(data->win_ptr), mlx_destroy_display(data->mlx_ptr),
		free(data), 1);
	data->image.addr = mlx_get_data_addr(data->image.img, &data->image.bits_per_pixel, &data->image.line_length, &data->image.endian);
	if (data->image.addr == NULL)
		return (free(data->image.img), free(data->win_ptr), mlx_destroy_display(data->mlx_ptr), free(data), 1);
	draw(data);
	mlx_key_hook(data->win_ptr, handle_input, data);
	mlx_loop(data->mlx_ptr);
}