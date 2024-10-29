/*
 * FdWatcher - File Descriptor Watcher Interface.
 */

typedef struct fdwatcher {
	int epoll_fd;
} FdWatcher;

const char *fdwatcher_ev_interface(void);

FdWatcher *fdwatcher_create(void);

int fdwatcher_add(FdWatcher *fdw, int fd, void *ptr);

int fdwatcher_remove(FdWatcher *fdw, int fd);

int fdwatcher_wait(FdWatcher *fdw, void **events, int nevents, int timeout);

void fdwatcher_destroy(FdWatcher *fdw);