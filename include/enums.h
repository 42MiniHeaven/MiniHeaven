/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 18:18:07 by azielnic          #+#    #+#             */
/*   Updated: 2026/04/16 18:18:10 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

enum	e_token_type
{
	WORD = 0,
	PIPE = 1,
	REDIR_OUT = 2,
	REDIR_IN = 3,
	APPEND = 4,
	HEREDOC = 5
};

enum	e_parser_state
{
	EXPECT_COMMAND = 0,
	EXPECT_ARG_OR_REDIR = 1,
	EXPECT_REDIR_TARGET = 2
};