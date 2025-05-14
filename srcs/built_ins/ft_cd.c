/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nora <nora@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 21:17:58 by nora              #+#    #+#             */
/*   Updated: 2025/05/12 18:07:29 by nora             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_cd_args(t_cmd *cmd)
{
	if (!cmd || !cmd->argv)
	{
		write(2, "minishell: cd: invalid input\n", 29);
		return (1);
	}
	if (!cmd->argv[1])
	{
		write(2, "minishell: cd: missing argument\n", 32);
		return (1);
	}
	if (cmd->argv[2])
	{
		write(2, "minishell: cd: too many arguments\n", 34);
		return (1);
	}
	return (0);
}

static char	*get_old_pwd(void)
{
	char	buffer[1024];

	if (!getcwd(buffer, sizeof(buffer)))
	{
		perror("minishell: cd: getcwd");
		return (NULL);
	}
	return (ft_strdup(buffer));
}

static int	try_chdir(char *target)
{
	if (chdir(target) != 0)
	{
		perror("minishell: cd");
		return (1);
	}
	return (0);
}

static int	update_pwd_env(t_shell *shell, char *old_pwd)
{
	char	buffer[1024];
	char	*new_pwd;
	int		status;

	status = 0;
	if (ft_setenv("OLDPWD", old_pwd, shell) != 0)
		status = 1;
	if (!getcwd(buffer, sizeof(buffer)))
	{
		perror("minishell: cd: getcwd after chdir");
		if (ft_unsetenv("PWD", shell) != 0)
			status = 1;
		return (status);
	}
	new_pwd = ft_strdup(buffer);
	if (!new_pwd || ft_setenv("PWD", new_pwd, shell) != 0)
		status = 1;
	free(new_pwd);
	return (status);
}

int	ft_cd(t_cmd *cmd, t_shell *shell)
{
	char	*target_path;
	char	*old_pwd;
	int		status;

	if (check_cd_args(cmd))
		return (shell->exit_status = 1);
	target_path = ft_strdup(cmd->argv[1]);
	old_pwd = get_old_pwd();
	if (!target_path || !old_pwd || try_chdir(target_path))
	{
		free(target_path);
		free(old_pwd);
		return (shell->exit_status = 1);
	}
	status = update_pwd_env(shell, old_pwd);
	free(old_pwd);
	free(target_path);
	shell->exit_status = status;
	return (status);
}
