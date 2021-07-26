#include "philo.h"

unsigned long tm_manger(void)
{
    unsigned long mnt;
    struct timeval tmp_mnt;

    gettimeofday(&tmp_mnt, NULL);
    mnt = convert_ms(tmp_mnt);
    return (mnt);
}

int a_manger(t_philo *philo)
{
    pthread_mutex_lock(&philo->all->forks[philo->left]);
    print_phrase(philo, TAKE_FORK, get_time());
    pthread_mutex_lock(&philo->all->forks[philo->right]);
    print_phrase(philo, TAKE_FORK, get_time());
    print_phrase(philo, EATING, get_time());
    my_sleep(philo->all->time_to_eat);
    pthread_mutex_unlock(&philo->all->forks[philo->left]);
    pthread_mutex_unlock(&philo->all->forks[philo->right]);
    philo->count_eat++;
    pthread_mutex_lock(&philo->all->manger);
    if (philo->all->each_must_eat != -1
            && philo->count_eat == philo->all->each_must_eat)
    {
        pthread_mutex_unlock(&philo->all->manger);
        return (1);
    }
    pthread_mutex_unlock(&philo->all->manger);
    return (0);
}

int qqun_est_mort(t_philo *philo, unsigned long mnt)
{
    if (philo->all->est_mort == 1
            || mnt - philo->last_eat > philo->all->time_to_die)
        return (1);
    return (0);
}

int print_phrase(t_philo *philo, int value, unsigned long mnt)
{
    pthread_mutex_lock(&philo->all->phrase);
    if (value != DEAD && qqun_est_mort(philo, mnt))
    {
        pthread_mutex_unlock(&philo->all->phrase);
        return (1);
    }
    printf("%lu\t%d\t", mnt - philo->all->debut_dinner, philo->pos);
    if (value == TAKE_FORK)
        printf(" has taken a fork\n");
    if (value == EATING)
    {
        printf(" is eating\n");
        philo->last_eat = mnt;
    }
    if (value == SLEEPING)
        printf(" is sleeping\n");
    if (value == THINKING)
        printf(" is thinking\n");
    if (value == DEAD)
        printf(" died\n");
    pthread_mutex_unlock(&philo->all->phrase);
    return (0);
}
