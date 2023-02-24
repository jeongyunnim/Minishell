#include "minishell.c"

t_env_deque	*save_env(char **env)
{
	unsigned int	i;
	unsigned int	j;
	t_env_deque		*envs;

	i = 0;
	j = 0;
	envs = (t_env_deque *)ft_calloc(1, sizeof(envs));
	if (envs == NULL)
		return (NULL);
	while (env[i] = NULL)
	{
		
	}
	return (envs);
}