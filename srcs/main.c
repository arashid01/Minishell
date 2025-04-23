/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amal <amal@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 01:31:06 by amal              #+#    #+#             */
/*   Updated: 2025/04/22 17:03:37 by amal             ###   ########.fr       */
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
		execute_pipeline_recursive(cmd_list, envp);
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



