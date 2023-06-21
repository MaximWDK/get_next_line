/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonet <mleonet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:33:00 by mleonet           #+#    #+#             */
/*   Updated: 2023/06/17 14:48:57 by mleonet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*str;

	fd = open("test.txt", O_RDONLY);
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		printf("%s", str);
	}
	close(fd);
}
