/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nora <nora@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:21:09 by nora              #+#    #+#             */
/*   Updated: 2025/05/07 20:09:43 by nora             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char *get_home_dir(t_shell *shell)
{
    char *home_value;
	
    home_value = expand_var(shell, "HOME");
    if (home_value)
        return (ft_strdup(home_value));
    return (NULL);
}

static char *handle_variable_expansion(const char *str, int *i, char *expanded, t_shell *shell)
{
    int var_start;
    int var_end;
    char *var_name;
    char *var_value;
    char *temp;

	var_start = *i + 1;
	var_end = var_start;
    if (str[var_start] == '?')
    {
        var_end = var_start + 1;
        var_value = ft_itoa(shell->exit_status);
        if (!var_value)
        {
            free(expanded);
            return (NULL);
        }
        temp = ft_strjoin(expanded, var_value);
        free(expanded);
        expanded = temp;
        free(var_value);
        if (!expanded)
            return (NULL);
        *i = var_end;
        return (expanded);
    }
    else if (str[var_start] && (ft_isalpha((unsigned char)str[var_start]) || str[var_start] == '_'))
    {
        while (str[var_end] && (ft_isalnum((unsigned char)str[var_end]) || str[var_end] == '_'))
            var_end++;
        var_name = ft_substr(str, var_start, var_end - var_start);
        if (!var_name)
        {
            free(expanded);
            return (NULL);
        }
        var_value = expand_var(shell, var_name);
        if (!var_value)
            var_value = ""; 
        temp = ft_strjoin(expanded, var_value);
        free(expanded);
        expanded = temp;
        if (!expanded)
        {
            free(var_name);
            return (NULL);
        }
        free(var_name);
        *i = var_end;
        return (expanded);
    }
    else
    {
       
        temp = ft_strjoin(expanded, "$");
        free(expanded);
        expanded = temp;
        if (!expanded)
            return (NULL);
        (*i)++;
        return (expanded);
    }
}

static char *handle_tilde_expansion(const char *str, int *i, char *expanded, t_shell *shell)
{
    char *home_dir;
    char *temp;
    
    home_dir = get_home_dir(shell);
    if (home_dir)
    {
        temp = ft_strjoin(expanded, home_dir);
        free(expanded);
        expanded = temp;
        free(home_dir);
        if (!expanded)
            return (NULL);
    }
    if (str[*i+1] == '/' || str[*i+1] == '\0')
    {
       (*i)++;
       return (expanded);
    }
    return (expanded);
}

static char *append_literal_char(char c, char *expanded)
{
    char current_char_str[2];
    char *temp;
	
    current_char_str[0] = c;
    current_char_str[1] = '\0';

    temp = ft_strjoin(expanded, current_char_str);
    free(expanded);
    expanded = temp;
    if (!expanded)
	    return (NULL);
    return (expanded);
}

char *expand_string(const char *str, t_shell *shell)
{
    char    *expanded; 
    int     i;
    int     in_squote;
    int     in_dquote;

    if (!str)
        return (NULL);
    expanded = ft_strdup("");
    if (!expanded)
        return (NULL);
    i = 0;
    in_squote = 0;
    in_dquote = 0;
    while (str[i])
    {
        if (str[i] == '\'' && !in_dquote)
        {
            in_squote = !in_squote;
            i++;
            continue;
        }
        if (str[i] == '"' && !in_squote)
        {
            in_dquote = !in_dquote;
            i++;
            continue;
        }
        if (str[i] == '$' && !in_squote)
        {
            expanded = handle_variable_expansion(str, &i, expanded, shell);
            if (!expanded)
                return (NULL);
            continue;
        }
        if (str[i] == '~' && (i == 0 || str[i-1] == '/') && !in_squote && !in_dquote)
        {
            expanded = handle_tilde_expansion(str, &i, expanded, shell);
            if (!expanded)
                return (NULL);
            if (str[i] == '~')
            {
                 expanded = append_literal_char(str[i], expanded);
                 if (!expanded)
                    return (NULL);
                 i++;
            }
            continue;
	    expanded = append_literal_char(str[i], expanded);
        if (!expanded)
            return (NULL);
        i++;
        }
    }
    return (expanded);
}

int expand_command(t_cmd *cmd, t_shell *shell)
{
    int i;
    char *expanded_arg;

    if (!cmd)
        return (0);
    i = 0;
    while (cmd->argv && cmd->argv[i])
    {
        expanded_arg = expand_string(cmd->argv[i], shell);
        if (!expanded_arg)
            return (1);
        free(cmd->argv[i]);
        cmd->argv[i] = expanded_arg;
        i++;
    }
    if (cmd->infile)
    {
        expanded_arg = expand_string(cmd->infile, shell);
        if (!expanded_arg)
            return (1);
        free(cmd->infile);
        cmd->infile = expanded_arg;
    }
    if (cmd->outfile)
    {
        expanded_arg = expand_string(cmd->outfile, shell);
        if (!expanded_arg)
            return (1);
        free(cmd->outfile);
        cmd->outfile = expanded_arg;
    }
    if (cmd->next)
    {
        if (expand_command(cmd->next, shell) != 0)
            return (1);
    }
    return (0);
}
