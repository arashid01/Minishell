/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nora <nora@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:30:29 by nora              #+#    #+#             */
/*   Updated: 2025/05/07 20:10:31 by nora             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_standard_whitespace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
}

int is_standard_whitespace_string(const char *str)
{
    int i = 0;
    if (!str)
        return (1);

    while (str[i])
    {
        if (!is_standard_whitespace(str[i]))
            return (0);
        i++;
    }
    return (1);
}


// checks the *name part* up to the first '=' or end of string.
int is_valid_env_name(const char *name)
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

long long ft_atolli(const char *str, int *status)
{
    long long   value;
    int         sign;
    int         i;

    value = 0;
    sign = 1;
    i = 0;
    if (status != NULL)
        *status = 0; // Assume success initially
    if (str == NULL)
    {
        if (status != NULL)
            *status = 1; // Indicate invalid input
        return (0);
    }
    while (str[i] && is_standard_whitespace(str[i]))
        i++;
    if (str[i] == '-')
    {
        sign = -1;
        i++;
    }
    else if (str[i] == '+')
    {
        i++;
    }
    if (str[i] == '\0')
    {
        if (status != NULL)
            *status = 2; // Indicate non-numeric (empty string)
        return (0);
    }
    while (str[i] && ft_isdigit((unsigned char)str[i]))
    {
        value = value * 10 + (str[i] - '0');
        i++;
    }
    if (str[i] != '\0')
    {
        if (status != NULL)
            *status = 2; 
    }
    value *= sign;
    return (value);
}

void free_token_list(t_token *token_list)
{
    t_token *current;
    t_token *next;

    current = token_list;
    while (current != NULL)
    {
        next = current->next;
        if (current->val)
            free(current->val);
        free(current);
        current = next;
    }
}
void free_cmd_list(t_cmd *cmd_list)
{
    t_cmd *current;
    t_cmd *next;
    int i;

    current = cmd_list;
    while (current != NULL)
    {
        next = current->next;
        if (current->argv)
        {
            i = 0;
            while (current->argv[i])
            {
                free(current->argv[i]);
                i++;
            }
            free(current->argv);
        }
        if (current->infile)
            free(current->infile);
        if (current->outfile)
            free(current->outfile);

        free(current);
        current = next;
    }
}
