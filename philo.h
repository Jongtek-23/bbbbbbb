#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

# define TAKE_FORK 0
# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define DEAD 4

typedef struct  s_all
{
    int nb_of_philos;
	unsigned long time_to_die;
	unsigned long time_to_eat;
	unsigned long time_to_sleep;
	int             each_must_eat;
    unsigned long   debut_dinner;
	int             est_mort;
	pthread_mutex_t *forks;
	pthread_mutex_t phrase;
	pthread_mutex_t manger;
	pthread_mutex_t mourir;
}               t_all;

typedef struct  s_philo
{
    t_all   *all;
    int     right;
    int     left;
    int     pos;
    int     count_eat;
    unsigned long   last_eat;
    pthread_t   philo_thread;
}               t_philo;
/*
typedef struct  s_all
{
    int nb_of_philos;
    unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
    int             each_must_eat;
    unsigned long   debut_dinner;
    int             est_mort;
    pthread_mutex_t *forks;
    pthread_mutex_t phrase;
    pthread_mutex_t manger;
    pthread_mutex_t mourir;
}               t_all;
*/

void    init_philos(t_all *all, t_philo *philos);
void    *philosopher(void *arg);
void    my_sleep(unsigned long itime);

int		table_of_philos(t_all *all, t_philo *philos);

int print_phrase(t_philo *philo, int value, unsigned long mnt);
int a_manger(t_philo *philo);

void    *handler_dead(void *arg);

int ft_is_str_number(char *str);
int	ft_error(char *str);
int	ft_atoi(const char *str);
unsigned long	convert_ms(struct timeval tiempo);
unsigned long	get_time(void);

#endif
