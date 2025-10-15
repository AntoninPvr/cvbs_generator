#!/bin/zsh
# Usage: ./test.sh

if [[ -z "$PROJECT_DIR" ]]; then
    echo "Please run setenv.sh in the project root directory before this script."
    exit 1
fi

BIN=$PROJECT_DIR/build/cvbs_generator
INPUT=$PROJECT_DIR/test/lenna.png
OUTPUT=$PROJECT_DIR/test/output.bin

if [[ ! -f "$BIN" ]]; then
    echo "Executable $BIN not found. Please build first."
    exit 1
fi

if [[ ! -f "$INPUT" ]]; then
    echo "Test input $INPUT not found. Please provide an image file named $INPUT."
    exit 1
fi

# Run the program with input
"$BIN" -i "$INPUT"

if [[ $? -eq 0 ]]; then
    echo "Test passed."
else
    echo "Test failed."
    exit 1
fi
