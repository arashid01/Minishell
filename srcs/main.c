/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amal <amal@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 01:31:06 by amal              #+#    #+#             */
/*   Updated: 2025/04/10 06:21:24 by amal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	char	*line;
	char	**str_tokens;
	t_token	*tokens;
	t_cmd	**cmds;
	int		cmd_count;
	int		token_count;
	
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			break;

		str_tokens = tokenize(line);
		token_count = count_tokens(line);
		tokens = build_token_list(str_tokens, token_count);
		cmds = parse_input(tokens, token_count, &cmd_count);

		if (cmd_count == 1)
			execute_command(cmds[0], envp);
	}

	free(line);
	free_tokens(tokens, token_count);
	free_cmds(cmds, cmd_count);
	return (0);
}


