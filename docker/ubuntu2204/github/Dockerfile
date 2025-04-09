FROM obsidian-ubuntu2204-base as obsidian-ubuntu2204-github-build

RUN git clone https://github.com/obsidian-language/obsidian-c

WORKDIR /obsidian-c

RUN meson setup build && \
    meson compile -C build

FROM obsidian-ubuntu2204-github-build

CMD ["./src/obsidian", "./examples/hello.ob"]