#include "bridge.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

pthread_mutex_t bridge_mutex;

void log_status(const char *dir, int id, const char *msg) {
    printf("[%s %2d] %s\n", dir, id, msg);
}

void* north_farmer(void* arg) {
    int id = *(int*)arg;
    free(arg);

    log_status("North", id, "wants to cross");
    pthread_mutex_lock(&bridge_mutex);

    log_status("North", id, "ENTERING bridge");
    int t = rand() % 3 + 1;  // 1..3 seconds
    sleep(t);
    char buf[64];
    snprintf(buf, sizeof(buf), "LEAVING bridge after %d sec", t);
    log_status("North", id, buf);

    pthread_mutex_unlock(&bridge_mutex);
    return NULL;
}

void* south_farmer(void* arg) {
    int id = *(int*)arg;
    free(arg);

    log_status("South", id, "wants to cross");
    pthread_mutex_lock(&bridge_mutex);

    log_status("South", id, "ENTERING bridge");
    int t = rand() % 3 + 1;  // 1..3 seconds
    sleep(t);
    char buf[64];
    snprintf(buf, sizeof(buf), "LEAVING bridge after %d sec", t);
    log_status("South", id, buf);

    pthread_mutex_unlock(&bridge_mutex);
    return NULL;
}

int main() {
    pthread_t north_threads[N_NORTH], south_threads[N_SOUTH];
    pthread_mutex_init(&bridge_mutex, NULL);
    srand(time(NULL));

    for (int i = 0; i < N_NORTH; i++) {
        int *id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&north_threads[i], NULL, north_farmer, id);
    }

    for (int i = 0; i < N_SOUTH; i++) {
        int *id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&south_threads[i], NULL, south_farmer, id);
    }

    for (int i = 0; i < N_NORTH; i++)
        pthread_join(north_threads[i], NULL);
    for (int i = 0; i < N_SOUTH; i++)
        pthread_join(south_threads[i], NULL);

    pthread_mutex_destroy(&bridge_mutex);
    return 0;
}
