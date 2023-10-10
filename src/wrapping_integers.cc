#include "wrapping_integers.hh"

#include <iostream>

using namespace std;

// relative = initial + abs

//! Transform an "absolute" 64-bit sequence number (zero-indexed) into a WrappingInt32
//! \param n The input absolute 64-bit sequence number
//! \param isn The initial sequence number
WrappingInt32 wrap(uint64_t n, WrappingInt32 isn) { 
	return isn + uint32_t(n); 
}

//! Transform a WrappingInt32 into an "absolute" 64-bit sequence number (zero-indexed)
//! \param n The relative sequence number
//! \param isn The initial sequence number
//! \param checkpoint A recent absolute 64-bit sequence number
//! \returns the 64-bit sequence number that wraps to `n` and is closest to `checkpoint`
//!
//! \note Each of the two streams of the TCP connection has its own ISN. One stream
//! runs from the local TCPSender to the remote TCPReceiver and has one ISN,
//! and the other stream runs from the remote TCPSender to the local TCPReceiver and
//! has a different ISN.


uint64_t unwrap(WrappingInt32 n, WrappingInt32 isn, uint64_t checkpoint) {

    WrappingInt32 wrappedCheckpoint = wrap(checkpoint, isn);

    int32_t minDiff = n.raw_value() - wrappedCheckpoint.raw_value();

    int32_t min_distance;
    if (minDiff < 0) {
        min_distance = minDiff + (1ul << 32);
    } else {
        min_distance = minDiff;
    }

    int64_t abs = static_cast<int64_t>(checkpoint) + min_distance;
    
    if (abs >= 0) {
        return static_cast<uint64_t>(abs);
    } else {
        return abs + (1ul << 32);
    }
}
