/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_quotes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 20:19:12 by azielnic          #+#    #+#             */
/*   Updated: 2026/04/03 22:44:13 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniheaven.h"

/*
 * QUOTE HANDLING
 * Quotes are handled in the lexer by checking unclosed quotes and in the 
 * expander by removing not needed quotes after expansion.
 */

// ********************************* LEXER ************************************

/*
 * DESCRIPTION
 * Checks for unclosed quotes before the creating tokens.
 */

bool	lex_unclosed_quotes(char *input, int *i)
{	
	char	quote;

	quote = input[*i];
	(*i)++;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (!input[*i])
	{
		syntax_error("unclosed quote");
		// set exit code
		return (false);	
	}
	(*i)++;
	return (true);
}
 
// ******************************** EXPANDER **********************************

/*
 * DESCRIPTION
 * Function exists for the remove_quotes() funtion to check the length of the 
 * new string without the quotes. It uses the mask and substracts the number of 
 * quotes.
 */

static int	count_len(char *mask)
{
	int	i;
	int	len;
	
	i = 0;
	len = 0;
	while (mask[i])
	{
		if (mask[i] != 'Q')
			len++;
		i++;
	}
	return(len);
}

static char	*remove_quotes(char *word, char *mask)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	result = ft_calloc(count_len(mask) + 1, sizeof(char));
	if (!result)
		return (NULL); // do we need an error?
	while (word[j] && mask[j])
	{
		while (mask[j] && mask[j] == 'Q')
			j++;
		result[i] = word[j];
		i++;
		j++;
	}
	return (result);
}

bool	quotes_removal(char **argv)
{
	int		i;
	char	*mask;
	char	*tmp;

	i = 0;
	while (argv[i])
	{
		mask = create_mask(argv[i]);
		tmp = remove_quotes(argv[i], mask);
		if (!tmp)
			return (free(mask), false);
		free(argv[i]);
		free(mask);
		argv[i] = tmp;
		i++;
	}
	return (true);
}

//********************************EXPANDER_HEREDOC*******************************

char	*remove_quote(char *str)
{
	int		len;
	char	*ret;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if ((str[0] == str[len]) && (str[0] == '"' || str[0] == '\''))
	{
		ret = ft_substr(str, 1, len - 2);
		free(str);
		return (ret);
	}
	else
		return (str);
}

int	need_heredoc_expansion(char *str)
{
	int	len;

	if (!str)
		return (0);
	len = ft_strlen(str);
	if (str[0] == str[len] && (str[0] == '\'' || str[0] == '"'))
		return (0);
	return (1);
}
