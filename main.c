#include "blockchain.h"

int main() {
    // Create the genesis block
    Block* genesis = create_genesis_block();
    display_block(genesis);

    // Add a new block
    Block* block1 = add_block(genesis, "Block 1: Alice sends 10 BTC to Bob");
    display_block(block1);

    // Write blocks to file
    FILE* file = fopen("blockchain.dat", "wb");
    write_block_to_file(file, genesis);
    write_block_to_file(file, block1);
    fclose(file);

    // Read blocks from file
    file = fopen("blockchain.dat", "rb");
    Block* read_block1 = read_block_from_file(file);
    display_block(read_block1);
    Block* read_block2 = read_block_from_file(file);
    display_block(read_block2);
    fclose(file);

    // Free memory
    free(genesis);
    free(block1);
    free(read_block1);
    free(read_block2);

    return 0;
}
