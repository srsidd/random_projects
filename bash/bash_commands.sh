 # To get terminal prompt like you want it -
 # ~/my_cool_folder/my_cool_repo(master u=) git status
 # Add then to bashrc
 # \[\e[1;96m\]\ -> neon blue
 # lower case w -> full path, upper case W -> only current directory
 # [\e[92m\] -> green
 # \h -> hostname
 # \$(__git_ps1 '(%s)') -> git aware prompt
 # \e[0;92m -> green color font for anything you type after this
 GIT_PS1_SHOWDIRTYSTATE=1
 PS1="\[\e[1;96m\]\W\[\e[92m\]@\h\[\e[1;91m\]\$(__git_ps1 '(%s)')\e[0;92m "
