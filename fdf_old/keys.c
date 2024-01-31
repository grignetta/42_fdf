
#include "fdf.h"

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