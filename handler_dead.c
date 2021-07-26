#include "philo.h"

void    *handler_dead(void *arg)
{
    t_philo *philo;
    unsigned long mnt;

    philo = arg;
    while (1)
    {
        if (philo->count_eat == philo->all->each_must_eat)
            break ;
        mnt = get_time();
        if (mnt - philo->last_eat > philo->all->time_to_die)
        {
            pthread_mutex_lock(&philo->all->mourir);
            if (philo->all->est_mort == 0)
            {
                philo->all->est_mort = 1;
                pthread_mutex_unlock(&philo->all->forks[philo->left]);
                print_phrase(philo, DEAD, mnt);
            }
            pthread_mutex_unlock(&philo->all->mourir);
            return (NULL);
        }
        my_sleep(1);
    }
    return (NULL);
}
