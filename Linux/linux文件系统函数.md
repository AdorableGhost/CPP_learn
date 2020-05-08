

<div style="font-family:'宋体';font-size:14px;line-height:21px;text-align:center;">
<span style="font-family:'Times New Roman';"><span style="font-size:14px;">&nbsp;</span><span style="font-weight:bold;"><span><span style="font-size:22px;">深入理解Linux文件系统编程(一)</span></span><span style="text-align:left;line-height:1.5;"><span><span style="font-size:22px;">&nbsp;</span></span><span style="font-size:14px;">&nbsp;&nbsp;</span></span></span></span></div>
<div style="font-family:'宋体';font-size:14px;line-height:21px;text-align:center;">
<span style="color:rgb(51,51,51);font-size:12px;"><span><a href="http://my.csdn.net/u012637501" rel="nofollow" style="color:rgb(51,51,51);"><span style="font-family:'Times New Roman';"></span></a></span></span></div>


<div style="font-family:'宋体';font-size:14px;line-height:21px;text-align:center;">
<span style="font-family:'Times New Roman';"><span style="font-size:14px;text-align:left;line-height:1.5;"></span></span></div>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:'Times New Roman';font-size:14px;">&nbsp; &nbsp;文件系统是linux操作系统组织系统资源的一种方式，操作系统的可用性取决于对文件系统的支持，操作系统就是通过文件系统接口提供各种功能。<span style="color:#7030a0;">对于Linux操作系统来说，文件是对系统资源的一个抽象，是对系统资源进行访问的一个通用接口</span>，诸如内存、硬盘、一般设备以及进程间通信的通道等资源都被表示为文件。对这些资源的操作，就相当于对一个文件进行相关的操作。</span></div>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-size:22px;"><span style="font-family:'Times New Roman';"><strong>一、基本概念</strong></span></span></div>

<span style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:'Times New Roman';font-size:14px;color:#ff0000;">1.系统调用(I/O函数库)</span></span>

<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:'Times New Roman';"><span style="font-size:14px;"><span style="color:#ff0000;"><span style="line-height:27px;"><span>&nbsp;
 &nbsp;&nbsp;</span></span></span></span><span style="line-height:1.5;"><span style="font-size:14px;">系统编程是指直</span></span><span style="font-size:14px;line-height:1.5;">接利用</span><span style="color:#7030a0;font-size:14px;line-height:1.5;">系统的底层接口</span><span style="font-size:14px;line-height:1.5;">进行编程。</span><span style="color:#7030a0;font-size:14px;line-height:1.5;">操作系统通过给用户提供一组特殊"接口"，以</span><span style="color:#7030a0;font-size:14px;line-height:1.5;">便用户程序可以通过这组特殊接口来获取操作系统的<span>内核提供的服务</span></span><span style="font-size:14px;line-height:1.5;">，包括进程控制(进程间通信)、文件系统控制、系统控制、存储管理、网络管理、socket管理、用户管理等，这种调用接口的方法也称之为</span><span style="color:#7030a0;font-size:14px;line-height:1.5;"><span style="line-height:1.5;">"<span>系统调用</span>"</span><span style="line-height:1.5;">。</span><span style="line-height:1.5;"><span>"系统调用接口"</span></span></span><span style="font-size:14px;line-height:1.5;">，即</span><span style="font-size:14px;line-height:24px;">一般通过CPU的软中断指令<span style="color:#7030a0;">实现从用户态到内核态的调用</span>,这是一种由应用程序主动发起的模式切换，让软中断处理完毕返回后重新切换到用户态，实现系统调用的返回。</span></span></div>
<span style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:'Times New Roman';font-size:14px;color:#ff0000;">2.标准I/O函数库</span></span>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:'Times New Roman';font-size:14px;"><span style="line-height:24px;">&nbsp; &nbsp; C标准库提供了文件的标准I/O库，与系统调用的区别在于实现了一个<span style="color:#7030a0;">垮平台的用户态缓冲</span>的解决方案。标准I/O库使用简单，与<span style="color:#7030a0;">系统调用I/O</span>相似，也包括打开、读写、关闭这些操作。</span></span></div>
<span style="font-family:'Times New Roman';font-size:14px;line-height:21px;"><span><span style="font-size:14px;color:#ff0000;">3</span><span style="font-size:14px;color:#ff0000;">.API-用户编程</span><span style="font-size:14px;color:#ff0000;">接口</span></span></span>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="line-height:24px;"><span style="font-family:'Times New Roman';font-size:14px;">&nbsp; &nbsp; 是一些预先定义的函数(即C标准库提供的编程接口)，目的是为开发人员提供编写应用程序的接口，从而使我们开发的应用程序<span style="color:#7030a0;">无需访问源码</span>。注意：<span style="color:#7030a0;">API和系统调用并不是一一对应的关系</span>，因为C标准库提供的有些接口根本<span style="color:#7030a0;">不需要请求内核服务</span>就可以完成，比如内存的复制、数学上的计算；或者有些API可能需要经过多次的系统调用才能完成其功能。</span></span></div>
<div style="font-family:'宋体';font-size:14px;line-height:21px;">
<hr><span><span style="font-family:'Times New Roman';color:#7030a0;">博主笔记1：<span style="line-height:1.5;">系统I/O函数和标准I/O函数的区别？</span></span></span></div>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:'Times New Roman';color:#7030a0;"><span style="line-height:1.5;">&nbsp; &nbsp; I/O操作-对文件进行输入/输出操作。虽然系统调用和标准I/O函数库均能实现对文件操作，但是两者性质是不同的：
 &nbsp;</span><span style="line-height:1.5;">&nbsp; &nbsp; &nbsp;</span></span></div>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:'Times New Roman';"><span style="color:#7030a0;">(1)系统调用是直接利用底层接口获取内核提供的服务，实现直接对文件的操作；而标准I/O函数库实际上是对底层系统调用的包装，其对设备或文件的操作先是经过一个</span><span style="color:#00b050;"><span>缓存区</span></span><span style="color:#7030a0;">然后再调用系统I/O函数来操作文件(有些API接口甚至不需要实现系统调用)。</span></span></div>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:'Times New Roman';"><span style="color:#7030a0;">(2)系统调用通过</span><span style="color:#00b050;"><span>文件描述符</span></span><span style="color:rgb(112,48,160);">对文件进行操作</span><span style="color:#7030a0;">；标志I/O库则通过</span><span style="color:#00b050;"><span>文件指针</span></span><span style="color:#7030a0;">对文件进行操作</span><br><span style="color:#7030a0;">(3)系统进行I/O操作时：系统调用要请求内核的服务，会引发CPu模式的切换，期间会有大量的堆栈数据保存操作导致系统开销较大，如果频繁的进行系统调用会</span><span style="color:#00b050;"><span>降低应用程序的运行效率</span></span><span style="color:#7030a0;">；标准I/O函数库通过引入缓冲机制，多个读写操作可以合并为依次系统调用，通过减少系统调用的次数，将大大</span><span style="color:#00b050;"><span>提高系统的运行效率</span></span><span style="color:#7030a0;">。</span><br></span>
<hr></div>
<span style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:'Times New Roman';font-size:14px;color:#ff0000;">4.文件描述符fd和索引节点</span></span>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:'Times New Roman';">&nbsp; &nbsp;一般来说，使用与管理文件我们都是通过文件名实现的。但是，对于应用编程而言，文件描述符更有用，而系统中的文件在本质上是通过其索引节点进行管理的。</span></div>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:'Times New Roman';"><span>(1)文件描述符</span>：<span style="color:#7030a0;"><span>在系统调用中</span></span>，我们主要是通过文件描述符实现文件的相应操作。文件描述符是应用程序打开一个文件返回的一个整数，它也就代表这个文件。就像体育比赛一样，每个运动员都会被分配一个编号，当我们为某个号码加油时，实际就是其对应的运动员加油。<span style="color:#7030a0;">在linux系统中，所有打开的文件都对应一个文件描述符，其本质是一个非负整数，由系统分配且范围为0~OPEN_MAX(1024).</span><span style="line-height:1.5;">每个<span style="color:#7030a0;"><span>进程在启动</span></span>后默认有三个打开的文件描述符0、1、2，如果启动时没有进行重定向，则文件描述符0关联到标准输入文件，1关联到标准输出，2关联到标准错误输出，即C库中表示：</span></span></div>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="line-height:1.5;"><span style="font-family:'Times New Roman';">#define STDIN_FILENO 0 &nbsp; &nbsp;//标准输入</span></span></div>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:'Times New Roman';">#define STDOUT_FILENO 0 &nbsp; &nbsp;//标准输出</span></div>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:'Times New Roman';">#define STDERR_FILENO 0 &nbsp; &nbsp;//标准错误输出</span></div>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:'Times New Roman';"><span>(2)索引节点</span>：从系统的角度来看，<span style="color:#7030a0;">文件的索引节点(inode)是文件的唯一标识。一个<span>文件的inode包含</span>文件系统处理<span>文件所需要的全部信息</span>，如访问权限、当前大小等</span>。包含两种类型inode:</span></div>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:'Times New Roman';">&nbsp; &nbsp; a.内核inode:保存在内存中，当系统中每个打开的文件都对应着一个内核inode，即与具体的文件系统类型无关；</span></div>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:'Times New Roman';">&nbsp; &nbsp; b.磁盘inode：保存在磁盘上，在文件系统中的每一个文件都有一个磁盘inode，它所保存的具体信息与文件系统的类型有关。</span></div>
<div style="font-family:'宋体';font-size:14px;line-height:21px;">
<hr><span style="font-family:'Times New Roman';color:#7030a0;"><span>博主笔记2：如何理解上述两种索引节点？</span></span></div>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:'Times New Roman';"><span style="color:#7030a0;">&nbsp; &nbsp; 当进程打开一个文件时，</span><span style="color:#00b050;"><span>文件的磁盘inode中的信息将会被载入内存</span></span><span style="color:#7030a0;">，并建立一个内核inode。</span></span></div>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:'Times New Roman';"><span style="color:#00b050;"><span>&nbsp; &nbsp; 当内核inode被修改后，系统负责将其同步到磁盘上</span></span><span style="color:#7030a0;">。磁盘inode与对应内核inode所保存的信息并不完全相同的。</span></span></div>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:'Times New Roman';"><span style="color:#7030a0;">&nbsp; &nbsp; 内核inode记录的是关于文件的更</span><span style="color:#00b050;"><span>通用</span></span><span style="color:#7030a0;">的一些信息；而忽略掉与具体文件系统类型相关的信息。</span></span></div>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:'Times New Roman';color:#7030a0;">&nbsp; &nbsp; 一般而言，一个文件inode应当记录如下信息：</span></div>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:'Times New Roman';color:#7030a0;">&nbsp; &nbsp; a.文件类型;</span></div>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:'Times New Roman';color:#7030a0;">&nbsp; &nbsp; b.与文件相关的硬链接的个数；</span></div>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:'Times New Roman';color:#7030a0;">&nbsp; &nbsp; c.以字节为单位的文件的长度；</span></div>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:'Times New Roman';color:#7030a0;">&nbsp; &nbsp; d.设备标识符</span></div>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:'Times New Roman';color:#7030a0;">&nbsp; &nbsp; e.各种时间截，包括文件状态的改变时间、文件的最后访问时间和最后修改时间等。<br></span>
<hr></div>
<span style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:'Times New Roman';font-size:14px;color:#ff0000;">5.文件指针与流</span></span>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:'Times New Roman';">&nbsp; &nbsp; 在标准I/O函数中，并不直接操作文件描述符，而是使用文件指针。文件指针与文件描述符是一一对应关系，这种对应关系由标准I/O库自己内部维护。</span></div>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span><span style="font-family:'Times New Roman';">(1)文件指针</span></span></div>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:'Times New Roman';">&nbsp; &nbsp;&nbsp;<span style="color:#7030a0;">文件指针指向的数据类型为FILE型</span>，但应用程序无需关心它的具体内容。在应用程序调用文件时，只需要提供文件指针即可。</span></div>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span><span style="font-family:'Times New Roman';">(2)流</span></span></div>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:'Times New Roman';">&nbsp; &nbsp; 在标准I/O中，一个<span style="color:#7030a0;">打开的文件称之为"流"(stream</span>),流可用于读(输入流)、写(输出流）或者读写(输入输出流)。每个进程在启动时，都会打开三个流，与打开的三个文件相对应：sdtin代表标准输入流、stdout代表标准输出流、stderr代表标准错误输出流，他们三个<span style="color:#7030a0;">都是(FILE*)型的指针</span>。</span></div>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:'Times New Roman';">注意：标准错误输出流不进行缓冲，输出的内容会马上同步到文件(即控制台设备)。</span>
<hr></div>
<span style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:'Times New Roman';"><span style="color:#7030a0;">博主笔记3：FILE型指针（</span><span style="color:rgb(112,48,160);">FILE *fp</span><span style="color:#7030a0;">）？</span></span></span>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:'Times New Roman';"><span style="color:#7030a0;">&nbsp; &nbsp; FILE是在stdio.h定义的</span><span style="color:#00b050;"><span>保存文件流信息</span></span><span style="color:#7030a0;">的一个结构体</span><span style="color:#00b050;"><span>类型</span></span><span style="color:#7030a0;">，</span><span style="color:rgb(112,48,160);line-height:1.5;">实际是C语言定义的标准数据结构，用于文件。</span><span style="color:rgb(112,48,160);line-height:1.5;">&nbsp;</span></span></div>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:'Times New Roman';"><span style="color:#7030a0;">&nbsp; &nbsp; FILE *fp：是声明一个FILE类型名为fp的指针，fp为指向FILE类型的对象，也可以理解成为FILE结构体的一个指针对象。在应用程序访问文件时，一般使用FILE*类型变量表示</span><span style="color:#00b050;"><span>文件句柄</span></span><span style="color:#7030a0;">，通过它来访问FILE结构体，对文件进行操作。<span>每打开一个文件就会</span></span><span><span style="color:#00b050;"><span>返回</span></span><span style="color:#7030a0;">一个文件指针(为FILE类型)，然后通过这个指针对象访问结构体的成员变量从而</span><span style="color:#00b050;"><span>获得文件信息</span></span></span><span style="color:#7030a0;">。</span></span></div>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:'Times New Roman';"><span style="color:#7030a0;">如fopen函数，FILE* fp</span><span style="color:rgb(112,48,160);line-height:1.5;">=fopen("1.txt","r+");</span></span></div>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:'Times New Roman';"><span style="color:#00b050;"><span>struct</span></span><span style="color:#7030a0;">&nbsp;_iobuf&nbsp;</span></span></div>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:'Times New Roman';color:#7030a0;">&nbsp;{</span></div>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:'Times New Roman';color:#7030a0;">&nbsp; &nbsp; &nbsp; &nbsp; &nbsp;char *_ptr; //文件输入的下一个位置</span></div>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:'Times New Roman';color:#7030a0;">&nbsp; &nbsp; &nbsp; &nbsp; &nbsp;int _cnt; //当前缓冲区的相对位置</span></div>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:'Times New Roman';color:#7030a0;">&nbsp; &nbsp; &nbsp; &nbsp; &nbsp;char *_base; //指基础位置(应该是文件的其始位置)</span></div>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:'Times New Roman';color:#7030a0;">&nbsp; &nbsp; &nbsp; &nbsp; &nbsp;int _flag; //文件标志</span></div>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:'Times New Roman';color:#7030a0;">&nbsp; &nbsp; &nbsp; &nbsp; &nbsp;int _file; //文件的有效性验证</span></div>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:'Times New Roman';color:#7030a0;">&nbsp; &nbsp; &nbsp; &nbsp; &nbsp;int _charbuf; //检查缓冲区状况,如果无缓冲区则不读取</span></div>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:'Times New Roman';color:#7030a0;">&nbsp; &nbsp; &nbsp; &nbsp; &nbsp;int _bufsiz; //文件的大小</span></div>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:'Times New Roman';color:#7030a0;">&nbsp; &nbsp; &nbsp; &nbsp; &nbsp;char *_tmpfname; //临时文件名</span></div>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:'Times New Roman';color:#7030a0;">};</span></div>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:'Times New Roman';color:#00b050;"><span>typedef struct _iobuf FILE;</span></span></div>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:'Times New Roman';color:#00b050;"><span>总结：FILE是C运行库中的结构体，文件描述符是posix系统级的。一切关于FILE的操作最终都将调用系统级的函数。</span></span></div>
<hr style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:'Times New Roman';font-size:14px;line-height:21px;"><span style="font-size:22px;"></span></span>
<div><span style="font-size:18px;"><strong>二、头文件</strong></span></div>
<div><span style="font-size:14px;line-height:1.5;"></span></div>
<span style="font-size:14px;color:#ff0000;">#include &lt;stdio.h&gt;&nbsp;</span>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:'Times New Roman';">&nbsp; &nbsp; 程序中用到系统提供的标准函数库中的输入输出函数，即提供标准输入输出信息</span>
<div><span style="font-family:'Times New Roman';color:#ff0000;"></span></div>
</div>
<span style="font-family:'Times New Roman';font-size:14px;color:#ff0000;">#include &lt;stdlib.h&gt;</span>
<div style="font-family:'宋体';font-size:14px;line-height:21px;">
<div><span style="font-family:'Times New Roman';color:#ff0000;"></span></div>
<div><span style="line-height:1.5;"><span style="font-family:'Times New Roman';">&nbsp; &nbsp; stdlib 头文件里包含了C、C++语言的最常用的系统函数。stdlib.h里面定义了五种类型、一些宏和通用工具函数。 类型例如size_t、wchar_t、div_t、ldiv_t和lldiv_t； 宏例如EXIT_FAILURE、EXIT_SUCCESS、RAND_MAX和MB_CUR_MAX等等；
 常用的函数如malloc()、calloc()、realloc()、free()、system()、atoi()、atol()、rand()、srand()、exit()等等。</span></span>
<div><span style="line-height:1.5;"><span style="font-family:'Times New Roman';"></span></span></div>
</div>
</div>
<span style="font-family:'Times New Roman';font-size:14px;color:#ff0000;">#include&lt;sys/types.h&gt;&nbsp;</span>
<div style="font-family:'宋体';font-size:14px;line-height:21px;">
<div>
<div><span style="line-height:1.5;"><span style="font-family:'Times New Roman';"></span></span></div>
<div><span style="line-height:1.5;"><span style="font-family:'Times New Roman';">&nbsp; &nbsp; 基本系统数据类型，是Unix/Linux系统的基本系统数据类型的头文件，含有size_t(反映内存中对象的大小-以字节为单位)、time_t(以秒为单位计时),pid_t(进程ID和进程组ID)、dev_t(设备号)、ssize_t(供返回字节计数或错误提示的函数使用)等类型</span></span></div>
<div><span style="font-family:'Times New Roman';"></span></div>
</div>
</div>
<span style="font-family:'Times New Roman';font-size:14px;color:#ff0000;">#include&lt;sys/stat.h&gt;</span>
<div style="font-family:'宋体';font-size:14px;line-height:21px;">
<div>
<div><span style="font-family:'Times New Roman';"></span></div>
<div><span style="font-family:'Times New Roman';">&nbsp; &nbsp; 包含的头文件stat.h在系统目录的sys目录下，获取文件属性。</span></div>
<div><span style="font-family:'Times New Roman';">&nbsp; &nbsp; &nbsp; &nbsp;struct stat{</span></div>
</div>
</div>
<blockquote style="font-family:'宋体';font-size:14px;line-height:21px;border:none;">
<blockquote style="border:none;">
<div>
<div>
<div><span style="font-family:'Times New Roman';">mode_t st_mode; //文件类型和权限信息</span></div>
</div>
</div>
</blockquote>
<blockquote style="border:none;">
<div>
<div><span style="font-family:'Times New Roman';">ino_t st_ino; //i结点标识</span></div>
</div>
</blockquote>
<blockquote style="border:none;">
<div>
<div><span style="font-family:'Times New Roman';">dev_t st_dev; //device number (file system)</span></div>
</div>
</blockquote>
<blockquote style="border:none;">
<div>
<div><span style="font-family:'Times New Roman';">dev_t st_rdev; //device number for special files</span></div>
</div>
</blockquote>
<blockquote style="border:none;">
<div>
<div><span style="font-family:'Times New Roman';">nlink_t st_nlink; //符号链接数</span></div>
</div>
</blockquote>
<blockquote style="border:none;">
<div>
<div><span style="font-family:'Times New Roman';">uid_t st_uid; //用户ID</span></div>
</div>
</blockquote>
<blockquote style="border:none;">
<div>
<div><span style="font-family:'Times New Roman';">gid_t st_gid; //组ID</span></div>
</div>
</blockquote>
<blockquote style="border:none;">
<div>
<div><span style="font-family:'Times New Roman';">off_t st_size; //size in bytes,for regular files</span></div>
</div>
</blockquote>
<blockquote style="border:none;">
<div>
<div><span style="font-family:'Times New Roman';">time_t st_st_atime; //最后一次访问的时间</span></div>
</div>
</blockquote>
<blockquote style="border:none;">
<div>
<div><span style="font-family:'Times New Roman';">time_t st_mtime; //文件内容最后一次被更改的时间</span></div>
</div>
</blockquote>
<blockquote style="border:none;">
<div>
<div><span style="font-family:'Times New Roman';">time_t st_ctime; //文件结构最后一次被更改的时间</span></div>
</div>
</blockquote>
<blockquote style="border:none;">
<div>
<div><span style="font-family:'Times New Roman';">blksize_t st_blksize; //best I/O block size</span></div>
</div>
</blockquote>
<blockquote style="border:none;">
<div>
<div><span style="font-family:'Times New Roman';">blkcnt_t st_blocks; //number of disk blocks allocated</span></div>
</div>
</blockquote>
<blockquote style="border:none;">
<div>
<div><span style="font-family:'Times New Roman';">};</span></div>
</div>
</blockquote>
</blockquote>
<span style="font-family:'Times New Roman';font-size:14px;color:#ff0000;">#include &lt;sys/fcntl.h&gt;</span>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="line-height:1.5;"><span style="font-family:'Times New Roman';">&nbsp; &nbsp; fcntl.h定义了很多宏和open,fcntl函数原型</span></span>
<div>
<div><span style="font-family:'Times New Roman';"></span></div>
</div>
</div>
<span style="font-family:'Times New Roman';font-size:14px;color:#ff0000;">&nbsp;#include&lt;unistd.h&gt;</span>
<div style="font-family:'宋体';font-size:14px;line-height:21px;">
<div><span style="font-family:'Times New Roman';"></span></div>
<div><span style="font-family:'Times New Roman';">&nbsp; &nbsp; unistd.h定义了更多的函数原型<br></span>
<div>
<pre style="font-family:Monaco, Consolas, Courier, 'Lucida Console', monospace;line-height:16px;color:rgb(51,51,51);"></pre>
<div><span style="font-size:22px;"><span style="font-family:'Times New Roman';"><strong>三、系统调用API接口</strong></span></span>
<div>
<div></div>
<div><span><span style="font-family:'Times New Roman';font-size:14px;">1.创建文件</span></span></div>
<div><span><span style="font-family:'Times New Roman';">(1)函数</span></span></div>
<div><span style="font-family:'Times New Roman';"><span></span></span><pre><code class="language-cpp hljs"><ol class="hljs-ln"><li><div class="hljs-ln-numbers"><div class="hljs-ln-line hljs-ln-n" data-line-number="1"></div></div><div class="hljs-ln-code"><div class="hljs-ln-line">   <span class="hljs-meta">#<span class="hljs-meta-keyword">include</span><span class="hljs-meta-string">&lt;sys/types.h&gt;</span></span></div></div></li><li><div class="hljs-ln-numbers"><div class="hljs-ln-line hljs-ln-n" data-line-number="2"></div></div><div class="hljs-ln-code"><div class="hljs-ln-line">   <span class="hljs-meta">#<span class="hljs-meta-keyword">include</span><span class="hljs-meta-string">&lt;sys/stat.h&gt;</span></span></div></div></li><li><div class="hljs-ln-numbers"><div class="hljs-ln-line hljs-ln-n" data-line-number="3"></div></div><div class="hljs-ln-code"><div class="hljs-ln-line">  <span class="hljs-function"><span class="hljs-keyword">int</span> <span class="hljs-title">creat</span><span class="hljs-params">(<span class="hljs-keyword">const</span> <span class="hljs-keyword">char</span> *filename,<span class="hljs-keyword">mode_t</span> mode)</span></span></div></div></li></ol></code><div class="hljs-button signin" data-title="登录后复制" onclick="hljs.signin(event)"></div></pre></div>
</div>
</div>
</div>
</div>
<div>
<div>
<div>
<div>
<div><span style="font-family:'Times New Roman';color:#002060;"><span></span></span></div>
<div><span><span style="font-family:'Times New Roman';">(2)说明</span></span></div>
</div>
</div>
</div>
</div>
<blockquote style="border:none;">
<div>
<div>
<div>
<div>
<div><span style="font-family:'Times New Roman';">filename:创建文件名(包含路径、缺省为当前目录)；</span></div>
</div>
</div>
</div>
</div>
<div>
<div><span style="font-family:'Times New Roman';color:#7030a0;">mode:文件属性(0-无任何权限；S_IRUSR或1-&gt;可读；S_IWUSR或2-&gt;可写；S_IXUSR或3-&gt;可执行；S_IRWXU或7-&gt;均可)</span></div>
</div>
</blockquote>
<div>
<div><span style="font-family:'Times New Roman';"></span></div>
</div>
<strong><span style="font-family:'Times New Roman';">(3)返回值</span></strong>
<blockquote style="border:none;">
<div>
<div>
<div>
<div>
<div><span style="font-family:'Times New Roman';">创建成功<span style="color:#7030a0;">返回文件描述符fd</span>；错误返回-1。</span></div>
</div>
</div>
</div>
</div>
<div>
<div>
<div><span style="font-family:'Times New Roman';color:#00b050;">注释：</span></div>
</div>
</div>
<div>
<div>
<div><span style="font-family:'Times New Roman';color:#00b050;">&nbsp; &nbsp; (1)mode_t表示unsigned int，所以mode_t 实际上也就是一种无符号整数</span></div>
</div>
</div>
<div>
<div>
<div><span style="font-family:'Times New Roman';color:#00b050;">&nbsp; &nbsp; (2)const是一个C语言的关键字，它限定一个变量不允许被改变。使用const在一定程度上可以提高程序的安全性和可靠性。</span></div>
</div>
</div>
</blockquote>
<div>
<div>
<div></div>
</div>
<strong><span style="font-family:'Times New Roman';font-size:14px;">2.打开文件</span></strong>
<div>
<div></div>
<div><span><span style="font-family:'Times New Roman';">（1）函数：</span></span><pre><code class="language-html hljs xml"><ol class="hljs-ln"><li><div class="hljs-ln-numbers"><div class="hljs-ln-line hljs-ln-n" data-line-number="1"></div></div><div class="hljs-ln-code"><div class="hljs-ln-line">#include<span class="hljs-tag">&lt;<span class="hljs-name">sys</span>/<span class="hljs-attr">types.h</span>&gt;</span></div></div></li><li><div class="hljs-ln-numbers"><div class="hljs-ln-line hljs-ln-n" data-line-number="2"></div></div><div class="hljs-ln-code"><div class="hljs-ln-line">#include<span class="hljs-tag">&lt;<span class="hljs-name">sys</span>/<span class="hljs-attr">stat.h</span>&gt;</span></div></div></li><li><div class="hljs-ln-numbers"><div class="hljs-ln-line hljs-ln-n" data-line-number="3"></div></div><div class="hljs-ln-code"><div class="hljs-ln-line">int open(const char *pathname,int flags);                     //文件已创建</div></div></li><li><div class="hljs-ln-numbers"><div class="hljs-ln-line hljs-ln-n" data-line-number="4"></div></div><div class="hljs-ln-code"><div class="hljs-ln-line">int open(const char *pathname,int flags,mode_t mode); //文件没有创建</div></div></li></ol></code><div class="hljs-button signin" data-title="登录后复制" onclick="hljs.signin(event)"></div></pre></div>
</div>
</div>
<div><span><span style="font-family:'Times New Roman';font-size:18px;color:#c00000;"></span></span></div>
<div>
<div>
<div>
<div>
<div><span style="font-family:'Times New Roman';font-size:18px;color:#c00000;"><span></span></span></div>
<div style="line-height:27px;"><span><span style="font-family:'Times New Roman';">（2）说明：</span></span></div>
</div>
</div>
</div>
</div>
<blockquote style="border:none;">
<div>
<div>
<div>
<div>
<div><span style="font-family:'Times New Roman';color:#7030a0;">flags:打开标识。</span></div>
</div>
</div>
</div>
</div>
<div>
<div>
<div><span style="font-family:'Times New Roman';color:#7030a0;">O_RDONLY-&gt;只读打开方式；O_WRONLY-&gt;只写打开方式；O_RDWR-&gt;可读可写O_APPEND-&gt;追加方式打开 O_CREAT-&gt;创建一个文件；O_NOBLOCK-&gt;非阻塞方式打开</span></div>
</div>
</div>
</blockquote>
<div>
<div>
<div><span style="font-family:'Times New Roman';"><span>（3）返回值</span>：打开成功返回文件描述符fd;错误返回-1，并把错误代码设给err。</span></div>
<div><span style="font-family:'Times New Roman';">&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; if(fd=open(argv[1],O_CREAT|O_RDONLY,0755))</span></div>
<div><span style="font-family:'Times New Roman';color:#00b050;">注释：非阻塞方式，即当文件打开失败时，进程不阻塞，跳过该部分执行进程剩余部分或者结束进程。</span></div>
<div></div>
</div>
<strong><span style="font-family:'Times New Roman';font-size:14px;">3.读一个文件</span></strong>
<div>
<div></div>
<div><span style="font-family:'Times New Roman';"><span>（1）函数</span>：</span><span style="font-family:'Times New Roman';">&nbsp; &nbsp; &nbsp;&nbsp;</span></div>
<div><span style="font-family:'Times New Roman';"></span><pre><code class="language-html hljs xml"><ol class="hljs-ln"><li><div class="hljs-ln-numbers"><div class="hljs-ln-line hljs-ln-n" data-line-number="1"></div></div><div class="hljs-ln-code"><div class="hljs-ln-line">   #include<span class="hljs-tag">&lt;<span class="hljs-name">unistd.h</span>&gt;</span></div></div></li><li><div class="hljs-ln-numbers"><div class="hljs-ln-line hljs-ln-n" data-line-number="2"></div></div><div class="hljs-ln-code"><div class="hljs-ln-line">   int read(int fd,const *buf,size_t length)</div></div></li></ol></code><div class="hljs-button signin" data-title="登录后复制" onclick="hljs.signin(event)"></div></pre></div>
</div>
</div>
<div>
<div>
<div>
<div>
<div><span style="font-family:'Times New Roman';"></span></div>
<div><span style="font-family:'Times New Roman';"></span></div>
</div>
</div>
</div>
</div>
<strong><span style="font-family:'Times New Roman';">（2）说明</span></strong>
<div>
<div>
<div>
<div>
<div><span style="font-family:'Times New Roman';">&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; 从文件描述符fd指向的文件中，读取length个<span><span style="font-size:14px;color:#7030a0;">字节</span></span>到buf所指向的缓存区中(文件内容-&gt;缓存Buf)。</span></div>
<div><span style="font-family:'Times New Roman';"></span></div>
</div>
</div>
</div>
</div>
<strong><span style="font-family:'Times New Roman';">（3）返回值</span></strong>
<blockquote style="border:none;">
<div>
<div>
<div>
<div>
<div><span style="font-family:'Times New Roman';">返回为<span style="color:#7030a0;"><span>实际读取的字节个数length</span></span>。</span></div>
</div>
</div>
</div>
</div>
</blockquote>
<div>
<div>
<div></div>
</div>
<strong><span style="font-family:'Times New Roman';font-size:14px;">4.写一个文件</span></strong>
<div>
<div></div>
<div><span style="font-family:'Times New Roman';"></span></div>
</div>
</div>
<strong><span style="font-family:'Times New Roman';">（1）函数：</span></strong>
<div><pre><code class="language-java hljs"><ol class="hljs-ln"><li><div class="hljs-ln-numbers"><div class="hljs-ln-line hljs-ln-n" data-line-number="1"></div></div><div class="hljs-ln-code"><div class="hljs-ln-line">    #include&lt;unistd.h&gt;</div></div></li><li><div class="hljs-ln-numbers"><div class="hljs-ln-line hljs-ln-n" data-line-number="2"></div></div><div class="hljs-ln-code"><div class="hljs-ln-line">    <span class="hljs-function"><span class="hljs-keyword">int</span> <span class="hljs-title">write</span><span class="hljs-params">(<span class="hljs-keyword">int</span> fd,<span class="hljs-keyword">const</span> *buf,size_t length)</span></span></div></div></li></ol></code><div class="hljs-button signin" data-title="登录后复制" onclick="hljs.signin(event)"></div></pre>
<div>
<div>
<div><span style="font-family:'Times New Roman';"></span></div>
<div><span style="font-family:'Times New Roman';"></span></div>
</div>
</div>
<strong><span style="font-family:'Times New Roman';">（2）说明</span></strong>
<div>
<div>
<div><span style="font-family:'Times New Roman';">&nbsp; &nbsp; &nbsp; &nbsp; 向文件描述符fd指向的文件，写入<span><span style="font-size:14px;color:#7030a0;">length个字节</span></span>到buf所指向的缓存区中</span></div>
<div><span style="font-family:'Times New Roman';"></span></div>
</div>
</div>
<strong><span style="font-family:'Times New Roman';">（3）返回值</span></strong>
<div><span style="font-family:'Times New Roman';"><span style="line-height:1.5;"><span>&nbsp; &nbsp;&nbsp;</span></span><span style="line-height:1.5;">实际写入的字节个数length</span></span>
<div>
<div>
<div><span style="font-family:'Times New Roman';color:#7030a0;">注释：(1)size_t实际为unsigned int类型，设计 size_t 就是为了适应多个平台的 ，size_t的引入增强了程序在不同平台上的可移植性。 在32位系统中size_t是4字节的，而在64位系统中，size_t是8字节的，这样利用该类型可以增强程序的可移植性。</span></div>
<div><span style="font-family:'Times New Roman';">&nbsp; &nbsp;</span></div>
<div></div>
</div>
<strong><span style="font-family:'Times New Roman';font-size:14px;">5.发送控制命令</span></strong>
<div>
<div></div>
<div><span style="font-family:'Times New Roman';"></span></div>
</div>
</div>
</div>
<strong><span style="font-family:'Times New Roman';">（1）函数</span></strong>
<div>
<div>
<div><pre><code class="language-html hljs xml"><ol class="hljs-ln"><li><div class="hljs-ln-numbers"><div class="hljs-ln-line hljs-ln-n" data-line-number="1"></div></div><div class="hljs-ln-code"><div class="hljs-ln-line">    #includ<span class="hljs-tag">&lt;<span class="hljs-name">sys</span>/<span class="hljs-attr">ioctl.h</span>&gt;</span></div></div></li><li><div class="hljs-ln-numbers"><div class="hljs-ln-line hljs-ln-n" data-line-number="2"></div></div><div class="hljs-ln-code"><div class="hljs-ln-line">    int ioctl(int fd,int request,...)</div></div></li></ol></code><div class="hljs-button signin" data-title="登录后复制" onclick="hljs.signin(event)"></div></pre></div>
<div><span style="font-family:'Times New Roman';"></span></div>
</div>
</div>
<strong><span style="font-family:'Times New Roman';">（2）说明</span></strong>
<div>
<div>
<div><span style="font-family:'Times New Roman';">&nbsp; &nbsp; &nbsp; &nbsp; ioctl操作用于向文件发送控制命令，<span style="color:#7030a0;">那些不能被抽象为读和写的文件操作统一由ioctl操作代表</span>。对于Linux系统，ioctl操作常用与修改设备的参数。</span></div>
<div><span style="font-family:'Times New Roman';">&nbsp; &nbsp; fd:要操作的文件的描述符;</span></div>
<div><span style="font-family:'Times New Roman';">&nbsp; &nbsp; request:代表<span style="color:#7030a0;"><span>要进行的操作</span></span>，不同的(设备)文件有不同的定义;</span></div>
<div><span style="font-family:'Times New Roman';">&nbsp; &nbsp; 可变参数：取<span style="color:#7030a0;">决于request参数</span>，通常是一个指向变量或者结构体的指针;</span></div>
<div><span style="font-family:'Times New Roman';">&nbsp; &nbsp; 返回值：成功返回0，错误返回-1 &nbsp;&nbsp;</span></div>
<div><span style="font-family:'Times New Roman';"></span></div>
</div>
</div>
<strong><span style="font-family:'Times New Roman';">（3）返回值</span></strong>
<div>
<div>
<div><span style="font-family:'Times New Roman';">&nbsp; &nbsp; &nbsp; &nbsp; 返回文件指针<span style="color:#7030a0;"><span>相对于文件头的位置</span></span>。</span></div>
<div></div>
</div>
<div>
<div><span style="font-family:'Times New Roman';"><span style="font-size:14px;"><span style="line-height:24px;"><span>6.关闭文件</span></span></span></span></div>
<div><span style="font-family:'Times New Roman';"><span style="font-size:14px;"><span style="line-height:24px;"><span></span></span></span></span></div>
</div>
</div>
<strong><span style="font-family:'Times New Roman';">(1)函数</span></strong>
<div><pre><code class="language-html hljs xml"><ol class="hljs-ln"><li><div class="hljs-ln-numbers"><div class="hljs-ln-line hljs-ln-n" data-line-number="1"></div></div><div class="hljs-ln-code"><div class="hljs-ln-line">    #include<span class="hljs-tag">&lt;<span class="hljs-name">unistd.h</span>&gt;</span></div></div></li><li><div class="hljs-ln-numbers"><div class="hljs-ln-line hljs-ln-n" data-line-number="2"></div></div><div class="hljs-ln-code"><div class="hljs-ln-line">    int close(int fd);</div></div></li></ol></code><div class="hljs-button signin" data-title="登录后复制" onclick="hljs.signin(event)"></div></pre></div>
<span style="font-family:'Times New Roman';"><span>(2)说明：</span>关闭文件，调用close()会让数据写回磁盘，并释放该文件所占的资源</span>
<div><span><span><span><span style="font-family:'Times New Roman';">&nbsp; &nbsp; fd为文件描述符</span></span></span></span></div>
<strong><span style="font-family:'Times New Roman';">(3)返回值</span></strong>
<div><span><span><span><span style="font-family:'Times New Roman';">&nbsp; &nbsp; 返回正常为0，失败为-1</span></span></span></span></div>
<div>
<hr></div>
</div>
<div><span style="font-family:'Times New Roman';color:#7030a0;"><span>博主笔记4：API的错误处理？</span></span></div>
<div><span style="font-family:'Times New Roman';color:#7030a0;">&nbsp; &nbsp; 在系统编程中，对API调用的错误处理是重要的一个环节，主要有三种方法：</span></div>
<div><span style="font-family:'Times New Roman';color:#7030a0;">(1)errno变量是一个整型值，当调用API出现错误时用于表示错误的类型，然后我们就可以根据errno变量装载的值，来对错误进行相应的处理，其接口头文件以及定义为：</span></div>
<div><span style="font-family:'Times New Roman';color:#7030a0;">#include&lt;errno.h&gt;</span></div>
<div><span style="font-family:'Times New Roman';color:#7030a0;">extern int errno;</span></div>
<div><span style="font-family:'Times New Roman';color:#7030a0;">当调用返回-1且errno变量被设置为EINTR，这说明在读入/写出有效字节前收到一个信号，这种情况可以重新进行读/写操作；</span></div>
<div><span style="font-family:'Times New Roman';color:#7030a0;">当调用返回-1且errno变量被设置为EAGAIN，这说明是在非阻塞方式下读文件/写文件，并且没有可读的数据/不能写文件；</span></div>
<div><span style="font-family:'Times New Roman';color:#7030a0;"><span>当调用返回-1且errno变量被设置为非</span><span>EINTR或</span><span>EAGAIN，表明有其他类型的错误发生，必须根据具体情况进行处理。</span></span></div>
<div><span style="font-family:'Times New Roman';color:#7030a0;">(2)errno可以用于输出不太直观，C标准库提供了一个函数用于</span><span style="font-family:'Times New Roman';color:#00b050;">将<span>错误码</span>转换为一个描述错误的字符串</span><span style="font-family:'Times New Roman';color:#7030a0;">，原型如下：</span></div>
<div><span style="font-family:'Times New Roman';color:#7030a0;">#include&lt;string.h&gt;</span></div>
<div><span style="font-family:'Times New Roman';color:#7030a0;">char *strerror(int errnum);</span></div>
<div><span style="font-family:'Times New Roman';color:#7030a0;">其中，参数errnum是错误码，返回值是错误码的字符串。</span></div>
<div><span style="font-family:'Times New Roman';color:#7030a0;">(3)</span><span style="font-family:'Times New Roman';color:#00b050;"><span>perror函数</span></span><span style="font-family:'Times New Roman';color:#7030a0;">：直接将</span><span style="font-family:'Times New Roman';color:#00b050;"><span>当前的errno变量对应的错误信息输出到标准错误输出(控制台设备文件)</span></span><span style="font-family:'Times New Roman';color:#7030a0;">，原型：</span></div>
<div><span style="font-family:'Times New Roman';color:#7030a0;">#include&lt;stdio.h&gt;</span></div>
<div><span style="font-family:'Times New Roman';color:#7030a0;">void perror(const char *s)</span></div>
<div><span style="font-family:'Times New Roman';color:#7030a0;">它</span><span style="font-family:'Times New Roman';color:#00b050;"><span>首先将字符串s输出，然后再输出对错误的描述</span></span><span style="font-family:'Times New Roman';color:#7030a0;">。其中，s字符串是人为设定的。</span></div>
<hr><strong><span style="font-family:SimHei;font-size:22px;"></span></strong></div>
<span style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:'Times New Roman';font-size:14px;"><strong>6.文件定位</strong></span></span>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span><span style="font-family:'Times New Roman';">（1）函数：</span></span><span style="font-family:'Times New Roman';">&nbsp;&nbsp;</span></div>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span><span style="font-family:'Times New Roman';"></span></span><pre><code class="language-html hljs xml"> int lseek(int fd,offset,int whence)</code><div class="hljs-button signin" data-title="登录后复制" onclick="hljs.signin(event)"></div></pre></div>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span><span style="font-family:'Times New Roman';">（2）说明：将文件读取指针相对whence移动offset个字节。</span></span></div>
<blockquote style="font-family:'宋体';font-size:14px;line-height:21px;border:none;">
<div><span><span style="font-family:'Times New Roman';">whence：SEEK_SET-&gt;相对文件开头；SEEK_CUR-&gt;相对文件读写指针当前位置；SEEK_END-&gt;相对文件末尾</span></span></div>
<div><span><span style="font-family:'Times New Roman';">offset：可为负数(向前移动)</span></span></div>
<div><span><span style="font-family:'Times New Roman';">lseek(fd,0,SEED_END)；//返回文件长度(大小)</span></span></div>
</blockquote>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span><span style="font-family:'Times New Roman';">（3）返回值：返回文件指针相对于文件头的位置。</span></span></div>
<span style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:'Times New Roman';font-size:14px;"><strong>7.访问判断</strong></span></span>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span><span style="font-family:'Times New Roman';">（1）函数：</span></span><span style="font-family:'Times New Roman';">&nbsp;
 &nbsp; &nbsp;&nbsp;</span></div>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span><span style="font-family:'Times New Roman';"></span></span><pre><code class="language-html hljs xml">int access(const char *pathname,int mode)</code><div class="hljs-button signin" data-title="登录后复制" onclick="hljs.signin(event)"></div></pre></div>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span><span style="font-family:'Times New Roman';">（2）说明：判断文件是否可以进行某种操作(如读或写)</span></span></div>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span><span style="font-family:'Times New Roman';">&nbsp; &nbsp; &nbsp; &nbsp; R_OK、W_OK、X_OK、F_OK(文件存在)</span></span></div>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span><span style="font-family:'Times New Roman';">（3）返回值：测试成功，函数返回为0；否者返回为-1.</span></span></div>
<div style="font-family:'宋体';font-size:14px;line-height:21px;">
<div><span style="line-height:1.5;"><span style="font-family:SimHei;font-size:22px;"><strong>四、标准I/O库API接口</strong></span></span></div>
<div>
<div><span style="font-family:'Times New Roman';"></span></div>
<div>
<div>
<div><span style="font-family:'Times New Roman';font-size:14px;"><span style="line-height:24px;">&nbsp; &nbsp; 相对于系统I/O函数库，<span style="color:#7030a0;">标准I/O库实现了一个<span>垮平台的用户缓冲机制</span></span>，这有利于<span style="color:#7030a0;">提高系统进行I/O操作的效率</span>。举个简单的I/O缓冲例子。当我们使用printf函数向标准输出写入多个字符时，其工作原理为：先将所写的字符依次放在一个用户缓冲区中，直到碰到一个换行符系统才会调用系统I/O函数write将缓存区中的数据写入标准输出。也就是说，在换行符之前写入的字符并不会立即出现在控制台屏幕上，需要write函数实现用户态和内核态的交互。</span></span></div>
<div><span style="font-family:SimHei;font-size:14px;"><span style="line-height:24px;"><span><strong>1.打开一个文件</strong></span></span></span></div>
<div><span style="font-family:'Times New Roman';font-size:14px;"><span style="line-height:24px;">（1）函数：</span></span><span style="line-height:24px;font-family:'Times New Roman';">&nbsp;
 &nbsp; &nbsp;&nbsp;</span></div>
<div><span style="font-family:'Times New Roman';"><span style="line-height:24px;"></span></span><pre><code class="language-html hljs xml"> FILE *fopen(const char *filename,const char *mode);</code><div class="hljs-button signin" data-title="登录后复制" onclick="hljs.signin(event)"></div></pre></div>
<div><span style="font-family:'Times New Roman';font-size:14px;"><span style="line-height:24px;">（2）说明：</span></span></div>
<div><span style="font-family:'Times New Roman';font-size:14px;"><span style="line-height:24px;">&nbsp; &nbsp; &nbsp; &nbsp; 打开一个文件流并<span style="color:#7030a0;"><span>为文件建立相应的信息区</span></span>(来存放文件信息)和<span style="color:#7030a0;"><span>文件缓冲区</span>用来暂时存放输入输出数据</span>返回</span></span></div>
<div><span style="font-family:'Times New Roman';font-size:14px;"><span style="line-height:24px;">&nbsp; &nbsp; &nbsp; &nbsp; filename:被打开文件的名称(包含路径)</span></span></div>
<div><span style="font-family:'Times New Roman';font-size:14px;"><span style="line-height:24px;">&nbsp; &nbsp; &nbsp; &nbsp;mode:字符串，用于表示打开的模式</span></span></div>
<div><span style="font-family:'Times New Roman';font-size:14px;"><span style="line-height:24px;">&nbsp;（3）返回值：成功返回一个FILE类型的文件指针（即</span></span><span style="font-family:'Times New Roman';font-size:14px;line-height:1.5;">fp指向文件信息区的起始地址</span><span style="line-height:24px;font-family:'Times New Roman';font-size:14px;">），失败返回NULL。</span></div>
</div>
</div>
</div>
</div>
<div style="font-family:'宋体';font-size:14px;line-height:21px;">
<div>
<div><span style="font-family:'Times New Roman';font-size:14px;"><span style="line-height:24px;">&nbsp;（4）举例：</span></span></div>
</div>
</div>
<blockquote style="font-family:'宋体';font-size:14px;line-height:21px;border:none;">
<div>
<div>
<div><span style="font-family:'Times New Roman';font-size:14px;"><span style="line-height:24px;">FILE *fp;</span></span></div>
</div>
</div>
<div>
<div>
<div><span style="font-family:'Times New Roman';font-size:14px;"><span style="line-height:24px;">if(fp=fopen("文件名","r")==NULL)</span></span></div>
</div>
</div>
<div>
<div>
<div><span style="font-family:'Times New Roman';font-size:14px;"><span style="line-height:24px;">{</span></span></div>
</div>
</div>
<blockquote style="border:none;">
<div>
<div>
<div><span style="font-family:'Times New Roman';font-size:14px;"><span style="line-height:24px;">printf("cannot open this file\n");</span></span></div>
</div>
</div>
</blockquote>
<blockquote style="border:none;">
<div>
<div>
<div><span style="font-family:'Times New Roman';font-size:14px;"><span style="line-height:24px;">exit(0);</span></span></div>
</div>
</div>
</blockquote>
<div>
<div>
<div><span style="font-family:'Times New Roman';font-size:14px;"><span style="line-height:24px;">}</span></span></div>
</div>
</div>
</blockquote>
<span style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:SimHei;font-size:14px;"><strong>2.关闭一个文件</strong></span></span>
<div style="font-family:'宋体';font-size:14px;line-height:21px;">
<div>
<div><span style="font-family:'Times New Roman';font-size:14px;"><span style="line-height:24px;"></span></span></div>
<div><span style="font-family:'Times New Roman';font-size:14px;"><span style="line-height:24px;">（1）函数</span></span><span style="line-height:24px;font-family:'Times New Roman';">&nbsp;
 &nbsp; &nbsp;</span></div>
<div><span style="font-family:'Times New Roman';"><span style="line-height:24px;"></span></span><pre><code class="language-html hljs xml"> int fclose(FILE *stream);</code><div class="hljs-button signin" data-title="登录后复制" onclick="hljs.signin(event)"></div></pre></div>
<div><span style="font-family:'Times New Roman';font-size:14px;"><span style="line-height:24px;">（2）说明：关闭打开的文件，关闭前系统会<span style="color:#7030a0;">自动调用fflush函数更新数据</span>即将文件流中的数据写入文件</span></span></div>
<div><span style="font-family:'Times New Roman';font-size:14px;"><span style="line-height:24px;">&nbsp; &nbsp; &nbsp; &nbsp; stream代表打开的文件</span></span></div>
<div><span style="font-family:'Times New Roman';font-size:14px;"><span style="line-height:24px;">（3）返回值：关闭成功返回0，否者返回EOF并设置变量errno的值以指示错误。</span></span></div>
<div><span style="font-family:'Times New Roman';font-size:14px;"></span></div>
</div>
</div>
<span style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:SimHei;font-size:14px;"><strong>3.文件写/读-以数据块为单位</strong></span></span>
<div style="font-family:'宋体';font-size:14px;line-height:21px;">
<div>
<div>
<div><span style="font-family:'Times New Roman';font-size:14px;"></span></div>
<div><span style="font-family:'Times New Roman';font-size:14px;">（1）函数</span></div>
</div>
</div>
</div>
<blockquote style="font-family:'宋体';font-size:14px;line-height:21px;border:none;">
<div>
<div>
<div><pre><code class="language-html hljs xml">size_t fread(void *buffer,size_t size,size_t count,FILE *stream):</code><div class="hljs-button signin" data-title="登录后复制" onclick="hljs.signin(event)"></div></pre></div>
</div>
</div>
<div>
<div>
<div><span style="font-family:'Times New Roman';font-size:14px;">a.说明：从stream文件指针所指向的文件流中所指向的文件<span style="color:#7030a0;">读取count个数据块且大小为size字节</span>到<span style="color:#7030a0;">缓存区</span></span></div>
</div>
</div>
<div>
<div>
<div><span style="font-family:'Times New Roman';font-size:14px;">b.返回值：返回数据块个数，为size_t类型。</span></div>
</div>
</div>
<div>
<div>
<div><span style="font-family:'Times New Roman';font-size:14px;">fwrite(buffer,size,count,fp):从缓冲区写入count个数据项到fp指向的文件</span></div>
</div>
</div>
</blockquote>
<div style="font-family:'宋体';font-size:14px;line-height:21px;">
<div>
<div><span style="font-family:'Times New Roman';font-size:14px;">（2）写文件举例：</span></div>
</div>
</div>
<blockquote style="font-family:'宋体';font-size:14px;line-height:21px;border:none;">
<div>
<div>
<div><span style="font-family:'Times New Roman';font-size:14px;">for(i=0;i</span></div>
</div>
</div>
<div>
<div>
<div><span style="font-family:'Times New Roman';font-size:14px;">{</span></div>
</div>
</div>
<div>
<div>
<div><span style="font-family:'Times New Roman';font-size:14px;">&nbsp; &nbsp; if(fwrite(&amp;stu[i],sizeof(struct Student),1,fp) !=1)；//从数组stu中写入1个大小为sizeof(struct Student)字节数据</span></div>
</div>
</div>
<div>
<div>
<div><span style="font-family:'Times New Roman';font-size:14px;">&nbsp; &nbsp; printf("file write error");</span></div>
</div>
</div>
<div>
<div>
<div><span style="font-family:'Times New Roman';font-size:14px;">}</span></div>
</div>
</div>
<div>
<div>
<div><span style="font-family:'Times New Roman';font-size:14px;">读文件举例：</span></div>
</div>
</div>
<div>
<div>
<div><span style="font-family:'Times New Roman';font-size:14px;">for(i=0;i</span></div>
</div>
</div>
<div>
<div>
<div><span style="font-family:'Times New Roman';font-size:14px;">{</span></div>
</div>
</div>
<div>
<div>
<div><span style="font-family:'Times New Roman';font-size:14px;">&nbsp; &nbsp; fread(&amp;stu[i],sizeof(struct Student),1,fp);</span></div>
</div>
</div>
<div>
<div>
<div><span style="font-family:'Times New Roman';font-size:14px;">&nbsp; &nbsp; printf("%s%d%s",stu[1].name.....);</span></div>
</div>
</div>
<div>
<div>
<div><span style="font-family:'Times New Roman';font-size:14px;">}</span></div>
</div>
</div>
</blockquote>
<div style="font-family:'宋体';font-size:14px;line-height:21px;">
<div>
<div>
<div><span style="font-family:'Times New Roman';font-size:14px;color:#7030a0;">注释：(1)sizeof(struct Student),求字节数，结构体大小字节数为所有变量类型大小字节之和。</span></div>
<div><span style="font-family:'Times New Roman';font-size:14px;color:#7030a0;">&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; (2)&amp;stu[i],参数&amp;stud[i] ：是一个指针，对fwrite来说，是要输出数据的地址。</span></div>
</div>
<div><span style="font-family:'Times New Roman';font-size:14px;"><span style="line-height:24px;"></span></span></div>
</div>
</div>
<span style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:SimHei;font-size:14px;">4.从/向文件读写一个字符</span></span>
<div style="font-family:'宋体';font-size:14px;line-height:21px;">
<div>
<div><span style="font-family:'Times New Roman';font-size:14px;"><span style="line-height:24px;"></span></span></div>
<div><span style="font-family:'Times New Roman';font-size:14px;"><span style="line-height:24px;"></span></span></div>
</div>
</div>
<span style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:SimHei;font-size:14px;">（1）函数</span></span><span style="line-height:24px;font-family:'Times New Roman';font-size:14px;">&nbsp; &nbsp; &nbsp;</span>
<div style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="line-height:24px;font-family:'Times New Roman';font-size:14px;"></span><pre><code class="language-html hljs xml"><ol class="hljs-ln"><li><div class="hljs-ln-numbers"><div class="hljs-ln-line hljs-ln-n" data-line-number="1"></div></div><div class="hljs-ln-code"><div class="hljs-ln-line">  int fget(FILE *stream)：从指向的文件读出一个字符</div></div></li><li><div class="hljs-ln-numbers"><div class="hljs-ln-line hljs-ln-n" data-line-number="2"></div></div><div class="hljs-ln-code"><div class="hljs-ln-line">     返回值：成功返回该字符；失败返回文件结束标志EOF(-1)</div></div></li><li><div class="hljs-ln-numbers"><div class="hljs-ln-line hljs-ln-n" data-line-number="3"></div></div><div class="hljs-ln-code"><div class="hljs-ln-line">  int  fput(ch,FILE *stream)：将一个字符ch写入一个文件中</div></div></li><li><div class="hljs-ln-numbers"><div class="hljs-ln-line hljs-ln-n" data-line-number="4"></div></div><div class="hljs-ln-code"><div class="hljs-ln-line">     返回值：成功返回该字符；失败返回结束标识EOF(-1)。</div></div></li><li><div class="hljs-ln-numbers"><div class="hljs-ln-line hljs-ln-n" data-line-number="5"></div></div><div class="hljs-ln-code"><div class="hljs-ln-line">  feof(FILE *stream)：该函数检查文件读写位置是否移动文件末尾。</div></div></li></ol></code><div class="hljs-button signin" data-title="登录后复制" onclick="hljs.signin(event)"></div></pre>
<div>
<div>
<div><span style="font-family:'Times New Roman';font-size:14px;color:#7030a0;"><span style="line-height:24px;">其中，putchar函数用于项标准输出写入一个字符，即int putchar(int c);等价于int fput(c,stdout);</span></span></div>
<div><span style="font-family:'Times New Roman';font-size:14px;"><span style="line-height:24px;"></span></span></div>
</div>
</div>
<strong><span style="font-family:SimHei;font-size:14px;">（2）应用举例</span></strong></div>
<blockquote style="font-family:'宋体';font-size:14px;line-height:21px;border:none;">
<div>
<div>
<div>
<div><span style="font-family:'Times New Roman';font-size:14px;"><span style="line-height:24px;">while(!feof(fp1)) //fp1为文件描述符，当文件读写位置移动到文件末尾时，feof(fp1)=1</span></span></div>
</div>
</div>
</div>
<div>
<div>
<div><span style="font-family:'Times New Roman';font-size:14px;"><span style="line-height:24px;">{</span></span></div>
</div>
</div>
<div>
<div>
<div><span style="font-family:'Times New Roman';font-size:14px;"><span style="line-height:24px;">&nbsp; &nbsp; ch=fgetc(fp1); //从文件1读取一个字符到ch</span></span></div>
</div>
</div>
<div>
<div>
<div><span style="font-family:'Times New Roman';font-size:14px;"><span style="line-height:24px;">&nbsp; &nbsp; fputc(ch,fp2);</span></span></div>
</div>
</div>
<div>
<div>
<div><span style="font-family:'Times New Roman';font-size:14px;"><span style="line-height:24px;">&nbsp; &nbsp; putchar(ch); //输出一个字符</span></span></div>
</div>
</div>
<div>
<div>
<div><span style="font-family:'Times New Roman';font-size:14px;"><span style="line-height:24px;">}</span></span></div>
</div>
</div>
<div>
<div>
<div><span style="font-family:'Times New Roman';font-size:14px;"><span style="line-height:24px;">while(ch!='#')</span></span></div>
</div>
</div>
<div>
<div>
<div><span style="font-family:'Times New Roman';font-size:14px;"><span style="line-height:24px;">{</span></span></div>
</div>
</div>
<div>
<div>
<div><span style="font-family:'Times New Roman';font-size:14px;"><span style="line-height:24px;">&nbsp; &nbsp; fputc(ch,fp); //向一个文件中写入一个字符</span></span></div>
</div>
</div>
<div>
<div>
<div><span style="font-family:'Times New Roman';font-size:14px;"><span style="line-height:24px;">&nbsp; &nbsp; putchar(ch); //输出一个字符</span></span></div>
</div>
</div>
<div>
<div>
<div><span style="font-family:'Times New Roman';font-size:14px;"><span style="line-height:24px;">&nbsp; &nbsp; ch=getchar(); //获取一个字符</span></span></div>
</div>
</div>
<div>
<div>
<div><span style="font-family:'Times New Roman';font-size:14px;"><span style="line-height:24px;">}</span></span></div>
</div>
</div>
</blockquote>
<span style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:SimHei;font-size:14px;"><strong>5.从/向文件读写字符串</strong></span></span>
<div style="font-family:'宋体';font-size:14px;line-height:21px;">
<div>
<div><span style="font-family:'Times New Roman';font-size:14px;"><span style="line-height:24px;"></span></span></div>
<div><span style="font-family:'Times New Roman';font-size:14px;"><span style="line-height:24px;">（1）函数</span></span><span style="line-height:24px;font-family:'Times New Roman';">&nbsp;
 &nbsp; &nbsp;&nbsp;</span></div>
<div><span style="font-family:'Times New Roman';"><span style="line-height:24px;"></span></span><pre><code class="language-html hljs xml"> char *fgets(char *s,int size,FILE *stream)</code><div class="hljs-button signin" data-title="登录后复制" onclick="hljs.signin(event)"></div></pre></div>
<div><span style="font-family:'Times New Roman';font-size:14px;"><span style="line-height:24px;">&nbsp; &nbsp; a.说明：从fp指向文件读写一个长度（字节为单位）为（n-1）(最后一个为结束标志位'\0')的字符串，存放到字符数组str。</span></span></div>
<div><span style="line-height:24px;font-family:'Times New Roman';font-size:14px;">&nbsp; &nbsp; b.返回值：成功返回数组str地址，失败返回NULL。</span></div>
<div><span style="font-family:'Times New Roman';font-size:14px;"><span style="line-height:24px;"></span></span><pre><code class="language-html hljs xml"> char fputs(const char *s,FILE *stream)</code><div class="hljs-button signin" data-title="登录后复制" onclick="hljs.signin(event)"></div></pre></div>
<div><span style="font-family:'Times New Roman';font-size:14px;"><span style="line-height:24px;">&nbsp; &nbsp; a.说明：把str所指向的字符串写入到文件指针变量fp所指向的文件中。</span></span></div>
<div><span style="font-family:'Times New Roman';font-size:14px;"><span style="line-height:24px;">&nbsp; &nbsp; b.返回值：非负数表示写入成功，有错误发生则返回EOF</span></span></div>
<div><span style="font-family:'Times New Roman';font-size:14px;"><span style="line-height:24px;">（2）应用举例</span></span></div>
</div>
</div>
<blockquote style="font-family:'宋体';font-size:14px;line-height:21px;border:none;">
<div>
<div>
<div><span style="font-family:'Times New Roman';font-size:14px;"><span style="line-height:24px;">while(fgets(str[i],10,fp)!=NULL)</span></span></div>
</div>
</div>
<div>
<div>
<div><span style="font-family:'Times New Roman';font-size:14px;"><span style="line-height:24px;">{</span></span></div>
</div>
</div>
<div>
<div>
<div><span style="font-family:'Times New Roman';font-size:14px;"><span style="line-height:24px;">&nbsp; &nbsp; printf("%s",str[i]);</span></span></div>
</div>
</div>
<div>
<div>
<div><span style="font-family:'Times New Roman';font-size:14px;"><span style="line-height:24px;">&nbsp; &nbsp; i++;</span></span></div>
</div>
</div>
<div>
<div>
<div><span style="font-family:'Times New Roman';font-size:14px;"><span style="line-height:24px;">}</span></span></div>
</div>
</div>
</blockquote>
<span style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:SimHei;font-size:14px;"><strong>6.文件定位</strong></span></span>
<div style="font-family:'宋体';font-size:14px;line-height:21px;">
<div>
<div>
<div><span style="font-family:'Times New Roman';font-size:14px;"></span></div>
<div><span style="font-family:'Times New Roman';font-size:14px;">（1）函数：</span></div>
<div><span style="font-family:'Times New Roman';font-size:14px;"></span><pre><code class="language-html hljs xml">  int fseek(FILE *stream,long offset,int whence)</code><div class="hljs-button signin" data-title="登录后复制" onclick="hljs.signin(event)"></div></pre></div>
<div><span style="font-family:'Times New Roman';font-size:14px;">（2）说明：用于<span style="color:#7030a0;"><span>移动</span>文件流的读写位置</span>。</span></div>
<div><span style="font-family:'Times New Roman';font-size:14px;">&nbsp; &nbsp; whence：表示偏移量相对于文件开始位置 SEEK_SET 0</span></div>
<div><span style="font-family:'Times New Roman';font-size:14px;">&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp;</span><span style="font-family:'Times New Roman';font-size:14px;">表示偏移量相对于</span><span style="font-family:'Times New Roman';font-size:14px;">文件当前位置 SEEK_CUR
 1&nbsp;</span></div>
<div><span style="font-family:'Times New Roman';font-size:14px;">&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp;</span><span style="font-family:'Times New Roman';font-size:14px;">表示偏移量相对于</span><span style="font-family:'Times New Roman';font-size:14px;">文件末尾位置 SEEK_END
 2</span></div>
<div><span style="font-family:'Times New Roman';font-size:14px;">（3）返回值：0表示操作成功，-1表示操作失败并且errno变量的值被设置为错误码</span></div>
<div></div>
</div>
</div>
</div>
<span style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:SimHei;font-size:14px;"><strong>7.其他文件定位函数</strong></span></span>
<div style="font-family:'宋体';font-size:14px;line-height:21px;">
<div>
<div>
<div></div>
<div>&nbsp;(1)函数</div>
<div>&nbsp; &nbsp; void rewind(FILE *stream);</div>
<div>&nbsp; 说明：<span style="color:#7030a0;">将读写位置移动到文件流的<span>开头</span></span></div>
<div>&nbsp;(2)函数</div>
<div>&nbsp; &nbsp; long ftell(FILE *stream)；</div>
<div>&nbsp; 说明：<span style="color:#7030a0;">得到文件流的读写位置</span>，返回值为文件流的当前读写位置(相对于头文件)</div>
<div>（3）函数</div>
<div>&nbsp; &nbsp; int fflush(FILE *stream);</div>
<div>&nbsp; 说明：<span style="color:#7030a0;">将文件流中的数据跟新到真实的文件中</span>，成功返回0，否者将返回EOF并且设置变量errno的值以指示错误。</div>
<div>&nbsp; &nbsp; &nbsp; &nbsp; 在fclose关闭文件之前，系统会自动调用fflush更新数据。</div>
<div></div>
</div>
</div>
</div>
<span style="font-family:'宋体';font-size:14px;line-height:21px;"><span style="font-family:SimHei;font-size:14px;"><strong>8.标准I/O错误处理</strong></span></span>
<div style="font-family:'宋体';font-size:14px;line-height:21px;">
<div>
<div>
<div></div>
<div>&nbsp; &nbsp; 当标准I/O操作发生错误处理时，一般返回NULL指针或者EOF，我们可以通过errno变量得到错误码。</div>
<div>&nbsp;(1)函数</div>
<div><pre><code class="language-html hljs xml"><ol class="hljs-ln"><li><div class="hljs-ln-numbers"><div class="hljs-ln-line hljs-ln-n" data-line-number="1"></div></div><div class="hljs-ln-code"><div class="hljs-ln-line">   int ferror(FILE *stream);</div></div></li><li><div class="hljs-ln-numbers"><div class="hljs-ln-line hljs-ln-n" data-line-number="2"></div></div><div class="hljs-ln-code"><div class="hljs-ln-line">   int feof(FILE *stream);</div></div></li></ol></code><div class="hljs-button signin" data-title="登录后复制" onclick="hljs.signin(event)"></div></pre></div>
<div>（2）说明</div>
<div>&nbsp; &nbsp; ferror函数用于<span style="color:#7030a0;"><span>判断文件流是否发生错误</span></span>，若返回非0值则表示发生了错误</div>
<div>&nbsp; &nbsp; feof函数用于<span><span style="color:#7030a0;">判断对文件流的读写是否已经达尾部</span></span>，若返回非0值则表示已经达尾部。</div>
</div>
<div><br></div>
</div>
<div><span style="font-family:'Times New Roman';"><br></span></div>
</div>
                                    </div><div><div></div></div>
                                    <div></div>


