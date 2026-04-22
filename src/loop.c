#include "miniheaven.h"

extern volatile sig_atomic_t	g_signal_status;

void	reset_shell(t_shell *data)
{
	data->input = NULL;
	data->tokens = NULL;
	data->cmds = NULL;
	data->should_exit = 0;
	data->fds = NULL;
	data->envp = NULL;
	data->path = NULL;
}

void	free_loop(t_shell *data)
{
	if (data->tokens)
		free_tokens(data->tokens);
	if (data->cmds)
		free_cmds(data->cmds);
	if (data->input)
		free(data->input);
	if (data->envp)
		free_arr(data->envp);
	if (data->path)
		free(data->path);
}

void	loop(t_shell *data)
{
	while (1)
	{
		reset_shell(data);
		handle_signals_prompt();
		// needs to be removed
		if (isatty(fileno(stdin)))
		{
			data->input = readline("miniheaven> ");
			if (!data->input)
				break ;
		}
		else
		{
			char *line;
			line = read_file(fileno(stdin));
			if (!line)
				break ;
			data->input = ft_strtrim(line, "\n");
			free(line);
		}
		// needs to be removed 
		// data->input = readline("miniheaven> ");
		if (!data->input)
			break ;
		if (g_signal_status != 0)
			set_exit_code(data);
		if (data->input)
		{
			if (ft_strlen(data->input) > 0)
				add_history(data->input);
			tokeniser(data, data->input);
		}
		if (parser(data) != 0)
		{
			data->last_exit = 2;
			free_loop(data);
			continue ;
		}
		if (prepare_heredocs(data, data->cmds) < 0)
		{
			free_loop(data);
			continue ;
		}
		expand_commands(data);
		execute(data);
		free_loop(data);
		if (data->should_exit == 1)
			break ;
	}
}

