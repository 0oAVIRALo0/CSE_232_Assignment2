# CSE_232_Assignment2

Part I:
The ByteStream class is a versatile tool for managing a stream of bytes, commonly used in
applications where data processing occurs at the byte level. It offers functionalities for reading,
writing, and monitoring the state of the stream.
Key Features
Initialization
➔ ByteStream(const size_t capa): The class can be initialized with a specified capacity
(capa). This capacity defines the maximum number of bytes that the stream can hold.
Writing Data
➔ size_t write(const string &data): This function allows you to write data to the stream. It
ensures that the stream doesn't exceed its defined capacity. The function returns the
number of bytes successfully written.
Reading Data
➔ string peek_output(const size_t len) const: This method enables you to inspect the next
len bytes from the output side of the buffer without removing them from the stream. It
helps in previewing the data.
➔ void pop_output(const size_t len): To consume data from the stream, you can use this
function. It removes the next len bytes from the output side of the buffer, allowing you to
process or discard them.
➔ string read(const size_t len): Similar to pop_output, this function reads the next len bytes
from the stream but returns a copy of the data before removal. It's useful when you need
to retain a copy of the data you're reading.
Control and Status
➔ void end_input(): You can use this method to mark the input as ended. Once input is
ended, no more data can be written to the stream.
➔ bool input_ended() const: This function checks whether the input has ended, providing a
convenient way to determine if further writing operations are allowed.
➔ size_t buffer_size() const: It returns the current size of the buffer, indicating how many
bytes are currently stored in the stream.➔ bool buffer_empty() const: You can use this function to check if the buffer is empty, which
is useful to determine if there is any data available for reading.
➔ bool eof() const: The eof function checks if the end of the stream has been reached. It
considers both the input being ended and the buffer being empty.
➔ size_t bytes_written() const: This method returns the total number of bytes that have
been written to the stream since its creation.
➔ size_t bytes_read() const: It returns the total number of bytes that have been read from
the stream since its creation.
➔ size_t remaining_capacity() const: To find out how much space is left in the stream (i.e.,
the remaining capacity), you can use this function.
Error Handling
➔ void set_error(): This function is used to set an error flag in cases where an error
condition is encountered during operations. You can check for errors using the error()
function.
➔ bool error() const: The error() function checks whether an error condition has been set in
the ByteStream. This allows for proper error handling when needed.
