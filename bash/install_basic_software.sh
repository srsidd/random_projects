#! /bin/bash
## NOTE - Don't run the script with sudo!
## Instead type in the password when it asks

sudo apt-get update


### Web Related stuff
# Install google-chrome
wget -q -O - https://dl-ssl.google.com/linux/linux_signing_key.pub | sudo apt-key add -
sudo sh -c 'echo "deb [arch=amd64] http://dl.google.com/linux/chrome/deb/ stable main" >> /etc/apt/sources.list.d/google-chrome.list'
sudo apt-get update
sudo apt-get install google-chrome-stable

# Install flash plugin for firefox
# Pepper flash since adobe flash was discontinued
sudo apt-get install browser-plugin-freshplayer-pepperflash


### System related Stuff
# Increase number of workspaces to 9 (3x3)
gsettings set org.compiz.core:/org/compiz/profiles/unity/plugins/core/ vsize 3
gsettings set org.compiz.core:/org/compiz/profiles/unity/plugins/core/ hsize 3

# To open a terminal from the current folder
sudo apt-get install nautilus-open-terminal-here

# Install curl
sudo apt-get install curl

# Get dropbox
cd ~ && wget -O - "https://www.dropbox.com/download?plat=lnx.x86_64" | tar xzf -
printf "\n\n\n\n Remember to run ~/.dropbox-dist/dropboxd separately to start dropbox\n\n\n\n"

# Good PDF reader
cd ~/Downloads
wget http://cdn01.foxitsoftware.com/pub/foxit/reader/desktop/linux/2.x/2.1/en_us/FoxitReader2.1.0805_Server_x64_enu_Setup.run.tar.gz
tar xzvf FoxitReader*.tar.gz
sudo chmod a+x FoxitReader*.run
./FoxitReader.*.run
cd

# Install xpad
sudo apt-get update
sudo apt-get install xpad

# Install htop
sudo apt install htop

# Install meld
sudo apt-get install meld

### Developer Stuff
# Install terminator
sudo apt-get install terminator

# For "making" and "compiling"
sudo apt-get install build-essential

# Ipython terminal
sudo apt-get install ipython

# Git aware prompt
mkdir ~/.bash
cd ~/.bash
git clone git://github.com/jimeh/git-aware-prompt.git
export GITAWAREPROMPT=~/.bash/git-aware-prompt
source "${GITAWAREPROMPT}/main.sh"
export PS1="\${debian_chroot:+(\$debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\] \[$txtcyn\]\$git_branch\[$txtred\]\$git_dirty\[$txtrst\]\$ "

# Bash history up-arrows.
echo "\"\e[A\": history-search-backward
\"\e[B\": history-search-forward
set show-all-if-ambiguous on
set completion-ignore-case on" > ~/.inputrc

# Install ros
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
sudo apt-key adv --keyserver hkp://ha.pool.sks-keyservers.net:80 --recv-key 421C365BD9FF1F717815A3895523BAEEB01FA116
sudo apt-get update
sudo apt-get install ros-kinetic-desktop-full
sudo rosdep init
rosdep update
echo "source /opt/ros/kinetic/setup.bash" >> ~/.bashrc
source ~/.bashrc
sudo apt-get install python-rosinstall

# Install extra packages for ros
sudo apt-get install ros-kinetic-ros-control

# Install catkin tools
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu `lsb_release -sc` main" > /etc/apt/sources.list.d/ros-latest.list'
wget http://packages.ros.org/ros.key -O - | sudo apt-key add -

sudo apt-get update
sudo apt-get install python-catkin-tools

# Create catkin-ws
mkdir -p ~/catkin_ws/src
cd ~/catkin_ws/src
# catkin_init_workspace
# source devel/setup.bash

# Install gedit plugins
sudo apt-get install gedit-plugins

# Install atom
sudo add-apt-repository ppa:webupd8team/atom -y
sudo apt update
sudo apt install atom

# Install Latex
sudo apt-get install texlive texstudio

# Install vim
sudo apt install vim

# VIM beast mode
git clone --depth=1 https://github.com/amix/vimrc.git ~/.vim_runtime
sh ~/.vim_runtime/install_awesome_vimrc.sh


### Entertainment stuff
# Install vlc media player
sudo apt-get install vlc
sudo apt-get install browser-plugin-vlc

# Install youtube-dl
sudo chmod a+rx /usr/local/bin/youtube-dl
sudo apt-get install -y libav-tools
