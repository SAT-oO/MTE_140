FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    build-essential \
    clang \
    gdb \
    cmake \
    git \
    vim \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace

CMD ["/bin/bash"]
