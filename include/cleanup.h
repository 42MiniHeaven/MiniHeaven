/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 19:52:36 by azielnic          #+#    #+#             */
/*   Updated: 2026/04/26 16:44:45 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEANUP_H
# define CLEANUP_H

# include "structs.h"

// Freeing
void	free_arr(char **arr);
void	free_environment(t_environment *list);
void	free_tokens(t_token *lst);
void	free_cmds(t_cmd *lst);
void	free_fds(t_fds *fd);
void	free_loop(t_shell *data);

// Error handling
void	ft_error(char *func, char *error, int fd);
void	redir_error(t_redir *tmp);
void	ft_err_three(char *func, char *error, char *extra);
void	ft_err_export_three(char *func, char *error, char *extra);
char	*ft_strjoin_three(char *s1, char *s2, char *s3);
void	handle_export_overflow(t_environment *list, char *str);

#endif
