#include "byte_stream.hh"

using namespace std;

ByteStream::ByteStream( uint64_t capacity ) : capacity_( capacity ) {}

bool Writer::is_closed() const
{
  return closed_;
}

void Writer::push( string data )
{
  if(error_ || closed_){
    return;
  }
  uint64_t space_left = capacity_ - buffer_.size();
  uint64_t bytes_to_push = min(space_left, static_cast<uint64_t>(data.size()));
  buffer_.insert(buffer_.end(), data.begin(), data.begin() + bytes_to_push);
  bytes_pushed_ += bytes_to_push;
}

void Writer::close()
{
  closed_ = true;
}

uint64_t Writer::available_capacity() const
{
  return capacity_ - buffer_.size();
}

uint64_t Writer::bytes_pushed() const
{
  return bytes_pushed_;
}

bool Reader::is_finished() const
{
  return closed_ && buffer_.empty();
}

uint64_t Reader::bytes_popped() const
{
  return bytes_popped_;
}

string_view Reader::peek() const
{
  return buffer_view_;
}

void Reader::pop( uint64_t len )
{
  uint64_t bytes_to_pop = min(len, static_cast<uint64_t>(buffer_.size()));
  buffer_.erase(buffer_.begin(), buffer_.begin() + bytes_to_pop);
  bytes_popped_ += bytes_to_pop;
}

uint64_t Reader::bytes_buffered() const
{
  return bytes_pushed_ - bytes_popped_;
}
