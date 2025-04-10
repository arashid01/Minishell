/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amal <amal@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 01:31:06 by amal              #+#    #+#             */
/*   Updated: 2025/04/10 05:51:14 by amal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char	*line;
	char	**str_tokens;
	t_token	*tokens;
	t_cmd	*cmds;
	t_cmd	*tmp;
	int		token_count;

	line = readline("minishell> ");
	if (!line)
		return (0);

	str_tokens = tokenize(line);
	if (!str_tokens)
		return (1);

	token_count = 0;
	while (str_tokens[token_count])
		token_count++;

	tokens = build_token_list(str_tokens, token_count);
	if (!tokens)
		return (1);

	cmds = parse_all_commands(tokens, token_count);
	tmp = cmds;
	while (tmp)
	{
		printf("Command:\n");
		for (int i = 0; tmp->args && tmp->args[i]; i++)
			printf("  Arg: %s\n", tmp->args[i]);
		if (tmp->infile)
			printf("  Infile: %s\n", tmp->infile);
		if (tmp->outfile)
			printf("  Outfile: %s (%s)\n", tmp->outfile, tmp->append ? "append" : "overwrite");
		tmp = tmp->next;
	}

	free(line);
	free_tokens(tokens, token_count);
	while (cmds)
	{
		tmp = cmds->next;
		free_cmd(cmds);
		cmds = tmp;
	}
	return (0);
}


