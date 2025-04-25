/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amal <amal@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 01:31:38 by amal              #+#    #+#             */
/*   Updated: 2025/04/25 16:13:23 by amal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>

# define WORD 1 //commands and args
# define PIPE 2 // |
# define REDIR_IN 3 // <
# define REDIR_OUT 4 // >
# define REDIR_APPEND 5 // >>
# define HEREDOC 6 // <<

typedef struct s_cmd
{
	int				append;
	int				has_pipe;
	char			*infile;
	char			*outfile;
	char			**argv;
	struct	s_cmd	*next;
}	t_cmd;

typedef	struct s_status
{
	int	normal;
	int	s_quote;
	int	d_quote;
} t_status;

typedef struct s_token
{
	int				type;
	char			*val;
	struct s_token	*next;
} t_token;

// ************** tokenization **************
t_token	*tokenize_line(char *line);

int		is_operator(char c);
char	*save_token(char *start, int len);

void	handle_quotes(char c, t_status *status);
void	handle_operator(char *line, int *i, t_token **token_list);
void	handle_word(char *line, int *i, t_status *status, t_token **token_list);

// ************** expansion **************
char	*expand_var(char **envp, char *var);

// ************** parsing **************
t_cmd	*parse_tokens(t_token *token_list);

// ************** execution **************
void execute_command(t_cmd *cmd_list, char **envp, int in_fd, int out_fd);

// remove later
void	print_tokens(t_token *token);
void	print_cmds(t_cmd *cmd);


#endif