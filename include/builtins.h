/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 16:08:13 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/16 18:37:09 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "structs.h"

int	builtin_cd(t_cmd *cmd, t_environment *list);
int	builtin_echo(t_cmd *cmd, t_environment *list);
int	builtin_env(t_cmd *cmd, t_environment *list);
int	builtin_exit(t_cmd *cmd, t_shell *data);
int	builtin_export(t_cmd *cmd, t_environment *list);
int	builtin_pwd(t_cmd *cmd, t_environment *list);
int	builtin_unset(t_cmd *cmd, t_environment *list);

#endif
