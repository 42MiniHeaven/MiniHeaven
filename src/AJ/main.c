/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 17:46:11 by azielnic          #+#    #+#             */
/*   Updated: 2026/03/18 22:43:17 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniheaven.h"

// ------------------- MAIN FOR EXPANDER ---------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// ----------------- MOCK STRUCTS -----------------

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	int		exit_code;
	t_env	*llist;
}	t_shell;

// ----------------- MOCK LIBFT -----------------

size_t	ft_strlen(const char *s) { return strlen(s); }

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	total;

	total = nmemb * size;
	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (total / nmemb != size)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	return memcpy(dst, src, n);
}

char	*ft_strdup(const char *s)
{
	return strdup(s);
}

char	*ft_substr(char *s, int start, int len)
{
	char *res = malloc(len + 1);
	memcpy(res, s + start, len);
	res[len] = '\0';
	return res;
}

int	ft_isalnum(int c)
{
	return isalnum(c);
}

char	*ft_itoa(int n)
{
	char *buf = malloc(12);
	sprintf(buf, "%d", n);
	return buf;
}

char	*ft_strchr(const char *s, int c)
{
	return strchr(s, c);
}

// ----------------- ENV HELPERS -----------------

char	*get_env_value(char *key, t_env *env)
{
	t_env	*node;

	node = env_find(env, key);
	if (!node)
		return (NULL);
	return (node->value);
}

// ----------------- REQUIRED STUBS -----------------

// // simple quote remover (VERY BASIC)
// char	*remove_quotes(char *str)
// {
// 	char *res = malloc(strlen(str) + 1);
// 	int i = 0, j = 0;

// 	while (str[i])
// 	{
// 		if (str[i] != '\'' && str[i] != '"')
// 			res[j++] = str[i];
// 		i++;
// 	}
// 	res[j] = '\0';
// 	free(str);
// 	return res;
// }

// not used in this test
void expand_agrs(char **argv, t_shell *data) {(void)argv;(void)data;}
void expand_redir(void *redir, t_shell *data) {(void)redir;(void)data;}

// ----------------- ENV SETUP -----------------

t_env *create_env(char *key, char *value)
{
	t_env *node = malloc(sizeof(t_env));
	node->key = key;
	node->value = value;
	node->next = NULL;
	return node;
}

// ----------------- MAIN -----------------

int main(void)
{
	t_shell shell;
	t_env *env1 = create_env("USER", "marvin");
	t_env *env2 = create_env("HOME", "/home/marvin");

	env1->next = env2;

	shell.llist = env1;
	shell.exit_code = 42;

	// ---- TEST CASES ----
	char *tests[] = {
		ft_strdup("hello $USER"),
		ft_strdup("'$USER'"),
		ft_strdup("\"$USER\""),
		ft_strdup("$HOME/path"),
		ft_strdup("$?"),
		ft_strdup("noexpand"),
		NULL
	};

	for (int i = 0; tests[i]; i++)
	{
		char *res = expand_word(tests[i], &shell);
		printf("Input : %s\nOutput: %s\n\n", tests[i], res);
		free(res);
	}

	return 0;
}

// int main(void)
// {
//     char    *line = "ls -l | cat << e";
//     t_token *tokens;
//     t_token *tmp;
//     t_cmd   *cmds;
//     t_cmd   *c;

//     tokens = lexer(line);

//     printf("=== TOKENS ===\n");
//     tmp = tokens;
//     while (tmp)
//     {
//         printf("TYPE=%d VALUE=%s\n", tmp->type, tmp->value);
//         tmp = tmp->next;
//     }

//     cmds = parse(tokens);
//     if (!cmds)
//         return (1);

//     printf("\n=== COMMANDS ===\n");
//     c = cmds;
//     while (c)
//     {
//         int i = 0;

//         printf("CMD: [%s]\n", c->cmd);

//         printf("ARGV:");
//         while (c->argv && c->argv[i])
//             printf(" [%s]", c->argv[i++]);
//         printf("\n");

//         t_redir *r = c->redir;
//         while (r)
//         {
//             printf("REDIR type=%d file=%s\n", r->type, r->file);
//             r = r->next;
//         }

//         c = c->next;
//         printf("\n");
//     }
//     destroy_all(cmds, tokens);
//     return (0);
// }
