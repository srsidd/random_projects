# Project for bash scripts

## bash aliases
```bash
# Personal Aliases
alias cbt="catkin build --this --no-deps"
alias cbn="catkin build --no-deps"
alias cb="catkin build"
alias cc="catkin clean -y"
alias cr="catkin run_tests"
alias sourceme="bash /home/sidd/.sourceme.sh"
```

## matlab style up arrow complete
```bash
touch ~/.inputrc
# Copy the lines from the inputrc file in the repo and paste it in ~/.inputrc
vim ~/.inputrc
```
## Increase bash history
Edit your `~.bashrc` and either replace the lines, or add these at the end
```bash
 HISTSIZE=20000
 HISTFILESIZE=40000
 ```

## sourceme
### How to install 
Clone this repository to your machine
Then add the following line to your bashrc -
```bash
alias sourceme='bash /path/to/file/sourceme.sh'
```

## atom-packages
```bash
# Export your package list:
$ apm list --installed --bare > my-package-list.txt
# Install your packages elsewhere:
$ apm install --packages-file my-package-list.txt
```
