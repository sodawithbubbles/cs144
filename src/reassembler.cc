#include "reassembler.hh"
#include <algorithm>
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
  output_.writer().push(move(data));

  if( is_last_substring )
  {
    output_.writer().close();
    ordered_buffer_.clear();
    bytes_buffered_ = 0;
  }
  ;
}

void Reassembler::cache_bytes(uint64_t first_index, std::string data, bool is_last_substring)
{
  auto end = ordered_buffer_.end();
  auto left = lower_bound( ordered_buffer_.begin(), end, []( auto&& e, uint64_t idx ) -> bool {
    return idx > ( get<0>( e ) + get<1>( e ).size() );
  } );
  auto right = upper_bound( left, end, [] ( uint64_t idx, auto&& e ) -> bool {
    return nxt_idx < get<0>( e );
  });
  
  if(const ; left != end)
}



uint64_t Reassembler::bytes_pending() const
{
  return bytes_buffered_;
}
