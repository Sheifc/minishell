/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:49:55 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/27 18:49:56 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIROMENT_H
# define ENVIROMENT_H

# include "error.h"
# include "libft.h"
# include "minishell.h"
# include "structures.h"

char	*create_new_result(const char *result, const char *pos,
			const char *value, const char *name);
char	*replace_variable(const char *pos, char *result, const char *name,
			t_shell *data);
int		is_preceded_by_double_less(const char *str, const char *pos);
char	*replace_env_variables(const char *input, t_shell *data);

char	*initialize_result(const char *input);
char	*extract_variable_name(const char *start);

bool	check_opening_quotes(const char *str, const char *pos);
bool	check_closing_quotes(const char *str, const char *pos,
			bool in_single_quote_o);
bool	is_btw_single_quotes(const char *str, const char *pos);

#endif
