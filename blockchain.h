#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define HASH_SIZE 64
#define DATA_SIZE 256
#define TIMESTAMP_SIZE 20
#define COMPRESSED_DATA_SIZE 512

typedef struct Block {
    int index;
    char timestamp[TIMESTAMP_SIZE];
    char data[DATA_SIZE];
    char previous_hash[HASH_SIZE];
    char hash[HASH_SIZE];
    int nonce;
    char compressed_data[COMPRESSED_DATA_SIZE];
    int compressed_size;
    struct Block* next;
} Block;

Block* create_genesis_block();
Block* add_block(Block* last_block, const char* data);
void write_block_to_file(FILE* file, Block* block);
Block* read_block_from_file(FILE* file);
void rle_compress(const char* input, char *output, int* output_size);
void rle_decompress(const char* input, char* output, int size);
void display_block(Block* block);

#endif