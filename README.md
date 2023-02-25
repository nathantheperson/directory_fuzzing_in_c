# directory_fuzzing_in_c
brute force get requests to specified port number<br>For unix based systems.
<br>
<br>
App is not finished
<br>
sends and handles http get request's.  Send HTTP GET requests to host using a wordlist. <br>
Then saves the HTTP response header to into a hash map and searches for "Content-Length" key <br>
as to dynamically receive the correct amount of bytes from the host before sending another GET request.  <br>
<br>
<br>
<br>I'm taking a break from this project but next I'm going to remove hash_table.* and replace it with my own hash function.
<br>Then implement https... which honestly shouldn't be too hard since parsing http and https should be identical.  I'm hoping
<br>https would just be a different set of socket calls.  Once the program is finished I'll add a valgrind outputin the readme
<br>
<br>
How to use the program
 - ./a.out hostname port path/to/wordlist http | cat > output.txt<br><br>
