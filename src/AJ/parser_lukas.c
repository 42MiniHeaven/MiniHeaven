void	parse(t_shell *data)
{
	if (!data || !data->tokens)
		return ;
	while (data->tokens)
	{

		data->tokens = data->tokens->next;
	}
}
