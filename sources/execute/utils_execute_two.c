/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execute_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:51:56 by thfranco          #+#    #+#             */
/*   Updated: 2024/09/04 20:36:36 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	store_word(char **result, t_vars *vars, char *str, int start)
{
	int	j;

	result[vars->r] = (char *)malloc(sizeof(char) * (vars->len + 1));
	if (!result[vars->r])
		return (-1);
	j = 0;
	while (j < vars->len)
	{
		result[vars->r][j] = str[start + j];
		j++;
	}
	result[vars->r][j] = '\0';
	return (0);
}

int	count_words(char *str)
{
	t_vars	vars;
	int		w;

	w = 0;
	vars.i = 0;
	vars.inside_quotes = 0;
	vars.quote_char = '\0';
	while (str[vars.i] != '\0')
	{
		vars.i = skip_whitespace(str, vars.i);
		handle_quotes(str, &vars.i, &vars.quote_char, &vars.inside_quotes);
		if (str[vars.i] != '\0')
			w++;
		vars.len = process_word(str, &vars.i, &vars.inside_quotes,
				vars.quote_char);
	}
	return (w);
}

void	initialize_vars(char *str, t_vars *vars, char ***result)
{
	vars->cw = count_words(str);
	vars->i = 0;
	vars->r = 0;
	vars->inside_quotes = 0;
	vars->quote_char = '\0';
	*result = to_malloc_matrix(*result, vars->cw);
}

char	**new_split(char *str)
{
	char	**result;
	t_vars	vars;
	int		start;

	initialize_vars(str, &vars, &result);
	while (str[vars.i] != '\0')
	{
		vars.i = skip_whitespace(str, vars.i);
		handle_quotes(str, &vars.i, &vars.quote_char, &vars.inside_quotes);
		start = vars.i;
		vars.len = process_word(str, &vars.i, &vars.inside_quotes,
				vars.quote_char);
		if (vars.len > 0)
		{
			if (store_word(result, &vars, str, start) == -1)
			{
				ft_free_tab(result);
				return (NULL);
			}
			vars.r++;
		}
	}
	result[vars.r] = NULL;
	return (result);
}
