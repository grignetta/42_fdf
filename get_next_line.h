/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpadenko <dpadenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 19:03:49 by dpadenko          #+#    #+#             */
/*   Updated: 2023/10/24 19:11:42 by dpadenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

size_t	ft_strlen(char *str);
void	my_free(char **str);
char	*ft_strjoin(char *read_str, char *buff);
char	*del_buf_return_res(char **buffer, char *res, int len_to_del);
char	*extract_til_nl_or_end(char **buff);
char	*read_buff_size(int fd, char **buffer);
int		check_nl(char *str);
char	*get_next_line(int fd);

#endif
