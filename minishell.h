/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 20:09:54 by jeseo             #+#    #+#             */
/*   Updated: 2023/02/21 21:56:24 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include "./libft/libft.h"

typedef struct s_node
{
	struct s_node	*previous;
	struct s_node	*next;
	char			*arg;
}	t_node;

typedef struct s_deque_edge
{
	struct s_node	*head_a;
	struct s_node	*tail_a;
}	t_deque;

/* parse.c */
int	parse(char *input);

/* deque_util.c */
t_deque	*lstnew(char *arg);
t_deque	*pop_head(t_deque **head);
t_deque	*pop_tail(t_deque **tail);
void	append_head(t_deque **head, t_deque **tail, t_deque *new);
void	append_tail(t_deque **head, t_deque **tail, t_deque *new);


#endif