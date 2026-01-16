/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:09:57 by lwittwer          #+#    #+#             */
/*   Updated: 2026/01/16 16:50:16 by lwittwer         ###   ########.fr       */
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
	char	**text; //appends every read input string to this function
	char	*word;	//delimiter for heredoc
	int		tsize;	//textarr size -> starts with 1 for NULL string
	int		expand;	//active expanding 0 false or 1 true
} t_heredoc;

//heredoc.c
void	mh_heredoc(int n, char *word);
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
