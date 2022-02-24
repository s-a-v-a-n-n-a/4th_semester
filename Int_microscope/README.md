**INVESTIGATION OF COPY AND MOVE OPERATORS**
===================================================
**AUTHORS**
-----------
Research was conducted by a second year student at MIPT Anna Savchuk in 2022.

**BEGINNING**
-------------
This project contains intercepted realisation of 32-bit int type. In the README the difference between compilator behavior when using move operators and not. 

Important flag of compilator is `-fno-elide-constructors`. It disables all optimizations connected with copy operators.

OS: Linux.

**HOW TO CONDUCT YOUR OWN INVESTIGATION**
-----------------------------------------
<li>
  If you want to play with using move operators or not, go to `math_structures/Intercepted_int.hpp` and comment or uncomment the line where MOVE_ON macros is defined.
</li>
<li>
  In your console type <pre><code>make clean</code></pre>. It just make sense :).
</li>
<li>
  Then type <pre><code>make run</code></pre>. Enjoy the picture!
</li>
<li>
  If you want to observe text dump, just open <pre><code>Int_dump.html</code></pre>.
</li>

**TO BE CONTINUED**
-------------------
You will be able to observe some examples soon.

**LITERATURE AND LINKS**
------------------------
<li> 
[Author's github page](https://github.com/s-a-v-a-n-n-a)
</li>
<li>
  [rvalue-links (short <s>int</s>) in Russian](https://habr.com/ru/post/226229/)
</li>
<li>
  [rvalue-links (long <s>int</s>) in Russian](https://habr.com/ru/post/322132/)
</li>