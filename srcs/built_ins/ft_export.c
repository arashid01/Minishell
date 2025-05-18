/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nora <nora@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 19:00:00 by nora              #+#    #+#             */
/*   Updated: 2025/05/14 21:43:13 by nora             ###   ########.fr       */
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
static int process_export_arg(char *arg, t_shell *shell)
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
