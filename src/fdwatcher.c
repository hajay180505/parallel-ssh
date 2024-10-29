#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/epoll.h>
#include "fdwatcher.h"

/*
 * Return event interface type as a string.
 */
const char * fdwatcher_ev_interface(void)
{
	return "epoll";
}

FdWatcher * fdwatcher_create(void)
{
	FdWatcher *fdw = malloc(sizeof (FdWatcher));

	if (fdw == NULL) {
		return NULL;
	}

	fdw->epoll_fd = epoll_create1(EPOLL_CLOEXEC);
	if (fdw->epoll_fd == -1) {
		goto fail;
	}

	return fdw;

fail:
	free(fdw);
	return NULL;
}


int fdwatcher_add(FdWatcher *fdw, int fd, void *ptr)
{
	int ret = -1;
	struct epoll_event ev;

	ev.events = EPOLLIN;
	ev.data.ptr = ptr;

	ret = epoll_ctl(fdw->epoll_fd, EPOLL_CTL_ADD, fd, &ev);
	return ret;
}

int fdwatcher_remove(FdWatcher *fdw, int fd)
{
	int ret = -1;
	ret = epoll_ctl(fdw->epoll_fd, EPOLL_CTL_DEL, fd, NULL);
	return ret;
}

int
fdwatcher_wait(FdWatcher *fdw, void **events, int nevents, int timeout)
{
	int num_events = -1;

	struct epoll_event ep_events[nevents];

	num_events = epoll_wait(fdw->epoll_fd, ep_events, nevents, timeout);
	for (int i = 0; i < nevents; i++) {
		struct epoll_event ev = ep_events[i];
		events[i] = ev.data.ptr;
	}

	return num_events;
}

void fdwatcher_destroy(FdWatcher *fdw)
{
	if (fdw == NULL) {
		return;
	}

	assert(fdw->epoll_fd >= 0);
	close(fdw->epoll_fd);
	free(fdw);
}
