/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 17:46:11 by azielnic          #+#    #+#             */
/*   Updated: 2026/02/04 22:23:52 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int main(void)
{
    char    *line = "ls -l | echo hello";
    // char    *line = "< input.txt";
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

        printf("CMD:");
        while (c->cmd && c->cmd[i])
            printf(" [%c]", c->cmd[i++]);
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
    destroy_all(cmds, tokens);
    return (0);
}
