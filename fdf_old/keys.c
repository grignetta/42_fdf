
#include "fdf.h"

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
	if (keycode == 65307)
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