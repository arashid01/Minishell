/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amal <amal@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:09:47 by amal              #+#    #+#             */
/*   Updated: 2025/04/18 18:19:21 by amal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	get_operator_type(t_token *token)
{
	if (ft_strncmp(token->val, ">>", 2) == 0)
		token->type = REDIR_APPEND;
	else if (ft_strncmp(token->val, "<<", 2) == 0)
		token->type = HEREDOC;
	else if (token->val[0] == '>')
		token->type = REDIR_OUT;
	else if (token->val[0] == '<')
		token->type = REDIR_IN;
	else if (token->val[0] == '|')
		token->type = PIPE;
	else
	{
		token->type = -1;
		printf("Unknown operator"); //remove later and handle -1
	}
}

static void	save_operator(char *line, int start, int end, t_token **token_list)
{
	t_token	*new;
	t_token	*runner;
	int		len;
	
	new = malloc(sizeof(t_token));
	if (!new)
		return ;
	len = end - start;
	new->val = save_token(&line[start], len);
	new->next = NULL;
	get_operator_type(new);
	if (*token_list == NULL)
		*token_list = new;
	else
	{
		runner = *token_list;
		while (runner->next)
			runner = runner->next;
		runner->next = new;
	}
}

void	handle_operator(char *line, int *i, t_token **token_list)
{
	int	start;

	start = *i;
	if ((line[*i] == '>' && line[*i + 1] == '>')
		|| (line[*i] == '<' && line[*i + 1] == '<'))
		(*i) += 2;
	else
		(*i)++;
	save_operator(line, start, *i, token_list);
}