/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:09:57 by lwittwer          #+#    #+#             */
/*   Updated: 2026/01/18 18:53:41 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif
#include <aio.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

typedef struct s_heredoc
{
	char	**lines; //appends every read input string to this function
	char	*word;	//delimiter for heredoc
	size_t	count;	//textarr size -> starts with 1 for NULL string
} t_heredoc;

//heredoc.c
void	mh_heredoc(char *word);
//static void	mh_heredoc_read(t_heredoc *data);
//static void	mh_heredoc_write(t_heredoc *data);
//static void	mh_heredoc_realloc(t_heredoc *data);
//heredoc_utils.c
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *s, int c, size_t n);
//free.c
void	free_arr(char **arr);
void	free_str(char *str);
#endif
