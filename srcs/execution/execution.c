/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amal <amal@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:23:25 by amal              #+#    #+#             */
/*   Updated: 2025/05/12 00:22:17 by amal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_command(t_cmd *cmd, char **envp, int in_fd, int out_fd)
{
	int	fds[2];
	pid_t	pid;
	int		saved_stdin;
	int		saved_stdout;

	if (!cmd)
		return ;
	if (cmd->next && pipe(fds) == -1)
		ft_error("pipe");

	if (is_builtin_cmd(cmd) && !cmd->has_pipe)
	{
		saved_stdin = dup(STDIN_FILENO);
		saved_stdout = dup(STDOUT_FILENO);
		handle_input_redirection(cmd, &in_fd);
		handle_output_redirection(cmd, &out_fd);
		execute_builtin(cmd);
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
		return ;
	}		
	pid = fork();
	if (pid == -1)
		ft_error("fork");
	if (pid == 0)
		child_process(cmd, envp, in_fd, out_fd, fds);
	else
		parent_process(cmd, pid, in_fd, fds, envp);
}
