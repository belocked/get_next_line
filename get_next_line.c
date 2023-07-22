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

char	*free_all(void **backup)
{
	if (backup == NULL || *backup == NULL)
		return (NULL);
	free(*backup);
	*backup = NULL;
	return (NULL);
}

char	*get_new_ret(char **backup)
{
	int		idx;
	char	*ret;

	idx = ft_strchr(*backup, '\n');
	if (idx == -1)
	{
		ret = ft_substr(*backup, 0, ft_strlen(*backup));
		if (!ret)
			return (free_all((void **)backup));
		free_all((void **)backup);
		return (ret);
	}
	ret = ft_substr(*backup, 0, idx + 1);
	if (!ret)
		return (free_all((void **)backup));
	return (ret);
}

char	*ch_init_backup(char **backup)
{
	int		i;
	char	*tmp;

	if (!(*backup))
		*backup = (char *)ft_calloc(1, sizeof(char));
	else if (ft_strchr(*backup, '\n') != -1)
	{
		i = ft_strchr(*backup, '\n');
		tmp = *backup;
		*backup = ft_substr(*backup, i + 1, ft_strlen(*backup) - i);
		free_all((void **)&tmp);
	}
	if (!(*backup))
		return (NULL);
	return (*backup);
}

char	*get_next_line(int fd)
{
	int			i;
	ssize_t		size;
	char		buf[BUFFER_SIZE + 1];
	static char	*backup;

	i = 0;
	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	backup = ch_init_backup(&backup);
	if (!backup)
		return (NULL);
	while (ft_strchr(backup, '\n') == -1 && ++i)
	{
		size = read(fd, buf, BUFFER_SIZE);
		if (size < 0)
			return (free_all((void **)&backup));
		buf[size] = 0;
		backup = ft_strjoin(backup, buf);
		if ((size == 0 && i == 1) && !(*backup))
			return (free_all((void **)&backup));
		if (size < BUFFER_SIZE)
			break ;
	}
	return (get_new_ret(&backup));
}