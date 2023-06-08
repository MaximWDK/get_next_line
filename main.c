/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonet <mleonet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:33:00 by mleonet           #+#    #+#             */
/*   Updated: 2023/06/08 17:57:05 by mleonet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd;
	int		i;
	char	*str;

	i = -1;
	fd = open("test.txt", O_RDONLY);
	while (++i < 10)
	{
		str = get_next_line(fd);
		printf("%s", str);
		free(str);
	}
	close(fd);
}
