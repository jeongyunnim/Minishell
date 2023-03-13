/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 20:09:54 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/13 20:22:09 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
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
	REDIRECT_IN='<',
	REDIRECT_OUT='>'
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

typedef struct s_cmd
{
	t_arg_deque		*redirections;
	char			**commands_args;
	struct s_cmd	*next;
	struct s_cmd	*previous;
}				t_cmd;

typedef struct s_cmd_deque
{
	t_cmd	*head;
	t_cmd	*tail;
}	t_cmd_deque;


typedef struct s_info
{
	t_arg_deque	*arguments;
	t_env_deque	*envs;
	t_cmd_deque	*cmds;
	char		**envp_bash;
	int			pipes;
	int			redirects;
}	t_info;

/* parse.c */
int		parse(char *input, t_info *info);

/* deque_arg_util.c */
t_arg		*lstnew_arg(char *arg);
t_arg		*pop_head_arg(t_arg **head);
t_arg		*pop_tail_arg(t_arg **tail);
void		append_head_arg(t_arg_deque **deque, t_arg *new);
void		append_tail_arg(t_arg_deque **deque, t_arg *new);

/* deque_env_util.c */
t_env		*lstnew_env(void);
t_env		*pop_head_env(t_env **head);
t_env		*pop_tail_env(t_env **tail);
void		append_head_env(t_env **head, t_env **tail, t_env *new);
void		append_tail_env(t_env **head, t_env **tail, t_env *new);

/* deque_cmd_util.c */
t_cmd		*lstnew_cmd(void);
t_cmd		*pop_head_cmd(t_cmd **head);
t_cmd		*pop_tail_cmd(t_cmd **tail);
void		append_head_cmd(t_cmd_deque **deque, t_cmd *new);
void		append_tail_cmd(t_cmd_deque **deque, t_cmd *new);

/* parse_save.c */
int			save_arg(char **input, char *arg, int arg_len, t_env_deque *envs);
int			arg_to_deque(t_arg_deque **args, char *arg, int special);
int			ft_isupper(int c);
int			is_quote(int c);
int			ft_ismeta(int c);

/* env_save.c */
t_env_deque	*save_env(char **env);
int			set_env_len(char *input, unsigned int *cnt, t_env_deque *env, char quote_flag);
int			replace_env(char **input, char **arg, t_env_deque *env, char quote_flag);

/* env_replace.c */
int			env_special_len(char *input);
int			env_special_replace(char **input, char **arg);

/* parse_count_len.c */
int			inside_quote_cnt(char *input, t_env_deque *env, unsigned int *cnt, char *quote_flag);
int			enter_quote(char input, char *quote_flag);
int			meta_len(char *input);

/* parse_divide_pipe */
int			print_args_deque(t_info *info);
int			divide_pipe(t_info *info);

/* exec_commands.c */
int			exec_commands(t_info *info);

/* exec_child.c */
int			child_process_run(t_info *info, int i, int fd[], int temp_fd);

#endif
