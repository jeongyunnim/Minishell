/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 20:53:12 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/05 17:41:09 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fork_to_execute_command(t_info *info)
{
	pid_t	pid;
	int		fd[2];
	int		i;

	i = 1;
	while (i < info->pipes)
	{
		pipe(fd);
		if (i == 0)
		{
			
		}
	}
	return (0);
}
