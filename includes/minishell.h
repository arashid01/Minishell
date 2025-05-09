/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nora <nora@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 01:31:38 by amal              #+#    #+#             */
/*   Updated: 2025/05/07 20:23:06 by nora             ###   ########.fr       */
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

typedef struct s_shell
{
	char	**envp;
	int		exit_status;
}	t_shell;

// **************** Tokenizer functions ****************
void	init_status(t_status *status);
void	get_tokens(char *line, t_status *status, t_token **token_list);
t_token	*tokenize_line(char *line);
int		is_operator(char c);
char	*save_token(char *start, int len);
void	handle_operator(char *line, int *i, t_token **token_list);
void	handle_quotes(char c, t_status *status);
void	handle_word(char *line, int *i, t_status *status, t_token **token_list);
void	print_tokens(t_token *token); 
// **************** Parser functions ****************
int		count_args(t_token *token);
char	**build_argv(t_token **token);
t_cmd	*parse_tokens(t_token *token_list);
void	print_cmds(t_cmd *cmd); 
// **************** Utility functions ****************
int is_standard_whitespace(char c);
int is_standard_whitespace_string(const char *str);
int is_valid_env_name(const char *name);
long long ft_atolli(const char *str, int *status);
void free_token_list(t_token *token_list);
void free_cmd_list(t_cmd *cmd_list);
void free_arr(char **arr);
// **************** Environment Management functions ****************
char	**copy_env(char **envp);
void	free_env(char **envp);

char	*expand_var(t_shell *shell, const char *var);
int		ft_setenv(const char *name, const char *value, t_shell *shell);
int		ft_unsetenv(const char *name, t_shell *shell);
// **************** Expander Phase functions ****************
char *expand_string(const char *str, t_shell *shell);
int expand_command(t_cmd *cmd, t_shell *shell);

// ************* Builtin functions *******************
int		parent_built_in(char *cmd_name);
int		child_built_in(char *cmd_name);
int		run_builtin(t_cmd *cmd, t_shell *shell);
int		ft_cd(t_cmd *cmd, t_shell *shell);
int		ft_echo(t_cmd *cmd, t_shell *shell);
int		ft_env(t_cmd *cmd, t_shell *shell);
int		ft_exit(t_cmd *cmd, t_shell *shell);
int		ft_pwd(t_cmd *cmd, t_shell *shell);
int		ft_unset(t_cmd *cmd, t_shell *shell);
int		ft_export(t_cmd *cmd, t_shell *shell);
int process_export_arg(char *arg, t_shell *shell);

// ********** Execution functions ****************
void	ft_error(const char *msg);
char	*find_path(char **envp);
char	*build_path(char *dir, char *cmd);
char	*find_exe(char *cmd, char **envp);
void	execute_command(t_cmd *cmd_list, t_shell *shell, int in_fd, int out_fd);
void    init_minishell(t_shell *shell);

// remove later
void    print_tokens(t_token *token);
void    print_cmds(t_cmd *cmd);

#endif