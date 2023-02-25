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

int	set_env_len(char *input, int *cnt, t_env_deque *env)
{
	t_env	*temp;
	unsigned int i;

	i = 0; 
	if (ft_isupper(input[i]) == 0)
	{
		if (ft_isdigit(input[i]) != 0)
		{
			i++;
		}
		else
		{
			while (input[i] != '\0')
			{
				if (ft_isalnum(input[i]) == 0)
				{
					return (i);
				}
				i++;
			}
		}
		return (i);
	}
	else
	{
		temp = env->head;
		while (temp != NULL)
		{
			i = 0;
			while (i < temp->name_len)
			{
				if (ft_isalnum(input[i]))
				{
					break ;
				}
				else if (input[i] != temp->name[i])
				{
					break ;
				}
				i++;
				if (i == temp->name_len)
				{
					*cnt += temp->value_len;
					return (i);
				}
			}
			temp = temp->next;
		}
	}
	return (i);
}

void	replace_env(char **input, char **arg, t_env_deque *env)
{
	t_env	*temp;
	unsigned int i;

	i = 0; 
	if (ft_isupper(*input[i]) == 0)
	{
		if (ft_isdigit(*input[i]) != 0)
		{
			(*input)++;
		}
		else
		{
			while (ft_isalnum(*input[i]) != 0)
			{
				(*input)++;
			}
		}
		return ;
	}
	else
	{
		temp = env->head;
		while (temp != NULL)
		{
			i = 0;
			while (i < temp->name_len)
			{
				if (ft_isalnum(*input[i]))
				{
					break ;
				}
				else if (*input[i] != temp->name[i])
				{
					break ;
				}
				i++;
				if (i == temp->name_len)
				{
					i = 0;
					while (i < temp->value_len)
					{
						*arg[i] = temp->value[i];
						i++;
					}
					(*input) += temp->name_len;
					return ;
				}
			}
			temp = temp->next;
		}
	}
	return ;
}
