/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabu-shr <rabu-shr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:03:34 by jalqam            #+#    #+#             */
/*   Updated: 2025/05/21 15:51:40 by rabu-shr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


// int is_expandable(char *str, int i, int in_squotes)
// {
//     return (str[i] == '$' && str[i + 1] && !in_squotes);
// }

// int handle_and_expand(char *str, int *i, char **result, t_env *env, int *quotes)
// {
//     if (handle_special_param(str, i, result, env))  // renamed here
//         return (1);
//     if (ft_isalpha(str[*i + 1]) || str[*i + 1] == '_' || str[*i + 1] == '$')
//         return expand_env_var(str, i, result, env, quotes[1]);
//     return (0);
// }

// int append_char_to_result_q(char **result, char c)
// {
//     char *temp;
//     temp = *result;
//     *result = ft_strjoin_char(*result, c);
//     free(temp);
//     return (*result != NULL);
// }

// int process_dollar_expansion(char *str, int *i, char **result, t_env *env, int *quotes)
// {
//     if (is_expandable(str, *i, quotes[0]))
//     {
//         if (handle_and_expand(str, i, result, env, quotes))
//             return (1);
//     }
//     return (0);
// }

// char *handle_dollar_expander(t_token *token, t_env *env)
// {
//     char *result;
//     char *str;
//     int i;
//     int quotes[2];

//     quotes[0] = 0;
//     quotes[1] = 0;
//     result = ft_strdup("");
//     if (!result)
//         return (NULL);
//     str = token->value;
//     i = 0;
//     while (str[i])
//     {
//         if (toggle_quotes(str[i], &quotes[0], &quotes[1]))
//         {
//             if (!append_char_to_result_q(&result, str[i++]))
//                 return (NULL);
//             continue;
//         }
//         if (process_dollar_expansion(str, &i, &result, env, quotes))
//             continue;
        
//         // Use append_char_to_result as declared (returns new pointer)
//         result = append_char_to_result(result, str[i++]);
//         if (!result)
//             return (NULL);
//     }
//     return (result);
// }