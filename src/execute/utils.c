/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabu-shr <rabu-shr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:46:52 by jalqam            #+#    #+#             */
/*   Updated: 2025/05/21 15:49:31 by rabu-shr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	init_expander_state(t_expander_state *exp, t_token *token, t_env *env)
// {
// 	exp->result = ft_strdup("");
// 	exp->str = token->value;
// 	exp->idx = 0;
// 	exp->env = env;
// 	exp->in_dquotes = 0;
// 	exp->in_squotes = 0;
// }

// int	handle_expander_quotes(t_expander_state *exp)
// {
// 	if (exp->str[exp->idx] == '\'' && !exp->in_dquotes)
// 	{
// 		if (exp->str[exp->idx + 1] == '\'')
// 		{
// 			exp->idx += 2;
// 			return (1);
// 		}
// 		exp->in_squotes = !exp->in_squotes;
// 		exp->idx++;
// 		return (1);
// 	}
// 	else if (exp->str[exp->idx] == '"' && !exp->in_squotes)
// 	{
// 		exp->in_dquotes = !exp->in_dquotes;
// 		exp->idx++;
// 		return (1);
// 	}
// 	return (0);
// }

// static int	handle_dollar(t_expander_state *exp)
// {
// 	if (exp->str[exp->idx] == '$' && exp->str[exp->idx + 1] && !exp->in_squotes)
// 	{
// 		if (handle_exit_status_expansion(exp->str, &exp->idx, &exp->result, exp->env)
// 			|| handle_special_param(exp->str, &exp->idx, &exp->result))
// 			return (1);
// 		if (ft_isalpha(exp->str[exp->idx + 1]) || exp->str[exp->idx + 1] == '_')
// 		{
// 			t_expander_state state;
// 			state.str = exp->str;
// 			state.idx = exp->idx;
// 			state.result = exp->result;
// 			state.env = exp->env;
// 			state.in_dquotes = exp->in_dquotes;
// 			state.in_squotes = exp->in_squotes;
// 			if (handle_variable_expansion(&state))
// 			{
// 				exp->idx = state.idx;
// 				exp->result = state.result;
// 				return (1);
// 			}
// 		}
// 	}
// 	return (0);
// }

// static int	append_char(t_expander_state *exp)
// {
// 	char *temp;

// 	temp = exp->result;
// 	exp->result = ft_strjoin_char(exp->result, exp->str[exp->idx++]);
// 	free(temp);
// 	return (exp->result == NULL);
// }

// char	*handle_dollar_expander(t_token *token, t_env *env)
// {
// 	t_expander_state	exp;

// 	init_expander_state(&exp, token, env);
// 	if (!exp.result)
// 		return (NULL);
// 	while (exp.str[exp.idx])
// 	{
// 		if (handle_expander_quotes(&exp))
// 			continue;
// 		if (handle_dollar(&exp))
// 			continue;
// 		if (append_char(&exp))
// 			return (NULL);
// 	}
// 	return (exp.result);
// }