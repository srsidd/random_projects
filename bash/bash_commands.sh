# To get terminal prompt like you want it -
# ~/my_cool_folder/my_cool_repo(master u=) git status
# Add then to bashrc
# lower case w -> full path, upper case W -> only current directory
# \$(__git_ps1 '(%s)') -> git aware prompt
# \[\033[0m\] -> green color font for anything you type
PS1="\[\e[1;96m\]\W\[\e[1;91m\]\$(__git_ps1 '(%s)')\[\033[0m\] "
