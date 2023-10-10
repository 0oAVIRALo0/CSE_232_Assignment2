# CSE_232_Assignment2

TCP Stream Reassembler

This code implements a TCP stream reassembler, capable of handling out-of-order segments and reconstructing the original data stream.

ByteStream Class
  - The ByteStream class provides an interface for writing and reading bytes. It handles input and output operations and keeps track of the number of bytes written and read. The class supports operations      like writing, reading, peeking, and checking stream status (input ended, empty, and EOF).

StreamReassembler Class
  - The StreamReassembler class is a stream reassembler capable of handling TCP segments received out of order. It buffers segments and reconstructs the original data stream based on their sequence            numbers. The reassembler ensures correct sequencing and handles cases where segments arrive out of order or with gaps.

TCPReceiver Class
  - The TCPReceiver class receives TCP segments, processes them, and interacts with the stream reassembler to reconstruct the original data stream. It manages sequence number unwrapping and handles            incoming segments with SYN and FIN flags.

How to Use

ByteStream Class:
  - Create a ByteStream object with a specified capacity.
  - Use write() to add data to the stream.
  - Use read(len) to read len bytes from the stream.
  - Check stream status using methods like input_ended(), eof(), and buffer_empty().

StreamReassembler Class:
  - Create a StreamReassembler object with a specified capacity.
  - Call push_substring(data, index, eof) to add segments to the reassembler.
  - Use unassembled_bytes() to check the number of unassembled bytes.
  - Use empty() to check if the reassembler is empty.
  - Call ack_index() to get the acknowledgment index.

TCPReceiver Class:
  - Receive TCP segments using the segment_received(seg) method.
  - Get the next acknowledgment number using ackno().
  - Check the window size using window_size().
