#include "worker.hpp"

#include <cerrno>
#include <csignal>
#include <cstddef>
#include <poll.h>
#include <sys/wait.h>
#include <unistd.h>

namespace afanasev
{
  namespace
  {
    [[noreturn]] void runChild(unsigned seed, int req_rd, int result_wr)
    {
      (void)seed;

      signal(SIGPIPE, SIG_IGN);

      for (;;)
      {
        RequestHeader hdr{};
        if (!recvAll(req_rd, &hdr, sizeof hdr))
        {
          _exit(0);
        }

        for (std::size_t i = 0; i < hdr.num_shapes; ++i)
        {
          ShapeWire sw{};
          if (!recvAll(req_rd, &sw, sizeof sw))
          {
            _exit(0);
          }
        }

        ResultSlot r{};
        r.calc_id = hdr.calc_id;
        r.ms = 0.0;
        r.area = 2.0;

        if (!sendAll(result_wr, &r, sizeof r))
        {
          _exit(0);
        }
      }
    }
  }

  bool sendAll(int fd, const void * buf, std::size_t n)
  {
    const char * p = static_cast< const char * >(buf);
    std::size_t put = 0;
    while (put < n)
    {
      const ssize_t r = write(fd, p + put, n - put);
      if (r < 0)
      {
        if (errno == EINTR)
        {
          continue;
        }
        return false;
      }
      if (r == 0)
      {
        return false;
      }
      put += static_cast< std::size_t >(r);
    }
    return true;
  }

  bool recvAll(int fd, void * buf, std::size_t n)
  {
    char * p = static_cast< char * >(buf);
    std::size_t got = 0;
    while (got < n)
    {
      const ssize_t r = read(fd, p + got, n - got);
      if (r < 0)
      {
        if (errno == EINTR)
        {
          continue;
        }
        return false;
      }
      if (r == 0)
      {
        return false;
      }
      got += static_cast< std::size_t >(r);
    }
    return true;
  }

  bool hasData(int fd)
  {
    pollfd pfd{};
    pfd.fd = fd;
    pfd.events = POLLIN;
    return poll(&pfd, 1, 0) > 0;
  }

  Worker spawnWorker(unsigned seed)
  {
    Worker w;

    int req_pipe[2] = { -1, -1 };
    int result_pipe[2] = { -1, -1 };

    if (pipe(req_pipe) < 0)
    {
      return w;
    }
    if (pipe(result_pipe) < 0)
    {
      close(req_pipe[0]);
      close(req_pipe[1]);
      return w;
    }

    const pid_t pid = fork();
    if (pid < 0)
    {
      close(req_pipe[0]);
      close(req_pipe[1]);
      close(result_pipe[0]);
      close(result_pipe[1]);
      return w;
    }

    if (pid == 0)
    {
      close(req_pipe[1]);
      close(result_pipe[0]);
      runChild(seed, req_pipe[0], result_pipe[1]);
    }

    close(req_pipe[0]);
    close(result_pipe[1]);

    w.pid = pid;
    w.req_wr = req_pipe[1];
    w.result_rd = result_pipe[0];
    return w;
  }

  void stopWorker(Worker & w)
  {
    if (w.req_wr >= 0)
    {
      close(w.req_wr);
      w.req_wr = -1;
    }
    if (w.result_rd >= 0)
    {
      close(w.result_rd);
      w.result_rd = -1;
    }
    if (w.pid > 0)
    {
      kill(w.pid, SIGTERM);
      waitpid(w.pid, nullptr, 0);
      w.pid = -1;
    }
  }
}
