/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonet <mleonet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:33:00 by mleonet           #+#    #+#             */
/*   Updated: 2023/07/26 00:32:07 by mleonet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd;
	int		fd2;
	char	*str;
	char	*str2;
	int		i;

	i = -1;
	fd = open("test.txt", O_RDONLY);
	fd2 = 1;
	while (++i < 5)
	{
		str = get_next_line(fd);
		str2 = get_next_line(fd2);
		printf("%s", str);
		printf("| %s", str2);
		free(str);
		free(str2);
	}
	close(fd);
	close(fd2);
}
