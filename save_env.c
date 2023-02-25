#include "minishell.h"

t_env_deque	*save_env(char *env[])
{
	unsigned int	i;
	unsigned int	name_len;
	t_env_deque		*envs;
	t_env			*new;

	i = 0;
	envs = (t_env_deque *)ft_calloc(1, sizeof(t_env_deque));
	if (envs == NULL)
		return (NULL);
	while (env[i] != NULL)
	{
		new = lstnew_env();
		name_len = ft_strchr(env[i], '=') - env[i];
		if (name_len == 0)
		{
			return (NULL);
		}
		new->name = ft_calloc(name_len + 1, sizeof(char));
		if (new->name == NULL)
		{
			return (NULL);
		}
		ft_strlcpy(new->name, env[i], name_len + 1);
		new->value = ft_strdup(env[i] + name_len + 1);
		if (new->value == NULL)
		{
			return (NULL);
		}
		new->name_len = name_len;
		new->value_len = strlen(env[i] + name_len + 1);
		append_tail_env(&envs->head, &envs->tail, new);
		new = NULL;
		i++;
	}
	return (envs);
}
