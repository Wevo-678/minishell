#include "../../includes/minishell.h"

/* Fill the data splited */
void	fill_data(t_node **node, int i, int len, int cmd)
{
	int	j;

	j = 0;
	while (j < len)
	{
		(*node)->data[cmd][j] = (*node)->data_dup[i + j];
		j++;
	}
	(*node)->data[cmd][j] = 0;
}

/* Malloc the second dimension of data */
/* Call the fill and the quote function */
/* Return first or NULL if malloc fails */
void	*split_init2(t_node **node, int nb_cmd)
{
	int		i;
	int		len;
	int		cmd;

	i = 0;
	cmd = 0;
	while (cmd < nb_cmd)
	{
		len = cmd_len((*node)->data_dup, i);
		while (!len)
		{
			i++;
			len = cmd_len((*node)->data_dup, i);
		}
		(*node)->data[cmd] = (char *)malloc(sizeof(char) * (len + 1));
		if ((*node)->data[cmd] == NULL)
			return (NULL);
		fill_data(node, i, len, cmd);
		i += len;
		cmd++;
	}
	free((*node)->data_dup);
	return (node);
}

/* Malloc the data for each node */
/* Call split_init2 */
/* Return first or NULL if malloc fails */
void	*split_init(t_node **first)
{
	t_node	*tmp;
	int		nb_cmd;

	tmp = (*first);
	while (tmp)
	{
		nb_cmd = count_cmd(tmp->data_dup);
		tmp->data = (char **)malloc(sizeof(char *) * (nb_cmd + 1));
		if (!(tmp->data))
			return (NULL);
		tmp->data[nb_cmd] = NULL;
		if (split_init2(&tmp, nb_cmd) == NULL)
			return (NULL);
		tmp = tmp->next;
	}
	return (first);
}
