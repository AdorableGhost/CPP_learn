<div class="postBody">
                
<div id="cnblogs_post_body" class="blogpost-body cnblogs-markdown">
    <h1 id="概述">1. 概述</h1>
<p>C++ 11 中的 Lambda 表达式用于定义并创建匿名的函数对象，以简化编程工作。<br>
Lambda 的语法形式如下：</p>
<pre><code class="hljs less"><span class="hljs-selector-attr">[函数对象参数]</span> (操作符重载函数参数) <span class="hljs-selector-tag">mutable</span> 或 <span class="hljs-selector-tag">exception</span> 声明 <span class="hljs-selector-tag">-</span>&gt; 返回值类型 {函数体}</code></pre>
<p>可以看到，Lambda 主要分为五个部分：[函数对象参数]、(操作符重载函数参数)、mutable 或 exception 声明、-&gt; 返回值类型、{函数体}.</p>
<h1 id="lambda-语法分析">2. Lambda 语法分析</h1>
<h2 id="函数对象参数">2.1 [函数对象参数]</h2>
<p>标识一个 Lambda 表达式的开始，这部分必须存在，不能省略。函数对象参数是传递给编译器自动生成的函数对象类的构造<br>
函数的。函数对象参数只能使用那些到定义 Lambda 为止时 Lambda 所在作用范围内可见的局部变量(包括 Lambda 所在类<br>
的 this)。函数对象参数有以下形式：</p>
<ul>
<li>空。没有任何函数对象参数。</li>
<li>=。函数体内可以使用 Lambda 所在范围内所有可见的局部变量（包括 Lambda 所在类的 this），并且是值传递方式（相<br>
当于编译器自动为我们按值传递了所有局部变量）。</li>
<li>&amp;。函数体内可以使用 Lambda 所在范围内所有可见的局部变量（包括 Lambda 所在类的 this），并且是引用传递方式<br>
（相当于是编译器自动为我们按引用传递了所有局部变量）。</li>
<li>this。函数体内可以使用 Lambda 所在类中的成员变量。</li>
<li>a。将 a 按值进行传递。按值进行传递时，函数体内不能修改传递进来的 a 的拷贝，因为默认情况下函数是 const 的，要<br>
修改传递进来的拷贝，可以添加 mutable 修饰符。</li>
<li>&amp;a。将 a 按引用进行传递。</li>
<li>a，&amp;b。将 a 按值传递，b 按引用进行传递。</li>
<li>=，&amp;a，&amp;b。除 a 和 b 按引用进行传递外，其他参数都按值进行传递。</li>
<li>&amp;，a，b。除 a 和 b 按值进行传递外，其他参数都按引用进行传递。</li>
</ul>
<h2 id="操作符重载函数参数">2.2 (操作符重载函数参数)</h2>
<p>标识重载的 () 操作符的参数，没有参数时，这部分可以省略。参数可以通过按值（如: (a, b)）和按引用 (如: (&amp;a, &amp;b)) 两种<br>
方式进行传递。</p>
<h2 id="mutable-或-exception-声明">2.3 mutable 或 exception 声明</h2>
<p>这部分可以省略。按值传递函数对象参数时，加上 mutable 修饰符后，可以修改传递进来的拷贝（注意是能修改拷贝，而不是<br>
值本身）。exception 声明用于指定函数抛出的异常，如抛出整数类型的异常，可以使用 throw(int)。</p>
<h2 id="返回值类型">2.4 -&gt; 返回值类型</h2>
<p>标识函数返回值的类型，当返回值为 void，或者函数体中只有一处 return 的地方（此时编译器可以自动推断出返回值类型）<br>
时，这部分可以省略。</p>
<h2 id="函数体">2.5 {函数体}</h2>
<p>标识函数的实现，这部分不能省略，但函数体可以为空。</p>
<h1 id="示例">3. 示例</h1>
<pre><code class="hljs cs">[<span class="hljs-meta"></span>] (<span class="hljs-keyword">int</span> x, <span class="hljs-keyword">int</span> y) { <span class="hljs-keyword">return</span> x + y; } <span class="hljs-comment">// 隐式返回类型</span>
[<span class="hljs-meta"></span>] (<span class="hljs-keyword">int</span>&amp; x) { ++x;  } <span class="hljs-comment">// 没有 return 语句 -&gt; Lambda 函数的返回类型是 'void'</span>
[<span class="hljs-meta"></span>] () { ++global_x;  } <span class="hljs-comment">// 没有参数，仅访问某个全局变量</span>
[<span class="hljs-meta"></span>] { ++global_x; } <span class="hljs-comment">// 与上一个相同，省略了 (操作符重载函数参数)</span></code></pre>
<p>可以像下面这样显示指定返回类型：</p>
<pre><code class="hljs cs">[<span class="hljs-meta"></span>] (<span class="hljs-keyword">int</span> x, <span class="hljs-keyword">int</span> y) -&gt; <span class="hljs-keyword">int</span> { <span class="hljs-keyword">int</span> z = x + y; <span class="hljs-keyword">return</span> z; }</code></pre>
<p>在这个例子中创建了一个临时变量 z 来存储中间值。和普通函数一样，这个中间值不会保存到下次调用。什么也不返回的<br>
Lambda 函数可以省略返回类型，而不需要使用 -&gt; void 形式。</p>
<p>Lambda 函数可以引用在它之外声明的变量. 这些变量的集合叫做一个闭包. 闭包被定义在 Lambda 表达式声明中的方括<br>
号 [] 内。这个机制允许这些变量被按值或按引用捕获。如下图的例子：<br>
<img src="https://images2018.cnblogs.com/blog/1382048/201805/1382048-20180509221109509-1786172899.jpg"></p>
<h2 id="示例-1">3.1 示例 1</h2>
<pre><code class="hljs cpp"><span class="hljs-built_in">std</span>::<span class="hljs-built_in">vector</span>&lt;<span class="hljs-keyword">int</span>&gt; some_list;
<span class="hljs-keyword">int</span> total = <span class="hljs-number">0</span>;
<span class="hljs-keyword">for</span> (<span class="hljs-keyword">int</span> i = <span class="hljs-number">0</span>; i &lt; <span class="hljs-number">5</span>; ++i) some_list.push_back(i);
<span class="hljs-built_in">std</span>::for_each(begin(some_list), end(some_list), [&amp;total](<span class="hljs-keyword">int</span> x)
{
    total += x;
});</code></pre>
<p>此例计算 list 中所有元素的总和。变量 total 被存为 Lambda 函数闭包的一部分。因为它是栈变量（局部变量）total 引<br>
用，所以可以改变它的值。</p>
<h2 id="示例-2">3.2 示例 2</h2>
<pre><code class="hljs cpp"><span class="hljs-built_in">std</span>::<span class="hljs-built_in">vector</span>&lt;<span class="hljs-keyword">int</span>&gt; some_list;
<span class="hljs-keyword">int</span> total = <span class="hljs-number">0</span>;
<span class="hljs-keyword">int</span> value = <span class="hljs-number">5</span>;
<span class="hljs-built_in">std</span>::for_each(begin(some_list), end(some_list), [&amp;, value, <span class="hljs-keyword">this</span>](<span class="hljs-keyword">int</span> x)
{
    total += x * value * <span class="hljs-keyword">this</span>-&gt;some_func();
});</code></pre>
<p>此例中 total 会存为引用, value 则会存一份值拷贝。对 this 的捕获比较特殊，它只能按值捕获。this 只有当包含它的最靠近<br>
它的函数不是静态成员函数时才能被捕获。对 protect 和 private 成员来说，这个 Lambda 函数与创建它的成员函数有相同<br>
的访问控制。如果 this 被捕获了，不管是显式还是隐式的，那么它的类的作用域对 Lambda 函数就是可见的。访问 this 的<br>
成员不必使用 this-&gt; 语法，可以直接访问。</p>
<h1 id="总结">4. 总结</h1>
<p>不同编译器的具体实现可以有所不同，但期望的结果是: 按引用捕获的任何变量，Lambda 函数实际存储的应该是这些变量在<br>
创建这个 Lambda 函数的函数的栈指针，而不是 Lambda 函数本身栈变量的引用。不管怎样，因为大多数 Lambda 函数都<br>
很小且在局部作用中，与候选的内联函数很类似，所以按引用捕获的那些变量不需要额外的存储空间。</p>
<p>如果一个闭包含有局部变量的引用，在超出创建它的作用域之外的地方被使用的话，这种行为是未定义的!</p>
<p>Lambda 函数是一个依赖于实现的函数对象类型,这个类型的名字只有编译器知道. 如果用户想把 lambda 函数做为一个参数来<br>
传递, 那么形参的类型必须是模板类型或者必须能创建一个 std::function 类似的对象去捕获 lambda 函数.使用 auto 关键字<br>
可以帮助存储 lambda 函数,</p>
<pre><code class="hljs markdown">auto my<span class="hljs-emphasis">_lambda_</span>func = [<span class="hljs-string">&amp;</span>](<span class="hljs-link">int x</span>) { /<span class="hljs-bullet">* ... *</span>/ };
auto my<span class="hljs-emphasis">_onheap_</span>lambda_func = new auto([<span class="hljs-string">=</span>](<span class="hljs-link">int x</span>) { /<span class="hljs-bullet">* ... *</span>/ });</code></pre>
<p>这里有一个例子, 把匿名函数存储在变量、数组或 vector 中,并把它们当做命名参数来传递<br>
<img src="https://images2018.cnblogs.com/blog/1382048/201805/1382048-20180509222452588-1779542133.jpg"></p>
<p>一个没有指定任何捕获的 lambda 函数,可以显式转换成一个具有相同声明形式函数指针.所以,像下面这样做是合法的:</p>
<pre><code class="hljs cpp"><span class="hljs-keyword">auto</span> a_lambda_func = [](<span class="hljs-keyword">int</span> x) { <span class="hljs-comment">/* ... */</span> };
<span class="hljs-keyword">void</span> (*func_ptr)(<span class="hljs-keyword">int</span>) = a_lambda_func;
func_ptr(<span class="hljs-number">4</span>); <span class="hljs-comment">// calls the lambda</span></code></pre>

</div>
