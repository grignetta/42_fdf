/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpadenko <dpadenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 20:20:29 by dpadenko          #+#    #+#             */
/*   Updated: 2024/02/05 19:51:58 by dpadenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_fdf	*creat_matrix(char *file_name, t_fdf *data)
{
	int	i;

	data->width = get_width(file_name, data);
	if (!data->width)
		return (NULL);
	data->z_matrix = (int **)malloc(sizeof(int *) * (data->height + 1));
	if (!data->z_matrix)
		return (NULL);
	i = 0;
	while (i < data->height)
		data->z_matrix[i++] = NULL;
	i = 0;
	while (i < data->height)
	{
		data->z_matrix[i] = (int *)malloc(sizeof(int) * (data->width + 1));
		if (!data->z_matrix[i])
			return (NULL);
		i++;
	}
	data->z_matrix[i] = NULL;
	return (data);
}

bool	read_file(char *file_name, t_fdf *data)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	data->height = get_height(file_name, data);
	if (data->height == 0)
		return (true);
	if (!creat_matrix(file_name, data))
		return (get_next_line(-1, data), true);
	fd = open(file_name, O_RDONLY, 0);
	if (fd == -1)
		return (get_next_line(-1, data), true);
	while (i < data->height)
	{
		line = get_next_line(fd, data);
		if (!line)
			return (free_matrix(data->z_matrix), close(fd), true);
		if (fill_matrix(data->z_matrix[i++], line))
			return (free(line), close(fd), get_next_line(-1, data), true);
		free(line);
	}
	if (close(fd) == -1)
		return (free_matrix(data->z_matrix), true);
	return (false);
}

bool	fill_matrix(int *z_line, char *line)
{
	char	**nums;
	int		i;

	nums = ft_split(line, ' ');
	if (!nums)
		return (true);
	i = 0;
	while (nums[i])
	{
		z_line[i] = ft_atoi(nums[i]);
		free(nums[i]);
		i++;
	}
	return (free(nums), false);
}

void	free_matrix(int **z_matrix)
{
	int	i;

	i = 0;
	if (z_matrix == NULL)
		return ;
	while (z_matrix[i])
		free(z_matrix[i++]);
	free(z_matrix);
	return ;
}
