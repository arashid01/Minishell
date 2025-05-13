/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amal <amal@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 23:58:52 by nora              #+#    #+#             */
/*   Updated: 2025/05/13 04:13:19 by amal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(t_cmd *cmd)
{
	char	buffer[1024];

	if (!cmd || !cmd->argv) // ask nora about !cmd->argv
	{
		write(2, "minishell: pwd: invalid input\n", 30);
		return (1);
	}
	if (cmd->argv[1] != NULL)
	{
		write(2, "minishell: pwd: too many arguments\n", 35);
		return (1);
	}
	if (getcwd(buffer, sizeof(buffer)) == NULL)
	{
		perror("minishell: pwd: getcwd");
		return (1);
	}
	write(1, buffer, ft_strlen(buffer));
	write(1, "\n", 1);
	return (0);
}
