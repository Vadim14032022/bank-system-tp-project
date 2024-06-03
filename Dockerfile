FROM ubuntu:latest

RUN apt -y update && apt -y install git make clang cmake

RUN useradd -ms /bin/bash devops2023user
USER devops2023user
