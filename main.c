#include "philo.h"

void	free_clean_mutex(t_all *all, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < all->nb_of_philos)
	{
		pthread_join(philos[i].philo_thread, NULL);
		i++;
	}
	i = 0;
	while (i < all->nb_of_philos)
	{
		pthread_mutex_destroy(&all->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&all->phrase);
	pthread_mutex_destroy(&all->manger);
	pthread_mutex_destroy(&all->mourir);
	free(all->forks);
	free(philos);
}

int	values_of_args(t_all *all, int argc, char *argv[])
{
    int i;

    i = 1;
    all->each_must_eat = -1;
    while (argv[i])
    {
        if (ft_is_str_number(argv[i]))
            return (ft_error("Error: No numbers\n"));
        i++;
    }
	all->nb_of_philos = ft_atoi(argv[1]);
	all->time_to_die = ft_atoi(argv[2]);
	all->time_to_eat = ft_atoi(argv[3]);
	all->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		all->each_must_eat = ft_atoi(argv[5]);
    return (0);
}

int	verif_values_of_args(t_all *all, int argc)
{
	if (all->nb_of_philos <= 0)
		return (ft_error("Error: number of philos\n"));
	if (all->time_to_die < 0)
		return (ft_error("Error: time to die\n"));
	if (all->time_to_eat < 0)
		return (ft_error("Error: time to eat\n"));
	if (all->time_to_sleep < 0)
		return (ft_error("Error: time to sleep\n"));
	if (argc == 6 && all->each_must_eat <= 0)
		return (ft_error("Error: num of each must eat\n"));
	return (0);
}

int	main(int argc, char *argv[])
{
	t_all	all;
    t_philo *philos;

	if (argc != 5 && argc != 6)
	{
		printf("Error with number of arguments\n");
		return (1);
	}
	if (values_of_args(&all, argc, argv))
        return (1);
	if (verif_values_of_args(&all, argc))
		return (1);
    if (table_of_philos(&all, philos))
        return (1);
	philos = malloc(sizeof(t_philo) * (all.nb_of_philos));
	if (philos == NULL)
		return (ft_error("Error: malloc failed\n"));
	init_philos(&all, philos);
	free_clean_mutex(&all, philos);
    return (0);
}
