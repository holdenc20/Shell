<!DOCTYPE html>
<html><head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <!-- The above 3 meta tags *must* come first in the head; any other head content must come *after* these tags -->
    <meta name="generator" content="pandoc">
    <meta name="description" content="">

    <title>CS3650 Computer Systems – Project 1: Shell</title>

    <!-- Bootstrap core CSS -->
    <link href="css/bootstrap.min.css" rel="stylesheet">

    <!-- IE10 viewport hack for Surface/desktop Windows 8 bug -->
    <link href="css/ie10-viewport-bug-workaround.css" rel="stylesheet">

    <!-- Custom styles for this template -->
    <link href="css/dashboard.css" rel="stylesheet">

    <style type="text/css">code{white-space: pre;}</style>
<!-- <style type="text/css">.sidebar ul{padding-left: 10px;}</style> -->
    <style type="text/css">
pre > code.sourceCode { white-space: pre; position: relative; }
pre > code.sourceCode > span { display: inline-block; line-height: 1.25; }
pre > code.sourceCode > span:empty { height: 1.2em; }
code.sourceCode > span { color: inherit; text-decoration: inherit; }
div.sourceCode { margin: 1em 0; }
pre.sourceCode { margin: 0; }
@media screen {
div.sourceCode { overflow: auto; }
}
@media print {
pre > code.sourceCode { white-space: pre-wrap; }
pre > code.sourceCode > span { text-indent: -5em; padding-left: 5em; }
}
pre.numberSource code
  { counter-reset: source-line 0; }
pre.numberSource code > span
  { position: relative; left: -4em; counter-increment: source-line; }
pre.numberSource code > span > a:first-child::before
  { content: counter(source-line);
    position: relative; left: -1em; text-align: right; vertical-align: baseline;
    border: none; display: inline-block;
    -webkit-touch-callout: none; -webkit-user-select: none;
    -khtml-user-select: none; -moz-user-select: none;
    -ms-user-select: none; user-select: none;
    padding: 0 4px; width: 4em;
    color: #aaaaaa;
  }
pre.numberSource { margin-left: 3em; border-left: 1px solid #aaaaaa;  padding-left: 4px; }
div.sourceCode
  {   }
@media screen {
pre > code.sourceCode > span > a:first-child::before { text-decoration: underline; }
}
code span.al { color: #ff0000; font-weight: bold; } /* Alert */
code span.an { color: #60a0b0; font-weight: bold; font-style: italic; } /* Annotation */
code span.at { color: #7d9029; } /* Attribute */
code span.bn { color: #40a070; } /* BaseN */
code span.bu { } /* BuiltIn */
code span.cf { color: #007020; font-weight: bold; } /* ControlFlow */
code span.ch { color: #4070a0; } /* Char */
code span.cn { color: #880000; } /* Constant */
code span.co { color: #60a0b0; font-style: italic; } /* Comment */
code span.cv { color: #60a0b0; font-weight: bold; font-style: italic; } /* CommentVar */
code span.do { color: #ba2121; font-style: italic; } /* Documentation */
code span.dt { color: #902000; } /* DataType */
code span.dv { color: #40a070; } /* DecVal */
code span.er { color: #ff0000; font-weight: bold; } /* Error */
code span.ex { } /* Extension */
code span.fl { color: #40a070; } /* Float */
code span.fu { color: #06287e; } /* Function */
code span.im { } /* Import */
code span.in { color: #60a0b0; font-weight: bold; font-style: italic; } /* Information */
code span.kw { color: #007020; font-weight: bold; } /* Keyword */
code span.op { color: #666666; } /* Operator */
code span.ot { color: #007020; } /* Other */
code span.pp { color: #bc7a00; } /* Preprocessor */
code span.sc { color: #4070a0; } /* SpecialChar */
code span.ss { color: #bb6688; } /* SpecialString */
code span.st { color: #4070a0; } /* String */
code span.va { color: #19177c; } /* Variable */
code span.vs { color: #4070a0; } /* VerbatimString */
code span.wa { color: #60a0b0; font-weight: bold; font-style: italic; } /* Warning */
    </style>
  </head>


  <body>
        <nav class="navbar navbar-inverse navbar-fixed-top">
          <div class="container-fluid">
    <!--    <nav class="navbar navbar-default navbar-static-top">
    <div class="container"> -->
            <div class="navbar-header">
              <button type="button" class="navbar-toggle collapsed" data-toggle="collapse" data-target="#navbar" aria-expanded="false" aria-controls="navbar">
                <span class="sr-only">Toggle navigation</span>
                <span class="icon-bar"></span>
                <span class="icon-bar"></span>
                <span class="icon-bar"></span>
              </button>
              <a class="navbar-brand" href="./">CS3650 Computer Systems</a>
            </div>
            <div id="navbar" class="navbar-collapse collapse">
              <ul class="nav navbar-nav">
                <li><a href="general.html">General</a></li>
                <li><a href="syllabus.html">Syllabus</a></li>
                <li><a href="schedule.html">Schedule</a></li>
                <li><a href="oh.html">Office Hours</a></li>
                <li><a href="hw.html">Assignments</a></li>
                <li><a href="resources.html">Resources</a></li>
    <!--            <li class="dropdown">
                  <a href="#" class="dropdown-toggle" data-toggle="dropdown" role="button" aria-haspopup="true" aria-expanded="false">Assignments<span class="caret"></span></a>
                  <ul class="dropdown-menu">
                    <li><a href="delivery.html">General</a></li>
                    <li><a href="hw.html">Assignments</a></li>
    <!-                <li role="separator" class="divider"></li>
                    <li class="dropdown-header">Nav header</li>
                    <li><a href="#">Separated link</a></li>
                    <li><a href="#">One more separated link</a></li>
    ->
                  </ul>
    </li> -->
                  </ul>
                
              
            </div>
          </div>
        </nav>

    <div class="container-fluid">
      <div class="row">
        <div id="sidebar" class="col-sm-3 col-md-2 sidebar">
          <!--<ul class="nav nav-sidebar">
            <li class="active"><a href="#">Overview <span class="sr-only">(current)</span></a></li>
          </ul>-->
          <h1 class="side-title">Project 1: Shell</h1>
          <ul>
          <li><a href="#part-1">Part 1: Tokenizer &amp; Basic Shell</a></li>
          <li><a href="#p1t1">Task 1.1: Shell Tokenizer</a></li>
          <li><a href="#p1t2">Task 1.2: Basic Shell</a></li>
          <li><a href="#part-2">Part 2: Advanced Shell Features</a>
          <ul>
          <li><a href="#p2t1">Task 2.1: Built-in Commands</a></li>
          </ul></li>
          <li><a href="#p2t2">Task 2.2: Sequencing Using <code>;</code></a>
          <ul>
          <li><a href="#p2t3">Task 2.3: Input Redirection <code>&lt;</code></a></li>
          <li><a href="#p2t4">Task 2.4: Output Redirection <code>&gt;</code></a></li>
          <li><a href="#p2t5">Task 2.5: Pipe <code>|</code></a></li>
          </ul></li>
          <li><a href="#deliverables">Deliverables</a></li>
          <li><a href="#the-grammar-of-shell">The Grammar of Shell</a></li>
          <li><a href="#strategy">Shell Implementation Strategy</a></li>
          <li><a href="#examples">Examples</a></li>
          <li><a href="#going-further">Going Further</a></li>
          <li><a href="#using-the-provided-makefile">Using the Provided Makefile</a></li>
          <li><a href="#hints-tips">Hints &amp; Tips</a></li>
          </ul>
        </div>
        <div class="col-sm-9 col-sm-offset-3 col-md-10 col-md-offset-2 main">
        

<div class="box submission">
<dl>
<dt>Due:</dt>
<dd><p><span>Friday, February 24, 10pm</span></p>
</dd>
<dt>Starter code:</dt>
<dd><p>See <a href="https://northeastern.instructure.com/courses/133161/assignments/1768297"><span>Project 1</span> on Canvas</a> for the Github Classroom link.</p>
</dd>
<dt>Submission:</dt>
<dd><p>This is a <strong>pair assignment</strong>, but you can work alone, if you so choose.</p>
<p>Submit the contents of your repository via Gradescope. See <a href="#deliverables">Deliverables</a> below for what to submit. If you are working with a partner, do not forget to include their name with the submission.</p>
</dd>
<dt>Team registration:</dt>
<dd><p>Use the Google form accessible via this project’s <a href="https://northeastern.instructure.com/courses/133161/assignments/1768297">Canvas page</a> to register your partner or that you want to work alone. If you are registering a partner, only 1 of the people in the team needs to register. Teams can have at most 2 people.</p>
</dd>
</dl>
</div>
<div class="box important">
<p>Do not use <code>login.khoury.northeastern.edu</code> to work on this assignment. Use your XOA VM or a local Linux environment, if you have one.</p>
</div>
<p>The first project of this class, is to write a <a href="https://en.wikipedia.org/wiki/Unix_shell">Shell</a>. This project is more involved than the previous assignments and requires more planning as well as programming. You are asked to develop a moderately complex piece of C code from scratch. Start early with planning, experimenting, and prototyping.</p>
<h1 id="part-1">Part 1: Tokenizer &amp; Basic Shell</h1>
<p>The first part of this assignment is to get a basic working shell. For this, we will first need to develop a <em>tokenizer</em>, that is, a piece of code that helps us split up an input line into meaningful <em>tokens</em>. The second task is to develop a basic shell that uses this tokenizer to process input from the user.</p>
<h1 id="p1t1">Task 1.1: Shell Tokenizer</h1>
<p>Before we can execute commands (or combination of them) we need to be able to process a command line and split it into chunks (lexical units), called <a href="https://en.wikipedia.org/wiki/Lexical_analysis#Token"><em>tokens</em></a>. The input of a tokenizer is a string and the output is a list of tokens. Our shell will use the tokens described in the table below. The tokens <code>(</code>, <code>)</code>, <code>&lt;</code>, <code>&gt;</code>, <code>;</code>, <code>|</code>, and the whitespace characters (space <code>' '</code>, tab <code>'\t'</code>) are <em>special</em>. Whitespace is not a token, but might separate tokens.</p>
<table class="table table-bordered table-hover">
<colgroup>
<col style="width: 21%">
<col style="width: 78%">
</colgroup>
<thead>
<tr class="header">
<th>Token(s)</th>
<th>Description / Meaning</th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td><code>(</code> <code>)</code></td>
<td>Parentheses allow grouping shell expressions</td>
</tr>
<tr class="even">
<td><code>&lt;</code></td>
<td>Input redirection</td>
</tr>
<tr class="odd">
<td><code>&gt;</code></td>
<td>Output redirection</td>
</tr>
<tr class="even">
<td><code>;</code></td>
<td>Sequencing</td>
</tr>
<tr class="odd">
<td><code>|</code></td>
<td>Pipe</td>
</tr>
<tr class="even">
<td><code>"hello &lt; (world;"</code></td>
<td>Quotes suspend the meaning of special characters (spaces, parentheses, …)</td>
</tr>
<tr class="odd">
<td><code>ls</code></td>
<td>Word (a sequence of non-special characters)</td>
</tr>
</tbody>
</table>
<p>Your first task is to write a function that takes a string (i.e., <code class="sourceCode c"><span class="dt">char</span> *</code> in C) as an argument and returns a list (array, linked list, etc.) of tokens. The maximum input string length can be explicitly bounded, but needs to be at least 255 characters.</p>
<p>You also need to provide a demo driver, <code>tokenize.c</code> that will showcase your function. The driver should read a single line from standard input and print out all the tokens in the line, one token per line. For example:</p>
<pre><code>$ echo 'this &lt; is &gt; a demo "This is a sentence" ; "some ( special &gt; chars"' | ./tokenize
this
&lt;
is 
&gt;
a
demo
This is a sentence
;
some ( special &gt; chars</code></pre>
<p>In this example, we print the example string to standard output, but immediately <a href="https://en.wikipedia.org/wiki/Pipeline_(Unix)"><em>pipe</em></a> that output into the input of the <code>tokenize</code> program. We will implement piping in our own shell in the next assignment.</p>
<p>Whitespace that is not in quotes should not be included in any token.</p>
<p>To help you get started writing a tokenizer, see the example included with the starter code.</p>
<p>What we are implementing here is a <a href="https://en.wikipedia.org/wiki/Deterministic_finite_automaton">Deterministic Finite-state Automaton (DFA)</a>, which is a recognizer for <a href="https://en.wikipedia.org/wiki/Regular_language">Reguar languages</a>. While not necessary to complete this assignment, you might want to read up on those to get a deeper understanding if you are interested.</p>
<h1 id="p1t2">Task 1.2: Basic Shell</h1>
<p>The next step is to implement basic shell functionality running a single user-specified command at a time. The shell should display a prompt, read the command and its arguments, and execute the command. This should be performed in a loop, until the user requests to exit the shell. The commands can have 0 or more arguments and these arguments may be enclosed in double quotes <code>"</code>, in which case the enclosed string is treated as a single argument.</p>
<p>Example interaction:</p>
<pre><code>$ ./shell
Welcome to mini-shell.
shell $ whoami
ferd
shell $ ls -aF
./        .git/     shell*    shell.o   tokens.h  vect.c    vect.o
../       Makefile  shell.c   tokens.c  tokens.o  vect.h
shell $ echo this should be printed
this should be printed
shell $ echo this is; echo a new line
this is
a new line
shell $ exit
Bye bye.</code></pre>
<p>Here are the requirements for the basic shell</p>
<ol type="1">
<li><p>After starting, the shell should print a welcome message: <code>Welcome to mini-shell.</code></p></li>
<li><p>You must have the following prompt: <code>shell $</code> in front of each command line that is entered.</p></li>
<li><p>The maximum size of a single line shall be at least 255 characters. Specify this number as a (global) constant.</p></li>
<li><p>Each command can have 0 or more arguments.</p></li>
<li><p>Any string enclosed in double quotes (<code>"</code>) shall be treated as a single argument, regardless of whether it contains spaces or special characters.</p></li>
<li><p>When you launch a new child process from your shell, the child process should run in the foreground by default until it is completed. The prompt should be printed again and the shell should wait for the next line of input.</p></li>
<li><p>If the user enters the command <code>exit</code>, the shell should print out <code>Bye bye.</code> and exit.</p></li>
<li><p>If the user presses <em>Ctrl-D</em> (end-of-file), the shell should exit in the same manner as above.</p></li>
<li><p>If a command is not found, your shell should print out an error message, <code>[command]: command not found</code> (replacing “<code>[command]</code>” with the actual command name), and resume execution.</p>
<p>For example:</p>
<pre><code>shell $ dfg
dfg: command not found
shell $</code></pre></li>
<li><p>System commands should not need a full path specification to run in the shell.</p>
<p>For example, issuing <code>ls</code> should work the same way it works in BASH and run the <code>ls</code> executable that might be stored in <code>/bin</code>, <code>/usr/bin</code>, or elsewhere in the <em>system path</em>.</p></li>
</ol>
<h1 id="part-2">Part 2: Advanced Shell Features</h1>
<p>Part 2 expands on the basic shell from <a href="#part-1">Part 1</a>. You are asked to implement 4 builtin commands, as well as the following 3 operators:</p>
<ul>
<li><strong>Sequencing</strong>, e.g., <code>echo one; echo two</code></li>
<li><strong>Input redirection</strong>, e.g., <code>sort &lt; foo.txt</code></li>
<li><strong>Output redirection</strong>, e.g., <code>sort foo.txt &gt; output.txt</code></li>
<li><strong>Pipes</strong>, e.g., <code>sort foo.txt | uniq</code></li>
</ul>
<p>Note that these operators can be combined. Follow the <a href="#strategy">implementation strategy</a> suggested below. This will give you the relative priorities of the operators.</p>
<h2 id="p2t1">Task 2.1: Built-in Commands</h2>
<p>In addition to running programs, shells also usually provide a variety of <em>built-in commands</em>. Let’s implement some.</p>
<p>The shell should support at least the following built-in commands, in addition to <code>exit</code> from <a href="#part-1">Part 1</a>:</p>
<dl>
<dt><code>cd</code> (<strong>c</strong>hange <strong>d</strong>irectory)</dt>
<dd>This command should change the current working directory of the shell to the <a href="https://en.wikipedia.org/wiki/Path_(computing)#Unix_style">path</a> specified as the argument.
</dd>
<dd>Tip: You can check what the current working directory is using the <code>pwd</code> command (not a built-in).
</dd>
<dt><code>source</code></dt>
<dd>Execute a script.
</dd>
<dd>Takes a filename as an argument and processes each line of the file as a command, including built-ins. In other words, each line should be processed as if it was entered by the user at the prompt.
</dd>
<dt><code>prev</code></dt>
<dd>Prints the previous command line and executes it again, without becomming the new command line.
</dd>
<dd>You do not have to support combining <code>prev</code> with other commands on a command line.
</dd>
<dt><code>help</code></dt>
<dd>Explains all the built-in commands available in your shell
</dd>
</dl>
<h1 id="p2t2">Task 2.2: Sequencing Using <code>;</code></h1>
<p>The behavior of <code>;</code> is to execute the command on the left-hand side of the operator, and once it completes, execute the command on the right-hand side.</p>
<p>For example:</p>
<pre><code>```
shell $ echo Boston; echo San Francisco; echo Dallas
Boston
San Francisco
Dallas
shell $ dfg; uptime
dfg: command not found
20:04:40 up 44 days,  6:14, 60 users,  load average: 2.05, 1.93, 1.70
shell $
```</code></pre>
<h2 id="p2t3">Task 2.3: Input Redirection <code>&lt;</code></h2>
<p>A command may be followed by <code>&lt;</code> and a file name. The command shall be run with the contents of the file replacing the standard input.</p>
<h2 id="p2t4">Task 2.4: Output Redirection <code>&gt;</code></h2>
<p>A command may be followed by <code>&gt;</code> and a file name. The command shall be run as normal, but the standard output should be captured in the given file. If the file exists, its original contents should be deleted (“truncated”) before output is written to it. If it does not exist, it should be created automatically. You do not need to implement output redirection for built-ins.</p>
<h2 id="p2t5">Task 2.5: Pipe <code>|</code></h2>
<p>The pipe operator <code>|</code> runs the command on the left hand side and the command on the right-hand side simultaneously and the standard output of the LHS command is redirected to the standard input of the RHS command. You do not have to support piping the output of built-ins.</p>
<h1 id="deliverables">Deliverables</h1>
<dl>
<dt>Parts 1 and 2.</dt>
<dd><p>Implement the shell in <code>shell.c</code>.</p>
</dd>
</dl>
<p>Include any <code>.c</code> and <code>.h</code> files your implementation depends on and commit everything to your repository. <strong>Do not</strong> include any executables, <code>.o</code> files, or other binary, temporary, or hidden files; or any extra directories.</p>
<div class="box important">
<p>All the functionality needs to be implemented by you, using system calls. Writing code that relies on the default shell in any form does not fulfill the requirements.</p>
</div>
<h1 id="the-grammar-of-shell">The Grammar of Shell</h1>
<p>A grammar for a language specifies all the <em>valid</em> examples of expressions (or sentences) in that language. Our shell has the following grammar. This should help decide what is a valid command line, but also to help you structure your code. If you took <em>Fundies</em>, it might help to think of a grammar as a collection of related (inductive) union definitions.</p>
<section id="shell-grammar" class="box">
<h5>Shell Grammar</h5>
<ul>
<li><p>A <strong>command line</strong> is one or more <em>pipe commands</em> separated by a semicolon: <code>;</code>.</p></li>
<li><p>A <strong>pipe command</strong> is one or more <em>redirections</em> separated by a pipe: <code>|</code>.</p></li>
<li><p>A <strong>redirection</strong> is a <em>simple command</em>, optionally followed by a <code>&gt;</code> or a <code>&lt;</code> and a file name.</p></li>
<li><p>A <strong>simple command</strong> is either a built-in command or a program name followed by zero or more arguments.</p></li>
</ul>
</section>
<h1 id="strategy">Shell Implementation Strategy</h1>
<p>Here’s a set of “rough and ready” guidelines for tackling the extra shell functionality. Note that each subcommand might contain other operators as well. You might want to implement sequencing or redirection first.</p>
<ol type="1">
<li><p>Sequencing: <code>command1; command2</code></p>
<ol type="a">
<li>Split the token list on semicolon.</li>
<li>Fork child A &amp; execute <code>command1</code> (recursively).</li>
<li>In parent: wait for child A to finish.</li>
<li>Fork child B &amp; execute <code>command2</code> (recursively).</li>
<li>In parent: wait for child B to finish.</li>
</ol>
<p>Note, that you may have success processing a sequence of commands using an ordinary loop too.</p></li>
<li><p>Pipe: <code>command1 | command2</code></p>
<ol type="a">
<li>Fork child A.</li>
<li>In child A: create a pipe.</li>
<li>In child A: fork child B.</li>
<li>In child B: hook pipe to <code>stdout</code>, close other side.</li>
<li>In child B: execute <code>command1</code>.</li>
<li>In child A: hook pipe to <code>stdin</code>, close other side.</li>
<li>In child A: execute <code>command2</code>.</li>
<li>In child A: wait for child B.</li>
<li>In parent: wait for child A.</li>
</ol></li>
<li><p>Redirection: <code>command &lt;OP&gt; file</code></p>
<ol type="a">
<li>Fork a child.</li>
<li>In child: replace the appropriate file descriptor to accomplish the redirect.</li>
<li>In child: execute <code>command</code> (recursively).</li>
<li>In parent: wait for child to finish.</li>
</ol></li>
</ol>
<h1 id="examples">Examples</h1>
<p>Here are some examples you can use to test the shell functionality.</p>
<ul>
<li><p>The line</p>
<pre><code>echo one; echo two</code></pre>
<p>should print</p>
<pre><code>one
two</code></pre></li>
<li><p>Running</p>
<pre><code>echo -e "1\n2\n3\n4\n5" &gt; numbers.txt; cat numbers.txt</code></pre>
<p>should print</p>
<pre><code>1
2
3
4
5</code></pre>
<p>and result in a file called <code>numbers.txt</code> being created in the current directory.</p></li>
<li><p>Running</p>
<pre><code>sort -nr &lt; numbers.txt</code></pre>
<p>after the above, should print</p>
<pre><code>5
4
3
2
1</code></pre></li>
<li><p>Running</p>
<pre><code>shuf -i 1-10 | sort -n | tail -5</code></pre>
<p>should print</p>
<pre><code>6
7
8
9
10</code></pre></li>
</ul>
<h1 id="going-further">Going Further</h1>
<p>You might consider some of the following optional features in your shell to challenge yourself (there is no extra credit for this):</p>
<ol type="1">
<li><p>Switching processes between foreground and background (<code>fg</code> and <code>bg</code> commands).</p></li>
<li><p>Grouping command expressions. E.g.:</p>
<pre><code>( cat prologue.txt ; ( cat names.txt | sort ) ; cat epilogue.txt ) | nl</code></pre></li>
</ol>
<h1 id="using-the-provided-makefile">Using the Provided Makefile</h1>
<p>As before, we provide you with a Makefile for convenience. It contains the following targets:</p>
<ul>
<li><code>make all</code> – compile everything</li>
<li><code>make tokenize</code> – compile the tokenizer demo</li>
<li><code>make tokenize-tests</code> – run a few tests against the tokenizer</li>
<li><code>make shell</code> – compile the shell</li>
<li><code>make shell-tests</code> – run a few tests against the shell</li>
<li><code>make test</code> – compile and run all the tests</li>
<li><code>make clean</code> – perform a minimal clean-up of the source tree</li>
</ul>
<section id="hints-tips" class="box">
<h1>Hints &amp; Tips</h1>
<ul>
<li><p>The starter code contains an example of a tokenizer. A good start is to try to modify the example to recognize the tokens of a shell.</p></li>
<li><p>A very basic tokenizer can also be written using the function <code class="sourceCode c">strtok</code>, which provides a somewhat different approach. However, trying to handle string tokens using this approach might prove tricky.</p></li>
<li><p>Use the function <code class="sourceCode c">fgets</code> or <code class="sourceCode c">getline</code> to get a line from <code class="sourceCode c">stdin</code>. Pay attention to the maximum number of characters you are able to read. Avoid <code class="sourceCode c">gets</code>.</p></li>
<li><p>Figure out how <code class="sourceCode c">fgets</code>/<code class="sourceCode c">getline</code> lets you know when the shell receives an end-of-file.</p></li>
<li><p>Use the provided unit tests as a minimum sanity check for your implementation. Especially before the autograder becomes available.</p></li>
<li><p><strong>Write your own (unit) tests.</strong> Doing so will save you time in the long run, especially in conjunction with the debugger. In office hours, the instructors or the TAs may ask you to show how you tested code that fails.</p></li>
<li><p>Follow good coding practices. Make sure your function prototypes (signatures) are correct and always provide purpose statements. Add comments where appropriate to document your thinking, although strive to write <a href="https://en.wikipedia.org/wiki/Self-documenting_code">self-documenting code</a>. Pick meaningful names for your functions and variables. The larger the scope of the variable, the expressive the variable name should be.</p></li>
<li><p>Think about and design your program in a top-down manner and split code into short functions. Leverage your knowledge of program design from previous classes.</p></li>
<li><p>Avoid producing <a href="https://en.wikipedia.org/wiki/Spaghetti_code">“spaghetti code”</a>. A mutli-branch <code class="sourceCode c"><span class="cf">if</span></code>-<code class="sourceCode c"><span class="cf">else</span> <span class="cf">if</span></code>-<code class="sourceCode c"><span class="cf">else</span></code> or a multi-case <code class="sourceCode c"><span class="cf">switch</span></code> should be the only reason to go beyond 30-40 lines per function. Even so, the body of each branch/case should be at most 3-5 lines long.</p></li>
<li><p>Use <code>valgrind</code> with <code>--leak-check=full</code> to check you are managing memory properly.</p></li>
<li><p>A string vector implementation might be useful.</p></li>
<li><p>Avoid printing extra lines (empty or non-empty) beyond what is required above. This goes both for the tokenizer and the shell. Extra output will most likely confuse our tests and give false negatives.</p></li>
<li><p><code>man</code> is your friend. Check out <code>fork</code>, <code>open</code>, <code>close</code>, <code>read</code>, <code>write</code>, <code>dup</code>, <code>pipe</code>, <code>exec</code>, …</p></li>
</ul>
</section>
        </div>
      </div>
    </div>
    
    <!-- Bootstrap core JavaScript
    ================================================== -->
    <!-- Placed at the end of the document so the pages load faster -->
    <script src="js/jquery.min.js"></script>
    <script>window.jQuery || document.write('<script src="../../assets/js/vendor/jquery.min.js"><\/script>')</script>
    <script src="js/bootstrap.min.js"></script>
    <!-- IE10 viewport hack for Surface/desktop Windows 8 bug -->
    <script src="js/ie10-viewport-bug-workaround.js"></script>
    <script>
        //document.getElementById('sidebar').getElementsByTagName('ul')[0].className += "nav nav-sidebar";
        
        /* ajust the height when click the toc
           the code is from https://github.com/twbs/bootstrap/issues/1768
        */
        var shiftWindow = function() { scrollBy(0, -50) };
        window.addEventListener("hashchange", shiftWindow);
        function load() { if (window.location.hash) shiftWindow(); }
    </script>
  

</body></html>
