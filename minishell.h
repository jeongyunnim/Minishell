/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 20:09:54 by jeseo             #+#    #+#             */
/*   Updated: 2023/02/23 22:22:06 by jeseo            ###   ########.fr       */
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

typedef struct s_arg
{
	struct s_arg	*previous;
	struct s_arg	*next;
	char			*arg;
	int				special;
}	t_arg;

typedef struct s_env
{
	struct s_env	*previous;
	struct s_env	*next;
	char			*name;
	char			*value;
}	t_env;

typedef struct s_arg_deque
{
	t_arg	*head;
	t_arg	*tail;
}	t_arg_deque;

typedef struct s_env_deque
{
	t_env	*head;
	t_env	*tail;
}	t_env_deque;

typedef struct s_info
{
	t_arg_deque	arguments;
	t_env_deque env;
}	t_info;

/* parse.c */
int		parse(char *input);
int		ft_isspecial(int c);

/* deque_arg_util.c */
t_arg	*lstnew_arg(char *arg);
t_arg	*pop_head_arg(t_arg **head);
t_arg	*pop_tail_arg(t_arg **tail);
void	append_head_arg(t_arg **head, t_arg **tail, t_arg *new);
void	append_tail_arg(t_arg **head, t_arg **tail, t_arg *new);

/* deque_env_util.c */
t_env	*lstnew_env(void);
t_env	*pop_head_env(t_env **head);
t_env	*pop_tail_env(t_env **tail);
void	append_head_env(t_env **head, t_env **tail, t_env *new);
void	append_tail_env(t_env **head, t_env **tail, t_env *new);


/* save_parse.c */
int		save_arg(char **input, char *arg, int arg_len);
int		arg_to_deque(t_arg_deque **args, char *arg);

/* save_parse.c */
t_env_deque	*save_env(char **env);


#endif

//ls|cat 작동 함.