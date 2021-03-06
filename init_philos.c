#include "philo.h"

void    my_sleep(unsigned long itime)
{
    unsigned long stime;
    unsigned long ctime;

    stime = get_time();
    while (1)
    {
        ctime = get_time();
        if (stime - ctime >= itime)
            return ;
        usleep(100);
    }    
}

void    *philosopher(void *arg)
{
    t_philo *philo;
    pthread_t   handler_thread;

    philo = arg;
    if (philo->pos % 2 == 0)
        my_sleep(philo->all->time_to_eat - 1);
    pthread_create(&handler_thread, NULL, handler_dead, philo);
    while (1)
    {
        if (a_manger(philo))
            break ;
        if (print_phrase(philo, SLEEPING, get_time()))
            break ;
        my_sleep(philo->all->time_to_sleep);
        if (print_phrase(philo, THINKING, get_time()))
            break ;
    }
    pthread_join(handler_thread, NULL);
    return (NULL);
}

void    init_philos(t_all *all, t_philo *philos)
{
    int i;

    i = 0;
	while (i < all->nb_of_philos)
    {
        philos[i].pos = i + 1;
		if (i == 0)
			philos[i].left = all->nb_of_philos - 1;
		else
			philos[i].left = i - 1;
		philos[i].right = i;
		philos[i].all = all;
        philos[i].count_eat = 0;
        philos[i].last_eat = get_time();
        pthread_create(&philos[i].philo_thread, NULL, philosopher, &philos[i]);
        i++;
    }
}
