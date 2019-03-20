/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 17:26:14 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/20 19:33:58 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

int				get_io_number(t_ast *ast, t_ast *redir, int token)
{
	if (!ast || !redir)
		return (ERROR);
	if (ast == redir)
		return (token == GREATAND ? 1 : 0);
	while (ast->left && ast->left != redir)
		ast = ast->left;
	if (ast && ast->token == DIGIT && ast->io_number == 1)
		return (ft_atoi(ast->value));
	return (ERROR);
}

static int		get_dest_fd(char *arg, int *is_close)
{
	int		i;
	int		dest;
	char	*tmp;

	i = 0;
	dest = 0;
	tmp = NULL;
	while (arg[i] && ft_isdigit(arg[i]))
		i++;
	if (arg[i] && (arg[i] != '-' || (ft_strlen(arg) - (i + 1)) > 0))
		return (ERROR);
	if (arg[i] == '-' && !arg[i + 1])
		*is_close = 1;
	if (!(tmp = ft_strndup(arg, i)))
		return (ERROR);
	dest = ft_atoi(tmp);
	ft_strdel(&tmp);
	return (dest);
}

static int		redir_null(void)
{
	int		fd;

	if ((fd = open("/dev/null", O_RDONLY)) == ERROR)
		return (-2);
	return (fd);
}

int				handle_agregation(t_ast *redir, t_ast *ast)
{
	int		fd;
	int		is_close;

	fd = 0;
	is_close = 0;
	(void)ast;
	if ((fd = get_dest_fd(redir->left->value, &is_close)) == ERROR)
	{
		ambiguous_redirect(redir->left->value);
		return (-2);
	}
	if (is_close == 1)
		return (redir_null());
	return (SUCCESS);
}