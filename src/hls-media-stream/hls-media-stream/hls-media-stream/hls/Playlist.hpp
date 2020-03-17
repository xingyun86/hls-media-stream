
#ifndef Playlist_hpp
#define Playlist_hpp

#include "oatpp/core/data/stream/ChunkedBuffer.hpp"
#include "oatpp/core/parser/Caret.hpp"

#include <chrono>

class Playlist {
private:
  
  struct RecordMarker {
    v_float64 duration;
    oatpp::String uri;
  };
  
private:
  typedef oatpp::collection::LinkedList<RecordMarker> RecordMarkerList;
private:
  std::shared_ptr<RecordMarkerList> m_records;
  v_float64 m_totalDuration;
public:
  
  Playlist(const std::shared_ptr<RecordMarkerList>& records)
    : m_records(records)
  {
    m_totalDuration = 0;
    m_records->forEach([this](const RecordMarker& marker){
      m_totalDuration += marker.duration;
    });
  }
  
  static Playlist parse(oatpp::parser::Caret& caret);
  static Playlist parseFromFile(const char* filename);
  
  std::shared_ptr<oatpp::data::stream::ChunkedBuffer> generateForTime(v_int64 millis, v_int32 numRecords);
  
  
};

#endif /* Playlist_hpp */
