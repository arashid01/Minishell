/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amal <amal@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:15:42 by amal              #+#    #+#             */
/*   Updated: 2025/04/18 18:52:10 by amal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	skip_quoted_str(char *line, int i, char quote_c)
{
	while (line[i])
	{
		if (quote_c == '"' && line[i] == '\\' && line[i + 1] == '"')
		{
			i += 2;
			continue;
		}
		if (line[i] == quote_c)
		{
			i++;
			break;
		}
		i++;
	}
	return (i);
}

static void	save_word(char *line, int start, int end, t_token **token_list)
{
	t_token	*new;
	t_token	*runner;
	int		len;
	
	new = malloc(sizeof(t_token));
	if (!new)
		return ;
	if (line[end - 1] == '\'' || line [end - 1] == '"')
		end--;
	len = end - start;
	new->val = save_token(&line[start], len);
	new->type = WORD;
	new->next = NULL;
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

void	handle_word(char *line, int *i, t_status *status, t_token **token_list)
{
	int	start;

	start = *i;
	while (line[*i])
	{
		if (status->normal && (line[*i] == 32 || is_operator(line[*i])))
			break ;
		if (line[*i] == '\'' || line[*i] == '"')
			skip_quoted_str(line, *i, line[*i]);
		handle_quotes(line[*i], status);
		(*i)++;
	}
	save_word(line, start, *i, token_list);
}
