/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amal <amal@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 01:31:06 by amal              #+#    #+#             */
/*   Updated: 2025/05/20 20:55:40 by amal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_shell	g_shell;

void	init_minishell(t_shell *shell)
{
	char	*line;
	t_token	*token_list;
	t_cmd	*cmd_list;

	(void)shell;

	while (1)
	{
		setup_parent_signals();
		line = readline("minishell$ ");
		if (!line)
			break ;
		add_history(line);
		token_list = tokenize_line(line, shell);
		print_tokens(token_list);
		cmd_list = parse_tokens(token_list);
		print_cmds(cmd_list);
		execute_command(cmd_list, shell, STDIN_FILENO, STDOUT_FILENO);
	}
	if (line)
		free(line);
	rl_clear_history();
	exit (0);
}

int main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	t_shell shell;

	shell.envp = copy_env(envp);
	if (!shell.envp)
	{
		perror("minishell : failed to initialize environment");
		return (1);
	}
	shell.exit_status = 0;
	init_minishell(&shell);
	free_env(shell.envp);
	return (shell.exit_status);
}
