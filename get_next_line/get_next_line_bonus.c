/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablidi <ablidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 14:29:23 by ablidi            #+#    #+#             */
/*   Updated: 2023/01/05 11:53:39 by ablidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_read_full(int fd, char *save, int *x)
{
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	while (!ft_strnchr(save, '\n'))
	{
		*x = read(fd, buf, BUFFER_SIZE);
		if (*x <= 0)
			break ;
		buf[*x] = '\0';
		save = ft_strjoin(save, buf);
	}
	free(buf);
	return (save);
}

char	*get_next_line(int fd)
{
	static char	*save[OPEN_MAX];
	char		*buf;
	int			x;

	x = 0;
	if (BUFFER_SIZE <= 0 || fd == 1 || fd == 2 || fd < 0)
	{
		if (save[fd])
			free(save[fd]);
		return (NULL);
	}
	save[fd] = ft_read_full(fd, save[fd], &x);
	if (ft_strlen(save[fd]) > 0 && x >= 0)
	{
		buf = ft_nwline(save[fd]);
		save[fd] = ft_cutnwline(save[fd]);
		return (buf);
	}
	free(save[fd]);
	save[fd] = 0;
	return (0);
}
