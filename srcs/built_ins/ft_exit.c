/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nora <nora@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 09:58:28 by nora              #+#    #+#             */
/*   Updated: 2025/05/17 14:07:06 by nora             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_isspace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

static long long	ft_atolli(const char *str, int *status)
{
	int			i;
	int			sign;
	long long	value;
	long long	prev;

	i = 0;
	sign = 1;
	value = 0;
	if (status)
		*status = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		sign = (str[i++] == '-') ? -1 : 1;
	if (!ft_isdigit(str[i]))
		return (*status = 2, 0);
	while (ft_isdigit(str[i]))
	{
		prev = value;
		value = value * 10 + (str[i++] - '0');
		if ((value / 10) != prev)
			return (*status = 2, 0);
	}
	if (str[i] != '\0')
		*status = 2;
	return (value * sign);
}

void	ft_exit(t_cmd *cmd, t_shell *shell)
{
	long long	exit_code;
	int			status;

	ft_putendl_fd("exit", STDERR_FILENO);
	if (!cmd || !cmd->argv || !cmd->argv[1])
	{
		//free_arr(shell->envp);
		exit(shell->exit_status);
	}
	exit_code = ft_atolli(cmd->argv[1], &status);
	if (status != 0)
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(cmd->argv[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		free_arr(shell->envp);
		exit(255);
	}
	if (cmd->argv[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		shell->exit_status = 1;
		return ;
	}
	//free_arr(shell->envp);
	exit((unsigned char)exit_code);
}
