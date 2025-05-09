/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nora <nora@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 11:21:04 by nora              #+#    #+#             */
/*   Updated: 2025/05/09 18:59:25 by nora             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parent_built_in(char *cmd)
{
	printf("Checking if %s is parent built-in\n", cmd);
	int	cmd_len;

	cmd_len = ft_strlen(cmd);
	if (!cmd)
		return (0);
	else if ((ft_strncmp(cmd, "cd", cmd_len)) == 0)
		return (1);
	else if ((ft_strncmp(cmd, "exit", cmd_len)) == 0)
		return (1);
	else if ((ft_strncmp(cmd, "export", cmd_len)) == 0)
		return (1);
	else if ((ft_strncmp(cmd, "unset", cmd_len)) == 0)
		return (1);
	return (0);
}


int child_built_in(char *cmd)
{
    int cmd_len;

    if (!cmd)
        return (0);
    cmd_len = ft_strlen(cmd);
    if (cmd_len == 0)
        return (0);
    if (ft_strncmp(cmd, "echo", cmd_len) == 0)
        return (1);
    else if (ft_strncmp(cmd, "pwd", cmd_len) == 0)
        return (1);
    else if (ft_strncmp(cmd, "env", cmd_len) == 0)
        return (1);
    else if (ft_strncmp(cmd, "cd", cmd_len) == 0)
        return (1);
    else if (ft_strncmp(cmd, "exit", cmd_len) == 0)
        return (1);
    else if (ft_strncmp(cmd, "export", cmd_len) == 0)
        return (1);
    return (0);
}
int run_builtin(t_cmd *cmd, t_shell *shell) 
{
	size_t arg_len;
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (1);
	arg_len = ft_strlen(cmd->argv[0]);
	if (ft_strncmp(cmd->argv[0], "cd", arg_len) == 0)
		return (ft_cd(cmd, shell));
	else if (ft_strncmp(cmd->argv[0], "echo", arg_len) == 0)
		return (ft_echo(cmd, shell)); 
	else if (ft_strncmp(cmd->argv[0], "env", arg_len) == 0)
		return (ft_env(cmd, shell));
	else if (ft_strncmp(cmd->argv[0], "exit", arg_len) == 0)
		return (ft_exit(cmd, shell));
	else if (ft_strncmp(cmd->argv[0], "pwd", arg_len) == 0)
		return (ft_pwd(cmd, shell));
	else if (ft_strncmp(cmd->argv[0], "unset", arg_len) == 0)
		return (ft_unset(cmd, shell));
	else if (ft_strncmp(cmd->argv[0], "export", arg_len) == 0)
		return (ft_export(cmd, shell));
    write(2, "minishell: internal builtin error: ", 35);
    write(2, cmd->argv[0], arg_len);
    write(2, "\n", 1);
	return (1);
}

