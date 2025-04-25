/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amal <amal@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:35:41 by amal              #+#    #+#             */
/*   Updated: 2025/04/25 17:48:18 by amal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_args(t_token *token)
{
	int	count;

	count = 0;
	while (token && token->type == WORD)
	{
		count++;
		token = token->next;
	}
	return (count);
}

char	**build_argv(t_token **token)
{
	int		i;
	int		argc;
	char	**argv;

	i = 0;
	argc = count_args(*token);
	argv = malloc (sizeof(char *) * (argc + 1));
	if (!argv)
		return (NULL);
	while (*token && (*token)->type == WORD)
	{
		argv[i++] = ft_strdup((*token)->val);
		*token = (*token)->next;
	}
	argv[i] = NULL;
	return (argv);
}

t_cmd	*parse_tokens(t_token *token_list)
{
	if (!token_list)
		return (NULL);
	t_cmd *cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = build_argv(&token_list);
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->append = 0;
	cmd->has_pipe = 0;
	cmd->next = NULL;
	while (token_list)
	{
		if (token_list->type == REDIR_IN && token_list->next
			&& token_list->next->type == WORD)
		{
			cmd->infile = ft_strdup(token_list->next->val);
			token_list = token_list->next;
		}
		else if (token_list->type == REDIR_OUT && token_list->next
			&& token_list->next->type == WORD)
		{
			cmd->outfile = ft_strdup(token_list->next->val);
			cmd->append = 0;
			token_list = token_list->next;
		}
		else if (token_list->type == REDIR_APPEND && token_list->next
			&& token_list->next->type == WORD)
		{
			cmd->outfile = ft_strdup(token_list->next->val);
			cmd->append = 1;
			token_list = token_list->next;
		}
		else if (token_list->type == PIPE)
		{
			cmd->has_pipe = 1;
			token_list = token_list->next;
			cmd->next = parse_tokens(token_list);
			break ;
		}
		token_list =  token_list->next;
	}
	return (cmd);
}

void print_cmds(t_cmd *cmd)
{
	int i = 0;
	while (cmd)
	{
		printf("Command:\n");
		while (cmd->argv[i])
		{
			printf("  Arg[%d]: %s\n", i, cmd->argv[i]);
			i++;
		}
		printf("  Has pipe: %d\n\n", cmd->has_pipe);
		i = 0;
		cmd = cmd->next;
	}
}
