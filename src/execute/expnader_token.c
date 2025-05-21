/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expnader_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabu-shr <rabu-shr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:06:21 by jalqam            #+#    #+#             */
/*   Updated: 2025/05/21 13:55:38 by rabu-shr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	handle_token_expansion(t_token *temp, t_env *env, char **expanded)
// {
// 	if (ft_strchr(temp->value, '$'))
// 	{
// 		*expanded = handle_dollar_expander(temp, env);
// 		if (*expanded)
// 		{
// 			free(temp->value);
// 			temp->value = *expanded;
// 			*expanded = NULL;
// 		}
// 	}
// }

// void	handle_token_quotes(t_token *temp, char **expanded)
// {
// 	if (ft_strchr(temp->value, '"') || ft_strchr(temp->value, '\''))
// 	{
// 		*expanded = handle_mixed_quotes(temp);
// 		if (*expanded)
// 		{
// 			free(temp->value);
// 			temp->value = *expanded;
// 			*expanded = NULL;
// 		}
// 	}
// }
