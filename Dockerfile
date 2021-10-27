FROM debian:11

# env vars
ENV USER=dev
ENV USER_ID=1000
ENV PASSWORD=pass
ENV WORKSPACE=/home/$USER/src

RUN apt-get clean && apt-get update

# install tools
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y \
  gawk wget git diffstat unzip texinfo gcc build-essential \
	chrpath socat cpio python3 python3-pip python3-pexpect \
	xz-utils debianutils iputils-ping python3-git python3-jinja2 \
	libegl1-mesa libsdl1.2-dev pylint3 xterm \
	python3-subunit mesa-common-dev locales sudo


# add a user
RUN useradd -u $USER_ID -U -m $USER && \
  echo "$USER:$PASSWORD" | chpasswd && adduser $USER sudo

# set up locale
RUN echo 'en_US.UTF-8 UTF-8' >> /etc/locale.gen && locale-gen

USER $USER

WORKDIR $WORKSPACE