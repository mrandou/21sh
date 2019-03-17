/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 19:58:42 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/17 03:11:44 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

static int 	process_input(t_param *param, t_sh *shell)
{
	t_ast *ast;

	ast = NULL;
	// display_tree(ast, 0, 0);
	// display_list(param->l_tokens);
	if (lex_input(param) != SUCCESS)
		return (FAILURE);
	else if (param->l_tokens && verify_lexer(param->l_tokens) == FAILURE)
		return (FAILURE);
	else if (!(ast = create_ast(param->l_tokens, param->l_tokens, NULL)))
		return (FAILURE);
	else if (apply_heredoc(ast) == FAILURE)
		return (FAILURE);
	else if (parser_execution(ast, shell) != 0)
		return (FAILURE);
	return (SUCCESS);
}

int     main(void)
{
	t_param *param;
	t_sh	*shell;
	int		ret;

	ret = 0;
	shell = init_shell();
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
			break;
	}
	sh_free_shell(shell);
	return (ret);
}