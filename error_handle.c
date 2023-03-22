/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:05:24 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/22 16:30:11 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(int type, char *arg)
{
	ft_putstr_fd("minishell: ", 2);
	if (type == SYNTAX_ERROR)
		ft_putstr_fd("syntax error near unexpected token `", 2);
	if (arg != NULL)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	if (type == PERMISSION_ERROR)
		ft_putstr_fd("Permission denied\n", 2);
	else if (type == OPEN_ERROR)
		ft_putstr_fd("No such file or directory\n", 2);
	else if (type == DIRECTORY_ERROR)
		ft_putstr_fd("Is a directory\n", 2);
	else if (type == QUOTE_ERROR)
		ft_putstr_fd("syntax error quote is not closed\n", 2);
	else if (type == SYNTAX_ERROR)
		ft_putstr_fd("'\n", 2);
	else if (type == HEREDOC_MAX_ERROR)
	{
		ft_putstr_fd("minishell: maximum here-document count exceeded\n", 2);	
		exit(2);
	}
	else if (type == COMMAND_ERROR)
		ft_putstr_fd("command not found\n", 2);
}

int	redirection_error(int fd, char *arg)
{
	if (fd == PERMISSION_ERROR)
		print_error(PERMISSION_ERROR, arg);
	else if (fd == OPEN_ERROR)
		print_error(OPEN_ERROR, arg);
	else
		print_error(DIRECTORY_ERROR, arg);
	return (ERROR);
}
