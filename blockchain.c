#include "blockchain.h"

void get_timestamp(char* buffer){
    time_t now = time(NULL);
    strftime(buffer, TIMESTAMP_SIZE, "%Y-%m-%d %H:%M:%S", localtime(&now));
}

Block* create_genesis_block(){
    Block* block = (Block*)malloc(sizeof(Block));
    block->index = 0;
    get_timestamp(block->timestamp);
    strcpy(block->data, "Genesis Block");
    strcpy(block->previous_hash, "0");
    block->nonce = 0;

    rle_compress(block->data, block->compressed_data, &block->compressed_size);

    block->next = NULL;
    return block;
}

Block* add_block(Block* last_block, const char* data){
    Block* block = (Block*)malloc(sizeof(Block));
    block->index = last_block->index + 1;
    get_timestamp(block->timestamp);
    strcpy(block->data, data);
    strcpy(block->previous_hash, last_block->hash);
    block->nonce = 0;

    rle_compress(block->data, block->compressed_data, &block->compressed_size);

    block->next = NULL;
    return block;
}

void write_block_to_file(FILE* file, Block* block) {
    fwrite(&block->index, sizeof(int), 1, file);
    fwrite(&block->timestamp, sizeof(char), TIMESTAMP_SIZE, file);
    fwrite(&block->previous_hash, sizeof(char), HASH_SIZE, file);
    fwrite(&block->compressed_size, sizeof(int), 1, file);
    fwrite(&block->compressed_data, sizeof(char), block->compressed_size, file);
}

Block* read_block_from_file(FILE* file){
    Block* block = (Block*)malloc(sizeof(Block));
    fread(&block->index, sizeof(int), 1, file);
    fread(&block->timestamp, sizeof(char), TIMESTAMP_SIZE, file);
    fread(&block->previous_hash, sizeof(char), HASH_SIZE, file);
    fread(&block->compressed_size, sizeof(int), 1, file);
    fread(&block->compressed_data, sizeof(char), block->compressed_size, file);

    rle_decompress(block->compressed_data, block->data, block->compressed_size);

    block->next = NULL;
    return block;
}

void rle_compress(const char* input, char* output, int* output_size) {
    int count, i = 0, j = 0;
    while (input[i] != '\0') {
        output[j++] = input[i];
        count = 1;
        while (input[i] == input[i + 1]) {
            count++;
            i++;
        }
        output[j++] = count + '0';
        i++;
    }
    output[j] = '\0';
    *output_size = j;
}

void rle_decompress(const char* input, char* output, int size) {
    int i = 0, j = 0;
    while (i < size) {
        char character = input[i++];
        int count = input[i++] - '0';
        for (int k = 0; k < count; k++) {
            output[j++] = character;
        }
    }
    output[j] = '\0';
}

void display_block(Block* block) {
    printf("Block #%d\n", block->index);
    printf("Timestamp: %s\n", block->timestamp);
    printf("Data: %s\n", block->data);
    printf("Previous Hash: %s\n", block->previous_hash);
    printf("Compressed Size: %d bytes\n", block->compressed_size);
    printf("\n");
}