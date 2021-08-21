#include <unistd.h>
#include "signal.h"
#include "minitalk.h"

static int	find_n(int *count, char arr[])
{
	int	n;

	n = 0;
	while (*count)
	{
		n = n * 2 + arr[8 - *count];
		arr[8 - *count] = 0;
		(*count)--;
	}
	return (n);
}

static void	hand_fun(int sign, siginfo_t *siginfo, void *context)
{
	static int	count = 0;
	static char	arr[] = {0, 0, 0, 0, 0, 0, 0, 0};
	char		c;

	if (sign == SIGUSR1)
		arr[count] = 1;
	else
		arr[count] = 0;
	count++;
	if (count == 8)
	{
		c = (char)find_n(&count, arr);
		write(1, &c, 1);
		if (c == 0)
		{
			kill(siginfo->si_pid, SIGUSR1);
			context = NULL;
		}
	}
}

int	main(void)
{
	char				*s;
	struct sigaction	sact;
	sigset_t			set;

	write(1, "Server's pid = ", 16);
	s = ft_itoa(getpid());
	write(1, s, (int)ft_strlen(s));
	write(1, "\n", 1);
	sact.sa_sigaction = hand_fun;
	sigemptyset(&set);
	sigaddset(&set, SIGUSR1);
	sigaddset(&set, SIGUSR2);
	sact.sa_mask = set;
	sact.sa_flags |= SA_SIGINFO;
	sigaction(SIGUSR1, &sact, 0);
	sigaction(SIGUSR2, &sact, 0);
	while (1)
	{
	}
}
