#ifndef PERFUTILS_PERFUTILS_H
#define PERFUTILS_PERFUTILS_H

#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/perf_event.h>
#include <sys/syscall.h>
#include <sys/types.h>


// Source: From perf_event_open manpage
static long
perf_event_open(struct perf_event_attr *hw_event, pid_t pid,
                int cpu, int group_fd, unsigned long flags)
{
    int ret;

    ret = syscall(__NR_perf_event_open, hw_event, pid, cpu,
                   group_fd, flags);
    return ret;
}


static long
perf_event_enable(int fd) {
ioctl(fd, PERF_EVENT_IOC_ENABLE, 0);    
}

static long
perf_event_disable(int fd) {
    ioctl(fd, PERF_EVENT_IOC_DISABLE, 0);
}

static long 
perf_event_reset(int fd) {
    ioctl(fd, PERF_EVENT_IOC_RESET, 0);
}

static long long
perf_event_read(int fd) {
    long long count = 0;
    read(fd, &count, sizeof(long long));
    return count;
}

static long
perf_event_close(int fd) {
    close(fd);
}





#endif // PERFUTILS_PERFUTILS_H
