# Project for bash scripts

## sourceme
### How to install 
Clone this repository to your machine
Then add the following line to your bashrc -
```
alias sourceme='bash /path/to/file/sourceme.sh'
```

## atom-packages
```
# Export your package list:
$ apm list --installed --bare > my-package-list.txt
# Install your packages elsewhere:
$ apm install --packages-file my-package-list.txt
```

## bash aliases
```
# Personal Aliases
alias cbt="catkin build --this --no-deps"
alias cb="catkin build"
alias sourceme="bash /home/sidd/.sourceme.sh"
alias cr="catkin run_tests"
```
