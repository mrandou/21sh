/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hy_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 11:42:59 by mrandou           #+#    #+#             */
/*   Updated: 2019/03/16 14:29:43 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

void	hy_dlst_push(t_dlist **history, char *content)
{
	t_dlist *newlist;

	if (!(newlist = (t_dlist *)malloc(sizeof(t_dlist))))
		return ;
	if (!(newlist->content = ft_strdup(content)))
	{
		if (newlist)
			free(newlist);
		return ;
	}
	newlist->next = *history;
	newlist->prev = NULL;
	if (*history)
		(*history)->prev = newlist;
	*history = newlist;
}

void	hy_dlst_free(t_dlist *dlist)
{
	t_dlist	*tmp;

	while (dlist->prev)
		dlist = dlist->prev;
	while (dlist)
	{
		tmp = dlist->next;
		if (dlist->content)
			free(dlist->content);
		if (dlist)
			free(dlist);
		dlist = tmp;
	}
}

int		hy_history(struct s_le *le_struct, char **env)
{
	int		fd;
	int		ret;
	char	*path;
	size_t	pos;

	path = NULL;
	if (!env || sh_find_variable("HOME", env, &pos) == -1)
		return (FAILURE);
	if (!(path = sh_get_var_value(env[pos])))
		return (FAILURE);
	if (!(path = ft_strjoin_free(path, HY_FILE)))
		return (FAILURE);
	ret = 1;
	le_struct->history = NULL;
	if ((fd = open(path, O_RDONLY | O_CREAT, S_IREAD | S_IWRITE)) == -1)
	{
		ft_strdel(&path);
		return (FAILURE);
	}
	ft_strdel(&path);
	if (hy_history_fill_list(le_struct, fd, ret))
	{
		close(fd);
		return (FAILURE);
	}
	close(fd);
	return (SUCCESS);
}

int		hy_history_fill_list(struct s_le *le_struct, int fd, int ret)
{
	char	*line;
	char	*tmp;

	tmp = NULL;
	while (ret != -1 && ret)
	{
		line = NULL;
		if ((ret = get_next_line(fd, &line)) == -1)
			return (FAILURE);
		while (ret != -1 && ret && is_valid_quotes(line))
		{
			if ((ret = get_next_line(fd, &tmp)) == -1)
				return (FAILURE);
			if (!ret && !tmp)
			{
				ft_strdel(&line);
				return (SUCCESS);
			}
			if (!(line = ft_strjoin_free(line, tmp)))
				return (FAILURE);
			ft_strdel(&tmp);
		}
		hy_dlst_push(&le_struct->history, line);
		ft_strdel(&line);
	}
	return (SUCCESS);
}

int		hy_history_write(char *command, char **env)
{
	int		fd;
	char	*path;
	size_t	pos;

	path = NULL;
	if (!env || sh_find_variable("HOME", env, &pos) == -1)
		return (FAILURE);
	if (!(path = sh_get_var_value(env[pos])))
		return (FAILURE);
	if (!(path = ft_strjoin_free(path, HY_FILE)))
		return (FAILURE);
	if ((fd = open(path, O_WRONLY | O_APPEND)) == -1)
	{
		ft_strdel(&path);
		return (FAILURE);
	}
	ft_strdel(&path);
	if ((write(fd, command, ft_strlen(command))) == -1
	|| write(fd, "\n", 1) == -1)
	{	
		close(fd);
		return (FAILURE);
	}
	close(fd);
	return (SUCCESS);
}
