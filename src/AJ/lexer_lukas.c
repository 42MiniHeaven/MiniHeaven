// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   lexer_lukas.c                                      :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2026/03/22 11:03:22 by lwittwer          #+#    #+#             */
// /*   Updated: 2026/03/22 15:11:28 by azielnic         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../include/miniheaven.h"

// int ft_is_operator(int c)
// {
//     return (c == '|' || c == '<' || c == '>');
// }

// // https://www.linux.org/threads/bash-03-%E2%80%93-command-line-processing.38676/ 
// // "A token that contains no quotes and at least one meta-character is an ‘operator’."

// int ft_isspace(int c)
// {
//     return (c == ' ');   // could include more whitespaces (tab and newline)
//     // could also include additional separation characters like & , and ;
// }

// void	token_add_back(t_token **head, t_token *new)
// {
// 	t_token	*tmp;

// 	if (!head || !new)
// 		return ;
// 	if (!*head)
// 	{
// 		*head = new;
// 		return ;
// 	}
// 	tmp = *head;
// 	while (tmp->next)
// 		tmp = tmp->next;
// 	tmp->next = new;
// }

// t_token *token_new(int type, char *value)
// {
// 	t_token	*token;

// 	token = malloc(sizeof(t_token));
// 	if (!token)
// 		return (NULL);
// 	token->value = value;
// 	token->type = type;
// 	token->next = NULL;
// 	return (token);
// }

// void	create_token(char *input, int *i, int start, t_token **head)
// {
// 	char	*value;
// 	t_token	*token;>

// 	value = ft_substr(input, start, *i - start);
// 	if (!value)
// 		syntax_error("failure assigning 'value' in lex_word function");
// 	token = token_new(WORD, value);
// 	if (!token)
// 		syntax_error("failure assigning 'token' in lex_word function");
// 	token_add_back(head, token);
// }

// void	lex_word(char *input, int *i, t_token **head)
// {
// 	int	start;
// >
// 	start = *i;
// 	while (input[*i] && !(ft_is_operator(input[*i])) && !(ft_isspace(input[*i])))
// 	{
// 		if (input[*i] && (input[*i] == '\'' || input[*i] == '"'))
// 		{
// 			if (!lex_quotes(input, i))
// 				return ;
// 		}
// 		else
// 			(*i)++;
// 	}
// 	create_token(input, i, start, head);
// }

// void	lex_operator(char *input, int *i, t_token **head)
// {
// 	t_token	*token;

// 	token = NULL;
// 	if (input[*i] == '|')
// 		token = token_new(PIPE, ft_strdup("|"));
// 	else if (input[*i] == '>' && input[(*i) + 1] != '>')
// 		token = token_new(REDIR_OUT, ft_strdup(">"));
// 	else if (input[*i] == '<' && input[(*i) + 1] != '<')
// 		token = token_new(REDIR_IN, ft_strdup("<"));
// 	else if (input[*i] == '>' && input[(*i) + 1] == '>')
// 	{
// 		token = token_new(APPEND, ft_strdup(">>"));
// 		(*i)++;
// 	}
// 	else if (input[*i] == '<' && input[(*i) + 1] == '<')
// 	{
// 		token = token_new(HEREDOC, ft_strdup("<<"));
// 		(*i)++;
// 	}
// 	(*i)++;
// 	token_add_back(head, token);
// }

// void	lexer(t_shell *data, char *input)
// {
// 	t_token	*tokens;
// 	size_t	input_len;
// 	int		i;

// 	tokens = NULL;
// 	if (!data || !input)
// 		return ;
// 	input_len = ft_strlen(input);
// 	i = 0;
// 	while ((size_t)i < input_len)
// 	{
// 		if (ft_isspace(input[i]))
// 		{
// 			i++;
// 			continue ;
// 		}
// 		else if (ft_is_operator(input[i]))
// 			lex_operator(input, &i, &tokens);
// 		else
// 			lex_word(input, &i, &tokens);
// 	}
// 	data->tokens = tokens;
// }
