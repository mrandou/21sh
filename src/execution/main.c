/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 19:58:42 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/19 14:29:45 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

static int	process_input(t_param *param, t_sh *shell)
{
	t_ast *ast;

	ast = NULL;
	if (lex_input(param) != SUCCESS)
		return (FAILURE);
	else if (param->l_tokens && verify_lexer(param->l_tokens) == FAILURE)
		return (FAILURE);
	else if (!(ast = create_ast(param->l_tokens, param->l_tokens, NULL)))
		return (FAILURE);
	else if (find_heredoc(ast) == FAILURE)
		return (FAILURE);
	else if (parser_execution(ast, shell) != 0)
		return (FAILURE);
	return (SUCCESS);
}

static int	edit_shlvl(char **env)
{
	size_t	pos;
	char	*new;
	char	*tmp;
	int		value;
	int		len;

	if (!env || sh_find_variable("SHLVL", env, &pos) == -1)
		return (FAILURE);
	len = ft_strlen(env[pos]);
	value = ft_atoi(ft_strchr(env[pos], '=') + 1);
	value += 1;
	if (!(new = ft_strnew(len + ft_nblen(value))))
		return (FAILURE);
	new = ft_strncpy(new, env[pos], len - ft_nblen(value - 1));
	if (!(tmp = ft_itoa(value)))
	{
		ft_strdel(&new);
		return (FAILURE);
	}
	new = ft_strcat(new, tmp);
	ft_strdel(&tmp);
	ft_strdel(&env[pos]);
	env[pos] = new;
	return (SUCCESS);
}

int			main(void)
{
	t_param *param;
	t_sh	*shell;
	int		ret;

	ret = 0;
	shell = init_shell();
	edit_shlvl(shell->env);
	while (21)
	{
		param = init_param();
		if (get_valid_input(param, shell->env, ret) == SUCCESS)
		{
			hy_history_write(param->input, shell->env);
			ret = process_input(param, shell);
		}
		free_param(param);
		param = NULL;
		if (!isatty(0))
			break ;
	}
	sh_free_shell(shell);
	return (ret);
}
