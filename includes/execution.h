/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 02:33:26 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/18 16:11:57 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../libsh/libsh.h"

int			exec_cmd(t_ast *ast, t_sh *shell);
int			exec_pipe_cmd(t_sh *shell, t_ast *ast);
int			parser_execution(t_ast *ast, t_sh *shell);

#endif
