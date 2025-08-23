/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpadenko <dpadenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 12:34:02 by dpadenko          #+#    #+#             */
/*   Updated: 2024/02/03 16:08:15 by dpadenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_height(char *file_name)
{
	char	*line;
	int		fd;
	int		height;

	fd = open(file_name, O_RDONLY, 0);
	if (fd == -1)
		return (0);
	height = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		height++;
		free(line);
	}
	close(fd);
	return (height);
}

int	get_width(char *file_name)
{
	int		width;
	int		fd;
	char	*line;

	fd = open(file_name, O_RDONLY, 0);
	if (fd == -1)
		return (0);
	line = get_next_line(fd);
	width = ft_wdcount(line, ' ');
	free(line);
	close(fd);
	return (width);
}

int	ft_wdcount(char const *s, char c)
{
	long unsigned int	i;
	int					count;
	int					word;

	i = 0;
	word = 0;
	count = 0;
	while (i < ft_strlen(s))
	{
		if (s[i] != c)
		{
			if (word == 0)
			{
				count++;
				word = 1;
			}
		}
		else
			word = 0;
		i++;
	}
	return (count);
}

int	update(t_fdf *data)
{
	clear_window(data);
	draw(data);
	return (0);
}
