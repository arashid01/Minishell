/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amal <amal@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 05:35:03 by amal              #+#    #+#             */
/*   Updated: 2025/04/10 05:35:04 by amal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_args(t_token *tokens, int count)
{
	int	i;
	int	arg_count;

	arg_count = 0;
	i = 0;
	while (i < count)
	{
		if (tokens[i].type == T_WORD)
		{
			if (i > 0 && (
				tokens[i - 1].type == T_REDIR_IN ||
				tokens[i - 1].type == T_REDIR_OUT ||
				tokens[i - 1].type == T_REDIR_AP ||
				tokens[i - 1].type == T_HEREDOC))
			{
				i++;
				continue;
			}
			arg_count++;
		}
		i++;
	}
	return (arg_count);
}

void	fill_command(t_cmd *cmd, t_token *tokens, int count)
{
	int	i = 0;
	int	arg_i = 0;

	while (i < count)
	{
		if (tokens[i].type == T_WORD)
		{
			if (i > 0 && (
				tokens[i - 1].type == T_REDIR_IN ||
				tokens[i - 1].type == T_REDIR_OUT ||
				tokens[i - 1].type == T_REDIR_AP ||
				tokens[i - 1].type == T_HEREDOC))
			{
				i++;
				continue;
			}
			cmd->args[arg_i++] = ft_strdup(tokens[i].value);
		}
		else if (tokens[i].type == T_REDIR_IN && i + 1 < count)
			cmd->infile = ft_strdup(tokens[i + 1].value);
		else if (tokens[i].type == T_REDIR_OUT && i + 1 < count)
		{
			cmd->outfile = ft_strdup(tokens[i + 1].value);
			cmd->append = 0;
		}
		else if (tokens[i].type == T_REDIR_AP && i + 1 < count)
		{
			cmd->outfile = ft_strdup(tokens[i + 1].value);
			cmd->append = 1;
		}
		i++;
	}
	cmd->args[arg_i] = NULL;
}

t_cmd	*parse_single_command(t_token *tokens, int count)
{
	t_cmd	*cmd;
	int		arg_count;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->append = 0;

	arg_count = count_args(tokens, count);
	cmd->args = malloc(sizeof(char *) * (arg_count + 1));
	if (!cmd->args)
		return (NULL);

	fill_command(cmd, tokens, count);
	return (cmd);
}

