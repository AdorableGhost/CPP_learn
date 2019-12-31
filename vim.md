## vim 操作快捷键！

这里是我新配置出来的 [jaywcjlove/vim-web](https://github.com/jaywcjlove/vim-web) 一直在打磨中，基本上可以用了。拿出来骗 star 先上图

图片描述

安装
最新版本的Vim 7.4+ 使用(brew install macvim)安装，vim 版本更新 brew install macvim --override-system-vim

查看配置位置
### 进入vim输入下面字符
:echo $MYVIMRC
下载vim-web
将插件以及配置下载到 ~/.vim/ 目录中，这个目录是存放所有插件和配置的地方。vimscript是vim自己的一套脚本语言，通过这种脚本语言可以实现与 vim 交互，达到功能扩展的目的。一组 vimscript 就是一个 vim 插件，vim 的很多功能都由各式插件实现。

$ git clone https://github.com/jaywcjlove/vim-web.git ~/.vim
$ ln -s ~/.vim/.vimrc ~/.vimrc
下载安装插件
安装~/.vimrc 中配置的插件，这个过程需要很长时间。

### 上面执行完成之后
### 开始下载安装插件
$ vim ### 在vim中运行 ":PlugInstall"
安装依赖
部分插件需要安装一些软件，vim的部分插件才起作用。

### 上面插件安装完成之后执行下面内容
### command-t 文件搜索插件安装
$ cd ~/.vim/plugged/command-t 
$ rake make
 
### 搜索文本内容工具
### 需要安装 CtrlSF的依赖ripgrep
$ brew install ripgrep
 
### 代码提示插件也需要你运行安装哦，不然没有效果嘞
$ cd ~/.vim/plugged/YouCompleteMe
$ ./install.py
### or 新版脚本过时了，推荐上面脚本
$ ./install.sh 
 
### 需要安装ctags 不然配置没效果哦
### ctags for Mac
$ brew install ctags
### ctags for Centos7
$ yum install ctags
注： 默认已经安装了前端必备插件。.vimrc 是控制 vim 行为的配置文件，位于 ~/.vimrc，不论 vim 窗口外观、显示字体，还是操作方式、快捷键、插件属性均可通过编辑该配置文件将 vim 调教成最适合你的编辑器。

界面字体设置

vim-powerline状态栏主题，界面箭头需要安装Powerline字体 （在我Mac上安装的是Sauce Code Powerline字体），下载安装完成之后，还需要你在命令行工具中设置该字体。

在iTerm2中设置方法：Command+, 进入偏好设置（Preferences）=> Profiles => Default(自己的主题配置) => Non-ASCII Font => Change Font(选择字体)

插件管理
这里面刚开始使用的Vim插件管理工具VundleVim/Vundle.vim，后面为了大家安装方便，使用了 junegunn/vim-plug，这个插件管理工具，俺十分不喜欢，多了个 autoload 目录，安装过程也奇丑无比，安装快速，所以就使用它吧，下面命令更新安装的 plug.vim，默认已经有了不需要这一步。

curl -fLo ~/.vim/autoload/plug.vim --create-dirs \
    https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim
安装插件
将配置信息其加入 ~/.vim/.vimrc 中的call plug###begin() 和 call plug###end() 之间，最后进入 vim 输入下面命令，摁 enter 进行安装。

:PlugInstall
更新插件
插件更新频率较高，差不多每隔一个月你应该看看哪些插件有推出新版本，批量更新，只需在 vim 中执行下面命令即可。

:PlugUpdate
卸载插件
先在 .vimrc 中注释或者删除对应插件配置信息，然后在 vim 中执行下面命令，即可删除对应插件。

:PlugClean
启动Vim
$ vim
Vim理解
这部分来源 一起来说 Vim 语

动词
动词代表了我们打算对文本进行什么样的操作。例如：

d ### 表示删除delete
r ### 表示替换replace
c ### 表示修改change
y ### 表示复制yank
v ### 表示选取visual select
名词
名词代表了我们即将处理的文本。Vim 中有一个专门的术语叫做 [文本对象] text object，下面是一些文本对象的示例：

w ### 表示一个单词word
s ### 表示一个句子sentence
p ### 表示一个段落paragraph
t ### 表示一个 HTML 标签tag
引号或者各种括号所包含的文本称作一个文本块。
介词
介词界定了待编辑文本的范围或者位置。

i ### 表示在...之内 inside
a ### 表示环绕... around
t ### 表示到...位置前 to
f ### 表示到...位置上 forward
数词
数词指定了待编辑文本对象的数量，从这个角度而言，数词也可以看作是一种介词。引入数词之后，文本编辑命令的语法就升级成了下面这样：

动词 介词/数词 名词
下面是几个例子：

c3w  ### 修改三个单词：change three words
d2w  ### 删除两个单词：delete two words
另外，数词也可以修饰动词，表示将操作执行 n 次。于是，我们又有了下面的语法：

数词 动词 名词
请看示例：

2dw ### 两次删除单词（等价于删除两个单词）: twice delete word
3x  ### 三次删除字符（等价于删除三个字符）：three times delete character
组词为句
有了这些基本的语言元素，我们就可以着手构造一些简单的命令了。文本编辑命令的基本语法如下：

动词 介词 名词
下面是一些例子（如果熟悉了上面的概念，你将会看到这些例子非常容易理解），请亲自在 Vim 中试验一番。

dip ### 删除一个段落: delete inside paragraph
vis ### 选取一个句子: visual select inside sentence
ciw ### 修改一个单词: change inside word
caw ### 修改一个单词: change around word
dtx ### 删除文本直到字符“x”（不包括字符“x”）: delete to x
dfx ### 删除文本直到字符“x”（包括字符“x”）: delete forward x
常用快捷键
这里的快捷键是我配置好的可用的。

;fl ### 换出菜单列表
nw  ### 窗口切换
;lw ### 跳转至右方的窗口
;hw ### 跳转至左方的窗口
;kw ### 跳转至上方的子窗口
;jw ### 跳转至下方的子窗口
 
 
### 可以直接在Tab之间切换。
gt ### 后一个Tab标签
gT ### 前一个Tab标签
;q ### 关闭一个标签
 
ctrl-f ### 下一页 f 就是`forword` 
ctrl-b ### 上一页 b 就是`backward`  
 
;t ### 通过搜索文件打开文件
 
### 快速文本内定位
;;b ### 光标前代码定位
;;e ### 光标后代码定位
;;f ### 光标后代码定位 <搜索自负> 出现定位信息
;;F ### 光标前代码定位 <搜索自负> 出现定位信息
 
;ilt ### 设置显示／隐藏标签列表子窗口(函数列表)的快捷键。速记：identifier list by tag
 
0   ### 行首
$   ### 行尾
 
:r ~/git/R.js ### 将文件内容导入到该文件中
:!which ls  ### 找命令不推出vim运行命令
:!date      ### 查看编辑时间
:r !date    ### 将当前编辑时间导入当前文本光标所在行
 
U ### 选中 - 变大写 
u ### 选中 - 变小写
~ ### 选中 - 变大写变小写，小写变大写
 
### 列选中编辑
Ctrl+v   ### 进入选中模式，`hjkl`方向键选择片区
Shift＋i ### 进入列选择批量编辑
 
;cc ### 代码注释"//"
;cm ### 代码段落注释"/**/"
;ci ### 注释相反，注释的取消注释，没注释的注释
;cs ### 段落注释，注释每行前面加"*"
;c$ ### 光标开始到行结束的位置注释
;cA ### 在行尾部添加注释符"//"
;cu ### 取消代码注释
 
;sp ### 选中搜索 - 文本中选中关键字
    ### normal模式下 选中搜索 - 文本中选中关键字
;sl ### 选中搜索 - 结果列表
 
### 多光标编辑
Shift+n ### 选中下一个相同字符
Shift+k ### 跳过当前选中的字符
 
za ### 单个代码折叠
zM ### 折叠左右代码
zR ### 所有代码折叠取消
 
;i  ### 开/关缩进可视化
>   ### 代码锁进 - 选中摁尖括号
<   ### 代码锁进 - 选中摁尖括号
 
:1,24s/header/www/g  ### 第1到24行将header替换成www
 
<c-z>  ### 退出Vim
基础使用
inoremap (Insert Mode)就只在插入(insert)模式下生效

vnoremap (Visual Mode)只在visual模式下生效

nnoremap (Normal Mode)就在normal模式下(狂按esc后的模式)生效

快捷键<c-y>, 表示(Ctrly,)

快捷键<S-n> 表示(Shiftn)

快捷键通配符
快捷键通配符 <leader> 相当于是一个通用的命令符，默认好像是\，你可以在.vimrc中将他改为任意一个按键，在我们这个配置我改为了冒号;

" 定义快捷键的前缀，即 <Leader>
let mapleader=";"
插入命令
a ### → 在光标所在字符后插入  
A ### → 在光标所在字符尾插入  
i ### → 在光标所在字符前插入  
I ### → 在光标所在行行首插入  
o ### → 在光标下插入新行  
O ### → 在光标上插入新行  
删除命令
x   ### → 删除关闭所在处字符  
nx  ### → 删除关闭所在处n个字符  
dd  ### → 删除光标所在行，
ndd ### → 删除n行  
dG  ### → 删除光标所在行到文件末尾内容  
D   ### → 删除光标所在处到行尾内容  
:n1,n2d ### → 删除指定范围的行 如：1,2d  
定位命令
:set number   ###→ 设置行号 简写set nu  
:set nonu   ###→ 取消行号  
gg  ###→ 到第一行  
G   ###→ 到最后一行  
nG  ###→ 到第n行  
:n  ###→ 到第n行  
S   ###→ 移至行尾  
0   ###→ 移至行尾  
hjkl ###→ 前下上后  
 
w   ###→ 到下一个单词的开头  
b   ###→ 与w相反  
e   ###→ 到下一个单词的结尾。  
ge  ###→ 与e相反  
 
0   ###→ 到行头  
^   ###→ 到本行的第一个非blank字符  
$   ###→ 到行尾  
g_  ###→ 到本行最后一个不是blank字符的位置。  
fa  ###→ 到下一个为a的字符处，你也可以fs到下一个为s的字符。  
t,  ###→ 到逗号前的第一个字符。逗号可以变成其它字符。  
3fa ###→ 在当前行查找第三个出现的a。  
F 和 T → 和 f 和 t 一样，只不过是相反方向。  
 
zz ### 将当前行置于屏幕中间（不是转载…）  
zt ### 将当前行置于屏幕顶端（不是猪头~）  
zb ### 底端啦~  
复制剪切
yy 和 p 的组合键，或者 dd 和 p 的组合键

yy    ### → 复制当前行  
nyy   ### → 复制当前行以下n行  
dd    ### → 剪切当前行  
ndd   ### → 剪切当前行以下n 行  
p、P  ### → 粘贴在当前光标所在行或行上  
2dd   ### → 删除2行  
3p    ### → 粘贴文本3次  
多光标编辑
借助 vim-multiple-cursors 实现多光标编辑功能。首先选中一个单词，然后使用快捷键Shift+n，就会选中下一个一模一样的字符，Shift+k跳过选中，然后你可以进行编辑了。默认这个插件快捷键是Ctrl+n，可能会冲突，单在我这里没有冲突，操作Shift+n快捷键更舒服，你可以配置自己的快捷键

let g:multi_cursor_next_key='<S-n>'
let g:multi_cursor_skip_key='<S-k>'
简单排版
:ce(nter)  ### 居中显示光标所在行
:ri(ght)   ### 靠右显示光标所在行
:le(ft)    ### 靠左显示光标所在行
J          ### 将光标所在下一行合并到光标所在行
 
>>         ### 光标所在行增加缩进(一个tab)
<<         ### 光标所在行减少缩进(一个tab)
 
n>>        ### 光标所在行开始的n行增加缩进
n<<        ### 光标所在行开始的n行减少缩进
刷新重载打开的文件
:e  ### 刷新当前文件
:e! ### 强制刷新当前文件
保存退出
:w new_filename     ### → 保存为指定文件  
:w   ### → 保存修改  
:wq  ### → 保存修改并推出  
ZZ   ### → 快捷键，保存修改并推出  
:q!  ### → 不保存修改推出  
:wq! ### → 保存修改并推出（文件所有者，root权限的用户）  
整页翻页
ctrl-f ### 下一页 f 就是`forword` 
ctrl-b ### 上一页 b 就是`backward`  
替换
替换取消
r ### → 取代关闭所在处字符  
R ### → 从光标所在处开始替换字符，摁ESC结束  
u ### → 取消上一步操作  
ctrl + r ### → 返回上一步  
快捷替换
可视化模式下选中其中一个，接着键入 ctrl-n，你会发现第二个该字符串也被选中了，持续键入 ctrl-n，你可以选中所有相同的字符串，把这个功能与 ctrlsf 结合

精确替换
vim 有强大的内容替换命令，进行内容替换操作时，注意：如何指定替换文件范围、是否整词匹配、是否逐一确认后再替换。

:[range]s/{pattern}/{string}/[flags]
如果在当前文件内替换，[range] 不用指定，默认就在当前文件内；

如果在当前选中区域，[range] 也不用指定，在你键入替换命令时，vim 自动将生成如下命令：:'<,'>s/{pattern}/{string}/[flags]

你也可以指定行范围，如，第三行到第五行：:3,5s/{pattern}/{string}/[flags]

如果对打开文件进行替换，你需要先通过 :bufdo 命令显式告知 vim 范围，再执行替换；

如果对工程内所有文件进行替换，先 :args **/.cpp */*.h 告知 vim 范围，再执行替换；

替换当前行第一个 vivian/ 为 sky/，### 作为分隔符 :s ###vivian/###sky/###

:%s/vivian/sky/g（等同于 :g/vivian/s//sky/g） 替换每一行中所有 vivian 为 sky

:n,$s/vivian/sky/g 替换第 n 行开始到最后一行中每一行所有 vivian 为 sky

:21,27s/^/###/g 行首替换###替换（增加）掉
:ab mymail asdf@qq.com 输入mymail 摁下空格自动替换成asdf@qq.com

开关注释
;cc，注释当前选中文本，如果选中的是整行则在每行首添加 //，如果选中一行的部分内容则在选中部分前后添加分别 /**/；

;cu，取消选中文本块的注释。

工程文件菜单
自定义快捷键

;fl          ### 显示文件菜单 file list
自带快捷键

shift+i      ### 显示/隐藏隐藏文件 
t       ### 在新 Tab 中打开选中文件/书签，并跳到新 Tab
T       ### 在新 Tab 中打开选中文件/书签，但不跳到新 Tab
i       ### split 一个新窗口打开选中文件，并跳到该窗口
gi      ### split 一个新窗口打开选中文件，但不跳到该窗口
s       ### vsplit 一个新窗口打开选中文件，并跳到该窗口
gs      ### vsplit 一个新 窗口打开选中文件，但不跳到该窗口
 
ctrl + w + h    ### 光标 focus 左侧树形目录
ctrl + w + l    ### 光标 focus 右侧文件显示窗口
ctrl + w + w    ### 光标自动在左右侧窗口切换
ctrl + w + r    ### 移动当前窗口的布局位置
o       ### 在已有窗口中打开文件、目录或书签，并跳到该窗口
go      ### 在已有窗口 中打开文件、目录或书签，但不跳到该窗口
 
!       ### 执行当前文件
O       ### 递归打开选中 结点下的所有目录
x       ### 合拢选中结点的父目录
X       ### 递归 合拢选中结点下的所有目录
e       ### Edit the current dif
 
双击    相当于 NERDTree-o
中键    对文件相当于 NERDTree-i，对目录相当于 NERDTree-e
 
D       ### 删除当前书签
###
P       ### 跳到根结点
p       ### 跳到父结点
K       ### 跳到当前目录下同级的第一个结点
J       ### 跳到当前目录下同级的最后一个结点
k       ### 跳到当前目录下同级的前一个结点
j       ### 跳到当前目录下同级的后一个结点
 
C       ### 将选中目录或选中文件的父目录设为根结点
u       ### 将当前根结点的父目录设为根目录，并变成合拢原根结点
U       ### 将当前根结点的父目录设为根目录，但保持展开原根结点
r       ### 递归刷新选中目录
R       ### 递归刷新根结点
m       ### 显示文件系统菜单
cd      ### 将 CWD 设为选中目录
 
I       ### 切换是否显示隐藏文件
f       ### 切换是否使用文件过滤器
F       ### 切换是否显示文件
B       ### 切换是否显示书签
###
q       ### 关闭 NerdTree 窗口
?       ### 切换是否显示 Quick Help
切割窗口
:new      ### 水平切割窗口
:split    ### 水平切割窗口(或者直接输入   :sp  也可以)
:vsplit   ### 垂直切割( 也可以  :vs  )
Tab操作
多tab窗口拆分
:tabnew [++opt选项] ［＋cmd］ 文件            ###建立对指定文件新的tab
:tabc      ###关闭当前的tab
:tabo      ###关闭所有其他的tab
:tabs      ###查看所有打开的tab
:tabp      ###前一个
:tabn      ###后一个
tab切换
### 下面为自定义快捷键
tnew ###新建tab
tn ###后一个 tab
tp ###前一个 tab
 
### 窗口切换
nw
 
### 标准模式下：
gt , gT ###可以直接在tab之间切换。
 
### 还有很多他命令， 看官大人自己， :help table 吧。
Ctrl+ww ### 移动到下一个窗口
### 或者 先按组合键ctrl+w ，然后都松开，然后通过j/k/h/l(等于vim移动的方向键) 来移动大哦哦左/上/下/右的窗口
Ctrl+wj ###移动到下方的窗口
Ctrl+wk ###移动到上方的窗口
HTML操作
便捷操作得益于插件Emmet.vim。键入 div>p###foo$*3>a 然后按快捷键 <c-y>, – 表示 <Ctrl-y> 后再按逗号【Ctrly,】。

按大写的 V 进入 Vim 可视模式，行选取上面三行内容，然后按键 <c-y>,，这时 Vim 的命令行会提示 Tags:，键入ul>li*，然后按 Enter。

<ctrl+y>d ### 根据光标位置选中整个标签  
<ctrl+y>D ### 根据光标位置选中整个标签内容  
<ctrl-y>n ### 跳转到下一个编辑点  
<ctrl-y>N ### 跳转到上一个编辑点  
<ctrl-y>i ### 更新图片大小  
<ctrl-y>m ### 合并成一行  
<ctrl-y>k ### 移除标签对  
<ctrl-y>j ### 分割/合并标签  
<ctrl-y>/ ### 切换注释  
<ctrl-y>a ### 从 URL 地址生成锚  
<ctrl-y>A ### 从 URL 地址生成引用文本  
代码片段补全
让vim 自动完成相同的代码片断，比如 if-else、switch。UltiSnips 这个插件可以帮助我们完成这项艰巨的工作。UltiSnips 有一套自己的代码模板语法规则，如下：

snippet if "if statement" i
if (${1:/* condition */}) { 
    ${2:TODO} 
} 
endsnippet
新版 UltiSnips 并未自带预定义的代码模板，你可以从 honza/vim-snippets 获取各类语言丰富的代码模板，这种模版我将它存放到 ~/.vim/mysnippets/ 目录里面，然后在配置中指定名字，同时修改出发快捷键，因为默认的快捷键与YCM插件冲突，需要在配置中更改。如下：

let g:UltiSnipsSnippetDirectories=["mysnippets"] " 配置目录
let g:UltiSnipsExpandTrigger="<leader><tab>"     " 配置快捷键
let g:UltiSnipsJumpForwardTrigger="<leader><tab>"    " 配向前跳转快捷键
let g:UltiSnipsJumpBackwardTrigger="<leader><s-tab>" " 配向后跳转快捷键
搜索查找
文件搜索
搜索有两个插件可以使用 wincent/command-t 和 junegunn/fzf，fzf没有下载下来，这里在使用 command-t ，使用的时候记得，进入目录 cd ~/.vim/plugged/command-t 运行 rake make。

;t ### 启动搜索文件
搜索文本内容
dyng/ctrlsf.vim，在插件完成安装之后，需要安装另外的工具，才能运行

brew install ripgrep
 
### 上面安装好了之后，在.vimrc中配置下面内容
### 快捷键速记法：search in project
let g:ctrlsf_ackprg = 'rg' 
### 设置快捷键
nnoremap <Leader>sp :CtrlSF<CR>
### 选中搜索 - 文本中选中关键字
vmap     <Leader>sp <Plug>CtrlSFVwordPath
### 选中搜索 - 结果列表
vmap     <Leader>sl <Plug>CtrlSFQuickfixVwordPath
基本使用方法

;sp  ### 搜索快捷键
:CtrlSF pattern dir  ### 如果后面不带 dir 则默认是 . 当前目录搜索 
### 使用 j k h l 浏览CtrlSP窗口  使用 Ctrl + j/k 在匹配项中跳转。
### 使用 q 则退出 CtrlSP窗口
### 使用 p 
基本搜索，这种搜索不需要依赖任何插件，输入 / 再输入需要搜索的内容，摁 Enter 键，将会高亮所有搜索的内容，在英文状态下摁 n 字母键向下查找

/搜索内容
 
### 切换 向上和向下搜索
### 输入 / 摁 Enter键，再摁 n 字母键向，下查找
### 输入 ? 摁 Enter键，再摁 n 字母键向，上查找
快速移动
Lokaltog/vim-easymotion 把满足条件的位置用 [;A~Za~z] 间的标签字符标出来，找到你想去的位置再键入对应标签字符即可快速到达。

;;b ### 光标前代码定位
;;e ### 光标后代码定位
;;f ### 光标后代码定位 <搜索自负> 出现定位信息
;;F ### 光标前代码定位 <搜索自负> 出现定位信息
插件列表
这里面所有的插件，并不是都放到了我的 .vimrc 文件中 .vimrc 配置文件中，是我个人喜欢并且习惯的配置。

插件管理工具
junegunn/vim-plug

VundleVim/Vundle.vim

主题风格
vim-colors-solarized 主题风格素雅 solarized

molokai 主题风格多彩 molokai

phd 主题风格复古 phd

使用界面
Mango A nice color scheme

VimAirline 美化状态栏偏好设置

vim-powerline 美化状态栏

vim-airline 美化状态栏和配置

vim-airline-themes airline主题

管理项目
NERDTree Manage your project files

VimFugitive Git 集成

VimGitGutter Git 集成，强烈推荐！

EditorconfigVim Shared coding conventions

command-t 文件搜索

vim-signature 书签可视化的插件

BOOKMARKS--Mark-and-Highlight-Full-Lines 它可以让书签行高亮

tagbar 方法地图导航

indexer.tar.gz 自动生成标签并引入

DfrankUtil 上面插件，依赖这个插件

vimprj 上面插件，依赖这个插件

ctrlsf.vim 上下文插件，例如搜素到关键字，中间缩略，展示一段上下文

vim-multiple-cursors 多光标编辑功能

gen_tags.vim 生成，加载，更新ctags/gtags文件。

代码书写
NERDCommenter 注释更容易

DrawIt ASCII art 风格的注释

VimTrailingWhitespace 突出尾随空格

Syntastic 语法检查

VimEasyAlign 调整部分代码

VimMultipleCursors Write on multiple lines easily

VimJsBeautify Reformat JavaScript, HTML and JSON files

VimYankStack Iterate over yanked stack on paste

VimSurround Quoting and parenthesizing

YouCompleteMe 键而全的、支持模糊搜索的、高速补全的插件

VimForTern Smart JavaScript autocompletion

VimNode Navigate through node.js code/modules

VimLint Linter used by syntastic for VimL

VimLParser VimL parser (required by VimLint)

emmet-vim 提高HTML和CSS的工作流

vim-cpp-enhanced-highlight C++ 语法高亮支持

vim-indent-guides 相同缩进的代码关联起来

vim-fswitch 接口文件（MyClass.h）与实现文件（MyClass.cpp）快捷切换的插件

MiniBufExplorer 显示多个 buffer 对应的 window

wildfire.vim 快捷键选中 <>、[]、{} 中间的内容

gundo.vim 让你有机会撤销最近一步或多步操作

vim-easymotion 快速移动，两次 <leader> 作为前缀键

Shougo/neocomplete.vim 强大的自动补全插件

vim-instant-markdown 编辑 markdown 文档，自动开启 firefox 为你显示 markdown 最终效果

fcitx.vim 中/英输入平滑切换

othree/xml.vim 中/提供快速编写xml/html的能力，如标签自动闭合等

pangloss/vim-javascript 提供js代码的智能缩进，仅使用了他的indent功能

代码阅读
语法高亮

vim-polyglot 支持常见的语法高亮

VimJson JSON 高亮和隐藏引号

vim-jsx JSX语法高亮

YaJS JavaScript 语法 (ES5 and ES6)

vim-css3-syntax CSS3 高亮，包括stylus,Less,Sass

vim-css-color css高亮颜色

gko/vim-coloresque css高亮颜色

ScssSyntax SCSS syntax

HTML5 HTML5 syntax

Stylus Stylus 代码高亮

JavaScriptLibrariesSyntax 语法高亮的知名的JS库

ultisnips 模板补全插件

vim-protodef 根据类声明自动生成类实现的代码框架

错误处理
YouCompleteMe unavailable: dlopen(/usr/local/Cellar/python/2.7.13/Frameworks/Python.framework/Versions/2.7/lib/python2.7/lib-dynload/_io.so, 2): Symbol not found:
__PyCodecInfo_GetIncrementalDecoder
  Referenced from: /usr/local/Cellar/python/2.7.13/Frameworks/Python.framework/Versions/2.7/lib/python2.7/lib-dynload/_io.so
  Expected in: flat namespace
 in /usr/local/Cellar/python/2.7.13/Frameworks/Python.framework/Versions/2.7/lib/python2.7/lib-dynload/_io.so
Press ENTER or type command to continue
参考资料
vim 大冒险：在游戏中学习 vim

VimScript学会如何自定义Vim编辑器

一起来说 Vim 语

css-color stopped working after updating Vim to 7.4

其它人的vimrc配置
luofei614/vim-plug

yangyangwithgnu/use_vim_as_ide

