/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 20:55:23 by andriamr          #+#    #+#             */
/*   Updated: 2026/01/24 16:24:16 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_is_quoted_token(char *token)
{
	int	i;

	if (!token || !*token)
		return (0);
	if (token[0] == '"' || token[0] == '\'')
		return (1);
	i = 0;
	while (token[i])
	{
		if (token[i] == '"' || token[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

static int	ft_count_words_expanded(char *str)
{
	int	count;
	int	in_word;
	int	i;

	count = 0;
	in_word = 0;
	i = 0;
	while (str && str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if ((str[i] == ' ' || str[i] == '\t') && in_word)
			in_word = 0;
		i++;
	}
	return (count);
}


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

// static char	**ft_split_expanded(char *str, t_pars *pars, int idx, t_cmd *cmd)
// {
// 	char	**words;
// 	char	**new_tokens;
// 	int		word_count;
// 	int		i;
// 	int		j;
// 	int		new_size;

// 	words = ft_split(str, ' ');
// 	if (!words || !words[0])
// 	{
// 		if (words)
// 			ft_free_split(words);
// 		return (pars->all_token);
// 	}
// 	word_count = 0;
// 	while (words[word_count])
// 		word_count++;
// 	if (word_count <= 1)
// 	{
// 		ft_free_split(words);
// 		return (pars->all_token);
// 	}
// 	new_size = pars->count_token + word_count - 1;
// 	new_tokens = ft_calloc(sizeof(char *), new_size + 1);
// 	if (!new_tokens)
// 	{
// 		ft_free_split(words);
// 		return (pars->all_token);
// 	}
// 	i = 0;
// 	j = 0;
// 	while (i < idx)
// 		new_tokens[j++] = ft_strdup(pars->all_token[i++]);
// 	i = 0;
// 	while (words[i])
// 		new_tokens[j++] = ft_strdup(words[i++]);
// 	i = idx + 1;
// 	while (pars->all_token[i])
// 		new_tokens[j++] = ft_strdup(pars->all_token[i++]);
// 	new_tokens[j] = NULL;
// 	ft_free_split(words);
// 	ft_free_split(pars->all_token);
// 	pars->count_token = new_size;
// 	(void)cmd;
// 	return (new_tokens);
// }

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

static void	handle_val_utils(char **res, char *val)
{
	char	*tmp;

	tmp = ft_strjoin(*res, val);
	free(*res);
	free(val);
	*res = tmp;
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