#include "../../includes/minishell.h"


		// if (input[i + j] == '\"' && !between_quotes(input, i + j))
		// 	return (j + 1);
		// if (input[i + j] == '\'' && !between_quotes(input, i + j))
		// 	return (j + 1);
		// if (input[i + j] == '<' && !between_quotes(input, i + j))
		// {
		// 	if (input[i + j + 1] == '<' && !j)
		// 		return (2);

		// }
		// 	return (j);
		// if (input[i + j] == '>' && !between_quotes(input, i + j))
		// 	return (j);
int main(int argc, char **argv)
{
	printf("str : %s\n", argv[1]);
	printf("len : %d\n", cmd_len(argv[1], 0));
	return (0);
}

/* /!\/!\/!\/!\/!\ A faire echo"test" a remplacer par echotest
ie : enlever les quotes  et remplacer les variables si necessaire
selon les quotes*/
/* /!\/!\/!\/!\/!\ A faire free les node->data_dup */