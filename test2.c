/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirosuzu <hirosuzu@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 18:08:32 by hirosuzu          #+#    #+#             */
/*   Updated: 2024/01/21 18:20:26 by hirosuzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

// 哲学者の数とフォークの数を定義（例：5）
#define PHILOSOPHERS 5

pthread_mutex_t forks[PHILOSOPHERS]; // フォークのミューテックス
pthread_mutex_t mutex_print;         // 出力のミューテックス

// 哲学者の動作をシミュレートする関数
void *philosopher(void *num) {
    int id = *(int*)num;

    while (1) {
        // 思考
        pthread_mutex_lock(&mutex_print);
        printf("Philosopher %d is thinking.\n", id);
        pthread_mutex_unlock(&mutex_print);
        usleep(1000); // 思考時間

        // フォークを取る
        pthread_mutex_lock(&forks[id]);
        pthread_mutex_lock(&forks[(id + 1) % PHILOSOPHERS]);

        // 食事
        pthread_mutex_lock(&mutex_print);
        printf("Philosopher %d is eating.\n", id);
        pthread_mutex_unlock(&mutex_print);
        usleep(1000); // 食事時間

        // フォークを置く
        pthread_mutex_unlock(&forks[id]);
        pthread_mutex_unlock(&forks[(id + 1) % PHILOSOPHERS]);

        // 睡眠
        usleep(1000); // 睡眠時間
    }

    return NULL;
}

int main() {
    pthread_t th[PHILOSOPHERS];
    int ids[PHILOSOPHERS];

    pthread_mutex_init(&mutex_print, NULL);
    for (int i = 0; i < PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

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

