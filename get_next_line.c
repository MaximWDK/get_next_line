/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonet <mleonet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:40:08 by mleonet           #+#    #+#             */
/*   Updated: 2023/06/19 18:50:23 by mleonet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*stash;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if (!stash)
	{
		stash = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!stash)
			return (0);
		*stash = '\0';
	}
	stash = read_and_insert_stash(fd, stash);
	if (!stash)
		return (0);
	return (extract_line(&stash));
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
		{
			free(stash);
			return (0);
		}
		readed = read(fd, buf, BUFFER_SIZE);
		if (readed == -1)
		{
			free(buf);
			free(stash);
			return (0);
		}
		buf[readed] = '\0';
		stash = add_to_stash(stash, buf);
		free(buf);
	}
	return (stash);
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
	{
		free(stash);
		return (0);
	}
	while (++i < leni)
		str[i] = stash[i];
	while (++j < lenj)
		str[i + j] = buf[j];
	str[i + j] = '\0';
	free(stash);
	return (str);
}

char	*extract_line(char **stash)
{
	int		i;
	char	*line;
	char	*remainder;

	i = 0;
	while ((*stash)[i] && (*stash)[i] != '\n')
		i++;
	if ((*stash)[i] == '\n')
	{
		line = get_the_line(*stash, i);
		remainder = get_remainder(*stash, i);
		free(*stash);
		*stash = remainder;
		return (line);
	}
	if (i > 0)
	{
		line = get_the_line(*stash, i);
		free(*stash);
		*stash = NULL;
		return (line);
	}
	free(*stash);
	*stash = NULL;
	return (NULL);
}
