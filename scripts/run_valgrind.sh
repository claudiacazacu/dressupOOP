#!/usr/bin/bash

INPUT_FILE=${INPUT_FILE:-tastatura.txt}
RUN_INTERACTIVE=${RUN_INTERACTIVE:-false}
BUILD_DIR=${BUILD_DIR:-build}
EXECUTABLE_NAME=${EXECUTABLE_NAME:-oop}

if [[ -n "$1" ]]; then
    BIN_DIR="$1"
elif [[ -d "install_dir/bin" ]]; then
    BIN_DIR="install_dir/bin"
else
    BIN_DIR="${BUILD_DIR}/bin"
fi

if [[ "${RUN_INTERACTIVE}" = true ]]; then
    cd "${BIN_DIR}"
    valgrind --leak-check=full \
            --show-leak-kinds=all \
            --track-origins=yes \
            --error-exitcode=1 \
            ./"${EXECUTABLE_NAME}"
else
    cd "${BIN_DIR}"
    cat < "${INPUT_FILE}" | tr -d '\r' | valgrind --leak-check=full \
            --show-leak-kinds=all \
            --track-origins=yes \
            --error-exitcode=1 \
            ./"${EXECUTABLE_NAME}"
fi