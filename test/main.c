#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <perf-utils/perf-utils.h>

int main(int argc, char** argv)  {


    struct perf_event_attr pe_cycles, pe_branch;
    long long count_cycles, count_branch;
    int fd_cycles, fd_branch;

    memset(&pe_cycles, 0, sizeof(pe_cycles));
    pe_cycles.type = PERF_TYPE_HARDWARE;
    pe_cycles.size = sizeof(pe_cycles);
    pe_cycles.config = PERF_COUNT_HW_INSTRUCTIONS;
    pe_cycles.disabled = 1;
    pe_cycles.exclude_kernel = 1;
    pe_cycles.exclude_hv = 1;
    pe_cycles.read_format = PERF_FORMAT_GROUP | PERF_FORMAT_ID;

    
    memset(&pe_branch, 0, sizeof(pe_branch));
    pe_branch.type = PERF_TYPE_HARDWARE;
    pe_branch.size = sizeof(pe_branch);
    pe_branch.config = PERF_COUNT_HW_BRANCH_MISSES;
    pe_branch.disabled = 1;
    pe_branch.exclude_kernel = 1;
    pe_branch.exclude_hv = 1;
    
    fd_cycles = perf_event_open(&pe_cycles, 0, -1, -1, 0);
    if (fd_cycles == -1) {
	fprintf(stderr, "Error opening leader %llx\n", pe_cycles.config);
	perror("Could not set up cycles event");

	exit(EXIT_FAILURE);
    }
    
    int group_fd = fd_cycles;

    int id_cycles = 0, id_branch = 0;

    ioctl(group_fd, PERF_EVENT_IOC_ID, &id_cycles);
    

    fd_branch = perf_event_open(&pe_branch, 0, -1, fd_cycles, 0);
    if (fd_cycles == -1) {
	fprintf(stderr, "Error opening leader %llx\n", pe_cycles.config);
	perror("Could not set up branch miss event");
	exit(EXIT_FAILURE);
    }
    
    ioctl(group_fd, PERF_EVENT_IOC_ID, &id_branch);

    char buf[4096];
    
    perf_event_reset(fd_cycles);
    perf_event_reset(fd_branch);
    
    perf_event_enable(fd_cycles);
    perf_event_enable(fd_branch);
        
    //perf_event_read(fd_branch); // Measures duration of perf_event_read
    read(group_fd, buf, sizeof(buf));

    perf_event_disable(fd_cycles);
    perf_event_disable(fd_branch);

    long long counts[2];

    struct read_format* fmt = buf;    
    int bytes_read = read(group_fd, buf, sizeof(buf));    

    for (uint64_t i = 0; i < fmt->nr; i++) {
	printf("Count = %ld\n", fmt->values[i].value);
    }
    
    printf("Bytes read = %d\n", bytes_read);
    //count_cycles = perf_event_read(fd_cycles);
    //count_branch = perf_event_read(fd_branch);
    count_cycles = counts[0];
    count_branch = counts[1];
    
    printf("Used %lld instructions\n", count_cycles);
    printf(" %lld branch misses\n", count_branch);

    perf_event_close(fd_cycles);
    perf_event_close(fd_branch);
    
    return 0;
}
