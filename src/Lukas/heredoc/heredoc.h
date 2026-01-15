/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:09:57 by lwittwer          #+#    #+#             */
/*   Updated: 2026/01/15 21:07:52 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

typedef struct s_heredoc
{
	char	**text;
	char	*EOF;
	char	*tmpfile;
} t_heredoc;

void	mh_heredoc(char **arr);
#endif
