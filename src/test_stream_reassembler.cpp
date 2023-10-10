#include "stream_reassembler.hh"
#include <iostream>
#include <cassert>


int main() {
    // Create a StreamReassembler with a capacity of 10
    StreamReassembler reassembler(10);

    // Test receiving "efgh" with an index of 4 and eof = false
    reassembler.push_substring("efgh", 4, false);

    // Test receiving "abcd" with an index of 0 and eof = false
    reassembler.push_substring("abcd", 0, false);

    // Check if the unassembled bytes are as expected
    assert(reassembler.unassembled_bytes() == 8);

    // Access the reassembled stream and verify it
    ByteStream &outputStream = reassembler.stream_out();
    assert(outputStream.input_size() == 8);
    assert(outputStream.read(8) == "abcdefgh");

    std::cout << "Test passed!" << std::endl;

    return 0;
}
