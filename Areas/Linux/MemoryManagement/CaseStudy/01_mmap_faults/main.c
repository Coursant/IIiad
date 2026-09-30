// Case: 01_mmap_faults
// Topic: 观察匿名私有映射的按需分配与 minor faults
// RUN: ./run.sh
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/resource.h>
#include <unistd.h>

static long minor_faults(void) {
    struct rusage usage;
    if (getrusage(RUSAGE_SELF, &usage) != 0) {
        perror("getrusage");
        exit(EXIT_FAILURE);
    }
    return usage.ru_minflt;
}

int main(void) {
    const long page_size = sysconf(_SC_PAGESIZE);
    if (page_size <= 0) {
        perror("sysconf");
        return EXIT_FAILURE;
    }

    const size_t length = 16u * 1024u * 1024u;
    const long before = minor_faults();
    unsigned char *region = mmap(NULL, length, PROT_READ | PROT_WRITE,
                                 MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (region == MAP_FAILED) {
        perror("mmap");
        return EXIT_FAILURE;
    }
    const long after_map = minor_faults();

    for (size_t offset = 0; offset < length; offset += (size_t)page_size) {
        region[offset] = 1;
    }
    const long after_touch = minor_faults();

    printf("page size: %ld bytes\n", page_size);
    printf("mapping: %zu bytes\n", length);
    printf("minor faults before mmap: %ld\n", before);
    printf("minor faults after mmap:  %ld (delta %+ld)\n",
           after_map, after_map - before);
    printf("minor faults after write: %ld (delta %+ld)\n",
           after_touch, after_touch - after_map);

    if (munmap(region, length) != 0) {
        perror("munmap");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
