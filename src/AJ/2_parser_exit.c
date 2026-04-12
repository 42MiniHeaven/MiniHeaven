#include "miniheaven.h"

void	parser_exit(t_parser *p)
{
	if (p->head)
		free_cmds(p->head);
	if (p->current)
		p->current = NULL;
	p->state = 0;
	p->last_redir = 0;
}