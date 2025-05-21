/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nora <nora@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:15:42 by amal              #+#    #+#             */
/*   Updated: 2025/05/21 11:09:55 by nora             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	save_word(char *line, int start, int end, t_token **token_list, t_shell *shell)
{
	t_token	*new;
	t_token	*runner;
	char	*str;
	int		len;
	
	new = malloc(sizeof(t_token));
	if (!new)
		return ;
	if (line[end - 1] == '\'' || line [end - 1] == '"')
		end--;
	len = end - start;
	str = save_token(&line[start], len);
	new->val = expand_exit_status(str, shell->exit_status);
	free(str);
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

void	handle_word(char *line, int *i, t_status *status, t_token **token_list, t_shell *shell)
{
	int	start;

	start = *i;
	while (line[*i])
	{
		if (status->normal && (line[*i] == 32 || is_operator(line[*i])))
			break ;
		handle_quotes(line[*i], status);
		(*i)++;
	}
	save_word(line, start, *i, token_list, shell);
}
