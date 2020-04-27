# Linux

## Linux  静态库
创建  ar  rcs  libmylib.a a.o

- nm 

## Lib 动态库
### 编译
- Compile command 
    -  gcc -fPIC -c a.c
    -  gcc -FPIC -c b.c
    - gcc  -shared -Wl ,soname ,libmylab.so.1 -o libmylab.so.1.0.1 a.o b.o
    - gcc -shared -Wl ,soname, linkname(链接名) -o realname(真名) so文件
-fPIC 生产与位置无关的代码
-c 只编译，不链接
-g 包含调试信息
-shared 生成固定的lib

### 使用
-  修改 /etc/ld.so.conf
    - 添加库目录
    -ldconfig  -v 更新下
- 使用的地方包含头文件
- 编译时带上库
- ldd 查看依赖