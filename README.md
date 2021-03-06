# IS521 Activity3: Backdoor
20163378 Jungsuk Oh

## File Description
* [**./interpreter/**](interpreter) : Reads in the bytecode generated by the [compiler](./compiler/) then executes it on the system
    * Implemented the functions to execute the bytecode.
    * Although I wrote the code myself, I have used [jaemoon-sim](https://github.com/KAIST-IS521/backdoor-jaemoon-sim), [JeongOhKye](https://github.com/KAIST-IS521/backdoor-JeongOhKye), and [blukat29](https://github.com/KAIST-IS521/backdoor-blukat29) as a reference.
* [**./login/**](login) : Simple login script. username: user / password: password. returns success upon logon failure otherwise.
    * I forked from [blukat29](https://github.com/KAIST-IS521/backdoor-blukat29)
* [**./test/**](test) : Uses all opcodes to test whether the interpreter works properly
    * I forked from [mikkang](https://github.com/KAIST-IS521/backdoor-mikkang)
* [**./backdoor/**](backdoor) : Installs a backdoor to the login program
	* Whenever the program prints out "User: ", the back door is activated. entering in the string "superuser" as a username will automatically authenticate the user without a password input.
	* The backdoor authentication is done by mannually changing the program counter. Therefore, it will not work on other login.mini programs.
* [**./compiler/**](compiler): Compiler that reads in the mini language code then translates it into a bytecode.
    * I justed used the default version that was given. I did not make any changes except for the manual copy and paste update from the Professor's update.


## What I learned
* I learned how an interpreter reads in the bytecode and executes them on a system.
* I learned how to write code in mini language. Although I have done assembly coding before, it has been a while.
* I learned how to generate backdoors by decting a program event and user inputs then modifying the program counter.
* A program cannot be trusted just based on its source code as the compiler or the interpreter can insert malicous code as seen in this activity.