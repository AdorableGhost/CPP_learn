<div class="postText">
		
<div id="cnblogs_post_body" class="blogpost-body ">
    <p>bind - boost</p>
<p>头文件: boost/bind.hpp</p>
<p>bind&nbsp;是一组重载的函数模板.<br>用来向一个函数(或函数对象)绑定某些参数.&nbsp;<br>bind的返回值是一个函数对象.</p>
<p>它的源文件太长了. 看不下去. 这里只记下它的用法:</p>
<p>9.1 对于普通函数</p>
<p>假如有函数 fun() 如下:&nbsp;<br>&nbsp;void fun(int x, int y)&nbsp;{<br>&nbsp;&nbsp;cout &lt;&lt; x &lt;&lt; ", " &lt;&lt; y &lt;&lt; endl;<br>&nbsp;}<br>现在我们看看怎么用bind 向其绑定参数.&nbsp;<br>对于像 fun 这样的普通函数. 若fun 有n个参数. 则 bind 需要 n+1 个参数: 原始函数的地址 以及 n个要绑定的参数.</p>
<p>第1种用法:&nbsp;<br>向原始函数 fun 绑定所有的参数<br>&nbsp;boost::bind(&amp;fun, 3, 4)&nbsp;&nbsp;&nbsp;&nbsp; // bind的实参表依次为: 要绑定的函数的地址, 绑定到fun的第一个参数值, 第二个参数值...<br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;// fun有多少个参数, 这里就要提供多少个.<br>表示将 3 和 4 作为参数绑定到 fun 函数.&nbsp;<br>因为绑定了所有的参数. 现在我们调用bind所返回的函数对象:<br>&nbsp;boost::bind(&amp;fun, 3, 4)( );&nbsp; //无参数.&nbsp;<br>就会输出 3, 4</p>
<p>第2种用法:&nbsp;<br>向原始函数 fun 绑定一部分参数<br>&nbsp;boost::bind(&amp;fun, 3, _1)&nbsp;&nbsp;&nbsp; // bind的实参表依次还是: 要绑定的函数的地址, 要绑定到fun的第一个参数值, 然后注意<br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;// 因为我们不打算向fun绑定第2个参数(即我们希望在调用返回的Functor时再指定这个参数的值)<br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;// 所以这里使用 _1 来占位. 这里的 _1 代表该新函数对象被调用时. 实参表的第1个参数.<br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;// 同理下边还会用到 _2 _3 这样的占位符.&nbsp;<br>这里只为fun绑定了第一个参数3. 所以在调用bind返回的函数对象时. 需要:<br>&nbsp;boost::bind(&amp;fun, 3, _1)(4);&nbsp; //这个4 会代替 _1 占位符.<br>输出 3, 4<br>同理 boost::bind(&amp;fun, _1, 3)(4);&nbsp;<br>输出 4, 3</p>
<p>第3种用法:<br>不向 fun 绑定任何参数<br>&nbsp;boost::bind(&amp;fun, _1, _2)&nbsp;&nbsp; // _1 _2 都是占位符. 上边已经说过了.<br>所以它就是 将新函数对象在调用时的实参表的第1个参数和第2个参数 绑定到fun函数.&nbsp;&nbsp;<br>&nbsp;boost::bind(&amp;fun, _1, _2)(3, 4);&nbsp;&nbsp;&nbsp; // 3将代替_1占位符, 4将代替_2占位符.<br>输出 3, 4<br>同理 boost::bind(&amp;fun, _2, _1)(3, 4);&nbsp;&nbsp; // 3将代替_1占位符, 4将代替_2占位符.<br>会输出 4, 3&nbsp;&nbsp;<br>同理 boost::bind(&amp;fun, _1, _1)(3); &nbsp;&nbsp;&nbsp; // 3将代替_1占位符<br>会输出 3, 3</p>
<p>对于普通函数就这些.&nbsp;对于函数对象. 如:<br>&nbsp;struct Func {<br>&nbsp;&nbsp;void operator()(int x) {<br>&nbsp;&nbsp;&nbsp;cout &lt;&lt; x &lt;&lt; endl;<br>&nbsp;&nbsp;}<br>&nbsp;} f;<br>绑定的时候可能要指出返回值的类型:<br>&nbsp;boost::bind&lt;void&gt;(f, 3)();&nbsp; //指出返回值的类型 void<br>&nbsp;</p>
<p>9.2 对于非静态成员函数</p>
<p>假如有:<br>&nbsp;struct A {<br>&nbsp;&nbsp;void func(int x, int y)&nbsp;{<br>&nbsp;&nbsp;&nbsp;cout &lt;&lt; x &lt;&lt; "," &lt;&lt; y &lt;&lt; endl;<br>&nbsp;&nbsp;}<br>&nbsp;};<br>&nbsp;<br>&nbsp;A a;&nbsp;&nbsp;<br>&nbsp;A* pa = new A;&nbsp;//指针<br>&nbsp;boost::shared_ptr&lt;A&gt; ptr_a(pa);&nbsp; //智能指针.<br>&nbsp;<br>现在要向像 A::func 这样的非静态成员函数绑定.&nbsp;<br>若A::func有n个参数, 则 bind 要有 n+2 个参数: 指向成员函数fun的指针, 绑定到this的对象, n个参数.<br>如:&nbsp;&nbsp;<br>&nbsp;boost::bind(&amp;A::func,&nbsp;a, 3, 4)();&nbsp;&nbsp;&nbsp; //输出 3, 4<br>&nbsp;boost::bind(&amp;A::func,&nbsp;pa, 3, 4)();&nbsp;&nbsp; //输出 3, 4<br>&nbsp;boost::bind(&amp;A::func,&nbsp;ptr_a, 3, 4)();//输出 3, 4<br>同样可以用 _1 这样的占位符. 如:<br>&nbsp;boost::bind(&amp;A::func, _1, 3, 4)(ptr_a);//输出 3, 4</p>
<p>可以看出. 不论传递给bind 的第2个参数是 对象. 对象指针. 还是智能指针. bind函数都能够正常工作.</p>
<p>&nbsp;</p>
<p><br>9.3 bind嵌套</p>
<p>有个类如下. 记录人的信息:<br>&nbsp;class Personal_info {<br>&nbsp;&nbsp;string name_;<br>&nbsp;&nbsp;int age_;<br>&nbsp;public:<br>&nbsp;&nbsp;int get_age();<br>&nbsp;&nbsp;string name();<br>&nbsp;};</p>
<p>&nbsp;vector&lt;Personal_info&gt; vec;&nbsp;<br>&nbsp;...<br>现在要对 vec 排序. 可以用 bind 函数做一个比较谓词<br>&nbsp;std::sort(&nbsp;&nbsp;<br>&nbsp;&nbsp;vec.begin(),&nbsp;&nbsp;<br>&nbsp;&nbsp;vec.end(),&nbsp;&nbsp;<br>&nbsp;&nbsp;boost::bind(&nbsp;<br>&nbsp;&nbsp;&nbsp;std::less&lt;int&gt;(),&nbsp;&nbsp;&nbsp;&nbsp;<br>&nbsp;&nbsp;&nbsp;boost::bind(&amp;personal_info::age,_1),&nbsp;&nbsp;&nbsp;&nbsp; //_1 占位符是 sort 中调用比较函数时的第一个参数.<br>&nbsp;&nbsp;&nbsp;boost::bind(&amp;personal_info::age,_2)));&nbsp;&nbsp; //_2 占位符是 sort 中调用比较函数时的第二个参数.</p>
<p><br>9.4 函数组合</p>
<p>假如有:<br>&nbsp;vector&lt;int&gt; ints;<br>&nbsp;...<br>想用 std::count_if() 来求ints中有多少是 &gt;5 且 &lt;=10 的. 这在常规代码中通常就要写一个函数来实现这个谓词:<br>&nbsp;if (i&gt;5 &amp;&amp; i&lt;=10) ...<br>现在用bind则可以:<br>&nbsp;std::count_if(&nbsp;&nbsp;<br>&nbsp;&nbsp;ints.begin(),&nbsp; ints.end(),&nbsp;&nbsp;<br>&nbsp;&nbsp;boost::bind(&nbsp;&nbsp;&nbsp;&nbsp;<br>&nbsp;&nbsp;&nbsp;std::logical_and&lt;bool&gt;(),&nbsp;&nbsp;&nbsp;&nbsp;<br>&nbsp;&nbsp;&nbsp;boost::bind(std::greater&lt;int&gt;(),_1,5),&nbsp;&nbsp;&nbsp;&nbsp;<br>&nbsp;&nbsp;&nbsp;boost::bind(std::less_equal&lt;int&gt;(),_1,10)));</p>
<p>&nbsp;</p>
<p>9.5 绑定到成员变量</p>
<p>有:<br>&nbsp;map&lt;int, string&gt; my_map;<br>&nbsp;my_map[0]="Boost";my_map[1]="Bind";<br>现在要输出所有元素的 second 成员. 也就是输出这些字符串. 其中的打印函数如下:<br>&nbsp;void print_string(const string&amp; s) {&nbsp;&nbsp;<br>&nbsp;&nbsp;std::cout &lt;&lt; s &lt;&lt; '/n';<br>&nbsp;}<br>则可以:<br>&nbsp;for_each(&nbsp;&nbsp;<br>&nbsp;&nbsp;my_map.begin(),&nbsp;&nbsp;<br>&nbsp;&nbsp;my_map.end(),&nbsp;&nbsp;<br>&nbsp;&nbsp;boost::bind(<br>&nbsp;&nbsp;&nbsp;&amp;print_string,&nbsp;<br>&nbsp;&nbsp;&nbsp;boost::bind(&amp;std::map&lt;int,std::string&gt;::value_type::second,_1)<br>&nbsp;&nbsp;&nbsp;)<br>&nbsp;&nbsp;);<br>&nbsp;&nbsp;<br>汗... 看不懂bind的源码. 也不知是如何实现这些功能的. 只能等&lt;&lt;boost源码剖析&gt;&gt;出来了.</p>
<p><br>&nbsp;注意:<br>(以下补于08年6月3日)<br><br>boost::bind() 返回的函数对象会保存要绑定的实参. 而且总是拷贝一份以值的方式保存..<br>这主要是考虑到被绑定的实参的生命期.&nbsp;&nbsp;<br>但这并不总是我们期望的. 例如有时我们希望它保存指针或引用:<br><br>有函数:<br>void f(int &amp; x) { ++x; }<br>然后:<br>int n = 0;<br>bind(&amp;f, n)();&nbsp;&nbsp;&nbsp; //我们希望 n==1 . 但实际上没有这样...<br><br>要避免这种对象复制. &nbsp;而要bind得到的函数对象保存实参的引用语义. 可以:<br>使用 boost::ref()&nbsp; 或 boost::cref() 如<br>bind(&amp;f,&nbsp;ref(n))();&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; //OK,&nbsp; 执行后 n==1<br><br>如果是绑定一个对象到它的成员函数上. 如:<br>A a;<br>bind(&amp;A::fun,&nbsp;a);&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; //则保存的是 a对象的拷贝.<br>要避免这种拷贝. 除了上面提到的 ref() 外, 也可以:<br>bind(&amp;A::fun,&nbsp;&amp;a);&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; //用指针.&nbsp; 反正用对象和用指针都可以. 而用指针可以避免对象拷贝的问题.&nbsp;<br><br><br><br>注意: (以下补于6月10日)<br>bind () 的第一个参数——被绑定函数——是不被求值的. 如下例:<br><br>typedef void (*pf)(int);<br>std::vector&lt;pf&gt; v;&nbsp; //v中有一些函数指针.<br>std::for_each(v.begin(), v.end(),&nbsp;bind(_1, 5));&nbsp;&nbsp;&nbsp;//想实现 _1(5);&nbsp; 这样的调用. 但这样不行!<br><br>正确的做法是借助&nbsp;boost::apply&nbsp;模板(来自boost/bind/apply.hpp).&nbsp;&nbsp;<br>apply也是一个函数对象. 它的作用如下:<br>apply&lt;void&gt;&nbsp;a;&nbsp;&nbsp; //模板参数为函数对象的返回值类型.<br>a(x);&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; //相当于调用 x();<br>a(x, y);&nbsp;&nbsp;&nbsp; //相当于调用&nbsp; x(y);<br>a(x, y, z);&nbsp; //相当于调用 x(y, z);<br>所以错误的bind应该写为:<br>std::for_each(v.begin(), v.end(), bind(apply&lt;void&gt;(), _1, 5));</p>
</div>
<div id="MySignature"></div>
<div class="clear"></div>
<div id="blog_post_info_block"><div id="BlogPostCategory">
    分类: 
            <a href="https://www.cnblogs.com/lidabo/category/542245.html" target="_blank">Boost</a></div>


    <div id="blog_post_info">
<div id="green_channel">
        <a href="javascript:void(0);" id="green_channel_digg" onclick="DiggIt(8350912,cb_blogId,1);green_channel_success(this,'谢谢推荐！');">好文要顶</a>
        <a id="green_channel_follow" onclick="follow('8e506bcc-b700-df11-ba8f-001cf0cd104b');" href="javascript:void(0);">关注我</a>
    <a id="green_channel_favorite" onclick="AddToWz(cb_entryId);return false;" href="javascript:void(0);">收藏该文</a>
    <a id="green_channel_weibo" href="javascript:void(0);" title="分享至新浪微博" onclick="ShareToTsina()"><img src="https://common.cnblogs.com/images/icon_weibo_24.png" alt=""></a>
    <a id="green_channel_wechat" href="javascript:void(0);" title="分享至微信" onclick="shareOnWechat()"><img src="https://common.cnblogs.com/images/wechat.png" alt=""></a>
</div>
<div id="author_profile">
    <div id="author_profile_info" class="author_profile_info">
        <div id="author_profile_detail" class="author_profile_info">
            <a href="https://home.cnblogs.com/u/lidabo/">DoubleLi</a><br>
            <a href="https://home.cnblogs.com/u/lidabo/followees/">关注 - 29</a><br>
            <a href="https://home.cnblogs.com/u/lidabo/followers/">粉丝 - 1757</a>
        </div>
    </div>
    <div class="clear"></div>
    <div id="author_profile_honor"></div>
    <div id="author_profile_follow">
                <a href="javascript:void(0);" onclick="follow('8e506bcc-b700-df11-ba8f-001cf0cd104b');return false;">+加关注</a>
    </div>
</div>
<div id="div_digg">
    <div class="diggit" onclick="votePost(8350912,'Digg')">
        <span class="diggnum" id="digg_count">0</span>
    </div>
    <div class="buryit" onclick="votePost(8350912,'Bury')">
        <span class="burynum" id="bury_count">0</span>
    </div>
    <div class="clear"></div>
    <div class="diggword" id="digg_tips">
    </div>
</div>

<script type="text/javascript">
    currentDiggType = 0;
</script></div>
    <div class="clear"></div>
    <div id="post_next_prev">

    <a href="https://www.cnblogs.com/lidabo/p/8350333.html" class="p_n_p_prefix">« </a> 上一篇：    <a href="https://www.cnblogs.com/lidabo/p/8350333.html" title="发布于 2018-01-25 11:13">Doubango开源项目</a>
    <br>
    <a href="https://www.cnblogs.com/lidabo/p/8350951.html" class="p_n_p_prefix">» </a> 下一篇：    <a href="https://www.cnblogs.com/lidabo/p/8350951.html" title="发布于 2018-01-25 14:04">ISE（Iris Server Engine）是一个基于现代C++的跨平台（Linux和Windows）框架</a>

</div>
</div>
	</div>