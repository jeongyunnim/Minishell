/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 21:09:47 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/22 21:34:02 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_oldpwd(t_env_deque *env)
{
	t_env	*env_temp;
	int		flag;

	env_temp = env->head;
	flag = 0;
	while (env_temp != NULL)
	{
		if (ft_strncmp(env_temp->name, "OLDPWD", 7) == 0)
		{
			flag = 1;
			break ;
		}
		env_temp = env_temp->next;
	}
	if (flag == 1)
	{
		free(env_temp->value);
		env_temp->value = NULL;
		env_temp->value_len = 0;
		return ;
	}
	env_temp = lstnew_env();
	env_temp->name = ft_strdup("OLDPWD");
	env_temp->name_len = 6;
	append_tail_env(&env->head, &env->tail, env_temp);
}

void	init_info(t_info *info, char *envp[])
{
	ft_memset(info, 0, sizeof(info));
	info->envs = save_env(envp);
	info->home_dir = getenv("HOME");
	init_oldpwd(info->envs);
	save_original_mode(&info->org_term);
	set_input_mode(&info->new_term);
}
