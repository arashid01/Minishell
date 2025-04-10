/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amal <amal@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 05:34:54 by amal              #+#    #+#             */
/*   Updated: 2025/04/10 05:34:55 by amal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_tokens(t_token *tokens, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(tokens[i].value);
		i++;
	}
	free(tokens);
}

void	free_cmd(t_cmd *cmd)
{
	int	i = 0;

	while (cmd->args && cmd->args[i])
	{
		free(cmd->args[i]);
		i++;
	}
	free(cmd->args);
	if (cmd->infile)
		free(cmd->infile);
	if (cmd->outfile)
		free(cmd->outfile);
	free(cmd);
}