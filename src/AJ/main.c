/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 17:46:11 by azielnic          #+#    #+#             */
/*   Updated: 2026/01/25 18:03:47 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int main(void)
{
    char    *line = "ls -l | cat << e";
    t_token *tokens;
    t_token *tmp;
    t_cmd   *cmds;
    t_cmd   *c;

    tokens = lexer(line);

    printf("=== TOKENS ===\n");
    tmp = tokens;
    while (tmp)
    {
        printf("TYPE=%d VALUE=%s\n", tmp->type, tmp->value);
        tmp = tmp->next;
    }

    cmds = parse(tokens);
    if (!cmds)
        return (1);

    printf("\n=== COMMANDS ===\n");
    c = cmds;
    while (c)
    {
        int i = 0;

        printf("CMD: %s\n", c->cmd);

        printf("ARGV:");
        while (c->argv && c->argv[i])
            printf(" [%s]", c->argv[i++]);
        printf("\n");

        t_redir *r = c->redir;
        while (r)
        {
            printf("REDIR type=%d file=%s\n", r->type, r->file);
            r = r->next;
        }

        c = c->next;
        printf("\n");
    }

    return (0);
}
