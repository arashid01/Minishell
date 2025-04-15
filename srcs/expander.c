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
		if (ft_strncmp(envp[i], var, var_len) == 0)
		{
			printf("%s is found\n", var);
			val = ft_strchr(envp[i], '=') + 1;
			printf("%s\n", val);
			return (val);
		}
		else
			i++;
	}
	printf("Var not found");
	return (NULL);
}