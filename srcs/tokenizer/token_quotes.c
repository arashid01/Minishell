/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amal <amal@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:17:43 by amal              #+#    #+#             */
/*   Updated: 2025/04/18 18:17:58 by amal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_quotes(char c, t_status *status)
{
	if (status->normal == 1 && c == '\'')
		{
			status->normal = 0;
			status->s_quote = 1;
		}
		else if (status->s_quote == 1 && c == '\'')
		{
			status->normal = 1;
			status->s_quote = 0;
		}
		else if (status->normal == 1 && c == '"')
		{
			status->normal = 0;
			status->d_quote = 1;
		}
		else if (status->d_quote == 1 && c == '"')
		{
			status->normal = 1;
			status->d_quote = 0;
		}
}