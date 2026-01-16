/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:15:33 by lwittwer          #+#    #+#             */
/*   Updated: 2026/01/16 17:42:14 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

//Idea: I want to create a Heredoc function that read input with read. into a buffer
//		Also i want to create a 2D String with the input from the user
//		I want to safe the delimiter in the struct and always check if the input is DELIM
//		I need to handle signels as readline would
//		I want to exit cleanly
//		and also expand correctly when we hav expansion on

static void	mh_heredoc_write(t_heredoc *data)
{
	int	i;

	i = -1;
	while (data->text[++i])
		write(1, data->text[i], ft_strlen(data->text[i]));
}

static void	mh_heredoc_realloc(t_heredoc *data, char *line)
{
	char	**tmp;
	int		i;

	if (!data || !line)
		return;	//free
	tmp = malloc((data->tsize + 1) * (sizeof(char *)));
	if (!tmp)
		return;	//free
	i = -1;
	while (++i < data->tsize - 1)
		tmp[i] = ft_strdup(data->text[i]);
	tmp[i] = ft_strdup(line);
	tmp[++i] = NULL;
	free_arr(data->text);
	data->text = tmp;
}

static void	mh_heredoc_read(t_heredoc *data)
{
	char	buff[BUFFER_SIZE + 1];
	char	*acc = NULL;
	ssize_t	acc_len = 0;
	ssize_t	bytes;
	
	while (1)
	{
		bytes = read(STDIN_FILENO, buff, BUFFER_SIZE);
		if (bytes == -1)
		{
			if (errno == EINTR)
			{
				 //abort heredoc
				 free(acc);
				 return;
			}
			//real error
			free(acc);
			return;
		}
		if (bytes == 0)	//EOF Ctrl + D
			break;
		buff[bytes] = '\0';
		mh_heredoc_realloc(data, buff);
	}
}

void	mh_heredoc(int	n, char *word)
{
	t_heredoc	data;
	(void)n;
	ft_memset(&data, 0, sizeof(data));
	data.word = ft_strdup(word);
	mh_heredoc_read(&data);
	mh_heredoc_write(&data);
}
