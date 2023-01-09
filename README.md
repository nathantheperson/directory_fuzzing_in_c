# directory_fuzzing_in_c
brute force get requests to specified port number<br>Unix based systems only.
<br>

<br>
If I had more time I would break hello_socket into three smaller functions one to establish<br>
a socket connection, another to send get requests and a third to close the socket at the end of the program.<br>
Then I would call all three from the main function (putting the send request function in a loop that breaks<br>
at the value of global varialbe file_size).  To be clear, this program opens and closes a socket every time <br>
a request is made.  The truth hurts sometimes.  Also the way that host names are checked to see if they need a domain
name resolution is not very thorough and the program will probably break if more than one subdomain is used <br>
(e.g. example.example.example.com)<br><br>
As of now, the main function sloppily checks for user input error, calls iterates_file which then <br>
controls the flow of the program.  <br>
<br>
How to use the program
 - ./a.out hostname port path/to/wordlist (request delay in seconds) | cat > output.txt<br><br>
