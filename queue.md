<div id="arc-body">只能访问 queue&lt;T&gt; 容器适配器的第一个和最后一个元素。只能在容器的末尾添加新元素，只能从头部移除元素。<br>
<br>
许多程序都使用了 queue 容器。queue 容器可以用来表示超市的结账队列或服务器上等待执行的数据库事务队列。对于任何需要用 FIFO 准则处理的序列来说，使用 queue 容器适配器都是好的选择。<br>
<br>
图 1 展示了一个 queue 容器及其一些基本操作：
<div style="text-align: center;">
<br>
<img alt="" src="./queue.jpg" style="width: 700px; height: 210px;"></div>
<div style="text-align: center;">
图 1 queue容器</div>
<br>
queue 的生成方式和 stack 相同，下面展示如何创建一个保存字符串对象的 queue:<br>
<div class="snippet-container" style="undefined;"><div class="sh_bright snippet-wrap"><div class="snippet-menu sh_sourceCode" style="display:none;"><pre><a class="snippet-copy sh_url" href="#" style="display: none;">复制</a><a class="snippet-text sh_url" href="#">纯文本</a><a class="snippet-window sh_url" href="#">复制</a></pre></div><pre class="cpp sh_cpp snippet-formatted sh_sourceCode"><ol class="snippet-num"><li>std<span class="sh_symbol">::</span><span class="sh_usertype">queue&lt;std::string&gt;</span><span class="sh_normal"> </span>words<span class="sh_symbol">;</span></li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">std::queue&lt;std::string&gt; words;</pre></div></div>
也可以使用拷贝构造函数：<br>
<div class="snippet-container" style="undefined;"><div class="sh_bright snippet-wrap"><div class="snippet-menu sh_sourceCode" style="display:none;"><pre><a class="snippet-copy sh_url" href="#" style="display: none;">复制</a><a class="snippet-text sh_url" href="#">纯文本</a><a class="snippet-window sh_url" href="#">复制</a></pre></div><pre class="cpp sh_cpp snippet-formatted sh_sourceCode"><ol class="snippet-num"><li>std<span class="sh_symbol">::</span><span class="sh_usertype">queue&lt;std::string&gt;</span><span class="sh_normal"> </span>copy_words <span class="sh_cbracket">{</span>words<span class="sh_cbracket">}</span><span class="sh_symbol">;</span> <span class="sh_comment">// A duplicate of words</span></li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">std::queue&lt;std::string&gt; copy_words {words}; // A duplicate of words</pre></div></div>
stack&lt;T&gt;、queue&lt;T&gt; 这类适配器类都默认封装了一个 deque&lt;T&gt; 容器，也可以通过指定第二个模板类型参数来使用其他类型的容器：<br>
<div class="snippet-container" style="undefined;"><div class="sh_bright snippet-wrap"><div class="snippet-menu sh_sourceCode" style="display:none;"><pre><a class="snippet-copy sh_url" href="#" style="display: none;">复制</a><a class="snippet-text sh_url" href="#">纯文本</a><a class="snippet-window sh_url" href="#">复制</a></pre></div><pre class="cpp sh_cpp snippet-formatted sh_sourceCode"><ol class="snippet-num"><li>std<span class="sh_symbol">::</span>queue<span class="sh_symbol">&lt;</span>std<span class="sh_symbol">::</span>string<span class="sh_symbol">,</span> std<span class="sh_symbol">::</span>list<span class="sh_symbol">&lt;</span>std<span class="sh_symbol">::</span>string<span class="sh_symbol">&gt;&gt;</span>words<span class="sh_symbol">;</span></li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">std::queue&lt;std::string, std::list&lt;std::string&gt;&gt;words;</pre></div></div>
底层容器必须提供这些操作：front()、back()、push_back()、pop_front()、empty() 和 size()。<br>
<h2>
queue 操作</h2>
queue 和 stack 有一些成员函数相似，但在一些情况下，工作方式有些不同：<br>
<ul>
<li>
front()：返回 queue 中第一个元素的引用。如果 queue 是常量，就返回一个常引用；如果 queue 为空，返回值是未定义的。</li>
<li>
back()：返回 queue 中最后一个元素的引用。如果 queue 是常量，就返回一个常引用；如果 queue 为空，返回值是未定义的。</li>
<li>
push(const T&amp; obj)：在 queue 的尾部添加一个元素的副本。这是通过调用底层容器的成员函数 push_back() 来完成的。</li>
<li>
push(T&amp;&amp; obj)：以移动的方式在 queue 的尾部添加元素。这是通过调用底层容器的具有右值引用参数的成员函数 push_back() 来完成的。</li>
<li>
pop()：删除 queue 中的第一个元素。</li>
<li>
size()：返回 queue 中元素的个数。</li>
<li>
empty()：如果 queue 中没有元素的话，返回 true。</li>
<li>
emplace()：用传给 emplace() 的参数调用 T 的构造函数，在 queue 的尾部生成对象。</li>
<li>
swap(queue&lt;T&gt; &amp;other_q)：将当前 queue 中的元素和参数 queue 中的元素交换。它们需要包含相同类型的元素。也可以调用全局函数模板&nbsp;swap() 来完成同样的操作。</li>
</ul>
<br>
queue&lt;T&gt; 模板定义了拷贝和移动版的 operator=()，对于所保存元素类型相同的 queue 对象，它们有一整套的比较运算符，这些运算符的工作方式和 stack 容器相同。<br>
<br>
和 stack 一样，queue 也没有迭代器。访问元素的唯一方式是遍历容器内容，并移除访问过的每一个元素。例如：<br>
<div class="snippet-container" style="undefined;"><div class="sh_bright snippet-wrap"><div class="snippet-menu sh_sourceCode" style="display:none;"><pre><a class="snippet-copy sh_url" href="#" style="display: none;">复制</a><a class="snippet-text sh_url" href="#">纯文本</a><a class="snippet-window sh_url" href="#">复制</a></pre></div><pre class="cpp sh_cpp snippet-formatted sh_sourceCode"><ol class="snippet-num"><li>std<span class="sh_symbol">::</span><span class="sh_usertype">deque&lt;double&gt; values {1.5, 2.5, 3.5, 4.5}; std::queue&lt;double&gt;</span><span class="sh_normal"> </span><span class="sh_function">numbers</span><span class="sh_symbol">(</span>values<span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_keyword">while</span> <span class="sh_symbol">(!</span>numbers<span class="sh_symbol">,</span> <span class="sh_function">empty</span><span class="sh_symbol">())</span></li><li><span class="sh_cbracket">{</span></li><li>    std <span class="sh_symbol">::</span>cout <span class="sh_symbol">&lt;&lt;</span> numbers<span class="sh_symbol">.</span> <span class="sh_function">front</span><span class="sh_symbol">()</span> <span class="sh_symbol">&lt;&lt;</span> <span class="sh_string">" "</span><span class="sh_symbol">;</span> <span class="sh_comment">// Output the 1st element </span></li><li>    numbers<span class="sh_symbol">.</span> <span class="sh_function">pop</span><span class="sh_symbol">();</span>  <span class="sh_comment">// Delete the 1st element</span></li><li><span class="sh_cbracket">}</span></li><li>std<span class="sh_symbol">::</span>cout <span class="sh_symbol">&lt;&lt;</span> std<span class="sh_symbol">::</span>endl<span class="sh_symbol">;</span></li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">std::deque&lt;double&gt; values {1.5, 2.5, 3.5, 4.5}; std::queue&lt;double&gt; numbers(values);

while (!numbers, empty())
{
    std ::cout &lt;&lt; numbers. front() &lt;&lt; " "; // Output the 1st element 
    numbers. pop();  // Delete the 1st element
}
std::cout &lt;&lt; std::endl;</pre></div></div>
用循环列出 numbers 的内容，循环由 empty() 返回的值控制。调用 empty() 可以保证我们能够调用一个空队列的 ftont() 函数。如代码所示，为了访问 queue 中的全部元素，必须删除它们。如果不想删除容器中的元素，必须将它们复制到另一个容器中。如果一定要这么操作，我们可能需要换一个容器。<br>
<h2>
queue 容器的实际使用</h2>
这里汇集了一些使用 queue 容器的示例。这是一个用 queue 模拟超市运转的程序。结账队列的长度是超市运转的关键因素。它会影响超市可容纳的顾客数——因为太长的队伍会使顾客感到气馁，从而放弃排队。在很多情形中——医院可用病床数会严重影响应急处理设施的运转，也会产生同样的队列问题。我们的超市模拟是一个简单模型，灵活性有限。<br>
<br>
可以在头文件 Customer.h 中定义一个类来模拟顾客：
<div class="snippet-container" style="undefined;"><div class="sh_bright snippet-wrap"><div class="snippet-menu sh_sourceCode" style="display:none;"><pre><a class="snippet-copy sh_url" href="#" style="display: none;">复制</a><a class="snippet-text sh_url" href="#">纯文本</a><a class="snippet-window sh_url" href="#">复制</a></pre></div><pre class="cpp sh_cpp snippet-formatted sh_sourceCode"><ol class="snippet-num"><li><span class="sh_comment">// Defines a customer by their time to checkout</span></li><li><span class="sh_preproc">#ifndef</span> CUSTOMER_H</li><li><span class="sh_preproc">#define</span> CUSTOMER_H</li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_keyword">class</span><span class="sh_normal"> </span><span class="sh_classname">Customer</span></li><li><span class="sh_cbracket">{</span></li><li><span class="sh_keyword">protected</span><span class="sh_symbol">:</span></li><li>    <span class="sh_usertype">size_t</span><span class="sh_normal"> </span>service_t <span class="sh_cbracket">{}</span><span class="sh_symbol">;</span> <span class="sh_comment">// Time to checkout</span></li><li><span class="sh_keyword">public</span><span class="sh_symbol">:</span></li><li>    <span class="sh_keyword">explicit</span> <span class="sh_function">Customer</span><span class="sh_symbol">(</span><span class="sh_usertype">size_t</span><span class="sh_normal"> </span>st <span class="sh_symbol">=</span> <span class="sh_number">10</span><span class="sh_symbol">)</span> <span class="sh_symbol">:</span>service_t <span class="sh_cbracket">{</span>st<span class="sh_cbracket">}{}</span></li><li><span style="display:none;">&nbsp;</span></li><li>    <span class="sh_comment">// Decrement time remaining to checkout</span></li><li>    Customer<span class="sh_symbol">&amp;</span> <span class="sh_function">time_decrement</span><span class="sh_symbol">()</span></li><li>    <span class="sh_cbracket">{</span></li><li>        <span class="sh_keyword">if</span> <span class="sh_symbol">(</span>service_t <span class="sh_symbol">&gt;</span> <span class="sh_number">0</span><span class="sh_symbol">)</span></li><li>            <span class="sh_symbol">--</span>service_t<span class="sh_symbol">;</span></li><li>        <span class="sh_keyword">return</span> <span class="sh_symbol">*</span><span class="sh_keyword">this</span><span class="sh_symbol">;</span></li><li>    <span class="sh_cbracket">}</span></li><li>    <span class="sh_type">bool</span> <span class="sh_function">done</span><span class="sh_symbol">()</span> <span class="sh_keyword">const</span> <span class="sh_cbracket">{</span> <span class="sh_keyword">return</span> service_t <span class="sh_symbol">==</span> <span class="sh_number">0</span><span class="sh_symbol">;</span> <span class="sh_cbracket">}</span></li><li><span class="sh_cbracket">}</span><span class="sh_symbol">;</span></li><li><span class="sh_preproc">#endif</span></li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">// Defines a customer by their time to checkout
#ifndef CUSTOMER_H
#define CUSTOMER_H

class Customer
{
protected:
    size_t service_t {}; // Time to checkout
public:
    explicit Customer(size_t st = 10) :service_t {st}{}

    // Decrement time remaining to checkout
    Customer&amp; time_decrement()
    {
        if (service_t &gt; 0)
            --service_t;
        return *this;
    }
    bool done() const { return service_t == 0; }
};
#endif</pre></div></div>
这里只有一个成员变量 service_t，用来记录顾客结账需要的时间。每个顾客的结账时间都不同。每过一分钟，会调用一次 time_decrement() 函数，这个函数会减少 service_t 的值，它可以反映顾客结账所花费的时间。当 service_t 的值为 0 时，成员函数 done() 返回 true。<br>
<br>
超市的每个结账柜台都有一队排队等待的顾客。Checkout.h 中定义的 Checkout 类如下：<br>
<div class="snippet-container" style="undefined;"><div class="sh_bright snippet-wrap"><div class="snippet-menu sh_sourceCode" style="display:none;"><pre><a class="snippet-copy sh_url" href="#" style="display: none;">复制</a><a class="snippet-text sh_url" href="#">纯文本</a><a class="snippet-window sh_url" href="#">复制</a></pre></div><pre class="cpp sh_cpp snippet-formatted sh_sourceCode"><ol class="snippet-num"><li><span class="sh_comment">// Supermarket checkout - maintains and processes customers in a queue</span></li><li><span class="sh_preproc">#ifndef</span> CHECKOUT_H</li><li><span class="sh_preproc">#define</span> CHECKOUT_H</li><li><span class="sh_preproc">#include</span> <span class="sh_string">&lt;queue&gt;</span> <span class="sh_comment">// For queue container</span></li><li><span class="sh_preproc">#include</span> <span class="sh_string">"Customer.h"</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_keyword">class</span><span class="sh_normal"> </span><span class="sh_classname">Checkout</span></li><li><span class="sh_cbracket">{</span></li><li><span class="sh_keyword">private</span><span class="sh_symbol">:</span></li><li>    std<span class="sh_symbol">::</span><span class="sh_usertype">queue&lt;Customer&gt;</span><span class="sh_normal"> </span>customers<span class="sh_symbol">;</span> <span class="sh_comment">// The queue waiting to checkout</span></li><li><span class="sh_keyword">public</span><span class="sh_symbol">:</span></li><li>    <span class="sh_type">void</span> <span class="sh_function">add</span><span class="sh_symbol">(</span><span class="sh_keyword">const</span> Customer<span class="sh_symbol">&amp;</span> customer<span class="sh_symbol">)</span> <span class="sh_cbracket">{</span> customers<span class="sh_symbol">.</span><span class="sh_function">push</span><span class="sh_symbol">(</span>customer<span class="sh_symbol">);</span> <span class="sh_cbracket">}</span></li><li>    <span class="sh_usertype">size_t</span><span class="sh_normal"> </span><span class="sh_function">qlength</span><span class="sh_symbol">()</span> <span class="sh_keyword">const</span> <span class="sh_cbracket">{</span> <span class="sh_keyword">return</span> customers<span class="sh_symbol">.</span><span class="sh_function">size</span><span class="sh_symbol">();</span> <span class="sh_cbracket">}</span></li><li>   </li><li>    <span class="sh_comment">// Increment the time by one minute</span></li><li>    <span class="sh_type">void</span> <span class="sh_function">time_increment</span><span class="sh_symbol">()</span></li><li>    <span class="sh_cbracket">{</span></li><li>        <span class="sh_keyword">if</span> <span class="sh_symbol">(!</span>customers<span class="sh_symbol">.</span><span class="sh_function">empty</span><span class="sh_symbol">())</span></li><li>        <span class="sh_cbracket">{</span> <span class="sh_comment">// There are customers waiting...</span></li><li>            <span class="sh_keyword">if</span> <span class="sh_symbol">(</span>customers<span class="sh_symbol">.</span><span class="sh_function">front</span><span class="sh_symbol">().</span><span class="sh_function">time_decrement</span><span class="sh_symbol">().</span><span class="sh_function">done</span><span class="sh_symbol">())</span>  <span class="sh_comment">// If the customer is done...</span></li><li>                customers<span class="sh_symbol">.</span><span class="sh_function">pop</span><span class="sh_symbol">();</span> <span class="sh_comment">// ...remove from the queue</span></li><li>        <span class="sh_cbracket">}</span></li><li>    <span class="sh_cbracket">}</span><span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li>    <span class="sh_type">bool</span> <span class="sh_keyword">operator</span><span class="sh_symbol">&lt;(</span><span class="sh_keyword">const</span> Checkout<span class="sh_symbol">&amp;</span> other<span class="sh_symbol">)</span> <span class="sh_keyword">const</span> <span class="sh_cbracket">{</span> <span class="sh_keyword">return</span> <span class="sh_function">qlength</span><span class="sh_symbol">()</span> <span class="sh_symbol">&lt;</span> other<span class="sh_symbol">.</span><span class="sh_function">qlength</span><span class="sh_symbol">();</span> <span class="sh_cbracket">}</span></li><li>    <span class="sh_type">bool</span> <span class="sh_keyword">operator</span><span class="sh_symbol">&gt;(</span><span class="sh_keyword">const</span> Checkout<span class="sh_symbol">&amp;</span> other<span class="sh_symbol">)</span> <span class="sh_keyword">const</span> <span class="sh_cbracket">{</span> <span class="sh_keyword">return</span> <span class="sh_function">qlength</span><span class="sh_symbol">()</span> <span class="sh_symbol">&gt;</span> other<span class="sh_symbol">.</span><span class="sh_function">qlength</span><span class="sh_symbol">();</span> <span class="sh_cbracket">}</span></li><li><span class="sh_cbracket">}</span><span class="sh_symbol">;</span></li><li><span class="sh_preproc">#endif</span></li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">// Supermarket checkout - maintains and processes customers in a queue
#ifndef CHECKOUT_H
#define CHECKOUT_H
#include &lt;queue&gt; // For queue container
#include "Customer.h"

class Checkout
{
private:
    std::queue&lt;Customer&gt; customers; // The queue waiting to checkout
public:
    void add(const Customer&amp; customer) { customers.push(customer); }
    size_t qlength() const { return customers.size(); }
   
    // Increment the time by one minute
    void time_increment()
    {
        if (!customers.empty())
        { // There are customers waiting...
            if (customers.front().time_decrement().done())  // If the customer is done...
                customers.pop(); // ...remove from the queue
        }
    };

    bool operator&lt;(const Checkout&amp; other) const { return qlength() &lt; other.qlength(); }
    bool operator&gt;(const Checkout&amp; other) const { return qlength() &gt; other.qlength(); }
};
#endif</pre></div></div>
这相当于自我解释。queue 容器是 Checkout 唯一的成员变量，用来保存等待结账的 Customer 对象。成员函数 add() 可以向队列中添加新顾客。只能处理队列中的第一个元素。 每过一分钟，调用一次 Checkout 对象的成员函数 time_increment(}，它会调用第一个 Customer 对象的成员函数 time_decrement() 来减少剩余的服务时间，然后再调用成员函数 done()。如果 done() 返回 true，表明顾客结账完成，因此把他从队列中移除。Checkout 对象的比较运算符可以比较队列的长度。<br>
<br>
为了模拟超市结账，我们需要有随机数生成的功能。因此打算使用 random 头文件中的一个非常简单的工具，但不打算深入解释它。我们会在教程后面的章节深入探讨 random 头文件中的内容。程序使用了一个 uniform_int_distribution() 类型的实例。顾名思义，它定义的整数值在最大值和最小值之间均匀分布。在均匀分布中，所有这个范围内的值都可能相等。可以在 10 和 100 之间定义如下分布：<br>
<div class="snippet-container" style="undefined;"><div class="sh_bright snippet-wrap"><div class="snippet-menu sh_sourceCode" style="display:none;"><pre><a class="snippet-copy sh_url" href="#" style="display: none;">复制</a><a class="snippet-text sh_url" href="#">纯文本</a><a class="snippet-window sh_url" href="#">复制</a></pre></div><pre class="cpp sh_cpp snippet-formatted sh_sourceCode"><ol class="snippet-num"><li>std<span class="sh_symbol">::</span><span class="sh_usertype">uniform_int_distribution&lt;&gt;</span><span class="sh_normal"> </span>d <span class="sh_cbracket">{</span><span class="sh_number">10</span><span class="sh_symbol">,</span> <span class="sh_number">100</span><span class="sh_cbracket">}</span><span class="sh_symbol">;</span></li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">std::uniform_int_distribution&lt;&gt; d {10, 100};</pre></div></div>
这里只定义了分布对象 d，它指定了整数值分布的范围。为了获取这个范围内的随机数，我们需要使用一个随机数生成器，然后把它作为参数传给 d 的调用运算符，从而返回一个随机整数。 random 头文件中定义了几种随机数生成器。这里我们使用最简单的一个，可以按如下方式定义：<br>
<div class="snippet-container" style="undefined;"><div class="sh_bright snippet-wrap"><div class="snippet-menu sh_sourceCode" style="display:none;"><pre><a class="snippet-copy sh_url" href="#" style="display: none;">复制</a><a class="snippet-text sh_url" href="#">纯文本</a><a class="snippet-window sh_url" href="#">复制</a></pre></div><pre class="cpp sh_cpp snippet-formatted sh_sourceCode"><ol class="snippet-num"><li>std<span class="sh_symbol">::</span><span class="sh_usertype">random_device</span><span class="sh_normal"> </span>random_number_engine<span class="sh_symbol">;</span></li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">std::random_device random_number_engine;</pre></div></div>
为了在 d 分布范围内生成随机数，我们可以这样写：<br>
<div class="snippet-container" style="undefined;"><div class="sh_bright snippet-wrap"><div class="snippet-menu sh_sourceCode" style="display:none;"><pre><a class="snippet-copy sh_url" href="#" style="display: none;">复制</a><a class="snippet-text sh_url" href="#">纯文本</a><a class="snippet-window sh_url" href="#">复制</a></pre></div><pre class="cpp sh_cpp snippet-formatted sh_sourceCode"><ol class="snippet-num"><li><span class="sh_keyword">auto</span> value <span class="sh_symbol">=</span> <span class="sh_function">d</span><span class="sh_symbol">(</span>random_number_engine<span class="sh_symbol">);</span> <span class="sh_comment">// Calls operator()() for d</span></li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">auto value = d(random_number_engine); // Calls operator()() for d</pre></div></div>
value 的值在 d 分布范围内。<br>
<br>
完整模拟器的源文件如下：
<div class="snippet-container" style="undefined;"><div class="sh_bright snippet-wrap"><div class="snippet-menu sh_sourceCode" style="display:none;"><pre><a class="snippet-copy sh_url" href="#" style="display: none;">复制</a><a class="snippet-text sh_url" href="#">纯文本</a><a class="snippet-window sh_url" href="#">复制</a></pre></div><pre class="cpp sh_cpp snippet-formatted sh_sourceCode"><ol class="snippet-num"><li><span class="sh_comment">// Simulating a supermarket with multiple checkouts</span></li><li><span class="sh_preproc">#include</span> <span class="sh_string">&lt;iostream&gt;</span>                              <span class="sh_comment">// For s</span><a href="/ref/tan.html" target="_blank" class="sh_url"><span class="sh_comment">tan</span></a><span class="sh_comment">dard streams</span></li><li><span class="sh_preproc">#include</span> <span class="sh_string">&lt;iomanip&gt;</span>                               <span class="sh_comment">// For stream manipulators</span></li><li><span class="sh_preproc">#include</span> <span class="sh_string">&lt;vector&gt;</span>                                <span class="sh_comment">// For vector container</span></li><li><span class="sh_preproc">#include</span> <span class="sh_string">&lt;string&gt;</span>                                <span class="sh_comment">// For string class</span></li><li><span class="sh_preproc">#include</span> <span class="sh_string">&lt;numeric&gt;</span>                               <span class="sh_comment">// For accumulate()</span></li><li><span class="sh_preproc">#include</span> <span class="sh_string">&lt;algorithm&gt;</span>                             <span class="sh_comment">// For min_element &amp; max_element</span></li><li><span class="sh_preproc">#include</span> <span class="sh_string">&lt;random&gt;</span>                                <span class="sh_comment">// For random number generation</span></li><li><span class="sh_preproc">#include</span> <span class="sh_string">"Customer.h"</span></li><li><span class="sh_preproc">#include</span> <span class="sh_string">"Checkout.h"</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_keyword">u</span><a href="/ref/sin.html" target="_blank" class="sh_url"><span class="sh_keyword">sin</span></a><span class="sh_keyword">g</span> std<span class="sh_symbol">::</span>string<span class="sh_symbol">;</span></li><li><span class="sh_keyword">using</span> distribution <span class="sh_symbol">=</span> std<span class="sh_symbol">::</span>uniform_int_distribution<span class="sh_symbol">&lt;&gt;;</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_comment">// Output histogram of service times</span></li><li><span class="sh_type">void</span> <span class="sh_function">histogram</span><span class="sh_symbol">(</span><span class="sh_keyword">const</span> std<span class="sh_symbol">::</span>vector<span class="sh_symbol">&lt;</span><span class="sh_type">int</span><span class="sh_symbol">&gt;&amp;</span> v<span class="sh_symbol">,</span> <span class="sh_type">int</span> min<span class="sh_symbol">)</span></li><li><span class="sh_cbracket">{</span></li><li>    <span class="sh_usertype">string</span><span class="sh_normal"> </span><span class="sh_function">bar</span> <span class="sh_symbol">(</span><span class="sh_number">60</span><span class="sh_symbol">,</span> <span class="sh_string">'*'</span><span class="sh_symbol">);</span>                          <span class="sh_comment">// Row of asterisks for bar</span></li><li>    <span class="sh_keyword">for</span> <span class="sh_symbol">(</span><span class="sh_usertype">size_t</span><span class="sh_normal"> </span>i <span class="sh_cbracket">{}</span><span class="sh_symbol">;</span> i <span class="sh_symbol">&lt;</span> v<span class="sh_symbol">.</span><span class="sh_function">size</span><span class="sh_symbol">();</span> <span class="sh_symbol">++</span>i<span class="sh_symbol">)</span></li><li>    <span class="sh_cbracket">{</span></li><li>        std<span class="sh_symbol">::</span>cout <span class="sh_symbol">&lt;&lt;</span> std<span class="sh_symbol">::</span><span class="sh_function">setw</span><span class="sh_symbol">(</span><span class="sh_number">3</span><span class="sh_symbol">)</span> <span class="sh_symbol">&lt;&lt;</span> i<span class="sh_symbol">+</span>min <span class="sh_symbol">&lt;&lt;</span> <span class="sh_string">" "</span>    <span class="sh_comment">// Service time is index + min</span></li><li>        <span class="sh_symbol">&lt;&lt;</span> std<span class="sh_symbol">::</span><span class="sh_function">setw</span><span class="sh_symbol">(</span><span class="sh_number">4</span><span class="sh_symbol">)</span> <span class="sh_symbol">&lt;&lt;</span> v<span class="sh_symbol">[</span>i<span class="sh_symbol">]</span> <span class="sh_symbol">&lt;&lt;</span> <span class="sh_string">" "</span>             <span class="sh_comment">// Output no. of occurrences</span></li><li>        <span class="sh_symbol">&lt;&lt;</span> bar<span class="sh_symbol">.</span><span class="sh_function">substr</span><span class="sh_symbol">(</span><span class="sh_number">0</span><span class="sh_symbol">,</span> v<span class="sh_symbol">[</span>i<span class="sh_symbol">])</span>                     <span class="sh_comment">// ...and that no. of asterisks</span></li><li>        <span class="sh_symbol">&lt;&lt;</span> <span class="sh_symbol">(</span>v<span class="sh_symbol">[</span>i<span class="sh_symbol">]</span> <span class="sh_symbol">&gt;</span> <span class="sh_keyword">static_cast</span><span class="sh_symbol">&lt;</span><span class="sh_type">int</span><span class="sh_symbol">&gt;(</span>bar<span class="sh_symbol">.</span><span class="sh_function">size</span><span class="sh_symbol">())</span> <span class="sh_symbol">?</span> <span class="sh_string">"..."</span><span class="sh_symbol">:</span> <span class="sh_string">""</span><span class="sh_symbol">)</span></li><li>        <span class="sh_symbol">&lt;&lt;</span> std<span class="sh_symbol">::</span>endl<span class="sh_symbol">;</span></li><li>    <span class="sh_cbracket">}</span></li><li><span class="sh_cbracket">}</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_type">int</span> <span class="sh_function">main</span><span class="sh_symbol">()</span></li><li><span class="sh_cbracket">{</span></li><li>    std<span class="sh_symbol">::</span><span class="sh_usertype">random_device</span><span class="sh_normal"> </span>random_n<span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li>    <span class="sh_comment">// Setup minimum &amp; maximum checkout periods - times in minutes</span></li><li>    <span class="sh_type">int</span> service_t_min <span class="sh_cbracket">{</span><span class="sh_number">2</span><span class="sh_cbracket">}</span><span class="sh_symbol">,</span> service_t_max <span class="sh_cbracket">{</span><span class="sh_number">15</span><span class="sh_cbracket">}</span><span class="sh_symbol">;</span></li><li>    <span class="sh_usertype">distribution</span><span class="sh_normal"> </span>service_t_d <span class="sh_cbracket">{</span>service_t_min<span class="sh_symbol">,</span> service_t_max<span class="sh_cbracket">}</span><span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li>    <span class="sh_comment">// Setup minimum &amp; maximum number of customers at store opening</span></li><li>    <span class="sh_type">int</span> min_customers <span class="sh_cbracket">{</span><span class="sh_number">15</span><span class="sh_cbracket">}</span><span class="sh_symbol">,</span> max_customers <span class="sh_cbracket">{</span><span class="sh_number">20</span><span class="sh_cbracket">}</span><span class="sh_symbol">;</span></li><li>    <span class="sh_usertype">distribution</span><span class="sh_normal"> </span>n_1st_customers_d <span class="sh_cbracket">{</span>min_customers<span class="sh_symbol">,</span> max_customers<span class="sh_cbracket">}</span><span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li>    <span class="sh_comment">// Setup minimum &amp; maximum intervals between customer arrivals</span></li><li>    <span class="sh_type">int</span> min_arr_interval <span class="sh_cbracket">{</span><span class="sh_number">1</span><span class="sh_cbracket">}</span><span class="sh_symbol">,</span> max_arr_interval <span class="sh_cbracket">{</span><span class="sh_number">5</span><span class="sh_cbracket">}</span><span class="sh_symbol">;</span></li><li>    <span class="sh_usertype">distribution</span><span class="sh_normal"> </span>arrival_interval_d <span class="sh_cbracket">{</span>min_arr_interval<span class="sh_symbol">,</span> max_arr_interval<span class="sh_cbracket">}</span><span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li>    <span class="sh_usertype">size_t</span><span class="sh_normal"> </span>n_checkouts <span class="sh_cbracket">{}</span><span class="sh_symbol">;</span></li><li>    std<span class="sh_symbol">::</span>cout <span class="sh_symbol">&lt;&lt;</span> <span class="sh_string">"Enter the number of checkouts in the supermarket: "</span><span class="sh_symbol">;</span></li><li>    std<span class="sh_symbol">::</span>cin <span class="sh_symbol">&gt;&gt;</span> n_checkouts<span class="sh_symbol">;</span></li><li>    <span class="sh_keyword">if</span> <span class="sh_symbol">(!</span>n_checkouts<span class="sh_symbol">)</span></li><li>    <span class="sh_cbracket">{</span></li><li>        std<span class="sh_symbol">::</span>cout <span class="sh_symbol">&lt;&lt;</span> <span class="sh_string">"Number of checkouts must be greater than 0. Setting to 1."</span> <span class="sh_symbol">&lt;&lt;</span> std<span class="sh_symbol">::</span>endl<span class="sh_symbol">;</span></li><li>        n_checkouts <span class="sh_symbol">=</span> <span class="sh_number">1</span><span class="sh_symbol">;</span></li><li>    <span class="sh_cbracket">}</span></li><li><span style="display:none;">&nbsp;</span></li><li>    std<span class="sh_symbol">::</span><span class="sh_usertype">vector&lt;Checkout&gt;</span><span class="sh_normal"> </span>checkouts <span class="sh_cbracket">{</span>n_checkouts<span class="sh_cbracket">}</span><span class="sh_symbol">;</span></li><li>    std<span class="sh_symbol">::</span><span class="sh_usertype">vector&lt;int&gt;</span><span class="sh_normal"> </span><span class="sh_function">service_times</span><span class="sh_symbol">(</span>service_t_max<span class="sh_symbol">-</span>service_t_min<span class="sh_number">+1</span><span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>    <span class="sh_comment">// Add customers waiting when store opens</span></li><li>    <span class="sh_type">int</span> count <span class="sh_cbracket">{</span><span class="sh_function">n_1st_customers_d</span><span class="sh_symbol">(</span>random_n<span class="sh_symbol">)</span><span class="sh_cbracket">}</span><span class="sh_symbol">;</span></li><li>    std<span class="sh_symbol">::</span>cout <span class="sh_symbol">&lt;&lt;</span> <span class="sh_string">"Customers waiting at store opening: "</span> <span class="sh_symbol">&lt;&lt;</span> count <span class="sh_symbol">&lt;&lt;</span> std<span class="sh_symbol">::</span>endl<span class="sh_symbol">;</span></li><li>    <span class="sh_type">int</span> added <span class="sh_cbracket">{}</span><span class="sh_symbol">;</span></li><li>    <span class="sh_type">int</span> service_t <span class="sh_cbracket">{}</span><span class="sh_symbol">;</span></li><li>    <span class="sh_keyword">while</span> <span class="sh_symbol">(</span>added<span class="sh_symbol">++</span> <span class="sh_symbol">&lt;</span> count<span class="sh_symbol">)</span></li><li>    <span class="sh_cbracket">{</span></li><li>        service_t <span class="sh_symbol">=</span> <span class="sh_function">service_t_d</span><span class="sh_symbol">(</span>random_n<span class="sh_symbol">);</span></li><li>        std<span class="sh_symbol">::</span><span class="sh_function">min_element</span><span class="sh_symbol">(</span>std<span class="sh_symbol">::</span><span class="sh_function">begin</span><span class="sh_symbol">(</span>checkouts<span class="sh_symbol">),</span> std<span class="sh_symbol">::</span><span class="sh_function">end</span><span class="sh_symbol">(</span>checkouts<span class="sh_symbol">))-&gt;</span><span class="sh_function">add</span><span class="sh_symbol">(</span><span class="sh_function">Customer</span><span class="sh_symbol">(</span>service_t<span class="sh_symbol">));</span></li><li>        <span class="sh_symbol">++</span>service_times<span class="sh_symbol">[</span>service_t <span class="sh_symbol">-</span> service_t_min<span class="sh_symbol">];</span></li><li>    <span class="sh_cbracket">}</span></li><li><span style="display:none;">&nbsp;</span></li><li>    <span class="sh_usertype">size_t</span><span class="sh_normal"> </span>time <span class="sh_cbracket">{}</span><span class="sh_symbol">;</span>                                <span class="sh_comment">// Stores time elapsed</span></li><li>    <span class="sh_keyword">const</span> <span class="sh_usertype">size_t</span><span class="sh_normal"> </span>total_time <span class="sh_cbracket">{</span><span class="sh_number">600</span><span class="sh_cbracket">}</span><span class="sh_symbol">;</span>                 <span class="sh_comment">// Duration of simulation - minutes</span></li><li>    <span class="sh_usertype">size_t</span><span class="sh_normal"> </span>longest_q <span class="sh_cbracket">{}</span><span class="sh_symbol">;</span>                           <span class="sh_comment">// Stores longest checkout queue length</span></li><li><span style="display:none;">&nbsp;</span></li><li>    <span class="sh_comment">// Period until next customer arrives</span></li><li>    <span class="sh_type">int</span> new_cust_interval <span class="sh_cbracket">{</span><span class="sh_function">arrival_interval_d</span><span class="sh_symbol">(</span>random_n<span class="sh_symbol">)</span><span class="sh_cbracket">}</span><span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li>    <span class="sh_comment">// Run store simulation for period of total_time minutes</span></li><li>    <span class="sh_keyword">while</span> <span class="sh_symbol">(</span>time <span class="sh_symbol">&lt;</span> total_time<span class="sh_symbol">)</span>                      <span class="sh_comment">// Simulation loops over time</span></li><li>    <span class="sh_cbracket">{</span></li><li>        <span class="sh_symbol">++</span>time<span class="sh_symbol">;</span>                                      <span class="sh_comment">// Increment by 1 minute</span></li><li><span style="display:none;">&nbsp;</span></li><li>        <span class="sh_comment">// New customer arrives when arrival interval is zero</span></li><li>        <span class="sh_keyword">if</span> <span class="sh_symbol">(--</span>new_cust_interval <span class="sh_symbol">==</span> <span class="sh_number">0</span><span class="sh_symbol">)</span></li><li>        <span class="sh_cbracket">{</span></li><li>            service_t <span class="sh_symbol">=</span> <span class="sh_function">service_t_d</span><span class="sh_symbol">(</span>random_n<span class="sh_symbol">);</span>         <span class="sh_comment">// Random customer service time</span></li><li>            std<span class="sh_symbol">::</span><span class="sh_function">min_element</span><span class="sh_symbol">(</span>std<span class="sh_symbol">::</span><span class="sh_function">begin</span><span class="sh_symbol">(</span>checkouts<span class="sh_symbol">),</span> std<span class="sh_symbol">::</span><span class="sh_function">end</span><span class="sh_symbol">(</span>checkouts<span class="sh_symbol">))-&gt;</span><span class="sh_function">add</span><span class="sh_symbol">(</span><span class="sh_function">Customer</span><span class="sh_symbol">(</span>service_t<span class="sh_symbol">));</span></li><li>            <span class="sh_symbol">++</span>service_times<span class="sh_symbol">[</span>service_t <span class="sh_symbol">-</span> service_t_min<span class="sh_symbol">];</span>  <span class="sh_comment">// Record service time</span></li><li><span style="display:none;">&nbsp;</span></li><li>            <span class="sh_comment">// Update record of the longest queue occurring</span></li><li>            <span class="sh_keyword">for</span> <span class="sh_symbol">(</span><span class="sh_keyword">auto</span> <span class="sh_symbol">&amp;</span> checkout <span class="sh_symbol">:</span> checkouts<span class="sh_symbol">)</span></li><li>                longest_q <span class="sh_symbol">=</span> std<span class="sh_symbol">::</span><span class="sh_function">max</span><span class="sh_symbol">(</span>longest_q<span class="sh_symbol">,</span> checkout<span class="sh_symbol">.</span><span class="sh_function">qlength</span><span class="sh_symbol">());</span></li><li><span style="display:none;">&nbsp;</span></li><li>            new_cust_interval <span class="sh_symbol">=</span> <span class="sh_function">arrival_interval_d</span><span class="sh_symbol">(</span>random_n<span class="sh_symbol">);</span></li><li>        <span class="sh_cbracket">}</span></li><li><span style="display:none;">&nbsp;</span></li><li>        <span class="sh_comment">// Update the time in the checkouts - serving the 1st customer in each queue</span></li><li>        <span class="sh_keyword">for</span> <span class="sh_symbol">(</span><span class="sh_keyword">auto</span> <span class="sh_symbol">&amp;</span> checkout <span class="sh_symbol">:</span> checkouts<span class="sh_symbol">)</span></li><li>            checkout<span class="sh_symbol">.</span><span class="sh_function">time_increment</span><span class="sh_symbol">();</span></li><li>    <span class="sh_cbracket">}</span></li><li><span style="display:none;">&nbsp;</span></li><li>    std<span class="sh_symbol">::</span>cout <span class="sh_symbol">&lt;&lt;</span> <span class="sh_string">"Maximum queue length = "</span> <span class="sh_symbol">&lt;&lt;</span> longest_q <span class="sh_symbol">&lt;&lt;</span> std<span class="sh_symbol">::</span>endl<span class="sh_symbol">;</span></li><li>    std<span class="sh_symbol">::</span>cout <span class="sh_symbol">&lt;&lt;</span> <span class="sh_string">"</span><span class="sh_specialchar">\n</span><span class="sh_string">Histogram of service times:</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">;</span></li><li>    <span class="sh_function">histogram</span><span class="sh_symbol">(</span>service_times<span class="sh_symbol">,</span> service_t_min<span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>    std<span class="sh_symbol">::</span>cout <span class="sh_symbol">&lt;&lt;</span> <span class="sh_string">"</span><span class="sh_specialchar">\n</span><span class="sh_string">Total number of customers today: "</span></li><li>            <span class="sh_symbol">&lt;&lt;</span> std<span class="sh_symbol">::</span><span class="sh_function">accumulate</span><span class="sh_symbol">(</span>std<span class="sh_symbol">::</span><span class="sh_function">begin</span><span class="sh_symbol">(</span>service_times<span class="sh_symbol">),</span> std<span class="sh_symbol">::</span><span class="sh_function">end</span><span class="sh_symbol">(</span>service_times<span class="sh_symbol">),</span> <span class="sh_number">0</span><span class="sh_symbol">)</span></li><li>            <span class="sh_symbol">&lt;&lt;</span> std<span class="sh_symbol">::</span>endl<span class="sh_symbol">;</span></li><li><span class="sh_cbracket">}</span></li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">// Simulating a supermarket with multiple checkouts
#include &lt;iostream&gt;                              // For s<a href="/ref/tan.html" target="_blank" class="sh_url">tan</a>dard streams
#include &lt;iomanip&gt;                               // For stream manipulators
#include &lt;vector&gt;                                // For vector container
#include &lt;string&gt;                                // For string class
#include &lt;numeric&gt;                               // For accumulate()
#include &lt;algorithm&gt;                             // For min_element &amp; max_element
#include &lt;random&gt;                                // For random number generation
#include "Customer.h"
#include "Checkout.h"

u<a href="/ref/sin.html" target="_blank" class="sh_url">sin</a>g std::string;
using distribution = std::uniform_int_distribution&lt;&gt;;

// Output histogram of service times
void histogram(const std::vector&lt;int&gt;&amp; v, int min)
{
    string bar (60, '*');                          // Row of asterisks for bar
    for (size_t i {}; i &lt; v.size(); ++i)
    {
        std::cout &lt;&lt; std::setw(3) &lt;&lt; i+min &lt;&lt; " "    // Service time is index + min
        &lt;&lt; std::setw(4) &lt;&lt; v[i] &lt;&lt; " "             // Output no. of occurrences
        &lt;&lt; bar.substr(0, v[i])                     // ...and that no. of asterisks
        &lt;&lt; (v[i] &gt; static_cast&lt;int&gt;(bar.size()) ? "...": "")
        &lt;&lt; std::endl;
    }
}

int main()
{
    std::random_device random_n;

    // Setup minimum &amp; maximum checkout periods - times in minutes
    int service_t_min {2}, service_t_max {15};
    distribution service_t_d {service_t_min, service_t_max};

    // Setup minimum &amp; maximum number of customers at store opening
    int min_customers {15}, max_customers {20};
    distribution n_1st_customers_d {min_customers, max_customers};

    // Setup minimum &amp; maximum intervals between customer arrivals
    int min_arr_interval {1}, max_arr_interval {5};
    distribution arrival_interval_d {min_arr_interval, max_arr_interval};

    size_t n_checkouts {};
    std::cout &lt;&lt; "Enter the number of checkouts in the supermarket: ";
    std::cin &gt;&gt; n_checkouts;
    if (!n_checkouts)
    {
        std::cout &lt;&lt; "Number of checkouts must be greater than 0. Setting to 1." &lt;&lt; std::endl;
        n_checkouts = 1;
    }

    std::vector&lt;Checkout&gt; checkouts {n_checkouts};
    std::vector&lt;int&gt; service_times(service_t_max-service_t_min+1);

    // Add customers waiting when store opens
    int count {n_1st_customers_d(random_n)};
    std::cout &lt;&lt; "Customers waiting at store opening: " &lt;&lt; count &lt;&lt; std::endl;
    int added {};
    int service_t {};
    while (added++ &lt; count)
    {
        service_t = service_t_d(random_n);
        std::min_element(std::begin(checkouts), std::end(checkouts))-&gt;add(Customer(service_t));
        ++service_times[service_t - service_t_min];
    }

    size_t time {};                                // Stores time elapsed
    const size_t total_time {600};                 // Duration of simulation - minutes
    size_t longest_q {};                           // Stores longest checkout queue length

    // Period until next customer arrives
    int new_cust_interval {arrival_interval_d(random_n)};

    // Run store simulation for period of total_time minutes
    while (time &lt; total_time)                      // Simulation loops over time
    {
        ++time;                                      // Increment by 1 minute

        // New customer arrives when arrival interval is zero
        if (--new_cust_interval == 0)
        {
            service_t = service_t_d(random_n);         // Random customer service time
            std::min_element(std::begin(checkouts), std::end(checkouts))-&gt;add(Customer(service_t));
            ++service_times[service_t - service_t_min];  // Record service time

            // Update record of the longest queue occurring
            for (auto &amp; checkout : checkouts)
                longest_q = std::max(longest_q, checkout.qlength());

            new_cust_interval = arrival_interval_d(random_n);
        }

        // Update the time in the checkouts - serving the 1st customer in each queue
        for (auto &amp; checkout : checkouts)
            checkout.time_increment();
    }

    std::cout &lt;&lt; "Maximum queue length = " &lt;&lt; longest_q &lt;&lt; std::endl;
    std::cout &lt;&lt; "\nHistogram of service times:\n";
    histogram(service_times, service_t_min);

    std::cout &lt;&lt; "\nTotal number of customers today: "
            &lt;&lt; std::accumulate(std::begin(service_times), std::end(service_times), 0)
            &lt;&lt; std::endl;
}</pre></div></div>
<br>
直接使用 using 指令可以减少代码输入，简化代码。顾客服务次数记录在 vector 中。服务时间减去 service_times 的最小值可以用来索引需要自增的 vector 元素，这导致 vector 的第一个元素会记录下最少服务时间的发生次数。histogram() 函数会以水平条形图的形式生成每个服务时间出现次数的柱状图。<br>
<br>
输入的唯一数字是 checkouts。此处选择将模拟持续时间设置为 600 分钟，也可以用参数输入这个时间。main() 函数生成了顾客服务时间，超市开门时等在门外的顾客数，以及顾客到达时间间隔的分布对象。它表明顾客在同一时间到达。我们可以轻松地将这个程序扩展为每次到达的顾客数是一个处于一定范围内的随机数。<br>
<br>
顾客总是可以被分配到最短的结账队列。通过调用 min_elemeiit() 算法可以找到最短的 Checkout 对象队列。这会使用&lt;运算符比较元素，但是这个算法的另一个版本有第三个参数可以指定比较函数。在这次模拟开始前，当超市开门营业时，在门外等待的顾客的初始 序列被添加到 Checkout 对象中，然后服务时间记录被更新。<br>
<br>
模拟在 <a href="/view/180.html" target="_blank">while 循环</a>中进行。在每次循环中，time 都会增加 1 分钟。在下一个顾客到达期间，new_cust_interval 会在每次循环中减小，直到等于 0。用新的随机服务时间生成新的顾客，然后把它加到最短的 Checkout 对象队列中。这个时候也会更新变量 longest_q，因为在添加新顾客后，可能出现新的最长队列。然后调用每个 Checkout 对象的 time_increment() 函数来处理队列中的第一个顾客。<br>
<br>
下面是一些示例输出：
<p class="info-box">
Enter the number of checkouts in the supermarket: 3<br>
Customers waiting at store opening: 19<br>
Maximum queue length = 10<br>
<br>
Histogram of service times:<br>
&nbsp; 2&nbsp;&nbsp; 16 ****************<br>
&nbsp; 3&nbsp;&nbsp; 15 ***************<br>
&nbsp; 4&nbsp;&nbsp; 12 ************<br>
&nbsp; 5&nbsp;&nbsp; 11 ***********<br>
&nbsp; 6&nbsp;&nbsp; 17 *****************<br>
&nbsp; 7&nbsp;&nbsp; 20 ********************<br>
&nbsp; 8&nbsp;&nbsp; 18 ******************<br>
&nbsp; 9&nbsp;&nbsp; 16 ****************<br>
10&nbsp;&nbsp; 10 **********<br>
11&nbsp;&nbsp; 12 ************<br>
12&nbsp;&nbsp; 16 ****************<br>
13&nbsp;&nbsp; 21 *********************<br>
14&nbsp;&nbsp; 17 *****************<br>
15&nbsp;&nbsp; 21 *********************<br>
<br>
Total number of customers today: 222</p>
这里有 3 个结账柜台。将它们设为 2 个时，最长队列的长度达到 42——已经长到会让顾客放弃付款。还可以做更多改进，让模拟更加真实。均匀分配并不符合实际，例如，顾客通常成群结队到来。可以增加一些其他的因素，比如收银员休息时间、某个收银员生病工作状态不佳，这些都会导致顾客不选择这个柜台结账。<br>
</div>
