/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 14:52:54 by azielnic          #+#    #+#             */
/*   Updated: 2026/01/18 21:34:58 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// PARSER GENEREL TO-DOS
// Handles grammar & structure:
//  -Pipe placement
//  -Redirection correctness
//  -Missing operands

// Why return type t_cmd* ? 
// --> Parser is creating the list, not modifying an existing one.
// Why t_token *tokens and not t_token **tokens?
// --> The pipeline is the top level, so parse_pipeline consumes all tokens.
// t_cmd   *parse_pipeline(t_token *tokens)
// {
//     t_cmd *cmds;

//     cmds = NULL;
//     while (tokens) // could lead to issues think of including length or next node
//     {
//         cmds = parse_cmommand(&tokens);
//     }
//     return;
// }
int check_operands()
{}

int check_redirections()
{

}

int check_pipes(t_token *tokens)
{
    t_token *current;
    t_token *prev;

    if (!tokens)
        return (1); // empty input ok for pipes
    if (tokens->type == PIPE)
    {
        printf("Syntax error: pipe at the beginning\n"); // replace printf
        return (0);
    }
    current = tokens;
    prev = NULL;
    while (current != NULL) // in case this creates issues create a new varaible
    {
        if (current->type == PIPE && prev && prev->type == PIPE)
        {
            printf("Syntax error: two pipes in a row\n"); // replace printf
            return (0);
        }
        prev = current;
        current = current->next;
    }
    if (prev && prev->type != WORD)
    {
            printf("Syntax error: word needed at the end\n"); // replace printf
            return (0);
    }
    return (1);
}

int parse_input_check(t_token *tokens)
{
    if (!tokens)
        return (0);
    if (!check_pipes(tokens))
        return (0);
    if (!check_redirections(tokens))
        return (0);
    if (!check_operands(tokens))
        return (0);
    return (1);
}

// Helper to create a token
t_token *create_token(char *value, int type)
{
    t_token *tok = malloc(sizeof(t_token));
    tok->value = value;
    tok->type = type;
    tok->next = NULL;
    return tok;
}

int main()
{
    // Example 1: valid input "echo hello | grep hi"
    t_token *t1 = create_token("echo", WORD);
    t_token *t2 = create_token("hello", WORD);
    t_token *t3 = create_token("|", PIPE);
    t_token *t4 = create_token("grep", WORD);
    t_token *t5 = create_token("hi", WORD);
    t1->next = t2;
    t2->next = t3;
    t3->next = t4;
    t4->next = t5;

    printf("Test 1: %d\n", parser_input_check(t1)); // should print 1

    // Example 2: pipe at the beginning "| ls"
    t_token *p1 = create_token("|", PIPE);
    t_token *p2 = create_token("ls", WORD);
    p1->next = p2;

    printf("Test 2: %d\n", parse_input_check(p1)); // should print 0

    // Example 3: pipe at the end "ls |"
    t_token *p3 = create_token("ls", WORD);
    t_token *p4 = create_token("|", PIPE);
    p3->next = p4;

    printf("Test 3: %d\n", parse_input_check(p3)); // should print 0

    // Example 4: two pipes in a row "ls || grep"
    t_token *p5 = create_token("ls", WORD);
    t_token *p6 = create_token("|", PIPE);
    t_token *p7 = create_token("|", PIPE);
    t_token *p8 = create_token("grep", WORD);
    p5->next = p6;
    p6->next = p7;
    p7->next = p8;

    printf("Test 4: %d\n", parse_input_check(p5)); // should print 0

    // Free memory (optional in tests, but good practice)
    t_token *tmp;
    while (t1)
    {
        tmp = t1->next;
        free(t1);
        t1 = tmp;
    }
    while (p1)
    {
        tmp = p1->next;
        free(p1);
        p1 = tmp;
    }
    while (p3)
    {
        tmp = p3->next;
        free(p3);
        p3 = tmp;
    }
    while (p5)
    {
        tmp = p5->next;
        free(p5);
        p5 = tmp;
    }

    return 0;
}
