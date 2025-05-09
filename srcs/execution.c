/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nora <nora@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:23:25 by amal              #+#    #+#             */
/*   Updated: 2025/05/09 18:57:45 by nora             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_error(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void free_arr(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	*find_path(char **envp)
{
	while (*envp)
	{
		if ((ft_strncmp(*envp, "PATH=", 5) == 0))
			return (*envp + 5);
		envp++;
	}
	return (NULL);
}

char	*build_path(char *dir, char *cmd)
{
	char *temp;
	char *cmd_path;

	temp = ft_strjoin(dir, "/");
	if (!temp)
		ft_error("Memory allocation failed");
	cmd_path = ft_strjoin(temp, cmd);
	free(temp);
	if (!cmd_path)
		ft_error("Memory allocation failed");
	return (cmd_path);
}

char	*find_exe(char *cmd, char **envp)
{
	char	**dir;
	char	*path;
	char	*cmd_path;
	int i;

	path = find_path(envp);
	if (!path)
		ft_error("PATH not found");
	dir = ft_split(path, ':');
	i = 0;
	while (dir[i])
	{
		cmd_path = build_path(dir[i], cmd);
		if (access(cmd_path, X_OK) == 0)
		{
			free_arr(dir);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	free_arr(dir);
	return (NULL);
}

void execute_command(t_cmd *cmd, t_shell *shell, int in_fd, int out_fd)
{
	int fds[2];
	int flags;
	pid_t pid;
	char	*cmd_path;

	if (!cmd)
		return;
	if (cmd->next && pipe(fds) == -1)
		ft_error("pipe");
	pid = fork();
	if (pid == -1)
		ft_error("fork");
	if (pid == 0)
	{
		if (cmd->infile)
		{
			in_fd = open(cmd->infile, O_RDONLY);
			if (in_fd == -1)
			ft_error(cmd->infile);
		}
		dup2(in_fd, STDIN_FILENO);
		if (in_fd != STDIN_FILENO)
			close(in_fd);
		if (cmd->outfile)
		{
			if (cmd->append)
				flags = O_WRONLY | O_CREAT | O_APPEND;
			else
				flags = O_WRONLY | O_CREAT | O_TRUNC;
			out_fd = open(cmd->outfile, flags, 0644);
			if (out_fd == -1)
				ft_error(cmd->outfile);
			dup2(out_fd, STDOUT_FILENO);
			close(out_fd);
		}
		else if (cmd->next)
		{
			dup2(fds[1], STDOUT_FILENO);
			close(fds[0]);
			close(fds[1]);
		}
		if (child_built_in(cmd->argv[0]) || parent_built_in(cmd->argv[0])) // Builtin check
		{
			shell->exit_status = run_builtin(cmd, shell);
			exit(shell->exit_status);
		}
		else
		{
			cmd_path = find_exe(cmd->argv[0], shell->envp);
			if (!cmd_path)
			{
				write(2, "minishell: ", 11);
				write(2, cmd->argv[0], ft_strlen(cmd->argv[0]));
				write(2, ": command not found\n", 20);
				shell->exit_status = 127;
				exit(shell->exit_status);
			}
		}
		execve(cmd_path, cmd->argv, shell->envp);
		perror("execve");
		free(cmd_path);
		exit(1);
	}
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	if (out_fd != STDOUT_FILENO)
		close(out_fd);
	if (cmd->next)
	{
		close(fds[1]);
		execute_command(cmd->next, shell, fds[0], STDOUT_FILENO);
		close(fds[0]);
	}
	else
		waitpid(pid, NULL, 0);
} 