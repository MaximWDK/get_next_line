/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonet <mleonet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:40:08 by mleonet           #+#    #+#             */
/*   Updated: 2023/06/08 18:05:09 by mleonet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*stash;

	stash = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, stash, 0) < 0)
		return (0);
	stash = read_and_insert_stash(fd, stash);
	if (!stash)
		return (0);
	return (stash);
}

char	*read_and_insert_stash(int fd, char *stash)
{
	char	*buf;
	int		readed;

	readed = 1;
	while (!is_newline(stash) && readed != 0)
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buf)
			return (0);
		readed = read(fd, buf, BUFFER_SIZE);
		if ((!stash && readed == 0) || readed == -1)
		{
			free(buf);
			return (0);
		}
		buf[readed] = '\0';
		stash = add_to_stash(stash, buf);
		free(buf);
	}
	return (stash);
}

int	is_newline(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*add_to_stash(char *stash, char *buf)
{
	int		i;
	int		j;
	int		leni;
	int		lenj;
	char	*str;

	i = -1;
	j = -1;
	leni = ft_strlen(stash);
	lenj = ft_strlen(buf);
	str = malloc(sizeof(char) * (leni + lenj + 1));
	if (!str)
		return (0);
	while (++i < leni)
		str[i] = stash[i];
	while (++j < lenj)
		str[i + j] = buf[j];
	str[i + j] = '\0';
	return (str);
}
