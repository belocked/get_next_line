/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bosekim <bosekim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 13:11:40 by bosekim           #+#    #+#             */
/*   Updated: 2023/05/31 13:11:42 by bosekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
int main()
{
	int fd = open("./test", O_RDONLY);
	int i = -10;
	while(++i)
	{
		char *buf;
		buf = ft_get_next_line(fd);
		printf("%d: %s\n",i+10,buf);
		int j =0;
		while(buf[j])
		{
			printf("j(%d) : %c(%d)\n",j,buf[j],buf[j]);
			j++;
		}
	}
}
char	*ft_get_next_line(int fd)
{
	char	*buf;
	int		read_byte;
	buf = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	read_byte = read(fd, buf, BUFFER_SIZE);
	if(read_byte < 1)
		return (NULL);
	return buf;
}