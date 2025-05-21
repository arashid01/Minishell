/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nora <nora@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 01:31:38 by amal              #+#    #+#             */
/*   Updated: 2025/05/21 11:28:48 by nora             ###   ########.fr       */
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
	int				has_heredoc;
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

extern t_shell	g_shell;

// ************** tokenization **************
t_token	*tokenize_line(char *line, t_shell *shell);
int		is_operator(char c);
char	*save_token(char *start, int len);
void	handle_quotes(char c, t_status *status);
void	handle_operator(char *line, int *i, t_token **token_list);
void	handle_word(char *line, int *i, t_status *status, t_token **token_list, t_shell *shell);

// ************** expansion **************
char	**copy_env(char **envp);
void	free_env(char **envp);
char	*expand_var(t_shell *shell, const char *var);
int		ft_setenv(const char *name, const char *value, t_shell *shell);
int		ft_unsetenv(const char *name, t_shell *shell);
char	*expand_exit_status(char *str, int exit_status);
char	*expand_variables(t_shell *shell, char *input, int exit_status);

// ************** parsing **************
t_cmd	*parse_tokens(t_token *token_list);

// ************** execution **************
void	execute_command(t_cmd *cmd, t_shell *shell, int in_fd, int out_fd);
void	parent_process(t_cmd *cmd, pid_t pid, int in_fd, int *fds, t_shell *shell);
void	child_process(t_cmd *cmd, t_shell *shell, int in_fd, int out_fd, int *fds);
void	handle_output_redirection(t_cmd *cmd, int *out_fd);
void	handle_input_redirection(t_cmd *cmd, int *in_fd);
char	*find_exe(char *cmd, char **envp);

// ************** builtins **************
int		is_builtin_cmd(t_cmd *cmd);
int		execute_builtin(t_cmd *cmd, t_shell *shell);
int		ft_echo(t_cmd *cmd, t_shell *shell);
int		ft_cd(t_cmd *cmd, t_shell *shell);
int		ft_pwd(t_cmd *cmd, t_shell *shell);
int		ft_export(t_cmd *cmd, t_shell *shell);
int		ft_env(t_cmd *cmd, t_shell *shell);
int		ft_unset(t_cmd *cmd, t_shell *shell);
void	ft_exit(t_cmd *cmd, t_shell *shell);
// ************** utils **************
void	ft_error(const char *msg);
void	free_arr(char **arr);

// ************** signals **************
void	setup_parent_signals(void);
void	setup_child_signals(void);
void	setup_heredoc_signals(void);

// remove later
void	print_tokens(t_token *token);
void	print_cmds(t_cmd *cmd);

#endif