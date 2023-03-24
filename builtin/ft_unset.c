/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyecheon <hyecheon@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:06:49 by hyecheon          #+#    #+#             */
/*   Updated: 2023/03/22 16:07:02 by hyecheon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	del_env(t_env **head, t_env **tail, t_env *target)
{
	if (target == NULL)
		return ;
	if (*head == target)
		*head = target->next;
	if (*tail == target)
		*tail = target->previous;
	if (target->previous != NULL)
		target->previous->next = target->next;
	if (target->next != NULL)
		target->next->previous = target->previous;
	free(target->name);
	free(target->value);
	free(target);
}

int	check_unset_valid(char *str)
{
	int	i;

	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	i = 1;
	while (str[i] != '\0')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	ft_unset(char **argv, t_env_deque *envs)
{
	int		i;
	t_env	*target;

	i = 1;
	while (argv[i] != NULL)
	{
		if (!check_unset_valid(argv[i]))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putendl_fd("' not a valid identifier", 2);
			return (1);
		}
		else
		{
			target = find_target(argv[i], envs);
			del_env(&envs->head, &envs->tail, target);
		}
		i++;
	}
	return (0);
}
