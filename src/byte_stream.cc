#include "byte_stream.hh"

#include <algorithm>

// You will need to add private members to the class declaration in `byte_stream.hh`

/* Replace all the dummy definitions inside the methods in this file. */


using namespace std;

ByteStream::ByteStream(const size_t capa) : buffer(), capacity(capa), endInput(false), error_(false), numOfBytesWritten(0), totalNumOfBytesWritten(0), numOfBytesRead(0)
{}

size_t ByteStream::write(const string &data) {
  if (endInput) {
    return 0;
  }

  size_t available_space = capacity - buffer.size();

  size_t bytesToWrite = 0;

  if (data.length() < available_space) {
    bytesToWrite = data.length();
  } else {
    bytesToWrite = available_space;
  }

  for (size_t i = 0; i < bytesToWrite; ++i) {
    buffer.push_back(data[i]);
  }  

  numOfBytesWritten += bytesToWrite; 

  totalNumOfBytesWritten += bytesToWrite;

  return bytesToWrite;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
  string result;

  bool lenFlag = false;
  bool bufferFlag = false;

  size_t n = 0;

  if (len < buffer.size()) {
    lenFlag = true;
  } else {
    bufferFlag = true;
  }

  if (lenFlag = true) {
    n = len;
  } else {
    n = buffer.size();
  }

  for (size_t i = 0; i < n; ++i) {
    result.push_back(buffer[i]);
  }

  return result;
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) {
  if (len > buffer.size()) {
    set_error();
  }

  size_t pop_size = min(len, buffer.size());
  numOfBytesRead += len;
  for (size_t i = 0; i < pop_size; i++) {
    buffer.pop_front();
  }
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
  if (len > buffer.size()) {
    set_error();
  }
  
  string ans = peek_output(len);
  pop_output(len);

  return ans;
}

void ByteStream::end_input() {endInput = true;}

bool ByteStream::input_ended() const {return endInput;}

size_t ByteStream::buffer_size() const {return buffer.size();}

bool ByteStream::buffer_empty() const {return buffer.empty();}

bool ByteStream::eof() const { return (endInput && buffer.empty());}

size_t ByteStream::bytes_written() const { return totalNumOfBytesWritten;}

size_t ByteStream::bytes_read() const { return numOfBytesRead;}

size_t ByteStream::remaining_capacity() const {
  if (capacity >= buffer.size()) {
    return capacity - buffer.size();
  } else {
    return 0;
  }
}
