/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirosuzu <hirosuzu@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 15:48:54 by hirosuzu          #+#    #+#             */
/*   Updated: 2024/01/21 15:49:22 by hirosuzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#define PHILOSOPHERS 5

pthread_mutex_t forks[PHILOSOPHERS];
pthread_mutex_t mutex_print;

void *philosopher(void *num) {
    int id = *(int*)num;
    struct timeval start, current;
    gettimeofday(&start, NULL);

    while (1) {
        gettimeofday(&current, NULL);
        long elapsed = (current.tv_sec - start.tv_sec) * 1000 + (current.tv_usec - start.tv_usec) / 1000;

        // 哲学者の状態をログに記録
        pthread_mutex_lock(&mutex_print);
        printf("%ld ms Philosopher %d is thinking.\n", elapsed, id);
        pthread_mutex_unlock(&mutex_print);

        // フォークを取る
        pthread_mutex_lock(&forks[id]);
        pthread_mutex_lock(&forks[(id + 1) % PHILOSOPHERS]);

        gettimeofday(&current, NULL);
        elapsed = (current.tv_sec - start.tv_sec) * 1000 + (current.tv_usec - start.tv_usec) / 1000;
        pthread_mutex_lock(&mutex_print);
        printf("%ld ms Philosopher %d has taken a fork and is eating.\n", elapsed, id);
        pthread_mutex_unlock(&mutex_print);

        usleep(1000); // 食事の時間

        pthread_mutex_unlock(&forks[id]);
        pthread_mutex_unlock(&forks[(id + 1) % PHILOSOPHERS]);

        usleep(1000); // 睡眠の時間
    }

    return NULL;
}

int main() {
    pthread_t th[PHILOSOPHERS];
    int ids[PHILOSOPHERS];

    for (int i = 0; i < PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }
    pthread_mutex_init(&mutex_print, NULL);

    for (int i = 0; i < PHILOSOPHERS; i++) {
        ids[i] = i;
        pthread_create(&th[i], NULL, philosopher, &ids[i]);
    }

    for (int i = 0; i < PHILOSOPHERS; i++) {
        pthread_join(th[i], NULL);
    }

    for (int i = 0; i < PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }
    pthread_mutex_destroy(&mutex_print);

    return 0;
}
