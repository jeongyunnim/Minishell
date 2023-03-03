/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 20:09:54 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/02 19:45:48 by jeseo            ###   ########.fr       */
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

int	g_exit_code;

typedef enum	e_special
{
	NONE,
	HEREDOC,
	APPEND,
	PIPE='|',
	REDIRECT_L='<',
	REDIRECT_R='>'
}				t_special;

typedef struct s_arg
{
	struct s_arg	*previous;
	struct s_arg	*next;
	char			*arg;
	int				special;// | < << > >> 
}	t_arg;

typedef struct s_env
{
	struct s_env	*previous;
	struct s_env	*next;
	char			*name;
	char			*value;
	unsigned int	name_len;
	unsigned int	value_len;
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
	t_arg_deque	*arguments;
	t_env_deque	*envs;
}	t_info;

/* parse.c */
int		parse(char *input, t_info *info);
int		is_quote_or_env(int c);

/* deque_arg_util.c */
t_arg		*lstnew_arg(char *arg);
t_arg		*pop_head_arg(t_arg **head);
t_arg		*pop_tail_arg(t_arg **tail);
void		append_head_arg(t_arg **head, t_arg **tail, t_arg *new);
void		append_tail_arg(t_arg **head, t_arg **tail, t_arg *new);

/* deque_env_util.c */
t_env		*lstnew_env(void);
t_env		*pop_head_env(t_env **head);
t_env		*pop_tail_env(t_env **tail);
void		append_head_env(t_env **head, t_env **tail, t_env *new);
void		append_tail_env(t_env **head, t_env **tail, t_env *new);


/* parse_save.c */
int			save_arg(char **input, char *arg, int arg_len, t_env_deque *envs);
int			arg_to_deque(t_arg_deque **args, char *arg, int special);
int			ft_isupper(int c);
int			ft_ismeta(int c);

/* env_save.c */
t_env_deque	*save_env(char **env);
int			set_env_len(char *input, unsigned int *cnt, t_env_deque *env);
int			replace_env(char **input, char **arg, t_env_deque *env);

/* env_replace.c */
int			special_parameter_len(char *input, unsigned int *cnt);
int			special_parameter_replace(char **input, char **arg);

/* parse_count_len.c */
int			inside_quote_cnt(char *input, t_env_deque *env, unsigned int *cnt, int *quote_flag);
int			quote_and_env_cnt(char *input, t_env_deque *env, unsigned int *cnt, int *quote_flag);

/* parse_prioritize */
int			prioritize(t_info *info);

#endif

//ls|cat 작동 함.
