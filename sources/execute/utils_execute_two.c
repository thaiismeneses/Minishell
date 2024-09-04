/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execute_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:51:56 by thfranco          #+#    #+#             */
/*   Updated: 2024/09/04 19:46:23 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int	skip_whitespace(char *str, int i)
// {
// 	while (str[i] == ' ' || str[i] == '\t')
// 		i++;
// 	return (i);
// }

// char	**to_malloc_matriz(char **str, int len)
// {
// 	str = (char **)malloc(sizeof(char *) * (len + 1));
// 	if (!str)
// 		return (NULL);
// 	return (str);
// }

// int	handle_quotes(char *str, int *i, char *quote_char, int *inside_quotes)
// {
// 	if (str[*i] == '"' || str[*i] == '\'')
// 	{
// 		*quote_char = str[*i];
// 		*inside_quotes = 1;
// 		(*i)++;
// 		return (1);
// 	}
// 	return (0);
// }
// int	process_word(char *str, int *i, int *inside_quotes, char quote_char)
// {
// 	int	len;

// 	len = 0;
// 	while (str[*i] != '\0' && (*inside_quotes || (str[*i] != ' '
// 				&& str[*i] != '\t')))
// 	{
// 		if (*inside_quotes && str[*i] == quote_char)
// 		{
// 			*inside_quotes = 0;
// 			(*i)++;
// 			break ;
// 		}
// 		(*i)++;
// 		len++;
// 	}
// 	return (len);
// }

// int	store_word(char **result, int r, char *str, int start, int len)
// {
// 	int	j;

// 	result[r] = (char *)malloc(sizeof(char) * (len + 1));
// 	if (!result[r])
// 		return (-1);
// 	j = 0;
// 	while (j < len)
// 	{
// 		result[r][j] = str[start + j];
// 		j++;
// 	}
// 	result[r][j] = '\0';
// 	return (0);
// }

// int	count_words(char *str)
// {
// 	int		w;
// 	int		inside_quotes;
// 	char	quote_char;

// 	int vars[5];
// 	w = 0;
// 	vars[0] = 0;
// 	inside_quotes = 0;
// 	quote_char = '\0';
// 	while (str[vars[0]] != '\0')
// 	{
// 		vars[0] = skip_whitespace(str, vars[0]);
// 		handle_quotes(str, &vars[0], &quote_char, &inside_quotes);
// 		if (str[vars[0]] != '\0')
// 			w++;
// 		vars[3] = process_word(str, &vars[0], &inside_quotes, quote_char);
// 	}
// 	return (w);
// }
// void	initialize_vars(char *str, int *vars, int *inside_quotes,
// 		char *quote_char, char ***result)
// {
// 	vars[4] = count_words(str);
// 	vars[0] = 0;
// 	vars[2] = 0;
// 	*inside_quotes = 0;
// 	*quote_char = '\0';
// 	*result = to_malloc_matriz(*result, vars[4]);
// }

// char	**new_split(char *str)
// {
// 	char	**result;
// 	int		inside_quotes;
// 	char	quote_char;
// 	int		start;
// 	int		vars[5];

// 	initialize_vars(str, vars, &inside_quotes, &quote_char, &result);
// 	while (str[vars[0]] != '\0')
// 	{
// 		vars[0] = skip_whitespace(str, vars[0]);
// 		handle_quotes(str, &vars[0], &quote_char, &inside_quotes);
// 		start = vars[0];
// 		vars[3] = process_word(str, &vars[0], &inside_quotes, quote_char);
// 		if (vars[3] > 0)
// 		{
// 			if (store_word(result, vars[2], str, start, vars[3]) == -1)
// 				return (NULL);
// 			vars[2]++;
// 		}
// 	}
// 	result[vars[2]] = NULL;
// 	return (result);
// }
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
	*result = to_malloc_matriz(*result, vars->cw);
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
				return (NULL);
			vars.r++;
		}
	}
	result[vars.r] = NULL;
	return (result);
}
