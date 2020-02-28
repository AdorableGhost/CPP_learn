<div style="background-color:#ffee">

# MarkDown 小知识

<!-- TOC -->

- [MarkDown 小知识](#markdown-%e5%b0%8f%e7%9f%a5%e8%af%86)
  - [注释](#%e6%b3%a8%e9%87%8a)
  - [注记](#%e6%b3%a8%e8%ae%b0)
  - [锚点](#%e9%94%9a%e7%82%b9)
  - [注脚](#%e6%b3%a8%e8%84%9a)
  - [使用LaTex数学公式](#%e4%bd%bf%e7%94%a8latex%e6%95%b0%e5%ad%a6%e5%85%ac%e5%bc%8f)

<!-- /TOC -->


## 注释


  ```
[comment]: <> (This is a comment, it will not be included)
[comment]: <> (in  the output file unless you use it in)
[comment]: <> (a reference style link.)
[//]: <> (This is also a comment.)
[//]: # (This may be the most platform independent comment)
  ```

  ## 注记
  - 在被引用的文本前加上>符号，以及一个空格就可以了，如果只输入了一个>符号会产生一个空白的引用。
  - 例子：
    > - lalalla ..这是一个注记

- Tips:
  - 可以引用其他元素
  - 可以嵌套

## 锚点
- 锚点其实就是页内超链接。比如我这里写下一个锚点，点击回到目录，就能跳转到目录。 在目录中点击这一节，就能跳过来。

- 注意：在简书中使用锚点时，点击会打开一个新的当前页面，虽然锚点用的不是很舒服，但是可以用注脚实现这个功能。

- 语法说明：
  -  在你准备跳转到的指定标题后插入锚点{#标记}，然后在文档的其它地方写上连接到锚点的链接。

## 注脚
- 语法说明：
  - 在需要添加注脚的文字后加上脚注名字[^注脚名字],称为加注。 然后在文本的任意位置(一般在最后)添加脚注，脚注前必须有对应的脚注名字。

## 使用LaTex数学公式

1. 行内公式：使用两个”$”符号引用公式:

   - ``` $公式$ ```

2. 行间公式：使用两对“$$”符号引用公式：

   - ```  $$公式$$ ```

输入$\sqrt{x^{2}}$
显示结果是x2−−√
具体可以参考 markdown编辑器使用LaTex数学公式（https://link.jianshu.com/?t=http%3A%2F%2Fblog.csdn.net%2Ftestcs_dn%2Farticle%2Fdetails%2F44229085）

latex数学符号详见：常用数学符号的 LaTeX 表示方法

<div id="article_content" class="article_content clearfix">
            <link rel="stylesheet" href="https://csdnimg.cn/release/phoenix/template/css/ck_htmledit_views-833878f763.css">
                            <div id="content_views" class="markdown_views prism-atom-one-dark">
                    <!-- flowchart 箭头图标 勿删 -->
                    <svg xmlns="http://www.w3.org/2000/svg" style="display: none;">
                        <path stroke-linecap="round" d="M5,0 0,2.5 5,5z" id="raphael-marker-block" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></path>
                    </svg>
                                            <p>转自<a href="https://mp.weixin.qq.com/s?__biz=MzIwMzYwMTk1NA==&amp;mid=2247489234&amp;idx=1&amp;sn=c6de4582a1400af22e0908f05a8870bc" rel="nofollow">码个蛋</a>公众号</p>

<p><font size="5"><span id="00">目录</span></font></p>

<p></p><div class="toc"><div class="toc">
<ul>
<li><ul>
<li><a href="#1-快捷键" rel="nofollow" target="_self">1. 快捷键</a></li>
<li><a href="#2-基本语法" rel="nofollow" target="_self">2. 基本语法</a><ul>
<li><a href="#21-字体设置斜体粗体删除线" rel="nofollow" target="_self">2.1 字体设置斜体、粗体、删除线</a></li>
<li><a href="#22-分级标题" rel="nofollow" target="_self">2.2 分级标题</a></li>
<li><a href="#23-链接" rel="nofollow" target="_self">2.3 链接</a></li>
<li><a href="#24-分割线" rel="nofollow" target="_self">2.4 分割线</a></li>
<li><a href="#25-代码块" rel="nofollow" target="_self">2.5 代码块</a></li>
<li><a href="#26-引用" rel="nofollow" target="_self">2.6 引用</a></li>
<li><a href="#27-列表" rel="nofollow" target="_self">2.7 列表</a></li>
<li><a href="#28-表格" rel="nofollow" target="_self">2.8 表格</a></li>
</ul>
</li>
<li><a href="#3-常用技巧" rel="nofollow" target="_self">3. 常用技巧</a><ul>
<li><a href="#31-换行" rel="nofollow" target="_self">3.1 换行</a></li>
<li><a href="#32-缩进字符" rel="nofollow" target="_self">3.2 缩进字符</a></li>
<li><a href="#33-特殊符号" rel="nofollow" target="_self">3.3 特殊符号</a></li>
<li><a href="#34-字体字号与颜色" rel="nofollow" target="_self">3.4 字体、字号与颜色</a></li>
<li><a href="#35-链接的高级操作" rel="nofollow" target="_self">3.5 链接的高级操作</a><ul>
<li><a href="#1行内式" rel="nofollow" target="_self">1.行内式</a></li>
<li><a href="#2参考式链接" rel="nofollow" target="_self">2.参考式链接</a></li>
<li><a href="#3内容目录" rel="nofollow" target="_self">3.内容目录</a></li>
<li><a href="#4锚点" rel="nofollow" target="_self">4.锚点</a></li>
<li><a href="#5注脚" rel="nofollow" target="_self">5.注脚</a></li>
</ul>
</li>
<li><a href="#36-背景色" rel="nofollow" target="_self">3.6 背景色</a></li>
<li><a href="#37-emoji表情符号" rel="nofollow" target="_self">3.7 emoji表情符号</a></li>
</ul>
</li>
<li><a href="#4-高端用法" rel="nofollow" target="_self">4. 高端用法</a><ul>
<li><a href="#41-latex数学公式" rel="nofollow" target="_self">4.1 Latex数学公式</a></li>
<li><a href="#42-流程图" rel="nofollow" target="_self">4.2 流程图</a></li>
<li><a href="#43-制作一份待办事宜-todo-列表" rel="nofollow" target="_self">4.3 制作一份待办事宜—-Todo 列表</a></li>
<li><a href="#44-绘制-序列图" rel="nofollow" target="_self">4.4 绘制 序列图</a></li>
<li><a href="#45-绘制-甘特图" rel="nofollow" target="_self">4.5 绘制 甘特图</a></li>
</ul>
</li>
<li><a href="#5-markdown工具" rel="nofollow" target="_self">5. Markdown工具</a></li>
</ul>
</li>
</ul>
</div>
</div>
<p></p>

<p><strong><font size="5">前言</font></strong> <br>
写过博客或者github上面的文档的，应该知道Markdown语法的重要性，不知道的朋友们也别着急，一篇博客轻松搞定Markdown语法。话说这个语法超级简单，一看就会，不信你点进来看看。</p>

<h2 id="1-快捷键"><a name="t0"></a><a name="t0"></a>1. 快捷键</h2>

<p><font size="1"><a href="#00" rel="nofollow" target="_self">跳转到目录</a></font></p>

<div class="table-box"><table>
<thead>
<tr>
  <th>功能</th>
  <th>快捷键</th>
</tr>
</thead>
<tbody><tr>
  <td>加粗</td>
  <td>Ctrl + B</td>
</tr>
<tr>
  <td>斜体</td>
  <td>Ctrl + I</td>
</tr>
<tr>
  <td>引用</td>
  <td>Ctrl + Q</td>
</tr>
<tr>
  <td>插入链接</td>
  <td>Ctrl + L</td>
</tr>
<tr>
  <td>插入代码</td>
  <td>Ctrl + K</td>
</tr>
<tr>
  <td>插入图片</td>
  <td>Ctrl + G</td>
</tr>
<tr>
  <td>提升标题</td>
  <td>Ctrl + H</td>
</tr>
<tr>
  <td>有序列表</td>
  <td>Ctrl + O</td>
</tr>
<tr>
  <td>无序列表</td>
  <td>Ctrl + U</td>
</tr>
<tr>
  <td>横线</td>
  <td>Ctrl + R</td>
</tr>
<tr>
  <td>撤销</td>
  <td>Ctrl + Z</td>
</tr>
<tr>
  <td>重做</td>
  <td>Ctrl + Y</td>
</tr>
</tbody></table></div>


<h2 id="2-基本语法"><a name="t1"></a><a name="t1"></a>2. 基本语法</h2>

<p><font size="1"><a href="#00" rel="nofollow" target="_self">跳转到目录</a></font></p>

<h3 id="21-字体设置斜体粗体删除线"><a name="t2"></a><a name="t2"></a>2.1 字体设置斜体、粗体、删除线</h3>

<p>*这里是文字*<br>_这里是文字_<br>**这里是文字**<br>***这里是文字***<br>~~这里是文字~~<br></p>

<p><img src="https://img-blog.csdn.net/20180802154402427?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3UwMTQwNjE2MzA=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70" alt="这里写图片描述" title=""></p>

<h3 id="22-分级标题"><a name="t3"></a><a name="t3"></a>2.2 分级标题</h3>

<p><font size="1"><a href="#00" rel="nofollow" target="_self">跳转到目录</a></font> <br>
<strong>写法1：</strong></p>

<p># 一级标题## 二级标题### 三级标题#### 四级标题##### 五级标题###### 六级标题 &nbsp;这个写法和 **文字**效果是一样的</p>

<p><img src="https://img-blog.csdn.net/2018080215454373?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3UwMTQwNjE2MzA=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70" alt="这里写图片描述" title=""></p>

<p><strong>写法2：</strong> <br>
</p><section class=""><section class=""><section class=""><p>这是一个一级标题<br>============================<br><br>或者<br><br>二级标题<br>- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - <br></p></section></section></section> <br>
<img src="https://img-blog.csdn.net/20180802154915835?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3UwMTQwNjE2MzA=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70" alt="这里写图片描述" title=""><p></p>

<h3 id="23-链接"><a name="t4"></a><a name="t4"></a>2.3 链接</h3>

<p><font size="1"><a href="#00" rel="nofollow" target="_self">跳转到目录</a></font> <br>
（1）插入本地图片链接 <br>
语法规则，有两种写法： <br>
<img src="https://img-blog.csdn.net/20180802155057285?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3UwMTQwNjE2MzA=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70" alt="这里写图片描述" title=""> <br>
注意：这个图片描述可以不写。</p>

<p>示例图如下： <br>
<img src="https://img-blog.csdn.net/20180802155239626?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3UwMTQwNjE2MzA=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70" alt="这里写图片描述" title=""></p>

<p>（2）插入互联网上图片 <br>
语法规则： <br>
<img src="https://img-blog.csdn.net/20180802155336302?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3UwMTQwNjE2MzA=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70" alt="这里写图片描述" title=""> <br>
注意：这个图片描述可以不写。</p>

<p>示例如下： <br>
<img src="https://img-blog.csdn.net/20180802155413115?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3UwMTQwNjE2MzA=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70" alt="这里写图片描述" title=""> <br>
（3）自动连接 <br>
Markdown 支持以比较简短的自动链接形式来处理网址和电子邮件信箱，只要是用&lt;&gt;包起来， Markdown 就会自动把它转成链接。也可以直接写，也是可以显示成链接形式的 <br>
例如： <br>
<img src="https://img-blog.csdn.net/20180802155459346?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3UwMTQwNjE2MzA=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70" alt="这里写图片描述" title=""></p>

<h3 id="24-分割线"><a name="t5"></a><a name="t5"></a>2.4 分割线</h3>

<p><font size="1"><a href="#00" rel="nofollow" target="_self">跳转到目录</a></font> <br>
你可以在一行中用三个以上的星号(*)、减号(-)、底线(_)来建立一个分隔线，行内不能有其他东西。你也可以在星号或是减号中间插入空格。 <br>
<img src="https://img-blog.csdn.net/20180802155556110?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3UwMTQwNjE2MzA=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70" alt="这里写图片描述" title=""></p>

<h3 id="25-代码块"><a name="t6"></a><a name="t6"></a>2.5 代码块</h3>

<p><font size="1"><a href="#00" rel="nofollow" target="_self">跳转到目录</a></font> <br>
对于程序员来说这个功能是必不可少的，插入程序代码的方式有两种，一种是利用缩进(tab), 另一种是利用英文“`”符号（一般在ESC键下方，和~同一个键）包裹代码。</p>

<p>（1）代码块：缩进 4 个空格或是 1 个制表符。效果如下： <br>
<img src="https://img-blog.csdn.net/20180802155701855?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3UwMTQwNjE2MzA=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70" alt="这里写图片描述" title=""> <br>
（2）行内式：如果在一个行内需要引用代码，只要用反引号`引起来就好（一般在ESC键下方，和~同一个键） <br>
<img src="https://img-blog.csdn.net/20180802155907712?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3UwMTQwNjE2MzA=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70" alt="这里写图片描述" title=""></p>

<p>（3）多行代码块与语法高亮：在需要高亮的代码块的前一行及后一行使用三个单反引号“`”包裹，就可以了。 <br>
示例如下： <br>
<img src="https://img-blog.csdn.net/20180802160015673?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3UwMTQwNjE2MzA=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70" alt="这里写图片描述" title=""></p>

<p>（4）代码块里面包含html代码 <br>
在代码区块里面， &amp; 、 &lt; 和 &gt; 会自动转成 HTML 实体，这样的方式让你非常容易使用 Markdown 插入范例用的 HTML 原始码，只需要复制贴上，剩下的 Markdown 都会帮你处理。</p>

<p><strong>注意：简书代码块里不支持html。</strong></p>

<p>示例如下： <br>
<img src="https://img-blog.csdn.net/20180802160155483?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3UwMTQwNjE2MzA=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70" alt="这里写图片描述" title=""></p>

<h3 id="26-引用"><a name="t7"></a><a name="t7"></a>2.6 引用</h3>

<p><font size="1"><a href="#00" rel="nofollow" target="_self">跳转到目录</a></font> <br>
在被引用的文本前加上&gt;符号，以及一个空格就可以了，如果只输入了一个&gt;符号会产生一个空白的引用。</p>

<p>（1）基本使用 <br>
使用如下图所示： <br>
<img src="https://img-blog.csdn.net/20180802160324418?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3UwMTQwNjE2MzA=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70" alt="这里写图片描述" title=""></p>

<p>（2）引用的嵌套使用 <br>
使用如图所示： <br>
<img src="https://img-blog.csdn.net/20180802160343802?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3UwMTQwNjE2MzA=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70" alt="这里写图片描述" title=""> <br>
（3）引用其它要素 <br>
引用的区块内也可以使用其他的 Markdown 语法，包括标题、列表、代码区块等。 <br>
使用如图所示： <br>
<img src="https://img-blog.csdn.net/20180802160421785?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3UwMTQwNjE2MzA=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70" alt="这里写图片描述" title=""></p>

<h3 id="27-列表"><a name="t8"></a><a name="t8"></a>2.7 列表</h3>

<p><font size="1"><a href="#00" rel="nofollow" target="_self">跳转到目录</a></font> <br>
（1）无序列表 <br>
使用 *，+，- 表示无序列表。 <br>
注意：符号后面一定要有一个空格，起到缩进的作用。 <br>
<img src="https://img-blog.csdn.net/2018080216053733?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3UwMTQwNjE2MzA=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70" alt="这里写图片描述" title=""></p>

<p>（2）有序列表 <br>
使用数字和一个英文句点表示有序列表。 <br>
注意：英文句点后面一定要有一个空格，起到缩进的作用。 <br>
<img src="https://img-blog.csdn.net/2018080216061165?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3UwMTQwNjE2MzA=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70" alt="这里写图片描述" title=""></p>

<p>（3）无序列表和有序列表同时使用 <br>
<img src="https://img-blog.csdn.net/20180802160735370?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3UwMTQwNjE2MzA=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70" alt="这里写图片描述" title=""></p>

<p>（4）列表和其它要素混合使用 <br>
列表不光可以单独使用，也可以使用其他的 Markdown 语法，包括标题、引用、代码区块等。</p>

<p><strong>注意事项：</strong></p>

<blockquote>
  <p>（1）加粗效果不能直接用于列表标题里面，但是可以嵌套在列表里面混合使用。 <br>
  （2）列表中包含代码块（前面加2个tab或者8个空格，并且需要空一行，否则不显示）。 <br>
  . <br>
  使用示例如下图： <br>
  <img src="https://img-blog.csdn.net/20180802160851570?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3UwMTQwNjE2MzA=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70" alt="这里写图片描述" title=""></p>
</blockquote>

<p>（5）注意事项 <br>
在使用列表时，只要是数字后面加上英文的点，就会无意间产生列表，比如2017.12.30 这时候想表达的是日期，有些软件把它被误认为是列表。解决方式：在每个点前面加上\就可以了。如下图所示： <br>
<img src="https://img-blog.csdn.net/20180802161039348?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3UwMTQwNjE2MzA=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70" alt="这里写图片描述" title=""></p>

<h3 id="28-表格"><a name="t9"></a><a name="t9"></a>2.8 表格</h3>

<p><font size="1"><a href="#00" rel="nofollow" target="_self">跳转到目录</a></font> <br>
表格的基本写法很简单，就跟表格的形状很相似： <br>
<img src="https://img-blog.csdn.net/20180802161209660?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3UwMTQwNjE2MzA=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70" alt="这里写图片描述" title=""></p>

<p>表格对齐方式：我们可以指定表格单元格的对齐方式，冒号在左边表示左对齐，右边表示有对齐，两边都有表示居中。</p>

<p>如下图所示： <br>
<img src="https://img-blog.csdn.net/20180802161235917?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3UwMTQwNjE2MzA=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70" alt="这里写图片描述" title=""></p>

<h2 id="3-常用技巧"><a name="t10"></a><a name="t10"></a>3. 常用技巧</h2>

<h3 id="31-换行"><a name="t11"></a><a name="t11"></a>3.1 换行</h3>

<p>方法1: 连续两个以上空格+回车 <br>
方法2：使用html语言换行标签：<br></p>

<h3 id="32-缩进字符"><a name="t12"></a><a name="t12"></a>3.2 缩进字符</h3>

<p>不断行的空白格 &nbsp; 或 &nbsp;半角的空格   或  全角的空格   或   <br>
<img src="https://img-blog.csdn.net/20180802162415963?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3UwMTQwNjE2MzA=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70" alt="这里写图片描述" title=""></p>

<h3 id="33-特殊符号"><a name="t13"></a><a name="t13"></a>3.3 特殊符号</h3>

<p>（1）对于 Markdown 中的语法符号，前面加反斜线\即可显示符号本身。</p>

<p>示例如下： <br>
<img src="https://img-blog.csdn.net/20180802162507298?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3UwMTQwNjE2MzA=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70" alt="这里写图片描述" title=""></p>

<p>（2）其他特殊字符，示例如下： <br>
<img src="https://img-blog.csdn.net/20180802162542616?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3UwMTQwNjE2MzA=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70" alt="这里写图片描述" title=""> <br>
想知道字符对应的Unicode码，可以看这个网站：<a href="https://unicode-table.com/cn/" rel="nofollow">https://unicode-table.com/cn/</a></p>

<p><strong>附上几个工具对特殊字符的支持的对比图:</strong> <br>
<img src="https://img-blog.csdn.net/20180802162726962?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3UwMTQwNjE2MzA=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70" alt="这里写图片描述" title=""></p>

<h3 id="34-字体字号与颜色"><a name="t14"></a><a name="t14"></a>3.4 字体、字号与颜色</h3>

<p>Markdown是一种可以使用普通文本编辑器编写的标记语言，通过类似HTML的标记语法，它可以使普通文本内容具有一定的格式。但是它本身是不支持修改字体、字号与颜色等功能的！</p>

<p>CSDN-markdown编辑器是其衍生版本，扩展了Markdown的功能（如表格、脚注、内嵌HTML等等）！对，就是内嵌HTML，接下来要讲的功能就需要使用内嵌HTML的方法来实现。</p>

<p>字体，字号和颜色编辑如下代码 <br>
<img src="https://img-blog.csdn.net/20180802162832307?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3UwMTQwNjE2MzA=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70" alt="这里写图片描述" title=""></p>

<p>具体颜色分类及标记请看下表： <br>
<img src="https://img-blog.csdn.net/20180802162907453?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3UwMTQwNjE2MzA=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70" alt="这里写图片描述" title=""></p>

<h3 id="35-链接的高级操作"><a name="t15"></a><a name="t15"></a>3.5 链接的高级操作</h3>

<p>链接的高级操作（这个需要掌握一下，很有用）</p>

<h4 id="1行内式">1.行内式</h4>

<p>这个在上文第二条基本语法的 链接这个小节已经过，这里就不继续讲解了。</p>



<h4 id="2参考式链接">2.参考式链接</h4>

<p>在文档要插入图片的地方写![图片或网址链接][标记]，在文档的最后写上[标记]:图片地址 “标题”。（最后这个”标题”可以不填写）</p>

<p>示例如下： <br>
<img src="https://img-blog.csdn.net/2018080216303854?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3UwMTQwNjE2MzA=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70" alt="这里写图片描述" title=""></p>



<h4 id="3内容目录">3.内容目录</h4>

<p>在段落中填写 [TOC] 以显示全文内容的目录结构。</p>



<h4 id="4锚点">4.锚点</h4>

<p>锚点其实就是页内超链接。比如我这里写下一个锚点，点击回到目录，就能跳转到目录。 在目录中点击这一节，就能跳过来。</p>

<p><strong>注意</strong>：在简书中使用锚点时，点击会打开一个新的当前页面，虽然锚点用的不是很舒服，但是可以用注脚实现这个功能。</p>

<p><strong>语法说明：</strong> <br>
在你准备跳转到的指定标题后插入锚点{#标记}，然后在文档的其它地方写上连接到锚点的链接。</p>

<p>使用如下图所示： <br>
<img src="https://img-blog.csdn.net/20180802163343495?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3UwMTQwNjE2MzA=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70" alt="这里写图片描述" title=""></p>



<h4 id="5注脚">5.注脚</h4>

<p><strong>语法说明：</strong> <br>
在需要添加注脚的文字后加上脚注名字[^注脚名字],称为加注。 然后在文本的任意位置(一般在最后)添加脚注，脚注前必须有对应的脚注名字。</p>

<p>示例如下： <br>
<img src="https://img-blog.csdn.net/20180802163447739?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3UwMTQwNjE2MzA=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70" alt="这里写图片描述" title=""> <br>
注：</p>

<blockquote>
  <ol>
  <li>脚注自动被搬运到最后面，请到文章末尾查看，并且脚注后方的链接可以直接跳转回到加注的地方。</li>
  <li>由于简书不支持锚点，所以可以用注脚实现页面内部的跳转。</li>
  </ol>
</blockquote>



<h3 id="36-背景色"><a name="t16"></a><a name="t16"></a>3.6 背景色</h3>

<p>Markdown本身不支持背景色设置，需要采用内置html的方式实现：借助 table, tr, td 等表格标签的 bgcolor 属性来实现背景色的功能。举例如下：</p>

<p>&lt;table&gt;&lt;tr&gt;&lt;td bgcolor=orange&gt;背景色是：orange&lt;/td&gt;&lt;/tr&gt;&lt;/table&gt;</p>

<p><img src="https://img-blog.csdn.net/20180802164159599?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3UwMTQwNjE2MzA=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70" alt="这里写图片描述" title=""></p>

<h3 id="37-emoji表情符号"><a name="t17"></a><a name="t17"></a>3.7 emoji表情符号</h3>

<p>emoji表情使用:EMOJICODE:的格式，详细列表可见  <br>
<a href="https://www.webpagefx.com/tools/emoji-cheat-sheet/" rel="nofollow">https://www.webpagefx.com/tools/emoji-cheat-sheet/</a></p>

<p>当然现在很多markdown工具或者网站都不支持。</p>

<p>下面列出几个平台的对比：</p>

<div class="table-box"><table>
<thead>
<tr>
  <th>工具或网站</th>
  <th>是否支持emoji表情符号</th>
</tr>
</thead>
<tbody><tr>
  <td>简书</td>
  <td>否</td>
</tr>
<tr>
  <td>MarkDownPad</td>
  <td>否（不知道付费版是否支持）</td>
</tr>
<tr>
  <td>有道云笔记</td>
  <td>否</td>
</tr>
<tr>
  <td>zybuluo.com</td>
  <td>否</td>
</tr>
<tr>
  <td>github</td>
  <td>是</td>
</tr>
</tbody></table></div>


<p><img src="https://img-blog.csdn.net/20180802164508437?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3UwMTQwNjE2MzA=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70" alt="这里写图片描述" title=""></p>

<h2 id="4-高端用法"><a name="t18"></a><a name="t18"></a>4. 高端用法</h2>

<h3 id="41-latex数学公式"><a name="t19"></a><a name="t19"></a>4.1 Latex数学公式</h3>

<p><strong>使用LaTex数学公式</strong></p>

<p>1.行内公式：使用两个”<span>$</span>”符号引用公式:</p>

<p><span>$</span>公式<span>$</span></p>

<p>2.行间公式：使用两对“<span>$</span><span>$</span>”符号引用公式：</p>

<p><span>$</span><span>$</span>公式<span>$</span><span>$</span></p>

<p>输入<span>$</span>\sqrt{x^{2}}<span>$</span> <br>
显示结果是<span class="MathJax_Preview" style="color: inherit; display: none;"></span><span class="MathJax" id="MathJax-Element-2-Frame" tabindex="0" style="position: relative;" data-mathml="<math xmlns=&quot;http://www.w3.org/1998/Math/MathML&quot;><msqrt><msup><mi>x</mi><mrow class=&quot;MJX-TeXAtom-ORD&quot;><mn>2</mn></mrow></msup></msqrt></math>" role="presentation"><nobr aria-hidden="true"><span class="math" id="MathJax-Span-1" style="width: 2.452em; display: inline-block;"><span style="display: inline-block; position: relative; width: 1.952em; height: 0px; font-size: 125%;"><span style="position: absolute; clip: rect(1.252em, 1001.95em, 2.552em, -999.998em); top: -2.298em; left: 0em;"><span class="mrow" id="MathJax-Span-2"><span class="msqrt" id="MathJax-Span-3"><span style="display: inline-block; position: relative; width: 1.952em; height: 0px;"><span style="position: absolute; clip: rect(3.103em, 1001em, 4.152em, -999.998em); top: -3.998em; left: 0.853em;"><span class="mrow" id="MathJax-Span-4"><span class="msubsup" id="MathJax-Span-5"><span style="display: inline-block; position: relative; width: 1.002em; height: 0px;"><span style="position: absolute; clip: rect(3.402em, 1000.5em, 4.152em, -999.998em); top: -3.998em; left: 0em;"><span class="mi" id="MathJax-Span-6" style="font-family: MathJax_Math-italic;">x</span><span style="display: inline-block; width: 0px; height: 4.002em;"></span></span><span style="position: absolute; top: -4.298em; left: 0.552em;"><span class="texatom" id="MathJax-Span-7"><span class="mrow" id="MathJax-Span-8"><span class="mn" id="MathJax-Span-9" style="font-size: 70.7%; font-family: MathJax_Main;">2</span></span></span><span style="display: inline-block; width: 0px; height: 4.002em;"></span></span></span></span></span><span style="display: inline-block; width: 0px; height: 4.002em;"></span></span><span style="position: absolute; clip: rect(3.603em, 1001.1em, 3.902em, -999.998em); top: -4.598em; left: 0.853em;"><span style="display: inline-block; position: relative; width: 1.103em; height: 0px;"><span style="position: absolute; font-family: MathJax_Main; top: -3.998em; left: -0.098em;">−<span style="display: inline-block; width: 0px; height: 4.002em;"></span></span><span style="position: absolute; font-family: MathJax_Main; top: -3.998em; left: 0.403em;">−<span style="display: inline-block; width: 0px; height: 4.002em;"></span></span></span><span style="display: inline-block; width: 0px; height: 4.002em;"></span></span><span style="position: absolute; clip: rect(3.052em, 1000.85em, 4.353em, -999.998em); top: -4.098em; left: 0em;"><span style="font-family: MathJax_Main;">√</span><span style="display: inline-block; width: 0px; height: 4.002em;"></span></span></span></span></span><span style="display: inline-block; width: 0px; height: 2.302em;"></span></span></span><span style="display: inline-block; overflow: hidden; vertical-align: -0.184em; border-left: 0px solid; width: 0px; height: 1.378em;"></span></span></nobr><span class="MJX_Assistive_MathML" role="presentation"><math xmlns="http://www.w3.org/1998/Math/MathML"><msqrt><msup><mi>x</mi><mrow class="MJX-TeXAtom-ORD"><mn>2</mn></mrow></msup></msqrt></math></span></span><script type="math/tex" id="MathJax-Element-2">\sqrt{x^{2}}</script></p>

<p>具体可以参考 markdown编辑器使用LaTex数学公式（<a href="https://link.jianshu.com/?t=http%3A%2F%2Fblog.csdn.net%2Ftestcs_dn%2Farticle%2Fdetails%2F44229085" rel="nofollow">https://link.jianshu.com/?t=http%3A%2F%2Fblog.csdn.net%2Ftestcs_dn%2Farticle%2Fdetails%2F44229085</a>）</p>

<p>latex数学符号详见：<a href="https://www.mohu.org/info/symbols/symbols.htm" rel="nofollow">常用数学符号的 LaTeX 表示方法</a></p>

<h3 id="42-流程图"><a name="t20"></a><a name="t20"></a>4.2 流程图</h3>

<p>这里简单介绍一下流程图的语法，仅作为了解，如下图所示： <br>
<img src="https://img-blog.csdn.net/20180802165820199?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3UwMTQwNjE2MzA=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70" alt="这里写图片描述" title=""></p>

<h3 id="43-制作一份待办事宜-todo-列表"><a name="t21"></a><a name="t21"></a>4.3 制作一份待办事宜—-Todo 列表</h3>

<p><img src="https://img-blog.csdn.net/20180802165859799?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3UwMTQwNjE2MzA=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70" alt="这里写图片描述" title=""></p>

<h3 id="44-绘制-序列图"><a name="t22"></a><a name="t22"></a>4.4 绘制 序列图</h3>

<p><img src="https://img-blog.csdn.net/2018080216592352?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3UwMTQwNjE2MzA=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70" alt="这里写图片描述" title=""></p>

<h3 id="45-绘制-甘特图"><a name="t23"></a><a name="t23"></a>4.5 绘制 甘特图</h3>

<p><img src="https://img-blog.csdn.net/20180802165941601?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3UwMTQwNjE2MzA=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70" alt="这里写图片描述" title=""></p>

<h2 id="5-markdown工具"><a name="t24"></a><a name="t24"></a>5. Markdown工具</h2>

<p>1.markdownpad软件，就是利用markdown语言写笔记的。官网下载地址：<a href="http://markdownpad.com/" rel="nofollow">http://markdownpad.com/</a></p>

<p>软件安装之后的示意图如下图所示： <br>
<img src="https://img-blog.csdn.net/20180802170021581?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3UwMTQwNjE2MzA=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70" alt="这里写图片描述" title=""></p>

<p>2.有道云笔记支持markdownpad语法。官方网址：<a href="http://note.youdao.com/" rel="nofollow">http://note.youdao.com/</a> 它有在线网页版以及PC端可以下载。当然有道云笔记也支持html语法。</p>

<p>网页版使用markdown示例图如下： <br>
<img src="https://img-blog.csdn.net/20180802170102176?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3UwMTQwNjE2MzA=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70" alt="这里写图片描述" title=""></p>

<p>3.在线编辑markdown <a href="https://www.zybuluo.com/mdeditor" rel="nofollow">https://www.zybuluo.com/mdeditor</a></p>

<p>本文参考文章：</p>

<p><a href="http://blog.csdn.net/u010177286/article/details/50358720">http://blog.csdn.net/u010177286/article/details/50358720</a></p>

<p><a href="https://www.zybuluo.com/mdeditor" rel="nofollow">https://www.zybuluo.com/mdeditor</a></p>

<p><a href="http://blog.leanote.com/post/freewalk/Markdown-%E8%AF%AD%E6%B3%95%E6%89%8B%E5%86%8C#title-18" rel="nofollow">http://blog.leanote.com/post/freewalk/Markdown-%E8%AF%AD%E6%B3%95%E6%89%8B%E5%86%8C#title-18</a></p>                                    </div>
                <link href="https://csdnimg.cn/release/phoenix/mdeditor/markdown_views-b6c3c6d139.css" rel="stylesheet">
                                                <div class="more-toolbox">
                <div class="left-toolbox">
                    <ul class="toolbox-list">
                        
                        <li class="tool-item tool-active is-like "><a href="javascript:;"><svg class="icon" aria-hidden="true">
                            <use xlink:href="#csdnc-thumbsup"></use>
                        </svg><span class="name">点赞</span>
                        <span class="count">126</span>
                        </a></li>
                        <li class="tool-item tool-active is-collection "><a href="javascript:;" data-report-click="{&quot;mod&quot;:&quot;popu_824&quot;}"><svg class="icon" aria-hidden="true">
                            <use xlink:href="#icon-csdnc-Collection-G"></use>
                        </svg><span class="name">收藏</span></a></li>
                        <li class="tool-item tool-active is-share"><a href="javascript:;" data-report-click="{&quot;mod&quot;:&quot;1582594662_002&quot;}"><svg class="icon" aria-hidden="true">
                            <use xlink:href="#icon-csdnc-fenxiang"></use>
                        </svg>分享</a></li>
                        <!--打赏开始-->
                                                <!--打赏结束-->
                                                <li class="tool-item tool-more">
                            <a>
                            <svg t="1575545411852" class="icon" viewBox="0 0 1024 1024" version="1.1" xmlns="http://www.w3.org/2000/svg" p-id="5717" xmlns:xlink="http://www.w3.org/1999/xlink" width="200" height="200"><defs><style type="text/css"></style></defs><path d="M179.176 499.222m-113.245 0a113.245 113.245 0 1 0 226.49 0 113.245 113.245 0 1 0-226.49 0Z" p-id="5718"></path><path d="M509.684 499.222m-113.245 0a113.245 113.245 0 1 0 226.49 0 113.245 113.245 0 1 0-226.49 0Z" p-id="5719"></path><path d="M846.175 499.222m-113.245 0a113.245 113.245 0 1 0 226.49 0 113.245 113.245 0 1 0-226.49 0Z" p-id="5720"></path></svg>
                            </a>
                            <ul class="more-box">
                                <li class="item"><a class="article-report">文章举报</a></li>
                            </ul>
                        </li>
                                            </ul>
                </div>
                            </div>
            <div class="person-messagebox">
                <div class="left-message"><a href="https://blog.csdn.net/u014061630">
                    <img src="https://profile.csdnimg.cn/8/F/A/3_u014061630" class="avatar_pic" username="u014061630">
                                            <img src="https://g.csdnimg.cn/static/user-reg-year/1x/6.png" class="user-years">
                                    </a></div>
                <div class="middle-message">
                                        <div class="title"><span class="tit"><a href="https://blog.csdn.net/u014061630" data-report-click="{&quot;mod&quot;:&quot;popu_379&quot;}" target="_blank">黑暗星球</a></span>
                                            </div>
                    <div class="text"><span>发布了60 篇原创文章</span> · <span>获赞 370</span> · <span>访问量 40万+</span></div>
                </div>
                                <div class="right-message">
                                            <a href="https://im.csdn.net/im/main.html?userName=u014061630" target="_blank" class="btn btn-sm btn-red-hollow bt-button personal-letter">私信
                        </a>
                                                            <a class="btn btn-sm  bt-button personal-watch" data-report-click="{&quot;mod&quot;:&quot;popu_379&quot;}">关注</a>
                                    </div>
                            </div>
                    </div>

                    <div>