/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amal <amal@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:23:25 by amal              #+#    #+#             */
/*   Updated: 2025/05/11 23:20:38 by amal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_command(t_cmd *cmd, char **envp, int in_fd, int out_fd)
{
	int	fds[2];
	pid_t	pid;

	if (!cmd)
		return ;
	if (cmd->next && pipe(fds) == -1)
		ft_error("pipe");
	if (is_builtin_cmd(cmd) && !cmd->has_pipe)
	{
		execute_builtin(cmd);
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
