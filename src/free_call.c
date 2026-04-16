/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_call.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azielnic <azielnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:09:47 by lwittwer          #+#    #+#             */
/*   Updated: 2026/04/16 18:41:16 by azielnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheaven.h"

/*
 * IDEA: 	Either all information from the lexer is duplicated or borrowed.
 * 			This is important when it comes to freeing.
 * 			Parser in our case -which creates the commands- borrows everything. 
 * 			Pointers are stored directly and no strdup is used. Tokens stay 
 * 			alive until execution finishes.
 *
 * Memory usage:	input
 *					→ lexer creates tokens
 *					→ parser builds AST using token pointers
 *					→ executor runs commands
 *					→ free AST (not strings)
 *					→ free tokens (strings freed here)
 *
 * INFO:	Only what was allocated needs to be freed. Only the t_redir
 *			contiguous block is allocated. The int is not dynamically
 *			allocated so also does not need to be freed. The other two are
 *			pointers (pointing to allocated memory somewhere but are not
 *			allocated themselves). The content of the pointers is feed 
 *			somehwere else.
 * 
 * 			t_redir includes:	-type (int)
 *								-file (char *)
 *								-fd (int)
 *								-next (t_redir *)		
 */

void	free_tokens(t_token *head)
{
	t_token	*next;

	while (head)
	{
		next = head->next;
		if (head->value)
		{
			free(head->value);
			head->value = NULL;
		}
		head->type = 0;
		free(head);
		head = next;
	}
}

static void	free_redirs(t_redir *head)
{
	t_redir	*next;

	while (head)
	{
		next = head->next;
		head->type = 0;
		if (head->file)
		{
			free(head->file);
			head->file = NULL;
		}
		if (head->tmp_file)
		{
			free(head->tmp_file);
			head->tmp_file = NULL;
		}
		free(head);
		head = next;
	}
}
void	free_cmds(t_cmd *head)
{
	t_cmd	*next;

	while (head)
	{
		next = head->next;
		if (head->argv)
		{
			free_arr(head->argv);
			head->argv = NULL;
		}
		if (head->redir)
		{
			free_redirs(head->redir);
			head->redir = NULL;
		}
		free(head);
		head = next;
	}
	next = NULL;
}
