/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:57:14 by azielnic          #+#    #+#             */
/*   Updated: 2026/01/12 21:01:46 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft/libft.h"

typedef enum e_token_type
{
    WORD,       	// ls, -l, filename
    PIPE,       	// |
    REDIR_OUT,  	// >
    REDIR_IN,   	// <
    APPEND,     	// >>
    HEREDOC     	// <<
}   t_token_type;

typedef struct s_token
{
    char            *value;
    t_token_type     type;
    struct s_token  *next;
}   t_token;

#endif
