/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 20:09:54 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/24 18:36:52 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <termios.h>
# include <signal.h>
# include "./libft/libft.h"

# define INT_MAX 2147483647

int	g_exit_code;

typedef enum e_special
{
	NONE,
	HEREDOC,
	APPEND,
	PIPE='|',
	REDIRECT_IN='<',
	REDIRECT_OUT='>'
}				t_special;

typedef enum e_mode
{
	FORK_CHILD_M,
	FORK_PARENT_M,
	INTERACTIVE_M,
	HEREDOC_M
}				t_mode;

typedef enum e_error_type
{
	PERMISSION_ERROR=-20,
	OPEN_ERROR,
	QUOTE_ERROR,
	DIRECTORY_ERROR,
	SYNTAX_ERROR,
	HEREDOC_MAX_ERROR,
	COMMAND_ERROR,
	FORK_ERROR,
	PIPE_ERROR,
	ALLOCATE_ERROR,
	ERROR=-1
}				t_error_type;

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
	char			**cmd_args;
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
	struct termios		org_term;
	struct termios		new_term;
	t_arg_deque			*arguments;
	t_env_deque			*envs;
	t_cmd_deque			*cmds;
	char				*home_dir;
	int					exit_code;
	int					pipes;
	int					redirects;

}	t_info;

typedef struct s_pipe_index
{
	int		fd[2];
	int		i;
	int		prev_pipe_read;
	pid_t	pid;
}	t_pipe_index;

typedef struct s_parse_index
{
	unsigned int	cnt;
	unsigned int	i;
	char			quote_flag;
}	t_parse_index;

/* init_info */
void		init_oldpwd(t_env_deque *env);
void		init_info(t_info *info, char *envp[]);

/* init_terminal */
void		save_original_mode(struct termios *org_term);
void		set_input_mode(struct termios *new_term);
void		reset_input_mode(struct termios *org_term);

/* parse.c */
int			parse(char *input, t_info *info);


/* parse_count_len.c */
int			is_only_white_space(char *input);
int			inside_quote_cnt(char *input, t_env_deque *env, unsigned int *cnt, char *quote_flag);
int			enter_quote(char input, char *quote_flag);
int			meta_len(char *input);
int			count_arg_len(char *input, t_parse_index index, t_env_deque *envs);

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

/* parse_util.c */
int			is_quote(int c);
int			is_meta(int c);
int			is_env_special(int c);

/* parse_save.c */
int			save_arg(char **input, char *arg, int arg_len, t_env_deque *envs);
int			arg_to_deque(t_arg_deque **args, char *arg, int special);

/* env_save.c */
t_env_deque	*save_env(char **env);
int			set_env_len(char *input, unsigned int *cnt, t_env_deque *env, char quote_flag);
void		replace_env(char **input, char **arg, t_env_deque *env, char quote_flag);

/* env_valid_check.c */
int			invalid_env_name(char *input, unsigned int *i);
int			valid_env_name_match(char *input, t_env_deque *env, unsigned int *i);

/* env_replace.c */
int			env_special_len(char *input);
int			env_special_replace(char **input, char **arg);
int			valid_env_name_replace(char **input, char **arg, t_env_deque *env);

/* parse_divide_pipe */
int			divide_pipe(t_info *info);

/* exec_commands.c */
int			exec_commands(t_info *info);
int			exec_builtin(char **cmd_line, t_env_deque *envs);
char		**envlist_to_arry(t_env_deque *envs);

/* exec_child.c */
void		child_process_run(t_cmd *cmd_node, t_pipe_index index, t_info *info);

/* exec_redirection.c */
int			check_access_read(char *file_name, t_special type);
int			check_access_write(char *file_name, t_special type);
int			handle_redirection(t_arg_deque *redirections);

/* exec_heredoc.c */
int			heredoc_handler(t_info *info);
char		*gen_temp_file_name(int flag);

/* exec_builtin.c */
int			exec_one_builtin(t_info *info, t_cmd *cmd_line);
int			isbuiltin(char **cmd_args);
int			exec_builtin(char **cmd_line, t_env_deque *envs);

/* free_util.c */
void		free_cmd_node(t_cmd **cmd_node);
void		free_arg_deque(t_arg_deque **arg_deque);
void		free_env_deque(t_env_deque **env_deque);

/* signal_handle.c */
void		set_signal_mode(int flag);
void		exited_by_signal(t_info *info, int siganl);

/* error_handle.c */
void		print_error(int type, char *arg);
void		print_system_error(int type);
int			redirection_error(int fd, char *arg);

/* parse_valid_check.c */
int			args_check(t_info *info);

#endif
