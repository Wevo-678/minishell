#include "../../includes/minishell.h"

// void	*split_init2(t_node **node)
// {
// 	int		i;
// 	int		len;
// 	int		new_word;

// 	i = 0;
// 	new_word = 1;
// 	len = cmd_len((*node)->data_dup, i);
// 	while ((*node)->data_dup[i])
// 		{
// 			if (new_word)
// 			{
// 				(*node)->data
// 				new_word = 0;
// 			}
// 			if (len == -2) //a remplir
// 				i++;
// 			i++;
// 		}
// }

// void	*split_init(t_node **first)
// {
// 	t_node	*tmp;

// 	tmp = (*first);
// 	while (tmp->next)
// 	{
// 		tmp->data = (t_node**)malloc(sizeof(t_node*) * (count_cmd(tmp->data_dup)));
// 		if (!(tmp->data))
// 			return (NULL);
// 		split_init2(&tmp);
// 		tmp = tmp->next;
// 	}
// }

//Hello

// /* /!\/!\/!\/!\/!\ A faire echo"test" a remplacer par echotest
// ie : enlever les quotes  et remplacer les variables si necessaire
// selon les quotes => remplacer si double quote, garder sinon */
// /* /!\/!\/!\/!\/!\ A faire free les node->data_dup */
// /* /!\/!\/!\/!\/!\ A mettre au debut check whitespace_cmd pour voir si on a une commande vide
// si jamais, juste faire un saut de ligne */