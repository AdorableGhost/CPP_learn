[原文](https://www.cnblogs.com/rxbook/p/9106513.html)
Linux下编译安装PHP7.2

        </h1>
        <div class="clear"></div>
        <div class="postBody">
【准备工作】

所有操作需要在root用户下

本机测试案例系统信息：centos7.3

安装路径：/usr/local/php

 

【安装PHP】

先安装如下依赖包

$ yum install -y gcc gcc-c++  make zlib zlib-devel pcre pcre-devel  libjpeg libjpeg-devel libpng libpng-devel freetype freetype-devel libxml2 libxml2-devel glibc glibc-devel glib2 glib2-devel bzip2 bzip2-devel ncurses ncurses-devel curl curl-devel e2fsprogs e2fsprogs-devel krb5 krb5-devel openssl openssl-devel openldap openldap-devel nss_ldap openldap-clients openldap-servers

 

下载PHP7.2.0安装包，点此下载 [密码:pm0q]

解压php-7.2.0.tar.gz  然后进入目录，编译。命令如下：

$ tar -zxvf php-7.2.0.tar.gz

$ cd php-7.2.0

$ ./configure --prefix=/usr/local/php --with-config-file-path=/usr/local/php --enable-mbstring --with-openssl --enable-ftp --with-gd --with-jpeg-dir=/usr --with-png-dir=/usr --with-mysql=mysqlnd --with-mysqli=mysqlnd --with-pdo-mysql=mysqlnd --with-pear --enable-sockets --with-freetype-dir=/usr --with-zlib --with-libxml-dir=/usr --with-xmlrpc --enable-zip --enable-fpm --enable-xml --enable-sockets --with-gd --with-zlib --with-iconv --enable-zip --with-freetype-dir=/usr/lib/ --enable-soap --enable-pcntl --enable-cli --with-curl

 

说明：由于PHP7.2不再支持mysql，而是用mysqli取代。因此会出现上面图中所示的warning。不过没关系，如果需要安装php的mysql扩展，文章后面会有说明。

编译完成之后，执行安装命令：

$ make && make install

 

说明：如果是在阿里云购买的云服务器，安装到这里可能会出现如下错误：

virtual memory exhausted: Cannot allocate memory
make: *** [ext/fileinfo/libmagic/apprentice.lo] Error 1  

解决方案：https://www.cnblogs.com/rxbook/p/8005944.html

 

安装过程大约需要20分钟时间.

 

【配置PHP】

在之前编译的源码包中，找到 php.ini-production，复制到/usr/local/php下，并改名为php.ini：

$ cp php.ini-production /usr/local/php/php.ini

[可选项] 设置让PHP错误信息打印在页面上 

$ vim /usr/local/php/php.ini 

1
display_errors = On
 

复制启动脚本：

$ cp ./sapi/fpm/init.d.php-fpm /etc/init.d/php-fpm

$ chmod +x /etc/init.d/php-fpm

修改php-fpm配置文件：

$ cd /usr/local/php/etc

$ cp php-fpm.conf.default php-fpm.conf

$ vim php-fpm.conf

1
① 去掉 pid = run/php-fpm.pid 前面的分号
$ cd php-fpm.d

$ cp www.conf.default www.conf

$ vim www.conf

1
② 修改user和group的用户为当前用户(也可以不改，默认会添加nobody这个用户和用户组)
 

【启动PHP】

$ /etc/init.d/php-fpm start        #php-fpm启动命令

$ /etc/init.d/php-fpm stop         #php-fpm停止命令

$ /etc/init.d/php-fpm restart        #php-fpm重启命令

$ ps -ef | grep php 或者 ps -A | grep -i php  #查看是否已经成功启动PHP

 

【PHP7.2的MySQL扩展】

由于PHP7.2不再支持mysql，而是用mysqli取代，如果需要安装php的mysql扩展，请看这里。

下载安装包：链接:https://pan.baidu.com/s/1bqDutYZ  密码:ae40

解压，并进入目录：

$ tar -zxvf mysql-24d32a0.tar.gz

$ cd mysql-24d32a0

$ /usr/local/php/bin/phpize  #使用phpize初始化

 

#编译mysql扩展，使用mysql native driver 作为mysql链接库

$ ./configure --with-php-config=/usr/local/php/bin/php-config --with-mysql=mysqlnd

接下来，安装：

$ make && make install

 

最后，编辑php.ini文件，在最后面加入 extension=mysql.so 即可。

$ vim /usr/local/php/php.ini

 

重启PHP，查看phpinfo()

$ /etc/init.d/php-fpm restart 

 

 

Linux PHP7的openssl扩展安装
Linux环境下使用PHPmailer发送邮件时，出现如下错误：

1
SMTP -> ERROR: Failed to connect to server: Unable to find the socket transport "ssl" - did you forget to enable it when you configured PHP? (32690)
出现这个问题的原因是当初编译安装PHP缺少了ssl库。

可以重新再次编译PHP，加上--enable-openssl （或者 --with-openssl）参数即可。

但是如果只为了安装这一个扩展就去重新编译，未免有点麻烦，其实可以简单一点，只要安装openssl.so扩展就可以了。

备注：其他的扩展安装方法同理。

 

    （1）找到之前编译安装PHP的安装包，或者从php的官网下载php7（本例使用php7，其他版本的PHP类似）

    （2）解压并进入文件夹 

1
    cd php7.0/ext/openssl
    （3）运行 phpize：

1
    /usr/local/php/bin/phpize
        备注，如果出现如下错误：Cannot find config.m4.

        Make sure that you run '/usr/local/php/bin/phpize' in the top level source directory of the module

        【解决办法】cp ./config0.m4 ./config.m4 即可解决

 

    （4）编译和安装

1
2
    ./configure --with-openssl --with-php-config=/usr/local/php/bin/php-config
    make && make install
    （5）然后进入最后提示的目录，查看文件：

    （6）将 openssl.so 复制到PHP的扩展目录下：

1
    cp openssl.so /usr/local/php/include/php/ext
    （7）找到php.ini，在最后面添加如下内容：

1
    extension=openssl.so
    （8）重启php-fpm和nginx/apache，查看phpinfo()；

   

 