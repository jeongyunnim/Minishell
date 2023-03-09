/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:14:39 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/09 17:32:47 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node *create_ast_node(t_special special, char *arg)
{
	t_ast_node	*new;

	new = ft_calloc(sizeof(t_ast_node), 1);
	new->value = arg;
	new->type = special;
	return (new);
}