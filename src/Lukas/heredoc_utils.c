/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 19:35:57 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/12 19:48:23 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

int	is_delimiter(char *line, char *eof)
{
	return (ft_strcmp(line, eof) == 0);
}

char	*process_line(t_redir *hd, t_shell *data, char *line)
{
	char	*expanded;

	if (!hd->expand)
		return (line);
	expanded = expand_line(data, line);
	free(line);
	return (expanded);
}

char	*read_heredoc_line(void)
{
	char	*line;
	char	*tmp;

	if (isatty(fileno(stdin)))
		return (readline("> "));
	tmp = read_file(fileno(stdin));
	if (!tmp)
		return (NULL);
	line = ft_strtrim(tmp, "\n");
	free(tmp);
	return (line);
}
