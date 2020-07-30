// Assignment name  : inter
// Expected files   : inter.c
// Allowed functions: write
// --------------------------------------------------------------------------------

// Write a program that takes two strings and displays, without doubles, the
// characters that appear in both strings, in the order they appear in the first
// one.

// The display will be followed by a \n.

// If the number of arguments is not 2, the program displays \n.

// Examples:

// $>./inter "padinton" "paqefwtdjetyiytjneytjoeyjnejeyj" | cat -e
// padinto$
// $>./inter ddf6vewg64f gtwthgdwthdwfteewhrtag6h4ffdhsd | cat -e
// df6ewg4$
// $>./inter "nothing" "This sentence hides nothing" | cat -e
// nothig$
// $>./inter | cat -e
// $

#include <unistd.h>
#include <stdio.h>

int 		main(int argc, char **argv)
{
	int		tab[256] = {0};
	int		i;
	char	n;

	n = '\n';
	i = 0;
	if (argc == 3)
	{
		while (argv[2][i])
		{
			if (tab[(int)argv[2][i]] == 0)
				tab[(int)argv[2][i]] = 1;
			i++;
		}
		i = 0;
		while (argv[1][i])
		{
			if (tab[(int)argv[1][i]] == 1)
			{
				write(1, &argv[1][i], 1);
				tab[(int)argv[1][i]] = 0;
			}
			i++;
		}
	}
	write(1, &n, 1);
	return (0);
}