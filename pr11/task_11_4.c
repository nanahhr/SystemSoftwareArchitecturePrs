#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ucontext.h>

static int log_fd = -1;

static void crash_handler(int sig, siginfo_t *si, void *ctx)
{
    int target_fd = (log_fd >= 0) ? log_fd : STDERR_FILENO;

    dprintf(target_fd, "\n========================================\n");
    dprintf(target_fd, "CRITICAL ERROR: Process crashed with signal %d\n", sig);
    if (si)
    {
        dprintf(target_fd, "Fault address: %p\n", si->si_addr);
    }

    ucontext_t *uc = (ucontext_t *)ctx;
    if (uc)
    {
        dprintf(target_fd, "--- REGISTER DUMP ---\n");
#if defined(__x86_64__)
        greg_t *g = uc->uc_mcontext.gregs;
        dprintf(target_fd, "Platform: x86_64\n");
        dprintf(target_fd, "RIP: 0x%llx  RSP: 0x%llx\n", (unsigned long long)g[REG_RIP], (unsigned long long)g[REG_RSP]);
        dprintf(target_fd, "RAX: 0x%llx  RBX: 0x%llx\n", (unsigned long long)g[REG_RAX], (unsigned long long)g[REG_RBX]);
        dprintf(target_fd, "RCX: 0x%llx  RDX: 0x%llx\n", (unsigned long long)g[REG_RCX], (unsigned long long)g[REG_RDX]);
#elif defined(__aarch64__)
        dprintf(target_fd, "Platform: AArch64 (ARM64)\n");
        dprintf(target_fd, "PC:  0x%llx  SP:  0x%llx\n", (unsigned long long)uc->uc_mcontext.pc, (unsigned long long)uc->uc_mcontext.sp);
        dprintf(target_fd, "X0:  0x%llx  X1:  0x%llx\n", (unsigned long long)uc->uc_mcontext.regs[0], (unsigned long long)uc->uc_mcontext.regs[1]);
#else
        dprintf(target_fd, "Platform: Generic/Unsupported for direct register dump\n");
#endif
    }
    dprintf(target_fd, "========================================\n");

    if (log_fd >= 0)
        close(log_fd);
    signal(sig, SIG_DFL);
    raise(sig);
}

void init_crash_logger(const char *filename)
{
    if (filename)
    {
        log_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    }

    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_sigaction = crash_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO | SA_NODEFER;

    sigaction(SIGSEGV, &sa, NULL);
    sigaction(SIGFPE, &sa, NULL);
    sigaction(SIGILL, &sa, NULL);
    sigaction(SIGBUS, &sa, NULL);
    sigaction(SIGABRT, &sa, NULL);
}

int main(void)
{
    init_crash_logger("crash.log");
    printf("Crash logger initialized. Simulating a crash...\n");

    volatile int *invalid_ptr = NULL;
    *invalid_ptr = 100;

    return 0;
}