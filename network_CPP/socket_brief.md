## [socket开发总结](https://www.cnblogs.com/ne-liqian/p/10006439.html)

**1.connect**

　　阻塞socket connect时会等待返回结果，等于0表示成功，小于0表示失败。

　　非阻塞socket connect时会立刻返回结果，等于0表示成功，小于0且errno == EINPROGRESS时表示连接正在进行，此时应该等待该socket触发写信号，触发时获取该socket的SO_ERROR选项，根据此值来判断socket是否connect成功。

**2.send**

　　[1]返回值等于发送长度，则表示成功。

　　[2]返回值小于发送长度，但是大于0，则表示发送缓冲区已满，等待继续发送剩下的数据。

　　[3]返回值小于0，如果(errno == EINTR || errno == EAGAIN || errno == EWOULDBLOCK || errno == 0)这些情况时，表示需要再次尝试发送。

　　[4]返回值等于0，表示传入的长度参数就是0或者缓冲区已满，应该尝试继续发送。

 

　　阻塞和非阻塞的处理方式是一样的，只有返回值小于0时，才能判断errno的值，否则errno的值是无效的。

　　如果send时，当前socket已经断开(对方已经关闭)，此时底层会抛出一个SIGPIPE信号，这个信号的缺省处理方法是退出进程，所以需要设置忽略此信号。

**3.recv**

　　[1]返回值大于0表示接收成功。

　　[2]返回值小于0时，如果(errno == EINTR || errno == EAGAIN || errno == EWOULDBLOCK || errno == 0)这些情况时，表示需要再次尝试接收。

　　[3]返回值等于0时，表示连接断开，需要关闭socket。

 

　　阻塞和非阻塞的处理方式是一样的，只有返回值小于0时，才能判断errno的值，否则errno的值是无效的。

**4.accept**

　　accept之后会返回一个新的socket，注意要看情况给这个socket设置相关的选项。

**5.select、epoll**

　　[1]select(maxfd + 1, &rfd, &wfd, NULL, &timeout);

　　  最后一个参数是超时时间，如果传0(struct timeval timeout = {0,0})表示只遍历一遍就返回。如果传NULL，表示直到遍历到有事件才返回。如果传大于0的值，则表示超时时间。

　　[2]epoll_wait(fd, events_ready, max_fd, -1);

　　  LT模式：socket有事件时通知应用程序，例如有读事件时：此时可以read缓冲区的部分或者全部数据(直到返回-1，errno为EAGAIN)，也可以不做任何处理，因为下次epoll_wait时，如果缓冲区有数据还会再次触发信号。

　　  ET模式：socket有事件时通知应用程序，但是只会通知一次，直到应用程序做了操作导致下次状态改变时才会再次触发，例如有读事件时：必须把缓冲区数据读完。这个模式只支持非阻塞socket。

　　  缺省是LT模式，如果要使用ET模式，则添加事件时加上EPOLLET标记：event.events = EPOLLIN | EPOLLOUT | EPOLLET;

　　注意select和epoll的最后一个值是超时时间，如果这个函数后面还有其他流程处理(例如检查状态等)，则一定要设置一个固定的超时时间或者填0。

**6.socket相关操作**

[![复制代码](https://common.cnblogs.com/images/copycode.gif)](javascript:void(0);)

```c++
/*设置文件打开数*/
struct rlimit l;
l.rlim_cur = 90000;
l.rlim_max = 90000;
setrlimit(RLIMIT_NOFILE, &l);

/*忽略SIGPIPE信号，否则对端关闭socket时，本端调用send()函数会导致进程退出*/
signal(SIGPIPE, SIG_IGN);

/*connect触发写信号时，通过判断该值判断连接是否成功。*/
int cc, optlen = sizeof(cc);
getsockopt(fd, SOL_SOCKET, SO_ERROR, (void *)&cc, (void *)&optlen);

/*设置socket的发送、接收缓冲区*/
int size = 8 * 1024 *1024;
setsockopt(sk, SOL_SOCKET, SO_SNDBUF, (void *)&size, sizeof(size));
setsockopt(sk, SOL_SOCKET, SO_RCVBUF, (void *)&size, sizeof(size));

/*阻塞socket设置收发超时时间*/
struct timeval tv = {2,0};
setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(struct timeval));
setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(struct timeval));

/*获取tcp socket的目的地址*/
struct sockaddr_in server_addr;
getsockname(fd, (struct sockaddr *)&server_addr, &addrlen);
```