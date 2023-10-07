#!/bin/bash
# "Ah, mas esse script tá mais feio que bater na mãe" sim, de fato, tal qual todo script em bash já feito

COUNT=10 # Número de repetições
BIN_FILE="bin/main" # Binário executável do programa

OUT_ROOT_DIR="out" # Diretório raiz de saída
BIN_OUT_DIR="out/default" # Diretório de saída dos arquivos gerados na execução
GPROF_OUT_DIR="out/gprof" # Diretório de saída dos arquivos de saída do gprof
DOT_OUT_DIR="out/dot" # Diretório de saída dos arquivos .dot
IMAGE_OUT_DIR="out/images" # Diretório de saída dos grafos de execução

# Cria diretórios
mkdir "$OUT_ROOT_DIR"
mkdir "$BIN_OUT_DIR"
mkdir "$GPROF_OUT_DIR"
mkdir "$DOT_OUT_DIR"
mkdir "$IMAGE_OUT_DIR"

# Build da aplicação
make all

# Execução da aplicação
for I in $(seq 1 $COUNT); do
    export GMON_OUT_PREFIX="$BIN_OUT_DIR/$I"
    ./$BIN_FILE
done

# Execução do gprof
OUT_FILES=$(ls ./$BIN_OUT_DIR)
for FILE_NAME in $OUT_FILES; do
    gprof $BIN_FILE "$BIN_OUT_DIR/$FILE_NAME" > "$GPROF_OUT_DIR/$FILE_NAME.txt"
done

# Execução do gprof2dot
OUT_FILES=$(ls ./$GPROF_OUT_DIR)
for FILE_NAME in $OUT_FILES; do
    gprof2dot "$GPROF_OUT_DIR/$FILE_NAME" > "$DOT_OUT_DIR/$FILE_NAME.dot"
done

# Execução do dot
OUT_FILES=$(ls ./$DOT_OUT_DIR)
for FILE_NAME in $OUT_FILES; do
    dot -Tpng -o "$IMAGE_OUT_DIR/$FILE_NAME.png" "$DOT_OUT_DIR/$FILE_NAME"
done


