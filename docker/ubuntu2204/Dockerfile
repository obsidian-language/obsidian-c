FROM obsidian-ubuntu2204-base as obsidian-ubuntu2204-build

COPY . /obsidian-c
WORKDIR /obsidian-c

RUN make

FROM obsidian-ubuntu2204-build

CMD ["./src/obsidian", "./examples/hello.ob"]