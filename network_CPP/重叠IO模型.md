# 重叠IO模型

## 上一个忘记关闭网络库了

## 重叠IO介绍

### 意义

- 重叠IO是windows提供的一种异步读写文件的机制

### 作用

- 正常读写文件（socket本质就是文件操作），如recv，是阻塞的，等协议缓冲区中的数据全部复制进咱们的buffer里，函数才结束并返回复制的个数，写也一样，同一时间只能读写一个，其他的全都靠边等
- 重叠IO机制读写，将读的指令以及咱们的buffer投给操作系统，然后函数直接返回，操作系统独立开个线程，将数据复制进咱们的buffer，数据复制期间，咱们就去做其他事儿，两不耽误，即读写过程变成了异步，可以同时投递多个读写操作
- 即：将accept recv  send优化成了异步过程，被AcceptEx WSARecv WSASend函数代替了

	- 所以说啊，这个是对基本c/s模型的直接优化

### 本质

- 结构体

	- WSAOVERLAPPED

		- struct _WSAOVERLAPPED {
  DWORD    Internal;
  DWORD    InternalHigh;
  DWORD    Offset;
  DWORD    OffsetHigh;
  WSAEVENT hEvent;
}

			- 前四个成员系统使用，咱们不需要直接使用
			- 成员1

				- 保留，供服务提供商定义使用

			- 成员2

				- 保留，供服务提供商定义使用

					- 接收或者发送的字节数

			- 成员3

				- 保留，供服务提供商定义使用

			- 成员4

				- 保留，供服务提供商定义使用

					- 一般是错误码

			- 成员5

				- 事件对象

					- 我们唯一关注的
					- 操作完成他就会被置成有信号

- 定义一个该结构体的变量与socket绑定

### 使用

- 异步选择模型把消息与socket绑一起，然后系统以消息机制处理反馈
- 事件选择模型把事件与socket绑一起，然后系统以事件机制处理反馈
- 重叠IO模型把重叠结构与socket绑一起，然后系统以重叠IO机制处理反馈

### 重叠IO反馈两种方式

- 事件通知
- 完成例程

	- 回调函数

## 重叠IO逻辑

### 事件通知

- 调用AcceptEx WSARecv WSASend投递
- 被完成的操作，事件信号置成有信号
- 调用WSAWaitForMultipleEvents获取事件信号

### 回调函数/完成例程

- 调用AcceptEx WSARecv WSASend投递
- 完成后自动调用回调函数

## 性能

### 网上有测试结果的

- 20000个客户端同时请求链接以及发送信息

	- 系统cpu使用率上升40%左右
	- 完成端口只2%左右

		- 极品

### 其他模型也能处理这么多

- 但是同步的原因，导致延迟太高

## 事件通知实现逻辑

### 创建事件数组，socket数组，重叠结构体数组

- 下标相同的绑定成一组

### 创建重叠IO模型使用的socket

- WSASocket

### 投递AcceptEx

- 立即完成

	- 对客户端套接字投递WSARecv

		- 立即完成

			- 处理信息
			- 对客户端套接字投递WSARecv

				- 重复上述

		- 延迟完成

			- 那就去循环等信号

	- 根据需求对客户端套接字投递WSASend

		- 立即完成

			- 处理信息
			- 根据需求对客户端套接字投递WSASend

				- 重复上述

		- 延迟完成

			- 那就去循环等信号

	- 对服务器套接字继续投递AcceptEx

		- 重复上述

- 延迟完成

	- 那就去循环等信号

### 循环等信号

- 等信号

	- WSAWaitForMultipleEvents

- 有信号

	- 获取重叠结构上的信息

		-  WSAGetOverlappedResult

	- 客户端退出

		- 删除服务器端的信息

	- 接收链接

		- 投递AcceptEx

			- 上边这个逻辑写好了，封装成函数，就非常清晰

	- 接收信息

		- 处理消息
		- 对客户端套接字投递WSARecv

	- 发送消息

		- 根据需求对客户端套接字投递WSASend

## 服务端

### 网络头文件 网络库 

- 最底层的网络函数，大家用QT MFC wpf，或者百度下载的很多其他的封装好的网络库，都是对咱们讲的这些最本质的网络函数的二次封装，咱们讲的是通用的，讲完这个大家也可以自己封装函数库给别人用了。
- #include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")

	- 函数库

		- winsock2.h

			- windows socket 第2版

				- 第一版是 winsock.h
				- 查看具体区别

			- 目前网络库有哪些版本？

				- 1.0
1.1
2.0
2.1
2.2

					- 演示MSDN

						- 查这个函数的详细信息

							- WSAStartup

			- 我们的开发环境支持哪个版本？

				- 打开头文件，看咱们当前编译器环境支持的最高版本

		- ws2_32.lib

			- windows socket 第2版  32位

				- 不管是64编译环境还是32编译环境，都是用这个，并没有ws2_64.dll

		- wsock32.lib

			- winsock.h 第一版网络库 对应的库文件

		- 这里不区分大小写

### 打开网络库

- int WSAStartup(
  WORD      wVersionRequired,
  LPWSADATA lpWSAData
);

	- 功能

		- 打开网络库/启动网络库，启动了这个库，这个库里的函数/功能才能使用
		- w windows
s  socket
a Asynchronous  异步
startup   启动

			- 同步与异步

				- 同步

					- 阻塞/卡死状态

				- 异步

					- 多个工作同时进行

	- 参数1

		- 我们要使用的库的版本
		- 类型是 WORD

			- 转定义：unsigned  short

		- WORD wVersionRequired = MAKEWORD(2,2);

			- MAKEWORD(主版本,副版本)， 1.0 2.2  
			- wVersionRequired

				- 数据高位/高地址是副版本
				- 数据低位/低地址是主版本
				- 用调试+计算器演示数据原理

		- 位运算，内存操作，小端存储

	- 参数2

		- LPWSADATA lpWSAData

			- 系统通过这个参数给我们一些配置信息

				- 注意

					- 当看到参数有 LP P前缀的时候，是说我们这里要传对应类型变量的地址，这是win32API 的规范 或者叫规则

			- 看下有哪些信息

				- struct WSAData {
  WORD           wVersion;
  WORD           wHighVersion;
  unsigned short iMaxSockets;
  unsigned short iMaxUdpDg;
  char           *lpVendorInfo;
  char           szDescription[WSADESCRIPTION_LEN + 1];
  char           szSystemStatus[WSASYS_STATUS_LEN + 1];
} 

					- wVersion

						- 我们要使用的版本

					- wHighVersion

						- 系统能提供给我们最高的版本

					- iMaxSockets

						- 返回可用的socket的数量，2版本之后就没用了

					- iMaxUdpDg

						- UDP数据报信息的大小，2版本之后就没用了  

					- lpVendorInfo

						- 供应商特定的信息，2版本之后就没用了  

					- szDescription
szSystemStatus

						- 当前库的描述信息，2.0是第二版的意思

			- 当输入的版本不存在

				- 输入1.3， 2.3

					- 有主版本，没有副版本

						- 得到该主版本的最大副版本 1.1 2.2并使用

				- 输入3.1  3.3

					- 超过最大版本号

						- 使用系统能提供的最大的版本 2.2

				- 输入 0.0 0.1 0.3

					- 主版本是0

						- 网络库打开失败，不支持请求的套接字版本

	- 返回值

		- 返回0为执行正确
		- 失败

			- 这些宏的本质
			- WSASYSNOTREADY   10091       底层网络子系统尚未准备好进行网络通信。                                                  系统配置问题，重启下电脑，检查ws2_32库是否存在，或者是否在环境配置目录下
WSAVERNOTSUPPORTED 10092 此特定Windows套接字实现不提供所请求的Windows套接字支持的版本。      要使用的版本不支持
WSAEPROCLIM        10067         已达到对Windows套接字实现支持的任务数量的限制。                                 Windows Sockets实现可能限制同时使用它的应用程序的数量
WSAEINPROGRESS 10036          正在阻止Windows Sockets 1.1操作。                                                          当前函数运行期间，由于某些原因造成阻塞，会返回在这个错误码，其他操作均禁止
WSAEFAULT            10014          lpWSAData参数不是有效指针。                                                                 参数写错了

### 校验版本

- 2 != HIBYTE(wsaData.wVersion) || 2 != LOBYTE(wsaData.wVersion)

	- HIBYTE是高位 副版本
	- LOBYTE是地位 主版本
	- 逻辑

		- 只要有一个不是2，说明系统不支持我们要的2.2版本

- 关闭库
并结束函数，可以给出相应提示

	- WSACleanup();
	- return 0；

### 创建SOCKET

- SOCKET WSAAPI WSASocket(
  int                 af,
  int                 type,
  int                 protocol,
  LPWSAPROTOCOL_INFOA lpProtocolInfo,
  GROUP               g,
  DWORD               dwFlags
);

	- 作用

		- 创建一个用于异步操作的SOCKET
		- WSASocket  windows专用

			- WSA的函数都是windows专用的
			- windows socket async

				- 都是用于支持异步操作的函数

	- 参数1

		- 地址的类型

			- AF_INET

	- 参数2

		- 套接字类型

			- SOCK_STREAM 

	- 参数3

		- 协议的类型

			- IPPROTO_TCP

	- 参数4

		- 设置套接字详细的属性

			- 指向WSAPROTOCOL_INFO结构的指针
			- 比如

				- 发送数据是否需要链接
				- 是否保证数据完整到达
				- 参数3填0，那么匹配哪个协议
				- 设置传输接收字节数
				- 设置套接字权限
				- 还有很多保留字段，供以后拓展使用

			- 大家知道有这个操作，以后需要了，就使用下

		- 不使用

			- NULL

	- 参数5

		- 一组socket的组ID，大概是想一次操作多个socket
		- 保留

			- 暂时无用

				- 填0

	- 参数6

		- 指定套接字属性
		- 填写

			- WSA_FLAG_OVERLAPPED

				- 创建一个供重叠IO模型使用的socket

		- 其他的

			- WSA_FLAG_MULTIPOINT_C_ROOT
WSA_FLAG_MULTIPOINT_C_LEAF
WSA_FLAG_MULTIPOINT_D_ROOT
WSA_FLAG_MULTIPOINT_D_LEAF

				- 用于多播协议

			- WSA_FLAG_ACCESS_SYSTEM_SECURITY

				- 套接字操作权限

					- 配合参数4

				- 意义

					- 可以对套接字send设置权限，那么在send的时候，就会触发相关的权限设置，提醒

			- WSA_FLAG_NO_HANDLE_INHERIT

				- 套接字不可被继承
				- 在多线程开发中，子线程会继承父线程的socket，即主线程创建了一个socket，那么子线程有两种使用方式：

					- 第一：直接用父类的，父子都使用这一个socket

						- 共享

					- 第二：把父类的这个socket复制一份，自己用，这两父子用两个socket，但是本质一样

						- 继承

	- 返回值

		- 成功返回可用的socket

			- 不用了就一定要销毁套接字

				- closesocket(socketListen);

		- 失败返回INVALID_SOCKET

			- 关闭网络库

				- WSACleanup();

			- 可用WSAGetLasterror()返回错误码

### 绑定地址与端口

- int bind(
  SOCKET              s,
  const sockaddr *addr,
  int                 namelen
);

	- 作用

		- 给我们的socket绑定端口号与具体地址

			- 地址

				- 找到咱们的电脑

					- 只有一个

			- 端口号

				- 找到我们机器上对应的软件，比如QQ，浏览器等等，都对应着自己的端口号

					- 多个

				- 每一种通信的端口号是唯一的
				- 同一个软件可能占用多个端口号

	- 参数1

		- 上一个函数创建了socket，绑定了协议信息（地址类型，套接字类型，协议类型），咱们bind函数就是绑定实质的地址，端口号

	- 参数2

		- 结构体

			- 地址类型
			- 装IP地址
			- 端口号

		- 结构体类型

			- sockaddr
			- 该参数使用方法

				- SOCKADDR_IN sockAddress;
sockAddress.sin_family = AF_INET;
sockAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
sockAddress.sin_port = 12345;
(sockaddr*)&sockAddress强转添加到参数2上

					- 成员1

						- 跟socket函数参数1是一样的

					- 成员2

						- IP地址

							- 192.168.xxx.xxx

								- 可以在控制台输入指令  ipconfig 就能看到了
								- 或者在网络设置中，能找到这个地址
								- 我就不演示了，我不想让你们发现我

							- 127.0.0.1

								- 回送地址  本地回环地址  本地网络测试

					- 参数3

						- 端口号

							- 本质

								- 就是一个整数

									- 0~65535

								- IP是我们机器的地址，端口就是我们具体的软件的通信口，一个软件可能会占用多个接口，比如一个软件可以聊天，可以下载，可以看视频..那么这些不同的通信内容，往往会有各自的协议，各自的端口。

									- IP是公司地址，端口就是各个部门的地址了

							- 填写哪个值呢？

								- 理论上只要这个范围0~65535都可以

									- 实际

										- 介于0～1023，为系统保留占用端口号

											- 21端口分配给FTP(文件传输协议)服务
25端口分配给SMTP（简单邮件传输协议）服务
80端口分配给HTTP服务

									- 所以

										- 我们不能写这个范围的

											- 我们的范围就是1024~65535

												- 稍微大点儿，1万多

											- 但是注意一点，端口号是唯一的，比如1234已经被别的软件占用了，那么你再使用1234这个端口号，那么就会绑定失败，因为已经呗占用了

												- 给大家演示下

											- 那大家如何查看自己要用的端口号有没有被占用呢？

												- 打开运行cmd输入netstat -ano

													- 查看被使用的所有端口

												- netstat -aon|findstr "12345"

													- 检查我们要使用的端口号是否被使用了
													- 使用了就会显示使用的程序，未被使用就啥都不显示

	- 参数3

		- 参数2的类型大小

			- sizeof(参数2)

	- 返回值

		- 成功返回0
		- 失败返回SOCKET_ERROR

			- 具体错误码通过int WSAGetLastError(void);获得 
			- closesocket(socketListen);
WSACleanup();

### 开始监听

- int WSAAPI listen(
  SOCKET s,
  int    backlog
);

	- 作用

		- 将套接字置于正在侦听传入连接的状态。

	- 参数1

		- 服务器端的socket，也就是socket函数创建的

	- 参数2

		- 挂起连接队列的最大长度。

			- 就是说，比如有100个用户链接请求，但是系统一次只能处理20个，那么剩下的80个不能不理人家，所以系统就创建个队列记录这些暂时不能处理，一会儿处理的链接请求，依先后顺序处理，那这个队列到底多大？就是这个参数设置，比如2，那么就允许两个新链接排队的。这个肯定不能无限大，那内存不够了。
			- 我们可以手动设置这个参数，但是别大了。可能2~10多，~20多。
			- 我们一般填写这个参数

				- SOMAXCONN

					- 作用是让系统自动选择最合适的个数
					- 不同的系统环境不一样，所以这个合适的数也都不一样

	- WSAAPI

		- 调用约定

			- 这个我们可以忽略，这是给系统看的，跟咱们没关
			- 决定三

				- 函数名字的编译方式
				- 参数的入栈顺序
				- 函数的调用时间

	- 返回值

		- 成功

			- 返回0

		- 失败

			- SOCKET_ERROR
			- 具体错误码

				-  WSAGetLastError()
				- 释放

					- closesocket(socketListen);
					- WSACleanup();

### 重叠IO开始了

- 投递异步接收链接请求

	- BOOL AcceptEx(
  SOCKET       sListenSocket,
  SOCKET       sAcceptSocket,
  PVOID        lpOutputBuffer,
  DWORD        dwReceiveDataLength,
  DWORD        dwLocalAddressLength,
  DWORD        dwRemoteAddressLength,
  LPDWORD      lpdwBytesReceived,
  LPOVERLAPPED lpOverlapped
);

		- 功能

			- 投递服务器socket，异步接收链接

		- 参数1

			- 服务器socket

		- 参数2

			- 链接服务器的客户端的socket

				- 注意：我们要调用WSASocket亲自创建
				- AcceptEx将客户端的IP端口号绑在这个socket上

		- 参数3

			- 缓冲区的指针，接收在新连接上发送的第一个数据

				- 客户端第一次send，由这个函数接收
				- 第二次以后就由WSARecv接收

			- char str[1024]
			- 不能设置NULL

		- 参数4

			- 设置0

				- 取消了3的功能

			- 设置成3的1024

				- 那么就会接收第一次的数据
				- 此时，客户端链接并发送了一条消息，服务器才产生信号

					- 所以会有阻塞状况，光链接不行，必须等客户端发来一条消息，他才完事儿，有信号
					- 咱们设置0就行了

		- 参数5

			- 为本地地址信息保留的字节数。此值必须至少比使用的传输协议的最大地址长度长16个字节
			- sizeof(struct sockaddr_in) + 16

		- 参数6

			- 为远程地址信息保留的字节数。此值必须至少比使用的传输协议的最大地址长度长16个字节。不能为零。
			- sizeof(struct sockaddr_in) + 16

		- 参数7

			- 该函数可以接收第一次客户端发来的信息，如果这个信息刚好是调用时候接收到了，也即立即接收到了（客户端链接的同时发送了信息），这时候装着接收到的字节数

				- 也就是这个接收是同步完成的时候，这个参数会被装上
				- 没有立即处理，也即异步接收到消息，这时候这个参数没用

			- 大家可以填写

				- 填写NULL

					- 不想获得这个字节数

				- 也可以填写DWORD变量的地址

					- 填这个就行

		- 参数8

			- 我们的重叠结构

		- 返回值

			- TRUE

				- 立即完成返回

					- 刚执行就已经有客户端到了

			- FALSE

				- 出错

					- int a = WSAGetLastError()
					- 如果a == ERROR_IO_PENDING

						- 异步等待
						- 客户端还没来

					- 其他，根据错误码解决

- 循环

	- 等信号

		- WSAWaitForMultipleEvents

			- 上限64个事件

				- WSAWaitForMultipleEvents(1, &g_allOverLap[i].hEvent, FALSE, 0, FALSE);

					- 参数6：IO完成例程有作用，咱们讲完事件讲IO例程

			- 采用循环一个一个等，会比较方便

				- if (WSA_WAIT_FAILED == dwIndex || WSA_WAIT_TIMEOUT == dwIndex)

	- 等到了

		- 获取

			- BOOL WSAAPI WSAGetOverlappedResult(
  SOCKET          s,
  LPWSAOVERLAPPED lpOverlapped,
  LPDWORD         lpcbTransfer,
  BOOL            fWait,
  LPDWORD         lpdwFlags
);

				- 功能

					- 获取对应socket上的具体情况

				- 参数1

					- 有信号的socket

				- 参数2

					- 对应的重叠结构

				- 参数3

					- 由发送或者接收到的实际字节数
					- 0

						- 表是客户端优雅的下线

				- 参数4

					- 仅当重叠操作选择了基于事件的完成通知时，才能将fWait参数设置为TRUE。
					- 选择事件通知，填TRUE

				- 参数5

					- 1、装WSARecv的参数5 lpflags
					- 2、不能是NULL

				- 返回值

					- true执行成功
					- false执行失败

						- WSAGetLastError() == 10054

							- 客户端强制退出

	- 分类处理

		- 如果客户端退出了

			- 删掉对应事件，socket，重叠IO

				- 一删删一组

		- 如果是客户端链接

			- 接收socket，并创建新的重叠结构，事件
			- 三者绑定到一起投递

				- WSARecv

					- int WSAAPI WSARecv(
  SOCKET                                 s,
  LPWSABUF                           lpBuffers,
  DWORD                                 dwBufferCount,
  LPDWORD                            lpNumberOfBytesRecvd,
  LPDWORD                            lpFlags,
  LPWSAOVERLAPPED         lpOverlapped,
  LPWSAOVERLAPPED_COMPLETION_ROUTINE 
                                                  lpCompletionRoutine
);

						- 作用

							- 投递异步接收信息

						- 参数1

							- 客户端socket

						- 参数2

							- 接收后的信息存储buffer

								- WSABUF   

									- struct _WSABUF {
  ULONG len;
  CHAR  *buf;
}

										- 成员1

											- 字节数

										- 成员2

											- 指向字符数组的指针

						- 参数3

							- 参数2是个WSABUF 的的个数

								- 1个

						- 参数4

							- 接收成功的话，这里装着成功接收到的字节数
							- 参数6重叠结构不为NULL的时候，此参数可以设置成NULL

						- 参数5

							- 指向用于修改WSARecv函数调用行为的标志的指针
							- MSG_PEEK

								- 协议缓冲区信息复制出来，不删除，跟recv参数5一样

							- MSG_OOB

								- 带外数据

							- MSG_PUSH_IMMEDIATE

								- 通知传送尽快完成

									- 比如传输10M数据，一次只能传1M，这个包要拆成10分发送，第一份发送中，后面9分要排队等着，指定了这个标记，那么指示了快点儿，别等了，那么没被发送的就被舍弃了，从而造成了数据发送缺失
									- 该参数不建议用于多数据的发送

										- 聊天的那种没问题，发个文件什么的，就不建议了

									- 提示系统尽快处理，所以能减少一定的延迟

							- MSG_WAITALL

								- 呼叫者提供的缓冲区已满。
连接已关闭。
请求已取消或发生错误。

									- 才把数据发送出去

							- MSG_PARTIAL

								- 传出的

									- 表示咱们此次接收到的数据是客户端发来的一部分，接下来接收下一部分

						- 参数6

							- 重叠结构

						- 参数7

							- 回调函数

								- 完成例程形式使用

									- 事件形式可以不使用
									- 设置NULL

						- 返回值

							- 立即发生

								- 0

									- 计算机比较闲，立刻就发出去了

							- SOCKET_ERROR

								- int a = WSAGetLastError()

									-  a == WSA_IO_PENDING
									- 表示

										- 你自己去干吧

				- 可在正确逻辑的任何位置投递WSASend

					- int WSAAPI WSASend(
  SOCKET                             s,
  LPWSABUF                           lpBuffers,
  DWORD                              dwBufferCount,
  LPDWORD                            lpNumberOfBytesSent,
  DWORD                              dwFlags,
  LPWSAOVERLAPPED                    lpOverlapped,
  LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
);

						- 作用

							- 投递异步发送消息

						- 参数1

							- 客户端socket

						- 参数2

							- 接收后的信息存储buffer

								- WSABUF   

									- struct _WSABUF {
  ULONG len;
  CHAR  *buf;
}

										- 成员1

											- 字节数

										- 成员2

											- 指向字符数组的指针

						- 参数3

							- 参数2是个WSABUF 的的个数

								- 1个

						- 参数4

							- 接收成功的话，这里装着成发送的字节数
							- 参数6重叠结构不为NULL的时候，此参数可以设置成NULL

						- 参数5

							- 函数调用行为的标志的

						- 参数6

							- 重叠结构

						- 参数7

							- 回调函数

								- 完成例程形式使用

									- 事件形式不使用
									- 设置NULL

						- 返回值

							- 立即发生

								- 0

									- 计算机比较闲，立刻就发出去了

							- SOCKET_ERROR

								- int a = WSAGetLastError()

									-  a == WSA_IO_PENDING
									- 表示

										- 你自己去干吧

			- 再次对服务器socket投递

				- AcceptEx

		- 如果是客户端发来了信息

			- 直接得到信息
			- 再次将该客户端socket投递出去

				- WSARecv

		- 注意：

			- 此三函数每完成一次就要重新投递一次
			- 意义与accpet recv send一样

				- 调用一次就发一次

	- 问题总结

		- 1、accept

			- 参数有误
			- 位置有误

		- 2、recv

			- 参数有误

		- 3、close

			- 检测有误

				- 强制退出用错误码10054检测
				- 优雅退出用参数3==0检测

		- 4、信号置空

			- //信号置空
			WSAResetEvent(g_allOlp[i].hEvent);

### 释放

- 也是控制台事件

	- 释放事件
	- 释放socket

### 优化

- 将上万的事件分组分线程等待处理

### 问题

- 在一次处理过程中，客户端产生多次send，服务器会产生多次接收消息，第一次接收消息会收完所有信息

### 对比基本c/s的结构吐

*XMind - Trial Version*