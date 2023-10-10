#include "tcp_receiver.hh"

#include <algorithm>


using namespace std;

void TCPReceiver::segment_received(const TCPSegment &seg) {
    const TCPHeader head = seg.header();
    bool syn = head.syn;
    bool fin = head.fin;

    if (!syn && !_synReceived) {
        return;
    }

    if (!_synReceived) {
        _isn = head.seqno;
        _synReceived = true;
    }
    // ...

    // --- Hint ------
        // convert the seqno into absolute seqno
    uint64_t checkpoint = _reassembler.ack_index();
    uint64_t abs_seqno = unwrap(head.seqno, _isn, checkpoint);
    uint64_t stream_idx = abs_seqno - _synReceived;
    // --- Hint ------  

    _reassembler.push_substring(seg.payload().copy(), stream_idx, fin);
    // ... 
}

optional<WrappingInt32> TCPReceiver::ackno() const {

    if (_synReceived) {
        optional<WrappingInt32> ans;
        uint64_t idx = _reassembler.ack_index() + 1;
        // If the output stream has ended, increment the index by 1 to include fin
        if (_reassembler.stream_out().input_ended()) {
            idx++;
        }
        ans = wrap(idx, _isn);
        return ans;
    }
    
    return nullopt;
}

size_t TCPReceiver::window_size() const {
    return _capacity - _reassembler.stream_out().buffer_size();
}
