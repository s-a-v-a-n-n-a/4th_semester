**STD::MOVE vs STD::FORWARDING**
================================
**AUTHORS**
-----------
Research was conducted by a second year student at MIPT Anna Savchuk in 2022. All pictures were also creates by author.

**INTRODUCTION**
--------------------
In [last article](https://github.com/s-a-v-a-n-n-a/4th_semester/tree/main/Int_microscope#readme) about move and copy investigation it was established that move is better in effectiveness. But is it really appropriate for constant usage and why?

In this investigation `std::move` and `std::forward` will be studied and some illustrating examples will be shown.

**INSTRUMENTS**
---------------
The instruments are actually the same as in the above-mentioned article but the main information will be doubled here for busy people.

This project contains intercepted realisation of 32-bit int type.

OS: Linux.

The  author used visual dump in dot to conduct the investigation.

There are several designations in graphical dump used. 
<li>
  Red structions show copy operators. Green ones are for move operators.
</li>
<li>
  Black dashed arrows are for showing the time that variable exists. They link its constructor and destructor respectively.
</li>
<li>
  Black solid lines show the connections between operations. If two numbers are added, the reader will be able to see connections between struction for operator+ and structions for variables. 
</li>
<li>
  To show the changes of the variable red solid arrows used. As not to clutter up the picture there is no red lines between constructors and destructors if they are only operators that changed the variable.
</li>
<li>
  Grey clusters used for entering the scope of a function. Its name is also written on clusrter's top.
</li>
<li>
  <em><b>Picture 0</b></em> shows the organization of information in rectangle boxes. For reasons of clarity the history shows operations since last change of variable.
</li>
<li>
  Hexagons show binary operations.
</li>

<img src="Research/Example.jpg" alt="Picture 0" width="400">
<em><b>Picture 0</b></em>

<em>The structure of rectangles.</em>

To disable copy elision `-fno-elide-constructors` flag is used.

**COMMENT**
-----------

In reasons of author's education `my_move` removes `std::move` and `my_forward` removes `std::forward`. They actually do the same but we need to understand how they work.

**MOTIVATION**
--------------
Imagine a situation when you want to optimize your program by moving the content from place to place but compiler copies it in reasons that are set in its rules. For example, working with different containers we sometimes want to move the content of variable than to copy it:

<pre><code>template< class T >
void imitaion(T&& arg) 
{
    Spy spy(__FUNCTION__);
    
    // like writing into container
    volatile auto local_tmp = arg;
}

template< class T >
void wrapper(T&& arg) 
{
    Spy spy(__FUNCTION__);
    
    imitaion(arg);
}

void test()
{
    wrapper(Intercepted_int(22));
}
</code></pre>

Compilator copies the argument because it turns into lvalue in `wrapper`. How that can be fixed? `std::move` can help:

<pre><code>template< class T >
void imitaion_with_move(T&& arg) 
{
    Spy spy(__FUNCTION__);
    
    // like writing into container
    volatile auto local_tmp = my_move(arg);
}

template< class T >
void wrapper(T&& arg) 
{
    Spy spy(__FUNCTION__);
    
    imitaion_with_move(arg);
}

void test()
{
    wrapper(Intercepted_int(22));
}
</code></pre>

Now we can observe the results:

| NOTHING WAS USED | MY_MOVE WAS USED |
|:-----------------------------------------------------------------:|:------------------------------------------------------------:|
| <img src="Research/Nothing_used.png" alt="Picture 1" width="400"> | <img src="Research/My_move.png" alt="Picture 2" width="400"> |
| ***Picture 1***<br/>Temporary variable turns into lvalue          | ***Picture 2***<br/>The lvalue is forced to be rvalue        |

**FIRST CONCLUSION**
--------------------
It can be seen that `std::move` is used to make everything an rvalue. That is true because it firstly removes any references and then uses static_cast. It is a really useful thing because it calls existing move operators and allows to work with such primitives as containers when there are no default and copy constructors. 

<img src="Research/std_move.jpg" alt="Picture 3" width="500">

**PROBLEM APPEARED**
--------------------
Let's look at the following example:

<pre><code>template< class T >
void imitaion_with_move(T&& arg) 
{
    Spy spy(__FUNCTION__);
    
    // like writing into container
    volatile auto local_tmp = my_move(arg);
}

template< class T >
void wrapper(T&& arg) 
{
    Spy spy(__FUNCTION__);
    
    imitaion_with_move(arg);
}

void test()
{
    VAR(a, 20);
    
    wrapper(a);
}
</code></pre>

Below we will make sure that our variable `a` will turn into zero (because it can be considered as int's default state) and it is not its desired behaviour.

Now `std::forward` comes to help us:

<pre><code>template< class T >
void imitaion_with_forward(T&& arg) 
{
    Spy spy(__FUNCTION__);
    
    // like writing into container
    volatile auto local_tmp = my_forward<T>(arg);
}

template< class T >
void wrapper(T&& arg) 
{
    Spy spy(__FUNCTION__);
    
    imitaion_with_forward(my_forward<T>(arg));
}

void test()
{
    VAR(a, 20);
    
    wrapper(a);
}
</code></pre>

Time to see the changes:

| STEALING MOVE | FAIR FORWARD |
|:----------------------------------------------------------------------------:|:----------------------------------------------------------------------------:|
| <img src="Research/Spurious_move_of_lvalue.png" alt="Picture 4" width="400"> | <img src="Research/Using_forward_on_lvalue.png" alt="Picture 5" width="400"> |
| ***Picture 4***<br/>In destructor `a` turns into 0, but it never changed intentionally         | ***Picture 5***<br/>Everything is ok        |

**A TINY CATCH**
----------------
Attentive reader may argue: if we pass this argument without `std::forward` the result will be the same:

| PASSING LVALUE WITH FORWARD | PASSING LVALUE WITHOUT FORWARD |
|:----------------------------------------------------------------------------:|:-------------------------------------------------------------------:|
| <img src="Research/Using_forward_on_lvalue.png" alt="Picture 5" width="400"> | <img src="Research/Copying_lvalue.png" alt="Picture 6" width="400"> |
| ***Picture 5***        | ***Picture 6***       |

The answer is simple: everything is about passed argument. Let us see the example where we pass rvalue as before:

<pre><code>template< class T >
void imitaion_with_forward(T&& arg) 
{
    Spy spy(__FUNCTION__);
    
    // like writing into container
    volatile auto local_tmp = my_forward<T>(arg);
}

template< class T >
void imitaion(T&& arg) 
{
    Spy spy(__FUNCTION__);
    
    // like writing into container
    volatile auto local_tmp = arg;
}

template< class T >
void wrapper(T&& arg) 
{
    Spy spy(__FUNCTION__);
    
    imitaion_with_forward(my_forward<T>(arg)); // or just `imitation(arg);` in other case
}

void test()
{
    wrapper(Intercepted_int(20));
}
</code></pre>

The result is:

| PASSING RVALUE WITH FORWARD | PASSING RVALUE WITHOUT FORWARD |
|:----------------------------------------------------------------------------:|:-------------------------------------------------------------------:|
| <img src="Research/Using_forward_on_rvalue.png" alt="Picture 7" width="400"> | <img src="Research/Nothing_used.png" alt="Picture 8" width="400"> |
| ***Picture 7***<br/>Forward turned into move        | ***Picture 8***<br/>Copy again       |

**SECOND CONCLUSION**
---------------------
Now it is clear that if we want to save values in intentionally created variables and avoid copies of one temporary `std::forward` is good enough. It casts lvalue to lvalue and rvalue of any type to rvalue.

<img src="Research/std_forward.jpg" alt="Picture 9" width="500">

**WHY NOT ONLY STD::FORWARD**
-----------------------------
A very good question if we can use only `std::forward` and never `std::move`. The answer is "no". Now the reason in ideas of their appearing. `std::forward` demands type specifying which overfills the code. In addition, which is also very important, it is supposed to be used for perfect forwarding, when passing argument through several amount of functions that "eat" the type. These two reasons are enough to use `std::forward` only for specific purpose and use `std::move` instead where it is needed.

**DISCUSSION**
--------------
Now we can get the understanding of how to solve the problem stated in introduction. The conclusion is written everywhere but for very busy people it will be also doubled here: "`std::move` is used for displacing and `std::forward` is used for universal referencing." It is quite important to differentiate these two purposes and to use developer-provided tools correctly. 

**LITERATURE AND LINKS**
------------------------

 - [Author's github page](https://github.com/s-a-v-a-n-n-a)

 - [About lvalues and rvalues](https://habr.com/ru/post/568306/)

 - [cppreference: remove_reference](https://en.cppreference.com/w/cpp/types/remove_reference)

 - [cppreference: std::move](https://en.cppreference.com/w/cpp/utility/move)

 - [cppreference: std::forward](https://en.cppreference.com/w/cpp/utility/forward)
