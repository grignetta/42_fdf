/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpadenko <dpadenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 20:20:29 by dpadenko          #+#    #+#             */
/*   Updated: 2024/02/03 15:25:28 by dpadenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_fdf	*creat_matrix(char *file_name, t_fdf *data)
{
	int	i;

	data->height = get_height(file_name);
	data->width = get_width(file_name);
	data->z_matrix = (int **)malloc(sizeof(int *) * (data->height + 1));
	if (!data->z_matrix)
		return (NULL);
	i = 0;
	while (i < data->height)
	{
		data->z_matrix[i] = (int *)malloc(sizeof(int) * (data->width + 2));
		if (!data->z_matrix[i])
		{
			free_matrix(data->z_matrix);
			return (NULL);
		}
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
	data->height = get_height(file_name);
	if (!creat_matrix(file_name, data))
		return (true);
	fd = open(file_name, O_RDONLY, 0);
	if (fd == -1)
		return (free_matrix(data->z_matrix), true);
	while (i < data->height)
	{
		line = get_next_line(fd);
		if (!line)
			return (free_matrix(data->z_matrix), close(fd), true);
		if (fill_matrix(data->z_matrix[i++], line))
			return (free_matrix(data->z_matrix), close(fd), true);
		free(line);
	}
	close(fd);
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
	z_line[i] = 0;
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
