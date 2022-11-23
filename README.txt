***********TESTCASES & ERRORS HANDELED***********

For Internal Commands:
    1. cd
    Testcases:
        i) cd .. 
            (goes back a directory)
        ii) cd [dir name]
            (goes to that directory)
        iii) cd /
            (goes to root directory)
    Invalid Options:
        i) cd xyz
            <customshell: cd: xyz: No such file or directory>
        ii) cd os op
            <customshell: cd: too many arguments>

    2. pwd
    Testcases:
        i) pwd
            </home/aadya/os>
        ii) pwd xyz
            </home/aadya/os>
            (no difference made by 'xyz', similar to bash shell)
        iii) pwd -P
            </home/aadya/os>
            (prints the actual path)
        iv) pwd -L
            </home/aadya/os>
            (prints the symbolic path)
    Invalid Options:
        i) pwd -pqr
            <customshell: pwd: -pqr: invalid option
            pwd: usage: pwd [-LP]>
        ii) pwd (1234)
            <customshell: syntax error near unexpected token>

    3. echo
    Testcases:
        i) echo this is a customshell
            <this is a customshell>
        ii) echo *
            (lists all files in directory)
        iii) echo "this is a customshell"
            <this is a customshell>
        iv) echo -e "  this \c is a customshell"
            <  this >
    Invalid Options:
        i) echo &pqr
            <customshell: pqr: command not found>
        ii) echo (12)
            <customshell: syntax error near unexpected token>
        iii) echo "hello world
            <customshell: unexpected EOF while looking for matching `"'>

    4. exit - exits the shell


For External Commands:
    1. ls
    Testcases:
        i) ls
            (lists files in the directory)
        ii) ls [filename]
            (prints filename if it exits)
        iii) ls -1
            (prints filename in new line)
        iv) ls -a
            (prints all files and directories, even those starting with '.')
    Invalid Options:
        i) ls xyz
            <ls: cannot access 'xyz': No such file or directory>
        ii) ls -y
            <ls: invalid option -- 'y'
            Try 'ls --help' for more information.>
        
    2. cat
    Testcases:  
        i) cat README.txt
            (shows content of this file)
        ii) cat -n README.txt
            (shows content of this file with line numbers)
        iii) cat >> README.txt
            (appends line to README.txt, if file not found then new file is created and line is appended)
    Invalid Options:
        i) cat xyz
            <cat: xyz: No such file or directory>
        ii) cat -p README.txt
            <cat: invalid option -- 'p'
            Try 'cat --help' for more information.>

    3. date
    Testcases:
        i) date
            (prints day, date, time)
        ii) date --date="yesterday"
            (prints yesterday's datetime)
        iii) date --date="tomorrow"
            (prints tomorrow's datetime)
    Invalid Options:
        i) date -xyz
            <date: invalid option -- 'x'
            Try 'date --help' for more information.>
        ii) date pqr
            <date: invalid date ‘pqr’>

    4. rm
    Testcases:
        i) rm [filename]
            (deletes file)
        ii) rm [filename1] [filename2] [...]
            (deletes all mentioned files)
        iii) rm -i [filename]
            (asks for confirmation before deleting file)
        iv) rm -d [dirname]
            (deletes directory)
    Invalid Options:
        i) rm x
            <rm: cannot remove 'x': No such file or directory>
        ii) rm
            <rm: missing operand
            Try 'rm --help' for more information.>

    5. mkdir
    Testcases:
        i) mkdir test
            (creates test directory)
        ii) mkdir -v one
            <mkdir: created directory 'one'>
        iii) mkdir [dir1] [dir2] [dir3]
            (creates dir1 dir2 dir3)
    Invalid Options:
        i) mkdir README.txt
            <mkdir: cannot create directory README.txt’: File exists>
        ii) mkdir
            <mkdir: missing operand
            Try 'mkdir --help' for more information.>


***********same commands for thread based execution, just add '&t' at start***********
