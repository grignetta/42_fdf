/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpadenko <dpadenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 19:03:30 by dpadenko          #+#    #+#             */
/*   Updated: 2023/10/24 19:09:46 by dpadenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

void	my_free(char **str)
{
	if (*str)
		free(*str);
	*str = NULL;
}

char	*ft_strjoin(char *read_str, char *buff)
{
	size_t	i;
	size_t	j;
	char	*str;

	if ((ft_strlen(read_str) + ft_strlen(buff)) == 0)
		return (NULL);
	str = malloc(sizeof(char) * ((ft_strlen(read_str) + ft_strlen(buff)) + 1));
	if (str == NULL)
		return (my_free(&read_str), my_free(&buff), NULL);
	i = 0;
	j = 0;
	while (read_str && read_str[i] != '\0')
	{
		str[i] = read_str[i];
		i++;
	}
	while (buff[j] != '\0')
		str[i++] = buff[j++];
	str[i] = '\0';
	return (my_free(&read_str), my_free(&buff), str);
}
