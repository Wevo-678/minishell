#include "../../includes/minishell.h"

void	delete_quotes(t_node **node)
{
	int	i;
	int	j;

	i = 0;
	while ()
}

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
/* Call the fill function */
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
			return NULL;
		fill_data(node, i, len, cmd);
		i += len;
		cmd++;
	}
	free((*node)->data_dup);
	return (node);
}

/* Malloc the data for each node */
/* Call split_init2 and the quote function */
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
		delete_quotes(&tmp);
		tmp = tmp->next;
	}
	return (first);
}

/* /!\/!\/!\/!\/!\ A faire echo"test" a remplacer par echotest
ie : enlever les quotes  et remplacer les variables si necessaire
selon les quotes => remplacer si double quote, garder sinon */
/* /!\/!\/!\/!\/!\ A faire free les node->data_dup */
/* /!\/!\/!\/!\/!\ A mettre au debut check whitespace_cmd pour voir si on a une commande vide
si jamais, juste faire un saut de ligne */
/* /!\/!\/!\/!\/!\ Cascade de NULL si malloc fail a mettre en place */
/*int	main(int argc, char **argv)
{
	t_node	*first;
	t_node	*tmp;
	int	i;

	(void)argc;
	first = NULL;
	dup_on_pipes(&first, argv[1]);
	tmp = (first);
	while (tmp)
	{
		printf("Dup : %s\n",tmp->data_dup);
		tmp = tmp->next;
	}
	split_init(&first);
	tmp = (first);
	while (tmp)
	{
		i = 0;
		while (tmp->data[i])
		{
			printf("Split %d : %s\n",i, tmp->data[i]);
			i++;
		}
		tmp = tmp->next;
	}
	return (0);
}*/