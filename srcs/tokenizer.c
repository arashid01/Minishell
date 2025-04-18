/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amal <amal@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:41:48 by amal              #+#    #+#             */
/*   Updated: 2025/04/18 17:05:56 by amal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_operator(char c)
{
	return ((c == '|') || (c == '<') || (c == '>'));
}

char	*save_token(char *start, int len)
{
	int		i;
	char	*token;

	i = 0;
	token = malloc(sizeof(char) * (len + 1));
	while (i < len)
	{
		token[i] = start[i];
		i++;
	}
	token[i] = '\0';
	return (token);
}

void	print_tokens(t_token *token)
{
	while (token)
	{
		ft_printf("A token: [%s] -> %d \n", token->val, token->type);
		token = token->next;
	}
}

void	get_operator_type(t_token *token)
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
		ft_printf("Unknown operator"); //remove later and handle -1
	}
}

void	save_operator(char *line, int start, int end, t_token **token_list)
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

void	save_word(char *line, int start, int end, t_token **token_list)
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

void	init_status(t_status *status)
{
	status->normal = 1;
	status->s_quote = 0;
	status->d_quote = 0;
}

void	handle_quotes(char c, t_status *status)
{
	if (status->normal == 1 && c == '\'')
		{
			status->normal = 0;
			status->s_quote = 1;
		}
		else if (status->s_quote == 1 && c == '\'')
		{
			status->normal = 1;
			status->s_quote = 0;
		}
		else if (status->normal == 1 && c == '"')
		{
			status->normal = 0;
			status->d_quote = 1;
		}
		else if (status->d_quote == 1 && c == '"')
		{
			status->normal = 1;
			status->d_quote = 0;
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

void	handle_word(char *line, int *i, t_status *status, t_token **token_list)
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
	save_word(line, start, *i, token_list);
}

void	get_tokens(char *line, t_status *status, t_token **token_list)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (status->normal && (line[i] == '\'' || line[i] == '"'))
		{
			handle_quotes(line[i], status);
			i++;
			continue;
		}
		else if (status->normal && line[i] == 32)
		{
			i++;
			continue;
		}
		else if (status->normal && is_operator(line[i]))
		{
			handle_operator(line, &i, token_list);
			continue;
		}
		else
			handle_word(line, &i, status, token_list);
	}
}
void	tokenize_line(char *line)
{
	t_status	status;
	t_token		*token_list;

	token_list = NULL;
	init_status(&status);
	get_tokens(line, &status, &token_list);
	print_tokens(token_list);
}
