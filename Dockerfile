FROM debian:10.11

SHELL ["/bin/bash", "-c"]

# env vars
ENV USER=dev
ENV USER_ID=1000
ENV PASSWORD=pass

RUN apt-get clean && apt-get update

# install tools
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y \
  gawk wget git diffstat unzip texinfo gcc build-essential automake \
	chrpath socat cpio python3 python3-pip python3-pexpect \
	xz-utils debianutils iputils-ping python3-git python3-jinja2 \
	libegl1-mesa libsdl1.2-dev pylint3 xterm \
	python3-subunit mesa-common-dev locales sudo file

RUN DEBIAN_FRONTEND=noninteractive apt-get install -y emacs


# add a user
RUN useradd -u $USER_ID -U -m $USER && \
  echo "$USER:$PASSWORD" | chpasswd && adduser $USER sudo

# set up locale
RUN echo 'en_US.UTF-8 UTF-8' >> /etc/locale.gen && locale-gen

USER $USER

WORKDIR /home/$USER

# pull yocto poky and layers
RUN git clone -b hardknott https://git.yoctoproject.org/git/poky.git

RUN git clone -b hardknott https://git.openembedded.org/meta-openembedded
RUN git clone -b hardknott https://git.yoctoproject.org/git/meta-raspberrypi