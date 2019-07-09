FROM alpine
RUN apk update \ 
    && apk add bash \
    && apk add openssl-dev && apk add libc6-compat \
    && apk add git \
    && apk add gcc \
    && apk add g++ \
    && apk add gdb \
    && apk add valgrind \
    && apk add cmake  \
    && apk add make \
    && apk add zlib-dev \
    && apk add boost-dev \
    && apk add py-pip \
    && mkdir /third_party && cd /third_party \
    && git clone https://github.com/microsoft/cpprestsdk.git \
    && cd /third_party/cpprestsdk \
    && git submodule update --init \
    && cmake . \
    && make -j4 \
    && make install

