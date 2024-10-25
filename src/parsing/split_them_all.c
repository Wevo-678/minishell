#include "../../includes/minishell.h"



// int main(int argc, char **argv)
// {
// 	printf("str : %s\n", argv[1]);
// 	printf("len : %d\n", cmd_len(argv[1], 0));
// 	return (0);
// }

/* /!\/!\/!\/!\/!\ A faire echo"test" a remplacer par echotest
ie : enlever les quotes  et remplacer les variables si necessaire
selon les quotes => remplacer si double quote, garder sinon */
/* /!\/!\/!\/!\/!\ A faire free les node->data_dup */
/* /!\/!\/!\/!\/!\ A mettre au debut check whitespace_cmd pour voir si on a une commande vide
si jamais, juste faire un saut de ligne */