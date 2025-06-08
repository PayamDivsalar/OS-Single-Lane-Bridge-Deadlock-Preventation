#ifndef BRIDGE_H
#define BRIDGE_H

#include <pthread.h>

#define N_NORTH 5
#define N_SOUTH 5

extern pthread_mutex_t bridge_mutex;

void log_status(const char *dir, int id, const char *msg);

void* north_farmer(void* arg);
void* south_farmer(void* arg);

#endif
