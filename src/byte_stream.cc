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
  buffer_.append(data, 0, bytes_to_push);
  bytes_pushed_ += bytes_to_push;
}

void Writer::close()
{
  closed_ = true;
}

uint64_t Writer::available_capacity() const
{
  return capacity_ - (bytes_pushed_ - bytes_popped_);
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
  return std::string_view( buffer_ );
}

void Reader::pop( uint64_t len )
{
  uint64_t buffer_size = buffer_.size();
  uint64_t pop_size = std::min(len, buffer_size);

  buffer_ = buffer_.substr(pop_size);
  bytes_popped_ += pop_size;
}

uint64_t Reader::bytes_buffered() const
{
  return buffer_.size();
}
