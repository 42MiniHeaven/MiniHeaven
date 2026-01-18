/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:15:33 by lwittwer          #+#    #+#             */
/*   Updated: 2026/01/18 18:56:30 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

//Idea: I want to create a Heredoc function that read input with read. into a buffer
//		Also i want to create a 2D String with the input from the user
//		I want to safe the delimiter in the struct and always check if the input is DELIM
//		I need to handle signels as readline would
//		I want to exit cleanly
//		and also expand correctly when we hav expansion on
/*
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
		size_t len = bytes;
		if (len > 0 && buff[len - 1] == '\n')
			buff[len - 1] = '\0';
		if (strcmp(buff, data->word) == 0)
			return;
		buff[bytes - 1] = '\n';
		mh_heredoc_realloc(data, buff);
	}
}

char *ft_strjoin_free(char *s1, const char *s2)
{
    size_t	len1;
    size_t	len2;
    char	*out;

	if (s1)
		len1 = ft_strlen(s1);
	else
		len1 = 0;
	len2 = ft_strlen(s2);
	out = malloc((len1 + len2 + 1) * sizeof(char));
    if (!out)
		return (NULL);
	if (s1)
		memcpy(out, s1, len1);
    memcpy(out + len1, s2, len2);
    out[len1 + len2] = '\0';
	free(s1);
	return out;
}


char *extract_line(char **stash)
{
    char	*nl;
    char	*line;
    char	*rest;
    size_t	len;

    if (!*stash || !(nl = strchr(*stash, '\n')))	//ft_strchr
        return NULL;

    len = nl - *stash + 1;
    line = strndup(*stash, len);
    rest = strdup(*stash + len);

    free(*stash);
    *stash = rest;
    return line;
}


static void	heredoc_read(int fd, const char *delim)
{
	char	buff[BUFFER_SIZE + 1];
	char	*stash = NULL;
	ssize_t	n;
	char	*line;

	while((n = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[n] = '\0';
		stash = ft_strjoin_free(stash, buff);
		while ((line = extract_line(&stash)))
		{
			if (!strcmp(line, delim) ||
				(!strncmp(line, delim, strlen(delim)) &&
				line [strlen(delim)] == '\n'))
				return;
			write(1, line, strlen(line));
			free(line);
		}
	}
}


void	mh_heredoc(char *word)
{
//	t_heredoc	data;

//	ft_memset(&data, 0, sizeof(data));
//	data.word = ft_strdup(word);
//	mh_heredoc_read(&data);
//	mh_heredoc_write(&data);
	heredoc_read(0, word);
}*/

// Append a new string to the heredoc lines
void heredoc_add_line(t_heredoc *hd, const char *line)
{
    char **new_lines = realloc(hd->lines, (hd->count + 1) * sizeof(char *));
    if (!new_lines) exit(1);
    hd->lines = new_lines;
    hd->lines[hd->count] = strdup(line);
    hd->count++;
}

// Join old stash with new buffer
char *strjoin_and_free(char *s1, const char *s2)
{
    size_t len1 = s1 ? strlen(s1) : 0;
    size_t len2 = strlen(s2);
    char *out = malloc(len1 + len2 + 1);
    if (!out) exit(1);
    if (s1) memcpy(out, s1, len1);
    memcpy(out + len1, s2, len2);
    out[len1 + len2] = '\0';
    free(s1);
    return out;
}

// Extract one line (up to '\n') from stash
char *extract_line(char **stash)
{
    char *nl;
    char *line;
    char *rest;
    size_t len;

    if (!*stash || !(nl = strchr(*stash, '\n')))
        return NULL;

    len = nl - *stash + 1;
    line = strndup(*stash, len);
    rest = strdup(*stash + len);
    free(*stash);
    *stash = rest;
    return line;
}

void heredoc_read(int fd, const char *delim, t_heredoc *hd)
{
    char buf[BUFFER_SIZE + 1];
    char *stash = NULL;
    ssize_t n;
    char *line;

    while ((n = read(fd, buf, BUFFER_SIZE)) > 0)
    {
        buf[n] = '\0';
        stash = strjoin_and_free(stash, buf);

        while ((line = extract_line(&stash)))
        {
            // Check delimiter (line must be exactly the delimiter + '\n')
            if (strcmp(line, delim) == 0 ||
                (strncmp(line, delim, strlen(delim)) == 0 && line[strlen(delim)] == '\n'))
            {
                free(line);
                goto done;  // stop reading
            }
            heredoc_add_line(hd, line);  // store line for later
            free(line);
        }
    }

done:
    // Output all lines after delimiter found
    for (size_t i = 0; i < hd->count; i++)
        write(1, hd->lines[i], strlen(hd->lines[i]));
}

void	mh_heredoc(char *word)
{
	t_heredoc	data;

	ft_memset(&data, 0, sizeof(data));
//	data.word = ft_strdup(word);
//	mh_heredoc_read(&data);
//	mh_heredoc_write(&data);
	heredoc_read(0, word, &data);
}
