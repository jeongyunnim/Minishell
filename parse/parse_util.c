/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 20:27:18 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/26 15:11:28 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_quote(int c)
{
	if (c == '\'' || c == '\"')
		return (1);
	else
		return (0);
}

int	is_meta(int c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	else
		return (0);
}

int	is_env_special(int c)
{
	if (c == '?' || c == '0' || c == '$')
		return (1);
	else
		return (0);
}
