/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amal <amal@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 01:31:06 by amal              #+#    #+#             */
/*   Updated: 2025/05/09 15:20:09 by amal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_minishell(char **envp)
{
	char	*line;
	t_token	*token_list;
	t_cmd	*cmd_list;
	
	(void)envp;
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		add_history(line);
		token_list = tokenize_line(line);
		print_tokens(token_list);
		cmd_list = parse_tokens(token_list);
		print_cmds(cmd_list);
		execute_command(cmd_list, envp, STDIN_FILENO, STDOUT_FILENO);
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
	
	init_minishell(envp);
	
	return (0);
}
