<!DOCTYPE html>
<html>
<head>
  <link href="css/bootstrap.min.css" rel="stylesheet">

<!-- IE10 viewport hack for Surface/desktop Windows 8 bug -->
<link href="css/ie10-viewport-bug-workaround.css" rel="stylesheet">

<!-- Custom styles for this template -->
<link href="css/dashboard.css" rel="stylesheet">

</head>
  
  <body>

<p>The first project of a Systems class, is to write a <a href="https://en.wikipedia.org/wiki/Unix_shell">Shell</a>.</p>
<h3 id="part-1">Tokenizer &amp; Basic Shell</h3>
<p>A <em>tokenizer</em> is a piece of code that helps us split up an input line into meaningful <em>tokens</em>.</p>
<h3 id="p1t1">Shell Tokenizer</h3>
<p>Before we can execute commands (or combination of them) we need to be able to process a command line and split it into chunks (lexical units), called <a href="https://en.wikipedia.org/wiki/Lexical_analysis#Token"><em>tokens</em></a>. The input of a tokenizer is a string and the output is a list of tokens. Our shell will use the tokens described in the table below. The tokens <code>(</code>, <code>)</code>, <code>&lt;</code>, <code>&gt;</code>, <code>;</code>, <code>|</code>, and the whitespace characters (space <code>' '</code>, tab <code>'\t'</code>) are <em>special</em>. Whitespace is not a token, but might separate tokens.</p>
<br>
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
<br>
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
<p>In this example, we print the example string to standard output, but immediately <a href="https://en.wikipedia.org/wiki/Pipeline_(Unix)"><em>pipe</em></a> that output into the input of the <code>tokenize</code> program.</p>
<p>Whitespace that is not in quotes should not be included in any token.</p>
<p>What we are implementing here is a <a href="https://en.wikipedia.org/wiki/Deterministic_finite_automaton">Deterministic Finite-state Automaton (DFA)</a>, which is a recognizer for <a href="https://en.wikipedia.org/wiki/Regular_language">Reguar languages</a>.</p>
<h3 id="p1t2">Basic Shell</h3>
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
<h3 id="part-2">Advanced Shell Features</h3>
<ul>
<li><strong>Sequencing</strong>, e.g., <code>echo one; echo two</code></li>
<li><strong>Input redirection</strong>, e.g., <code>sort &lt; foo.txt</code></li>
<li><strong>Output redirection</strong>, e.g., <code>sort foo.txt &gt; output.txt</code></li>
<li><strong>Pipes</strong>, e.g., <code>sort foo.txt | uniq</code></li>
</ul>
<p>Note that these operators can be combined. Follow the <a href="#strategy">implementation strategy</a> suggested below. This will give you the relative priorities of the operators.</p>
<h2 id="p2t1">Built-in Commands</h2>
<p>In addition to running programs, shells also usually provide a variety of <em>built-in commands</em></p>
<p>The shell supports the following built-in commands, in addition to <code>exit</code></p>
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
<dt><code>help</code></dt>
<dd>Explains all the built-in commands available in your shell
</dd>
</dl>
<h3 id="p2t2">Sequencing Using <code>;</code></h3>
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
<h2 id="p2t3">Input Redirection <code>&lt;</code></h2>
<p>A command may be followed by <code>&lt;</code> and a file name. The command shall be run with the contents of the file replacing the standard input.</p>
<h2 id="p2t4">Output Redirection <code>&gt;</code></h2>
<p>A command may be followed by <code>&gt;</code> and a file name. The command shall be run as normal, but the standard output should be captured in the given file. If the file exists, its original contents should be deleted (“truncated”) before output is written to it. If it does not exist, it should be created automatically.</p>
<h2 id="p2t5">Pipe <code>|</code></h2>
<p>The pipe operator <code>|</code> runs the command on the left hand side and the command on the right-hand side simultaneously and the standard output of the LHS command is redirected to the standard input of the RHS command.</p>




<h3 id="the-grammar-of-shell">The Grammar of Shell</h3>
<p>A grammar for a language specifies all the <em>valid</em> examples of expressions (or sentences) in that language. Our shell has the following grammar. This should help decide what is a valid command line, but also to help you structure your code.</p>
<section id="shell-grammar" class="box">
<h5>Shell Grammar</h5>
<ul>
<li><p>A <strong>command line</strong> is one or more <em>pipe commands</em> separated by a semicolon: <code>;</code>.</p></li>
<li><p>A <strong>pipe command</strong> is one or more <em>redirections</em> separated by a pipe: <code>|</code>.</p></li>
<li><p>A <strong>redirection</strong> is a <em>simple command</em>, optionally followed by a <code>&gt;</code> or a <code>&lt;</code> and a file name.</p></li>
<li><p>A <strong>simple command</strong> is either a built-in command or a program name followed by zero or more arguments.</p></li>
</ul>
</section>

<h3 id="examples">Examples</h3>
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

<h3 id="using-the-provided-makefile">Using the Provided Makefile</h3>
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
    
</body></html>
