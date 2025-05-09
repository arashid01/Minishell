/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd+export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nora <nora@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 19:08:45 by nora              #+#    #+#             */
/*   Updated: 2025/05/07 20:31:41 by nora             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_cd(t_cmd *cmd, t_shell *shell)
{
	char	*target_path;
	char	buffer[1024];
	char	*old_str;
	char	*new_str;
	int	status;

	status = 0;
	if (!cmd || !cmd->argv)
    {
        write(2, "minishell: cd: invalid input\n", 29);
        return (1);
    }
	if (cmd->argv[1] == NULL)
	{
		perror("minishell: cd: missing argument\n");
		return (1);
	}
	if (cmd->argv[2] != NULL)
	{
		perror("minishell: cd: too many arguments\n");
		return (1);
	}
	target_path = ft_strdup(cmd->argv[1]);
	if (!target_path)
	{
		perror("minishell: cd");
		return (1);
	}
	if (getcwd(buffer, sizeof(buffer)) == NULL)
	{
		perror("minishell: cd: getcwd before chdir");
		free(target_path);
		shell->exit_status = 1;
		return (1);
	}
	old_str = ft_strdup(buffer);
	if (!old_str)
	{
		perror("minishell: cd");
		free(target_path);
		shell->exit_status = 1;
		return (1);
	}
	if (chdir(target_path) != 0)
	{
		perror("minshell: cd");
		free(target_path);
		free(old_str);
		shell->exit_status = 1;
		return (1);
	}
	if (ft_setenv("OLDPWD", old_str, shell) != 0)
		status = 1;
	free(old_str);
	if (getcwd(buffer, sizeof(buffer)) == NULL)
	{
		perror("minishell: cd: getcwd after chdir");
		if (ft_unsetenv("PWD", shell) != 0)
			status = 1;
	}
	else
	{
		new_str = ft_strdup(buffer);
		if (!new_str)
		{
			perror("minishell: cd");
			status = 1;
		}
		else
		{
			if (ft_setenv("PWD", new_str, shell) != 0)
				status = 1;
			free(new_str);
		}
	
	}
	free(target_path);
	shell->exit_status = status;
	return (status);
}

int process_export_arg(char *arg, t_shell *shell)
{
    char *equal_sign_pos;
    char *name_part;
    char *value_part;
    int status;

    status = 0;
    equal_sign_pos = ft_strchr(arg, '=');
    if (!is_valid_env_name(arg))
    {
        write(2, "minishell: export: '", 20);
        write(2, arg, ft_strlen(arg));
        write(2, "': not a valid identifier\n", 26);
        return (1);
    }
    if (equal_sign_pos != NULL)
    {
        name_part = ft_substr(arg, 0, equal_sign_pos - arg);
        if (!name_part)
        {
             perror("minishell: export: malloc failed");
             return (1);
        }
        value_part = equal_sign_pos + 1;
        if (ft_setenv(name_part, value_part, shell) != 0)
             status = 1;
        free(name_part);
    }
    else
    {
        name_part = arg;
        value_part = "";
        if (ft_setenv(name_part, value_part, shell) != 0)
             status = 1;
    }
    return (status);
}


int ft_export(t_cmd *cmd, t_shell *shell)
{
    int i;
    char    *equal_sign_pos;
    int overall_status;

    if (!cmd || !cmd->argv || !shell || !shell->envp)
    {
        write(2, "minishell: export: invalid input or environment\n", 48);
        shell->exit_status = 1;
        return (1);
    }
    if (cmd->argv[1] == NULL)
    {
        i = 0;
       while (shell->envp[i])
       {
            write(1, "declare -x ", 11);
            equal_sign_pos = ft_strchr(shell->envp[i], '=');
            if (equal_sign_pos != NULL)
            {
                write(1, shell->envp[i], equal_sign_pos - shell->envp[i]);
                write(1, "=\"", 2);
                write(1, equal_sign_pos + 1, ft_strlen(equal_sign_pos + 1));
                write(1, "\"", 1);
            }
            else
                write(1, shell->envp[i], ft_strlen(shell->envp[i]));
            write(1, "\n", 1);
            i++;
       }
       shell->exit_status = 0;
       return (0);
    }
    i = 1;
    overall_status = 0;
    while (cmd->argv[i])
    {
        if (process_export_arg(cmd->argv[i], shell) != 0)
        	overall_status = 1;
        i++;
    }
    shell->exit_status = overall_status;
    return (overall_status);
}
