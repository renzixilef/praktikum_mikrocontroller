FROM ubuntu:latest

RUN apt-get update && apt-get install -y \
    build-essential \
    gdb \
    cmake \
    wget \
    openjdk-21-jdk \
    openjdk-21-jre \
    git \
    unzip \
    libgtk-3-dev \
    bash-completion

RUN apt-get upgrade -y

# gnu arm toolchain install
RUN wget -O /tmp/arm-gnu-toolchain-13.2.rel1-x86_64-arm-none-eabi.tar.xz https://armkeil.blob.core.windows.net/developer/Files/downloads/gnu/13.2.rel1/binrel/arm-gnu-toolchain-13.2.rel1-x86_64-arm-none-eabi.tar.xz && \
    mkdir -p /opt/arm-gnu-toolchain && \
    tar -xvf /tmp/arm-gnu-toolchain-13.2.rel1-x86_64-arm-none-eabi.tar.xz -C /opt/arm-gnu-toolchain --strip-components 1 && \
    rm /tmp/arm-gnu-toolchain-13.2.rel1-x86_64-arm-none-eabi.tar.xz

# openocd install
RUN apt-get install -y openocd

ENV PATH="/opt/arm-gnu-toolchain/bin:${PATH}"

RUN cmake -B /workspace/build -S /workspace
RUN cmake --build /workspace/build

WORKDIR /workspace


