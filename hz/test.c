#include <sys/time.h>

unsigned long int i_time_ms() {
  static struct timeval last = {0, 0};
  struct timeval current;
  static unsigned long int last_ms = 0;

  gettimeofday(&current, NULL);
  printf ("L Sec: %lu \t Usec: %lu\n", last.tv_sec, last.tv_usec);
  printf ("C Sec: %lu \t Usec: %lu\n", current.tv_sec, current.tv_usec);
  if (last.tv_sec != 0)
  {
    last_ms += (current.tv_sec - last.tv_sec) * 1000 +
      (current.tv_usec - last.tv_usec) / 1000;
  }
  last.tv_sec = current.tv_sec;
  last.tv_usec = current.tv_usec;
  return last_ms;
}

int main ()
{
  int x = 1000;

  while (x)
  {
    printf ("Time: %lu\n", i_time_ms());
    x--;
  }
}
