#include "reassembler.hh"

using namespace std;

void Reassembler::insert( uint64_t first_index, string data, bool is_last_substring )
{
  Writer writer_ = writer();
  uint64_t capacity_ = writer_.available_capacity();
  writer_.push(data);
  // Your code here.
  (void)first_index;
  (void)data;
  (void)is_last_substring;
}

void Reassembler::push_bytes(uint64_t first_index, string data, bool is_last_substring)
{
  if( first_index < expected_index_)
    data.erase(0, expected_index_ - first_index);
  expected_index_ += data.size();
  
  ;
}

uint64_t Reassembler::bytes_pending() const
{
  return bytes_buffered_;
}
