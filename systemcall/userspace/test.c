#include <stdio.h>
      #include <stdlib.h>
      #include <errno.h>
      #include <linux/unistd.h>       /* for _syscallX macros/related stuff */
      #include <linux/kernel.h>       /* for struct sysinfo */

_syscall1(int, struct sysinfo, struct sysinfo *,struct info);

      int
      main(void)
      {
          struct sysinfo s_info;
          int error;

          error = sysinfo(&s_info);
          printf("code error = %d\n", error);
          printf("Uptime = %lds\nLoad: 1 min %lu / 5 min %lu / 15 min %lu\n"
                 "RAM: total %lu / free %lu / shared %lu\n"
                 "Memory in buffers = %lu\nSwap: total %lu / free %lu\n"
                 "Number of processes = %d\n",
                 s_info.uptime, s_info.loads[0],
                 s_info.loads[1], s_info.loads[2],
                 s_info.totalram, s_info.freeram,
                 s_info.sharedram, s_info.bufferram,
                 s_info.totalswap, s_info.freeswap,
                 s_info.procs);
          exit(EXIT_SUCCESS);
      }
