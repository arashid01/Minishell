/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nora <nora@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:59:18 by nora              #+#    #+#             */
/*   Updated: 2025/05/14 21:07:39 by nora             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int is_valid_env_name(const char *name)
{
    int i = 0;

    if (!name || name[0] == '\0')
        return (0);
    if (!ft_isalpha((unsigned char)name[i]) && name[i] != '_')
        return (0);
    i++;

    while (name[i] && name[i] != '=')
    {
        if (!ft_isalnum((unsigned char)name[i]) && name[i] != '_')
        {
            return (0);
        }
        i++;
    }
    return (1);
}

static int process_unset_arguments(t_cmd *cmd, t_shell *shell)
{
    int i;
    int status;

    i = 1;
    status = 0;
    while (cmd->argv[i])
    {
        if (!is_valid_env_name(cmd->argv[i]))
        {
             write(2, "minishell: unset: '", 19);
             write(2, cmd->argv[i], ft_strlen(cmd->argv[i]));
             write(2, "': not a valid identifier\n", 26);
             status = 1;
        }
        else
        {
            ft_unsetenv(cmd->argv[i], shell);
        }
        i++;
    }
    return (status);
}


int ft_unset(t_cmd *cmd, t_shell *shell)
{
    int status;

    if (!cmd || !cmd->argv || !shell || !shell->envp)
    {
        write(2, "minishell: unset: invalid input\n", 33);
        shell->exit_status = 1;
        return (1);
    }

    if (!cmd->argv[1])
        return (shell->exit_status = 0, 0);

    status = process_unset_arguments(cmd, shell);

    return (shell->exit_status = status, status);
}
