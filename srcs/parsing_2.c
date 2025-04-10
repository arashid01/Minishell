/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amal <amal@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 05:38:25 by amal              #+#    #+#             */
/*   Updated: 2025/04/10 06:22:29 by amal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*parse_all_commands(t_token *tokens, int count)
{
	t_cmd	*head = NULL;
	t_cmd	*curr = NULL;
	int		start = 0;
	int		i = 0;

	while (i <= count)
	{
		if (i == count || tokens[i].type == T_PIPE)
		{
			t_cmd *new_cmd = parse_single_command(&tokens[start], i - start);
			if (!new_cmd)
				return (NULL);

			if (!head)
				head = new_cmd;
			else
				curr->next = new_cmd;

			curr = new_cmd;
			start = i + 1;
		}
		i++;
	}
	return (head);
}
t_cmd	**parse_input(t_token *tokens, int token_count, int *cmd_count)
{
	t_cmd	**cmds;

	cmds = malloc(sizeof(t_cmd *) * 1);
	if (!cmds)
		return (NULL);
	cmds[0] = parse_single_command(tokens, token_count);
	*cmd_count = 1;
	return (cmds);
}
