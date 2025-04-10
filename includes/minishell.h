/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amal <amal@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 01:31:38 by amal              #+#    #+#             */
/*   Updated: 2025/04/10 05:51:46 by amal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

# define T_WORD 0
# define T_PIPE 1
# define T_REDIR_IN 2
# define T_REDIR_OUT 3
# define T_REDIR_AP 4
# define T_HEREDOC 5

typedef struct s_token
{
	char	*value;
	int		type;
}	t_token;

typedef struct	s_cmd
{
	char			**args;
	char			*infile;
	char			*outfile;
	int				append;
	struct s_cmd	*next;
}	t_cmd;

int		count_tokens(char *line);
char	**tokenize(char *line);
t_token	*build_token_list(char **str_tokens, int count);

t_cmd	*parse_single_command(t_token *tokens, int count);
t_cmd	*parse_all_commands(t_token *tokens, int count);

void	free_tokens(t_token *tokens, int count);
void	free_cmd(t_cmd *cmd);

#endif