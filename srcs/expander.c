#include "../includes/minishell.h"

char	*expand_var(char **envp, char *var)
{
	int		i;
	int		var_len;
	char	*val;

	i = 0;
	var_len = ft_strlen(var);
	while (envp[i])
	{
		if ((ft_strncmp(envp[i], var, var_len) == 0) 
				&& (envp[i][var_len] == '='))
		{
			ft_printf("%s is found\n", var);
			val = ft_strchr(envp[i], '=') + 1;
			ft_printf("%s\n", val);
			return (val);
		}
		else
			i++;
	}
	ft_printf("Var not found\n");
	return (NULL);
}