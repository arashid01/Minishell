/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amal <amal@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:29:46 by amal              #+#    #+#             */
/*   Updated: 2025/05/19 06:41:21 by amal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_input_redirection(t_cmd *cmd, int *in_fd)
{
	if (cmd->infile)
	{
		*in_fd = open(cmd->infile, O_RDONLY);
		if (*in_fd == -1)
			ft_error(cmd->infile);
		if (dup2(*in_fd, STDIN_FILENO) == -1)
			ft_error("dup2");
		if (*in_fd != STDIN_FILENO)
			close(*in_fd);
	}
	else if (*in_fd != STDIN_FILENO)
	{
		if (dup2(*in_fd, STDIN_FILENO) == -1)
			ft_error("dup2");
		close(*in_fd);
	}
}

void	handle_output_redirection(t_cmd *cmd, int *out_fd)
{
	int flags;

	if (cmd->outfile)
	{
		if (cmd->append)
			flags = O_WRONLY | O_CREAT | O_APPEND;
		else
			flags = O_WRONLY | O_CREAT | O_TRUNC;
		*out_fd = open(cmd->outfile, flags, 0644);
		if (*out_fd == -1)
			ft_error(cmd->outfile);
		if (dup2(*out_fd, STDOUT_FILENO) == -1)
			ft_error("dup2");
		close(*out_fd);
	}
	else if (cmd->next)
	{
		if (dup2(*out_fd, STDOUT_FILENO) == -1)
			ft_error("dup2");
		close(*out_fd);
	}
	else if (*out_fd != STDOUT_FILENO)
		close(*out_fd);
}

static void execute_single_command(t_cmd *cmd, t_shell *shell, int in_fd, int out_fd)
{
	handle_input_redirection(cmd, &in_fd);
	handle_output_redirection(cmd, &out_fd);
	execve(find_exe(cmd->argv[0], shell->envp), cmd->argv, shell->envp);
	perror("execve");
	exit(1);
}

void	child_process(t_cmd *cmd, t_shell *shell, int in_fd, int out_fd, int *fds)
{
	setup_child_signals();
	if (cmd->next)
	{
		close(fds[0]);
		execute_single_command(cmd, shell, in_fd, fds[1]);
	}
	else
		execute_single_command(cmd, shell, in_fd, out_fd);
}

void	parent_process(t_cmd *cmd, pid_t pid, int in_fd, int *fds, t_shell *shell)
{
	int	status;

	if (in_fd != STDIN_FILENO)
		close(in_fd);
	if (cmd->next)
	{
		close(fds[1]);
		execute_command(cmd->next, shell, fds[0], STDOUT_FILENO);
		close(fds[0]);
	}
	else
	{
		waitpid(pid, NULL, 0);
		if (cmd->infile && ft_strncmp(cmd->infile, "/tmp/.heredoc_tmp", 17) == 0)
			unlink(cmd->infile);
	}
}
