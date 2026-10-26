
FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    pkg-config \
    libssl-dev \
    libjsoncpp-dev \
    uuid-dev \
    zlib1g-dev \
    libc-ares-dev \
    libbrotli-dev \
    libpq-dev \
    postgresql-client \
    && rm -rf /var/lib/apt/lists/*

RUN git clone https://github.com/drogonframework/drogon.git /tmp/drogon \
    && cd /tmp/drogon \
    && git checkout v1.9.7 \
    && git submodule update --init

RUN cd /tmp/drogon \
    && mkdir -p build && cd build \
    && cmake .. \
        -DCMAKE_BUILD_TYPE=Release \
        -DBUILD_EXAMPLES=OFF \
        -DBUILD_CTL=OFF \
        -DBUILD_TESTING=OFF

RUN cd /tmp/drogon/build \
    && make -j$(nproc)

RUN cd /tmp/drogon/build \
    && make install

RUN ls /usr/local/lib/cmake/Drogon/DrogonConfig.cmake

RUN rm -rf /tmp/drogon

WORKDIR /app
COPY . /app

RUN mkdir -p build && cd build \
    && cmake .. -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_PREFIX_PATH=/usr/local \
    && make -j$(nproc)

EXPOSE 8080

CMD ["./build/apps/knowledge-base-service/knowledge-base-service"]