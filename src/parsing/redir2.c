/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picarlie <picarlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:58:16 by picarlie          #+#    #+#             */
/*   Updated: 2025/01/27 17:05:46 by picarlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	heredoc(char *strEOF)
{
	int		fd;
	char	*line;

	fd = open(".tmp", O_RDWR | O_CREAT | O_TRUNC, 0777);
	printf("%s\n", strEOF);
	while (1)
	{
		line = readline(">");
		if (!ft_strcmp(line, strEOF))
		{
			close(fd);
			fd = open(".tmp", O_RDONLY, 0777);
			unlink(".tmp");
			free(line);
			return (fd);
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}
