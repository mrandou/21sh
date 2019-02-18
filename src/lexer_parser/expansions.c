/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 14:18:40 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/02/18 15:53:44 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

static ssize_t		tilde_expansion(char **arg)
{
	char	*tmp;

	tmp = NULL;
	if (!arg || !(*arg))
		return (FAILURE);
	if ((*arg)[0] == C_TILDE && ft_strlen(*arg) > 1 && (*arg)[1] == C_SLASH)
	{
		if (!(tmp = ft_strdup((*arg) + 1)))
			ms_malloc_error();
		ft_strdel(arg);
		if (!(*arg = ft_strjoin(DEFAULT_HOME, tmp)))
			ms_malloc_error();
		ft_strdel(&tmp);
	}
	else if ((*arg)[0] == C_TILDE)
	{
		ft_strdel(arg);
		if (!(*arg = ft_strdup(DEFAULT_HOME)))
			ms_malloc_error();
	}
	return (SUCCESS);
}

static void			concat_d_expansion(char *ptr, char *arg, t_expansion *st,
					char **env)
{
	if (!(st->sub = (ptr != arg ? ft_strsub(arg, 0, (size_t)(ptr - arg)) :
	ft_strdup(""))))
		ms_malloc_error();
	if ((st->v_value = ms_get_var_path(ptr + 1, env, &st->index)) != NULL)
	{
		if (st->join && (st->join[0]))
		{
			ft_strdel(&st->sub);
			st->sub = ft_strndup(st->join, ft_strlen(st->join) - st->index - 1);
			ft_strdel(&st->join);
			st->join = NULL;
		}
		if (!(st->join = ft_strjoin_free(st->sub, st->v_value)) ||
		!(st->sub = ft_strsub(ptr + 1, st->index, ft_strlen(ptr + st->index)))
		|| !(st->join = ft_strjoin_free(st->join, st->sub)))
			ms_malloc_error();
		ft_strdel(&st->v_value);
	}
}

static void			dollar_expansion(char **cmdline, char **env, char *arg,
										char *ptr)
{
	t_expansion	st;

	st.index = 0;
	st.join = NULL;
	while (ptr)
	{
		concat_d_expansion(ptr, arg, &st, env);
		ft_strdel(&st.sub);
		arg = ptr + st.index;
		ptr = ft_strchr(ptr + st.index + 1, VAL_DOLLAR);
	}
	ft_strdel(cmdline);
	*cmdline = st.join;
}

ssize_t				apply_expansions(t_sh *shell)
{
	size_t		i;
	char		*ptr;

	ptr = NULL;
	i = 0;
	while (shell->cmd[i])
	{
		if ((ptr = ft_strchr(shell->cmd[i], VAL_DOLLAR)) &&
				ft_strlen(shell->cmd[i]) > 1)
					dollar_expansion(shell->cmd + i, shell->env, shell->cmd[i], ptr);
		else if ((ft_strcmp(shell->cmd[i], "~") == SUCCESS) ||
					ft_strchr(shell->cmd[i], VAL_TILDE))
			if (tilde_expansion(shell->cmd + i) == FAILURE)
				return (FAILURE);
		i++;
	}
	return (SUCCESS);
}
