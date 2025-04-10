/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amal <amal@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 01:31:06 by amal              #+#    #+#             */
/*   Updated: 2025/04/10 05:29:47 by amal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char	*line;
	char	**str_tokens;
	t_token	*tokens;
	t_cmd	*cmd;
	int		count;

	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			break;
		if (line[0] == '\0')
			continue;

		str_tokens = tokenize(line);
		count = count_tokens(line);
		tokens = build_token_list(str_tokens, count);
		cmd = parse_single_command(tokens, count);

		printf("Args:\n");
		for (int i = 0; cmd->args && cmd->args[i]; i++)
			printf("- %s\n", cmd->args[i]);
		printf("Infile: %s\n", cmd->infile);
		printf("Outfile: %s (append: %d)\n", cmd->outfile, cmd->append);

		free_tokens(tokens, count);
		free(str_tokens);
		free_cmd(cmd);
		free(line);
	}
	return (0);
}

