#include <unistd.h>
#include "signal.h"
#include "minitalk.h"

void	char_to_double(int pidn, char c)
{
	int	i;
	int	arr[8];

	arr[7] = 128;
	arr[6] = 64;
	arr[5] = 32;
	arr[4] = 16;
	arr[3] = 8;
	arr[2] = 4;
	arr[1] = 2;
	arr[0] = 1;
	c = (int)c;
	i = 7;
	while (i >= 0)
	{
		if (c / arr[i])
			kill(pidn, SIGUSR1);
		else
			kill(pidn, SIGUSR2);
		usleep(50);
		c = c % arr[i];
		i--;
	}
}

static void	hand_fun(int sign)
{
	if (sign == SIGUSR1)
		write(1, "Got responce from server",
			ft_strlen("Got responce from server"));
}

int	main(int argc, char **argv)
{
	char	*s;
	int		server_pid;

	if (argc == 3)
	{
		signal(SIGUSR1, &hand_fun);
		server_pid = ft_atoi(argv[1]);
		if (server_pid <= 0)
		{
			write(1, "PID Error\n", ft_strlen("PID Error") + 1);
			return (0);
		}
		s = argv[2];
		while (*s)
		{
			char_to_double(server_pid, s[0]);
			s++;
		}
		char_to_double(server_pid, 0);
		sleep(1);
	}
	else
		write(1, "Should be 2 arguments\n", ft_strlen("Should be 2 arguments\n"));
}
