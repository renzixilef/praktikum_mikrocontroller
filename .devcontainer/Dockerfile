FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    build-essential \
    gdb \
    cmake \
    wget \
    openjdk-21-jdk \
    openjdk-21-jre \
    git \
    sshpass \
    openssh-client \
    unzip \
    libgtk-3-dev \
    bash-completion

RUN apt-get upgrade -y

# gnu arm toolchain install
RUN wget -O /tmp/arm-gnu-toolchain-13.2.rel1-x86_64-arm-none-eabi.tar.xz https://armkeil.blob.core.windows.net/developer/Files/downloads/gnu/13.2.rel1/binrel/arm-gnu-toolchain-13.2.rel1-x86_64-arm-none-eabi.tar.xz && \
    mkdir -p /opt/arm-gnu-toolchain && \
    tar -xvf /tmp/arm-gnu-toolchain-13.2.rel1-x86_64-arm-none-eabi.tar.xz -C /opt/arm-gnu-toolchain --strip-components 1 && \
    rm /tmp/arm-gnu-toolchain-13.2.rel1-x86_64-arm-none-eabi.tar.xz

# cubemx install
RUN mkdir -p /var/cubemx
RUN sshpass -p mxdownload sftp -o StrictHostKeyChecking=no cubemxdownloader@hyend.ext.selfnet.de:cubemx.zip /var/cubemx/
RUN unzip /var/cubemx/cubemx.zip -d /var/cubemx
RUN chmod +x /var/cubemx/SetupSTM32CubeMX-6.10.0
WORKDIR /var/cubemx
RUN echo -e "1\n1\n1\n\n\nY\n\n" | ./SetupSTM32CubeMX-6.10.0
RUN rm -r /var/cubemx
RUN git config --global core.filemode false
RUN git config --global core.autocrlf true

# openocd install
RUN apt-get install -y openocd

ENV PATH="/opt/arm-gnu-toolchain/bin:${PATH}"

WORKDIR /workspace


