/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 13:41:10 by dideryck          #+#    #+#             */
/*   Updated: 2019/03/07 02:58:24 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

int    parser_execution(t_ast *ast, t_sh *shell)
{
    int     ret;

    ret = 0;
    if (!ast)
        return (SUCCESS);
    if (ast->token == SEPARATOR && ast->right)
        ret = parser_execution(ast->right, shell);
    else if (ast->token == PIPE)
        return (do_pipe(shell, ast));
    else if (find_next_redir(ast))
        return (exec_redirection(ast, shell));
    else if (ast->token >= WORD)
    {
        shell->fork = 1;
        return (exec_cmd(ast, shell));
    }
    if (ast->token == SEPARATOR && ast->left)
        ret = parser_execution(ast->left, shell);
    return (ret);
}