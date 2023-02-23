/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 20:09:54 by jeseo             #+#    #+#             */
/*   Updated: 2023/02/23 16:45:43 by jeseo            ###   ########.fr       */
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

# define ERROR -1
# define INT_MAX 2147483647

typedef enum	e_special
{
	NONE,
	PIPE,
	REDIRECTION_L,
	HEREDOC,
	REDIRECTION_R,
	APPEND
}				t_special;

typedef struct s_node
{
	struct s_node	*previous;
	struct s_node	*next;
	char			*arg;
	int				special;
}	t_node;

typedef struct s_deque_edge
{
	struct s_node	*head;
	struct s_node	*tail;
}	t_deque;

/* parse.c */
int	parse(char *input);

/* deque_util.c */
t_node	*lstnew(char *arg);
t_node	*pop_head(t_node **head);
t_node	*pop_tail(t_node **tail);
void	append_head(t_node **head, t_node **tail, t_node *new);
void	append_tail(t_node **head, t_node **tail, t_node *new);

/* arg_to_deque.c */
int		save_arg(char **input, char *arg, int arg_len);
int		arg_to_deque(t_deque **args, char *arg);

#endif