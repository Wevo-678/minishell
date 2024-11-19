#include "../../includes/minishell.h"

int unclosed_quote_check(char *s)
{
	bool	d_quote;
	bool	s_quote;
	int i;

	d_quote = false;
	s_quote = false;
	i = 0;
	while(s[i])
	{
		if(s[i] == '\'' && s_quote == false && d_quote == false)
			s_quote = true;
		else if(s[i] == '\'' && s_quote == true && d_quote == false)
			s_quote = false;
		else if(s[i] == '\"' && s_quote == false && d_quote == false)
			d_quote = true;
		else if(s[i] == '\"' && s_quote == false && d_quote == true)
			d_quote = false;
		i++;
	}
	if (s_quote == false && d_quote == false)
		return(1);
	else 
		return (0);
}

int	treat_input(char *input)
{
	if (unclosed_quote_check(input) == 0)
	{
		printf("minishell: unclosed quote error.\n");
		return (-1);
	}
	else if (check_empty_pipe(input) == 1 || check_empty_redir(input) == 1)
	{
		printf("minishell: syntax error near unexpected token\n");
		return (-2);
	}
	return (0);
}
