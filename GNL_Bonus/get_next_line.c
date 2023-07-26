/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonet <mleonet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:40:08 by mleonet           #+#    #+#             */
/*   Updated: 2023/07/26 00:29:01 by mleonet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*stash[OPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if (!stash[fd])
	{
		stash[fd] = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!stash[fd])
			return (0);
		*stash[fd] = '\0';
	}
	stash[fd] = read_and_insert_stash(fd, stash[fd]);
	if (!stash[fd])
		return (0);
	return (extract_line(&stash[fd]));
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

char	*extract_line_utils(char **stash, int index, int add)
{
	char	*line;
	char	*remainder;

	remainder = get_remainder(*stash, index);
	line = get_the_line(*stash, index, add);
	free(*stash);
	if (!remainder || !line)
	{
		free(line);
		free(remainder);
		*stash = NULL;
		return (NULL);
	}
	*stash = remainder;
	return (line);
}

char	*extract_line(char **stash)
{
	int		i;
	int		add;

	add = 1;
	i = 0;
	while ((*stash)[i] && (*stash)[i] != '\n')
		i++;
	if ((*stash)[i] == '\n')
		return (extract_line_utils(stash, i, add));
	if (i > 0)
	{
		if (!(*stash)[i])
			i--;
		return (extract_line_utils(stash, i, add));
	}
	free(*stash);
	*stash = NULL;
	return (NULL);
}
