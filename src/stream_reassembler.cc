#include "stream_reassembler.hh"
#include <climits>

// Add private members to the class declaration in `stream_reassembler.hh` if necessary.

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

StreamReassembler::StreamReassembler(const size_t capacity)
    : _capacity(capacity), _output(capacity), _wait_index(0), eof_index(INT_MAX) {}

void StreamReassembler::push_substring(const std::string &data, const uint64_t index, const bool eof) {
    if (eof) {
        eof_index = index + data.size();
    }

    size_t start_index = index;
    size_t end_index = index + data.length();

    if (start_index == _wait_index) {
        size_t capacity_left = _capacity - _output.buffer_size();
        if (data.length() <= capacity_left) {
            _output.write(data);
            _wait_index += data.length();
        } else {
            string truncated_segment = data.substr(0, capacity_left);
            _output.write(truncated_segment);
            _wait_index += truncated_segment.length();
        }
        
        if (eof) {
            _output.end_input();
            return;
        }
    } else if (start_index < _wait_index) {
        size_t truncate_size = _wait_index - start_index;
        if (truncate_size >= data.length()) {
            return;
        }
        size_t new_idx = start_index + truncate_size;
        string truncated_segment = data.substr(truncate_size);
        insert_in_buffer(truncated_segment, new_idx);
    } else {
        insert_in_buffer(data, start_index);
    }


    for (auto it = buffered_segments.begin(); it != buffered_segments.end();) {
        size_t _index = it->first;
        if (_index < _wait_index) {
            it = buffered_segments.erase(it);
        } else if (_index == _wait_index) {
            char s = it->second;
            // char -> str
            string str(1, s);
            if (str.length() <= _output.remaining_capacity()) {
                _output.write(str);
                _wait_index += 1;
                it = buffered_segments.erase(it);
            } else {
                break;
            }

            if (_wait_index >= eof_index) {
                _output.end_input();
                break;
            }

        } else {
            ++it;
        }
    }
}

void StreamReassembler::insert_in_buffer(const string &data, uint64_t index) {
    size_t idx = index;
    for (char c : data) {
        // Check if the index is already in buffered_segments
        if (buffered_segments.find(idx) == buffered_segments.end()) {
            // If not, insert the character at that index
            buffered_segments[idx] = c;
        }
        // Move to the next index and character in the data string
        ++idx;
    }
}

size_t StreamReassembler::unassembled_bytes() const {
    size_t total_bytes = 0;
    for (const auto& it : buffered_segments) {
        total_bytes += 1;
    }

    return total_bytes;
}

bool StreamReassembler::empty() const {
    return _output.buffer_empty() && buffered_segments.empty();
}

size_t StreamReassembler::ack_index() const {
    return _wait_index;
}