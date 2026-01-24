/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 20:55:23 by andriamr          #+#    #+#             */
/*   Updated: 2026/01/24 20:22:18 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**ft_abort_expansion(char **words, char **original)
{
	if (words)
		ft_free_split(words);
	return (original);
}

static void	ft_fill_new_tokens(char **dest, char **src, char **add, int idx)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (i < idx)
		dest[j++] = ft_strdup(src[i++]);
	k = 0;
	while (add[k])
		dest[j++] = ft_strdup(add[k++]);
	i++;
	while (src[i])
		dest[j++] = ft_strdup(src[i++]);
	dest[j] = NULL;
}

char	**ft_split_expanded(char *str, t_pars *pars, int idx, t_cmd *cmd)
{
	char	**words;
	char	**new_tok;
	int		cnt;

	(void)cmd;
	words = ft_split(str, ' ');
	if (!words || !words[0])
		return (ft_abort_expansion(words, pars->all_token));
	cnt = 0;
	while (words[cnt])
		cnt++;
	if (cnt <= 1)
		return (ft_abort_expansion(words, pars->all_token));
	new_tok = ft_calloc(sizeof(char *), pars->count_token + cnt);
	if (!new_tok)
		return (ft_abort_expansion(words, pars->all_token));
	ft_fill_new_tokens(new_tok, pars->all_token, words, idx);
	ft_free_split(words);
	ft_free_split(pars->all_token);
	pars->count_token += cnt - 1;
	return (new_tok);
}

void	process_all_tokens(t_pars *pars, t_cmd *cmd)
{
	int		i;
	char	*cleaned;
	char	*original;
	int		was_quoted;
	int		word_count;

	i = 0;
	if (!pars || !pars->all_token)
		return ;
	while (pars->all_token[i])
	{
		original = pars->all_token[i];
		was_quoted = ft_is_quoted_token(original);
		cleaned = expand_and_clean(original, cmd);
		free(pars->all_token[i]);
		pars->all_token[i] = cleaned;
		word_count = ft_count_words_expanded(cleaned);
		if (!was_quoted && word_count > 1)
		{
			pars->all_token = ft_split_expanded(cleaned, pars, i, cmd);
			i += word_count;
		}
		else
			i++;
	}
}

int	handle_var(char *str, int i, char **res, t_cmd *cmd)
{
	int		start;
	char	*key;
	char	*val;

	i++;
	start = i;
	if (str[i] == '?')
		i++;
	else if (ft_isdigit(str[i]))
		i++;
	else
		while (ft_isalnum(str[i]) || str[i] == '_')
			i++;
	if (start == i)
		val = ft_strdup("$");
	else
	{
		key = ft_substr(str, start, i - start);
		val = get_env_val(key, cmd);
		free(key);
	}
	handle_val_utils(res, val);
	return (i);
}
