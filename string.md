<div class="htmledit_views" id="content_views">
                                            <h2><a name="t0"></a>STL的含义：标准模板库</h2>

<blockquote>
<p><strong>STL的内容：</strong></p>

<ul><li>容器：数据的仓库</li>
	<li>算法：与数据结构相关的算法、通用的算法（和数据结构无关）</li>
</ul><p>注：熟悉常用的算法 sort&nbsp; reverse</p>

<ul><li>迭代器：算法和容器的连接</li>
	<li>适配器：类似于转接线，苹果线要连接安卓线</li>
</ul></blockquote>

<blockquote>
<h3><a name="t1"></a>容器：</h3>

<p>序列式容器（线性结构）</p>

<p style="text-indent:50px;">string：</p>

<p style="text-indent:50px;">array：C11静态顺序表</p>

<p style="text-indent:50px;">vector：动态顺序表</p>

<p style="text-indent:50px;">list：带头节点的双向循环链表</p>

<p style="text-indent:50px;">deque：动态二维数组</p>

<p style="text-indent:50px;">forward_list：带头结点的循环单链表</p>

<p style="text-indent:50px;">stack：栈</p>

<p style="text-indent:50px;">queue：队列</p>
</blockquote>

<blockquote>
<h3><a name="t2"></a>String类：按照类的方式进行动态管理字符串</h3>

<p>底层：是一种顺序表的结构，元素是char类型的字符</p>

<hr><p><strong>string类的常用构造函数：</strong></p>

<ul><li>string&nbsp; str——构造空的string类对象，即空字符串</li>
	<li>string str(str1)——str1 和 str 一样</li>
	<li>string&nbsp; str("ABC")——等价于 str="ABC"</li>
	<li>string&nbsp; str("ABC",strlen)——等价于 "ABC" 存入 str 中，最多存储 strlen 个字节</li>
	<li>string&nbsp; str("ABC",stridx,strlen)——等价于 "ABC" 的stridx 位置，作为字符串开头，存到str中，最多存储 strlen 个字节</li>
	<li>string&nbsp; str(srelen,'A')——存储 strlen 个 'A' 到 str 中</li>
</ul><pre class="has" name="code"><code class="language-cpp hljs"><ol class="hljs-ln"><li><div class="hljs-ln-numbers"><div class="hljs-ln-line hljs-ln-n" data-line-number="1"></div></div><div class="hljs-ln-code"><div class="hljs-ln-line"><span class="hljs-comment">//用法小实例</span></div></div></li><li><div class="hljs-ln-numbers"><div class="hljs-ln-line hljs-ln-n" data-line-number="2"></div></div><div class="hljs-ln-code"><div class="hljs-ln-line"><span class="hljs-meta">#<span class="hljs-meta-keyword">include</span><span class="hljs-meta-string">&lt;iostream&gt;</span></span></div></div></li><li><div class="hljs-ln-numbers"><div class="hljs-ln-line hljs-ln-n" data-line-number="3"></div></div><div class="hljs-ln-code"><div class="hljs-ln-line"><span class="hljs-keyword">using</span> <span class="hljs-keyword">namespace</span> <span class="hljs-built_in">std</span>;</div></div></li><li><div class="hljs-ln-numbers"><div class="hljs-ln-line hljs-ln-n" data-line-number="4"></div></div><div class="hljs-ln-code"><div class="hljs-ln-line"> </div></div></li><li><div class="hljs-ln-numbers"><div class="hljs-ln-line hljs-ln-n" data-line-number="5"></div></div><div class="hljs-ln-code"><div class="hljs-ln-line"><span class="hljs-function"><span class="hljs-keyword">int</span> <span class="hljs-title">main</span><span class="hljs-params">()</span> </span>{</div></div></li><li><div class="hljs-ln-numbers"><div class="hljs-ln-line hljs-ln-n" data-line-number="6"></div></div><div class="hljs-ln-code"><div class="hljs-ln-line">	<span class="hljs-built_in">string</span> s1;   <span class="hljs-comment">//空字符串</span></div></div></li><li><div class="hljs-ln-numbers"><div class="hljs-ln-line hljs-ln-n" data-line-number="7"></div></div><div class="hljs-ln-code"><div class="hljs-ln-line">	<span class="hljs-function"><span class="hljs-built_in">string</span> <span class="hljs-title">s2</span><span class="hljs-params">(<span class="hljs-number">10</span>,<span class="hljs-string">'$'</span>)</span></span>;  <span class="hljs-comment">//十个 $</span></div></div></li><li><div class="hljs-ln-numbers"><div class="hljs-ln-line hljs-ln-n" data-line-number="8"></div></div><div class="hljs-ln-code"><div class="hljs-ln-line">	<span class="hljs-function"><span class="hljs-built_in">string</span> <span class="hljs-title">s3</span><span class="hljs-params">(<span class="hljs-string">"hello world"</span>)</span></span>;  <span class="hljs-comment">//hello word</span></div></div></li><li><div class="hljs-ln-numbers"><div class="hljs-ln-line hljs-ln-n" data-line-number="9"></div></div><div class="hljs-ln-code"><div class="hljs-ln-line"> </div></div></li><li><div class="hljs-ln-numbers"><div class="hljs-ln-line hljs-ln-n" data-line-number="10"></div></div><div class="hljs-ln-code"><div class="hljs-ln-line">	<span class="hljs-built_in">cout</span> &lt;&lt; s3.size &lt;&lt; <span class="hljs-built_in">endl</span>;</div></div></li><li><div class="hljs-ln-numbers"><div class="hljs-ln-line hljs-ln-n" data-line-number="11"></div></div><div class="hljs-ln-code"><div class="hljs-ln-line">	<span class="hljs-built_in">cout</span> &lt;&lt; s3.length &lt;&lt; <span class="hljs-built_in">endl</span>; <span class="hljs-comment">//都是求字符串长度  11</span></div></div></li><li><div class="hljs-ln-numbers"><div class="hljs-ln-line hljs-ln-n" data-line-number="12"></div></div><div class="hljs-ln-code"><div class="hljs-ln-line">	<span class="hljs-built_in">cout</span> &lt;&lt; s3.capacity &lt;&lt; <span class="hljs-built_in">endl</span>; <span class="hljs-comment">//求s3的容量</span></div></div></li><li><div class="hljs-ln-numbers"><div class="hljs-ln-line hljs-ln-n" data-line-number="13"></div></div><div class="hljs-ln-code"><div class="hljs-ln-line"> </div></div></li><li><div class="hljs-ln-numbers"><div class="hljs-ln-line hljs-ln-n" data-line-number="14"></div></div><div class="hljs-ln-code"><div class="hljs-ln-line">	s3.clear();  <span class="hljs-comment">//清空</span></div></div></li><li><div class="hljs-ln-numbers"><div class="hljs-ln-line hljs-ln-n" data-line-number="15"></div></div><div class="hljs-ln-code"><div class="hljs-ln-line">	<span class="hljs-function"><span class="hljs-built_in">string</span> <span class="hljs-title">s4</span><span class="hljs-params">(s3)</span></span>; <span class="hljs-comment">//s4 和 s3一样</span></div></div></li><li><div class="hljs-ln-numbers"><div class="hljs-ln-line hljs-ln-n" data-line-number="16"></div></div><div class="hljs-ln-code"><div class="hljs-ln-line">}</div></div></li></ol></code><div class="hljs-button signin" data-title="登录后复制" onclick="hljs.signin(event)"></div></pre>

<p><strong>注：使用string类时，必须包含头文件以及using namespace std。</strong></p>

<hr><h3><a name="t3"></a>string常用成员函数：</h3>

<p><strong>assign函数：</strong></p>

<ul><li>str<strong>.</strong>assign("ABC")——清空字符串，并设置为 "ABC"</li>
	<li>str<strong>.</strong>assign("ABC",2)——清空字符串，并设置为"AB"，保留两个字符</li>
	<li>str<strong>.</strong>assign("ABC",1,1)——清空字符串，设置为 "ABC" 中的从 位置1 开始，保留 1个 字符</li>
	<li>str<strong>.</strong>assign(5，'A')——清空字符串，然后字符串设置为 5个 'A'</li>
</ul><hr><ul><li>str<strong>.</strong>length()——求字符串长度</li>
	<li>str<strong>.</strong>size()——和 length() 一样</li>
	<li>str<strong>.</strong>capacity()——获取容量，包含了不用增加内存就能使用的字符数</li>
	<li>str<strong>.reasize</strong>(10)——设置当前 str 的大小为10，若大小大与当前串的长度，\0 来填充</li>
	<li>str<strong>.reasize</strong>(10,char c)——设置当前 str 的大小为10，若大小大与当前串的长度，字0符c 来填充</li>
	<li>str.reserve(10)——设置str的容量 10，不会填充数据</li>
	<li>str.swap(str1)——交换<strong> str1 </strong>和<strong> str</strong> 的字符串</li>
	<li>str.push_back('A')——在str末尾添加一个字符&nbsp; 'A' ，参数必须是字符形式</li>
	<li>str.append("ABC")——在str末尾添加一个字符串 "ABC"，参数必须是字符串形式</li>
</ul><hr><p><strong>insert函数方法：&nbsp;</strong></p>

<ul><li>str.insert(2,3,'A')——在str下标为2的位置添加 3个 字符'A'</li>
	<li>str.insert(2,"ABC")——在str下标为2的位置添加 字符串 "ABC"</li>
	<li>str.insert(2,"ABC",1)——在str下标为2的位置添加 字符串 "ABC" 中 1个 字符</li>
	<li>str.insert(2,"ABC",1,<strong>1</strong>)——在str下标为2的位置添加 字符串 "ABC" 中从位置 1 开始的 1 个字符</li>
</ul><p>注：上个函数参数中加粗的 <strong>1 </strong>，可以是&nbsp;<strong>string::npos</strong>，这时候最大值，从 位置1 开始后面的全部字符</p>

<ul><li>str.insert( iterator pos, size_type count, CharT ch )——在 str 中，迭代器指向的 pos位置 插入 count个 字符 ch</li>
</ul><p>s4.insert(++str1.begin(),2,'a'); &nbsp; &nbsp; &nbsp;&nbsp; 结果：s4：ABCD &nbsp;&nbsp; -&gt; &nbsp;&nbsp; AaaBCD</p>

<ul><li>str.insert( iterator pos, InputIt first, InputIt last )——在 str 中，pos位置 插入 str1 的 开始位置 到 结束为止</li>
</ul><p>s4.insert(s4.begin(),str1.begin(),str1.end()); &nbsp; &nbsp; &nbsp; &nbsp;结果：s4：ABCD&nbsp; str1：abc &nbsp; -&gt; &nbsp;&nbsp; abcABCD</p>

<hr><ul><li>str.erase(2)——删除 下标2 的位置开始，之后的全删除</li>
	<li>str.erase(2,1)——删除 下标2 的位置开始，之后的 1个 删除</li>
	<li>str.clear()——删除 str 所有</li>
	<li>str.replace(2,4,"abcd")——从 下标2 的位置，替换 4个字节 ，为"abcd"</li>
	<li>str.empty()——判空</li>
</ul><hr><h3><a name="t4"></a><strong>反转相关：</strong></h3>

<p style="text-indent:50px;"><strong>(位于头文件&lt;algorithm&gt;)</strong></p>

<ul><li style="text-indent:0px;">reverse(str.begin(),str.end())——str的开始 到 结束字符反转&nbsp;</li>
</ul><p>reverse(s4.begin,s4.end); &nbsp; &nbsp; &nbsp;&nbsp; 结果：s4：ABCD &nbsp; -&gt; &nbsp;&nbsp; DCBA</p>

<hr><h3><a name="t5"></a><strong>查找相关：</strong></h3>

<p style="text-indent:50px;">查找<strong>成功返回位置</strong> ，查找<strong>失败</strong>，<strong>返回-1</strong></p>

<p><strong>find函数：</strong>从<strong>头查</strong>找</p>

<ul><li>str.find('A')——查找 'A'</li>
	<li>str.find("ABC")——查找 "ABC"</li>
</ul><p>int n=s4.find("ABC"); &nbsp; s4：ABCD &nbsp;&nbsp; -&gt; &nbsp; n = 0</p>

<ul><li>str.find('B',1)——从 位置1 处，查找'B'</li>
	<li>str.find("ABC",1,2)——从 位置1 处，开始查找 'ABC' 的前 2个 字符</li>
</ul><hr><p><strong>rfind函数：</strong>从<strong>尾部查</strong>找</p>

<ul><li>str.rfind('A')——查找 'A'</li>
	<li>str.rfind("ABC")——查找 "ABC"</li>
</ul><p>int n=s4.rfind("ABC"); &nbsp; s4：AAAABCD &nbsp;&nbsp; -&gt; &nbsp; n = 3</p>

<ul><li>str.rfind('B',1)——从 位置1 处，向前查找'B'</li>
	<li>str.rfind("ABC",1,2)——从 位置1 处，开始向前查找 'ABC' 的前 2个 字符</li>
</ul><hr><p><strong>find_first_of()函数：</strong></p>

<p style="text-indent:50px;">查找<strong>是否包含</strong>有<strong>子串中任何一个字符</strong></p>

<ul><li style="text-indent:0px;">str.find_first_of("abBc")——查找 "abBc" 和str 相等的任何字符，"abBc" 中有就返回位置</li>
	<li style="text-indent:0px;">str.find_first_of("abBc",1)——查找 "abBc" 和str 相等的任何字符，从 位置1 处，开始查找"abBc" 中的字符，"abBc" 中有的就返回位置</li>
	<li style="text-indent:0px;">str.find_first_of("abBc",1,2)——查找 "abBc" 和str 相等的任何字符，从 位置1 处，开始查找"abBc" 的前 2个 字符，"abBc" 中有的就返回位置</li>
</ul><hr><p><strong>find_last_of()函数：</strong></p>

<p style="text-indent:50px;">find_first_not_of ()末尾查找, 从末尾处开始,向前查找是否包含有子串中任何一个字符</p>

<ul><li>str.find_last_of("abBc")——查找 "abBc" 和str 相等的任何字符，向前查找，"abBc" 中有的返回位置</li>
	<li>str.find_last_of("abBc",1)——查找 "abBc" 和str 相等的任何字符，从 位置1 处，开始向前查找"abBc" 中的字符，"abBc" 中有的就返回位置</li>
	<li>str.find_last_of("abBc",10,2)——查找 "abBc" 和str 相等的任何字符，从 位置10 处，开始向前查找"abBc" 的前 2个 字符，"abBc" 中有的就返回位置</li>
</ul><hr><p><strong>拷贝相关的：</strong></p>

<ul><li style="text-indent:0px;">str1=str.substr(2)——提取子串，提取出 str 的 下标为2 到末尾，给 str1</li>
	<li style="text-indent:0px;">str1=str.substr(2,3)——提取子串，提取出 str 的 下标为2 开始，提取三个字节，给 str1</li>
	<li style="text-indent:0px;">const char* s1=str.data()——将string类转为字符串数组，返回给s1</li>
</ul><p style="text-indent:0px;">char* s=new char[10]</p>

<ul><li style="text-indent:0px;">str.copy(s,count,pos)——将 str 里的 pos 位置开始，拷贝 count个 字符,存到 s 里</li>
</ul><hr><p><strong>比较相关的函数：</strong></p>

<p><strong>compare函数：完全相等返回0；完全不等返回小于0；部分相等返回大于0</strong></p>

<p style="text-indent:0;"><strong>示例对象：string str(“abcd”)</strong></p>

<ul><li style="text-indent:0px;">str.compare(“abcd”)——完全相等，返回0</li>
	<li style="text-indent:0px;">str.compare(“dcba”)——返回一个小于0的值</li>
	<li style="text-indent:0px;">str.compare(“ab”)——返回大于0的值</li>
	<li style="text-indent:0px;">str.compare(str)——相等</li>
	<li style="text-indent:0px;">str.compare(0,2,str,2,2)——用<strong>str的 下标0 开始的 2个字符</strong> 和 <strong>str的 下标2 开始的 2个 字符</strong>比较——就是用 "ab" 和 "cd”" 比较，结果小于零</li>
	<li style="text-indent:0px;">str.compare(1,2,”bcx”,2)——用<strong>str的 下标1 开始的 2个字符</strong> 和 <strong>"bcx"的 前 2个 字符</strong>比较——就是用 "bc" 和 "bc”" 比较，结果是零</li>
</ul></blockquote>
                                    </div>