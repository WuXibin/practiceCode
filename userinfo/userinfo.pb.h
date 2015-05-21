// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: userinfo.proto

#ifndef PROTOBUF_userinfo_2eproto__INCLUDED
#define PROTOBUF_userinfo_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2005000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace AdServerCommon {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_userinfo_2eproto();
void protobuf_AssignDesc_userinfo_2eproto();
void protobuf_ShutdownFile_userinfo_2eproto();

class USER_INFO_S;
class USER_INFO_S_USER_TAG_S;

// ===================================================================

class USER_INFO_S_USER_TAG_S : public ::google::protobuf::Message {
 public:
  USER_INFO_S_USER_TAG_S();
  virtual ~USER_INFO_S_USER_TAG_S();

  USER_INFO_S_USER_TAG_S(const USER_INFO_S_USER_TAG_S& from);

  inline USER_INFO_S_USER_TAG_S& operator=(const USER_INFO_S_USER_TAG_S& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const USER_INFO_S_USER_TAG_S& default_instance();

  void Swap(USER_INFO_S_USER_TAG_S* other);

  // implements Message ----------------------------------------------

  USER_INFO_S_USER_TAG_S* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const USER_INFO_S_USER_TAG_S& from);
  void MergeFrom(const USER_INFO_S_USER_TAG_S& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required int32 tag = 1;
  inline bool has_tag() const;
  inline void clear_tag();
  static const int kTagFieldNumber = 1;
  inline ::google::protobuf::int32 tag() const;
  inline void set_tag(::google::protobuf::int32 value);

  // required float score = 2;
  inline bool has_score() const;
  inline void clear_score();
  static const int kScoreFieldNumber = 2;
  inline float score() const;
  inline void set_score(float value);

  // @@protoc_insertion_point(class_scope:AdServerCommon.USER_INFO_S.USER_TAG_S)
 private:
  inline void set_has_tag();
  inline void clear_has_tag();
  inline void set_has_score();
  inline void clear_has_score();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::int32 tag_;
  float score_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];

  friend void  protobuf_AddDesc_userinfo_2eproto();
  friend void protobuf_AssignDesc_userinfo_2eproto();
  friend void protobuf_ShutdownFile_userinfo_2eproto();

  void InitAsDefaultInstance();
  static USER_INFO_S_USER_TAG_S* default_instance_;
};
// -------------------------------------------------------------------

class USER_INFO_S : public ::google::protobuf::Message {
 public:
  USER_INFO_S();
  virtual ~USER_INFO_S();

  USER_INFO_S(const USER_INFO_S& from);

  inline USER_INFO_S& operator=(const USER_INFO_S& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const USER_INFO_S& default_instance();

  void Swap(USER_INFO_S* other);

  // implements Message ----------------------------------------------

  USER_INFO_S* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const USER_INFO_S& from);
  void MergeFrom(const USER_INFO_S& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  typedef USER_INFO_S_USER_TAG_S USER_TAG_S;

  // accessors -------------------------------------------------------

  // repeated .AdServerCommon.USER_INFO_S.USER_TAG_S m_user_auto_brand = 1;
  inline int m_user_auto_brand_size() const;
  inline void clear_m_user_auto_brand();
  static const int kMUserAutoBrandFieldNumber = 1;
  inline const ::AdServerCommon::USER_INFO_S_USER_TAG_S& m_user_auto_brand(int index) const;
  inline ::AdServerCommon::USER_INFO_S_USER_TAG_S* mutable_m_user_auto_brand(int index);
  inline ::AdServerCommon::USER_INFO_S_USER_TAG_S* add_m_user_auto_brand();
  inline const ::google::protobuf::RepeatedPtrField< ::AdServerCommon::USER_INFO_S_USER_TAG_S >&
      m_user_auto_brand() const;
  inline ::google::protobuf::RepeatedPtrField< ::AdServerCommon::USER_INFO_S_USER_TAG_S >*
      mutable_m_user_auto_brand();

  // repeated .AdServerCommon.USER_INFO_S.USER_TAG_S m_user_auto_serie = 2;
  inline int m_user_auto_serie_size() const;
  inline void clear_m_user_auto_serie();
  static const int kMUserAutoSerieFieldNumber = 2;
  inline const ::AdServerCommon::USER_INFO_S_USER_TAG_S& m_user_auto_serie(int index) const;
  inline ::AdServerCommon::USER_INFO_S_USER_TAG_S* mutable_m_user_auto_serie(int index);
  inline ::AdServerCommon::USER_INFO_S_USER_TAG_S* add_m_user_auto_serie();
  inline const ::google::protobuf::RepeatedPtrField< ::AdServerCommon::USER_INFO_S_USER_TAG_S >&
      m_user_auto_serie() const;
  inline ::google::protobuf::RepeatedPtrField< ::AdServerCommon::USER_INFO_S_USER_TAG_S >*
      mutable_m_user_auto_serie();

  // repeated .AdServerCommon.USER_INFO_S.USER_TAG_S m_user_auto_level = 3;
  inline int m_user_auto_level_size() const;
  inline void clear_m_user_auto_level();
  static const int kMUserAutoLevelFieldNumber = 3;
  inline const ::AdServerCommon::USER_INFO_S_USER_TAG_S& m_user_auto_level(int index) const;
  inline ::AdServerCommon::USER_INFO_S_USER_TAG_S* mutable_m_user_auto_level(int index);
  inline ::AdServerCommon::USER_INFO_S_USER_TAG_S* add_m_user_auto_level();
  inline const ::google::protobuf::RepeatedPtrField< ::AdServerCommon::USER_INFO_S_USER_TAG_S >&
      m_user_auto_level() const;
  inline ::google::protobuf::RepeatedPtrField< ::AdServerCommon::USER_INFO_S_USER_TAG_S >*
      mutable_m_user_auto_level();

  // repeated .AdServerCommon.USER_INFO_S.USER_TAG_S m_user_auto_price = 4;
  inline int m_user_auto_price_size() const;
  inline void clear_m_user_auto_price();
  static const int kMUserAutoPriceFieldNumber = 4;
  inline const ::AdServerCommon::USER_INFO_S_USER_TAG_S& m_user_auto_price(int index) const;
  inline ::AdServerCommon::USER_INFO_S_USER_TAG_S* mutable_m_user_auto_price(int index);
  inline ::AdServerCommon::USER_INFO_S_USER_TAG_S* add_m_user_auto_price();
  inline const ::google::protobuf::RepeatedPtrField< ::AdServerCommon::USER_INFO_S_USER_TAG_S >&
      m_user_auto_price() const;
  inline ::google::protobuf::RepeatedPtrField< ::AdServerCommon::USER_INFO_S_USER_TAG_S >*
      mutable_m_user_auto_price();

  // repeated .AdServerCommon.USER_INFO_S.USER_TAG_S m_user_auto_spec = 5;
  inline int m_user_auto_spec_size() const;
  inline void clear_m_user_auto_spec();
  static const int kMUserAutoSpecFieldNumber = 5;
  inline const ::AdServerCommon::USER_INFO_S_USER_TAG_S& m_user_auto_spec(int index) const;
  inline ::AdServerCommon::USER_INFO_S_USER_TAG_S* mutable_m_user_auto_spec(int index);
  inline ::AdServerCommon::USER_INFO_S_USER_TAG_S* add_m_user_auto_spec();
  inline const ::google::protobuf::RepeatedPtrField< ::AdServerCommon::USER_INFO_S_USER_TAG_S >&
      m_user_auto_spec() const;
  inline ::google::protobuf::RepeatedPtrField< ::AdServerCommon::USER_INFO_S_USER_TAG_S >*
      mutable_m_user_auto_spec();

  // repeated .AdServerCommon.USER_INFO_S.USER_TAG_S m_user_auto_sect = 6;
  inline int m_user_auto_sect_size() const;
  inline void clear_m_user_auto_sect();
  static const int kMUserAutoSectFieldNumber = 6;
  inline const ::AdServerCommon::USER_INFO_S_USER_TAG_S& m_user_auto_sect(int index) const;
  inline ::AdServerCommon::USER_INFO_S_USER_TAG_S* mutable_m_user_auto_sect(int index);
  inline ::AdServerCommon::USER_INFO_S_USER_TAG_S* add_m_user_auto_sect();
  inline const ::google::protobuf::RepeatedPtrField< ::AdServerCommon::USER_INFO_S_USER_TAG_S >&
      m_user_auto_sect() const;
  inline ::google::protobuf::RepeatedPtrField< ::AdServerCommon::USER_INFO_S_USER_TAG_S >*
      mutable_m_user_auto_sect();

  // repeated .AdServerCommon.USER_INFO_S.USER_TAG_S m_user_auto_place = 7;
  inline int m_user_auto_place_size() const;
  inline void clear_m_user_auto_place();
  static const int kMUserAutoPlaceFieldNumber = 7;
  inline const ::AdServerCommon::USER_INFO_S_USER_TAG_S& m_user_auto_place(int index) const;
  inline ::AdServerCommon::USER_INFO_S_USER_TAG_S* mutable_m_user_auto_place(int index);
  inline ::AdServerCommon::USER_INFO_S_USER_TAG_S* add_m_user_auto_place();
  inline const ::google::protobuf::RepeatedPtrField< ::AdServerCommon::USER_INFO_S_USER_TAG_S >&
      m_user_auto_place() const;
  inline ::google::protobuf::RepeatedPtrField< ::AdServerCommon::USER_INFO_S_USER_TAG_S >*
      mutable_m_user_auto_place();

  // optional int32 m_user_group = 8;
  inline bool has_m_user_group() const;
  inline void clear_m_user_group();
  static const int kMUserGroupFieldNumber = 8;
  inline ::google::protobuf::int32 m_user_group() const;
  inline void set_m_user_group(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:AdServerCommon.USER_INFO_S)
 private:
  inline void set_has_m_user_group();
  inline void clear_has_m_user_group();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::RepeatedPtrField< ::AdServerCommon::USER_INFO_S_USER_TAG_S > m_user_auto_brand_;
  ::google::protobuf::RepeatedPtrField< ::AdServerCommon::USER_INFO_S_USER_TAG_S > m_user_auto_serie_;
  ::google::protobuf::RepeatedPtrField< ::AdServerCommon::USER_INFO_S_USER_TAG_S > m_user_auto_level_;
  ::google::protobuf::RepeatedPtrField< ::AdServerCommon::USER_INFO_S_USER_TAG_S > m_user_auto_price_;
  ::google::protobuf::RepeatedPtrField< ::AdServerCommon::USER_INFO_S_USER_TAG_S > m_user_auto_spec_;
  ::google::protobuf::RepeatedPtrField< ::AdServerCommon::USER_INFO_S_USER_TAG_S > m_user_auto_sect_;
  ::google::protobuf::RepeatedPtrField< ::AdServerCommon::USER_INFO_S_USER_TAG_S > m_user_auto_place_;
  ::google::protobuf::int32 m_user_group_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(8 + 31) / 32];

  friend void  protobuf_AddDesc_userinfo_2eproto();
  friend void protobuf_AssignDesc_userinfo_2eproto();
  friend void protobuf_ShutdownFile_userinfo_2eproto();

  void InitAsDefaultInstance();
  static USER_INFO_S* default_instance_;
};
// ===================================================================


// ===================================================================

// USER_INFO_S_USER_TAG_S

// required int32 tag = 1;
inline bool USER_INFO_S_USER_TAG_S::has_tag() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void USER_INFO_S_USER_TAG_S::set_has_tag() {
  _has_bits_[0] |= 0x00000001u;
}
inline void USER_INFO_S_USER_TAG_S::clear_has_tag() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void USER_INFO_S_USER_TAG_S::clear_tag() {
  tag_ = 0;
  clear_has_tag();
}
inline ::google::protobuf::int32 USER_INFO_S_USER_TAG_S::tag() const {
  return tag_;
}
inline void USER_INFO_S_USER_TAG_S::set_tag(::google::protobuf::int32 value) {
  set_has_tag();
  tag_ = value;
}

// required float score = 2;
inline bool USER_INFO_S_USER_TAG_S::has_score() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void USER_INFO_S_USER_TAG_S::set_has_score() {
  _has_bits_[0] |= 0x00000002u;
}
inline void USER_INFO_S_USER_TAG_S::clear_has_score() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void USER_INFO_S_USER_TAG_S::clear_score() {
  score_ = 0;
  clear_has_score();
}
inline float USER_INFO_S_USER_TAG_S::score() const {
  return score_;
}
inline void USER_INFO_S_USER_TAG_S::set_score(float value) {
  set_has_score();
  score_ = value;
}

// -------------------------------------------------------------------

// USER_INFO_S

// repeated .AdServerCommon.USER_INFO_S.USER_TAG_S m_user_auto_brand = 1;
inline int USER_INFO_S::m_user_auto_brand_size() const {
  return m_user_auto_brand_.size();
}
inline void USER_INFO_S::clear_m_user_auto_brand() {
  m_user_auto_brand_.Clear();
}
inline const ::AdServerCommon::USER_INFO_S_USER_TAG_S& USER_INFO_S::m_user_auto_brand(int index) const {
  return m_user_auto_brand_.Get(index);
}
inline ::AdServerCommon::USER_INFO_S_USER_TAG_S* USER_INFO_S::mutable_m_user_auto_brand(int index) {
  return m_user_auto_brand_.Mutable(index);
}
inline ::AdServerCommon::USER_INFO_S_USER_TAG_S* USER_INFO_S::add_m_user_auto_brand() {
  return m_user_auto_brand_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::AdServerCommon::USER_INFO_S_USER_TAG_S >&
USER_INFO_S::m_user_auto_brand() const {
  return m_user_auto_brand_;
}
inline ::google::protobuf::RepeatedPtrField< ::AdServerCommon::USER_INFO_S_USER_TAG_S >*
USER_INFO_S::mutable_m_user_auto_brand() {
  return &m_user_auto_brand_;
}

// repeated .AdServerCommon.USER_INFO_S.USER_TAG_S m_user_auto_serie = 2;
inline int USER_INFO_S::m_user_auto_serie_size() const {
  return m_user_auto_serie_.size();
}
inline void USER_INFO_S::clear_m_user_auto_serie() {
  m_user_auto_serie_.Clear();
}
inline const ::AdServerCommon::USER_INFO_S_USER_TAG_S& USER_INFO_S::m_user_auto_serie(int index) const {
  return m_user_auto_serie_.Get(index);
}
inline ::AdServerCommon::USER_INFO_S_USER_TAG_S* USER_INFO_S::mutable_m_user_auto_serie(int index) {
  return m_user_auto_serie_.Mutable(index);
}
inline ::AdServerCommon::USER_INFO_S_USER_TAG_S* USER_INFO_S::add_m_user_auto_serie() {
  return m_user_auto_serie_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::AdServerCommon::USER_INFO_S_USER_TAG_S >&
USER_INFO_S::m_user_auto_serie() const {
  return m_user_auto_serie_;
}
inline ::google::protobuf::RepeatedPtrField< ::AdServerCommon::USER_INFO_S_USER_TAG_S >*
USER_INFO_S::mutable_m_user_auto_serie() {
  return &m_user_auto_serie_;
}

// repeated .AdServerCommon.USER_INFO_S.USER_TAG_S m_user_auto_level = 3;
inline int USER_INFO_S::m_user_auto_level_size() const {
  return m_user_auto_level_.size();
}
inline void USER_INFO_S::clear_m_user_auto_level() {
  m_user_auto_level_.Clear();
}
inline const ::AdServerCommon::USER_INFO_S_USER_TAG_S& USER_INFO_S::m_user_auto_level(int index) const {
  return m_user_auto_level_.Get(index);
}
inline ::AdServerCommon::USER_INFO_S_USER_TAG_S* USER_INFO_S::mutable_m_user_auto_level(int index) {
  return m_user_auto_level_.Mutable(index);
}
inline ::AdServerCommon::USER_INFO_S_USER_TAG_S* USER_INFO_S::add_m_user_auto_level() {
  return m_user_auto_level_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::AdServerCommon::USER_INFO_S_USER_TAG_S >&
USER_INFO_S::m_user_auto_level() const {
  return m_user_auto_level_;
}
inline ::google::protobuf::RepeatedPtrField< ::AdServerCommon::USER_INFO_S_USER_TAG_S >*
USER_INFO_S::mutable_m_user_auto_level() {
  return &m_user_auto_level_;
}

// repeated .AdServerCommon.USER_INFO_S.USER_TAG_S m_user_auto_price = 4;
inline int USER_INFO_S::m_user_auto_price_size() const {
  return m_user_auto_price_.size();
}
inline void USER_INFO_S::clear_m_user_auto_price() {
  m_user_auto_price_.Clear();
}
inline const ::AdServerCommon::USER_INFO_S_USER_TAG_S& USER_INFO_S::m_user_auto_price(int index) const {
  return m_user_auto_price_.Get(index);
}
inline ::AdServerCommon::USER_INFO_S_USER_TAG_S* USER_INFO_S::mutable_m_user_auto_price(int index) {
  return m_user_auto_price_.Mutable(index);
}
inline ::AdServerCommon::USER_INFO_S_USER_TAG_S* USER_INFO_S::add_m_user_auto_price() {
  return m_user_auto_price_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::AdServerCommon::USER_INFO_S_USER_TAG_S >&
USER_INFO_S::m_user_auto_price() const {
  return m_user_auto_price_;
}
inline ::google::protobuf::RepeatedPtrField< ::AdServerCommon::USER_INFO_S_USER_TAG_S >*
USER_INFO_S::mutable_m_user_auto_price() {
  return &m_user_auto_price_;
}

// repeated .AdServerCommon.USER_INFO_S.USER_TAG_S m_user_auto_spec = 5;
inline int USER_INFO_S::m_user_auto_spec_size() const {
  return m_user_auto_spec_.size();
}
inline void USER_INFO_S::clear_m_user_auto_spec() {
  m_user_auto_spec_.Clear();
}
inline const ::AdServerCommon::USER_INFO_S_USER_TAG_S& USER_INFO_S::m_user_auto_spec(int index) const {
  return m_user_auto_spec_.Get(index);
}
inline ::AdServerCommon::USER_INFO_S_USER_TAG_S* USER_INFO_S::mutable_m_user_auto_spec(int index) {
  return m_user_auto_spec_.Mutable(index);
}
inline ::AdServerCommon::USER_INFO_S_USER_TAG_S* USER_INFO_S::add_m_user_auto_spec() {
  return m_user_auto_spec_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::AdServerCommon::USER_INFO_S_USER_TAG_S >&
USER_INFO_S::m_user_auto_spec() const {
  return m_user_auto_spec_;
}
inline ::google::protobuf::RepeatedPtrField< ::AdServerCommon::USER_INFO_S_USER_TAG_S >*
USER_INFO_S::mutable_m_user_auto_spec() {
  return &m_user_auto_spec_;
}

// repeated .AdServerCommon.USER_INFO_S.USER_TAG_S m_user_auto_sect = 6;
inline int USER_INFO_S::m_user_auto_sect_size() const {
  return m_user_auto_sect_.size();
}
inline void USER_INFO_S::clear_m_user_auto_sect() {
  m_user_auto_sect_.Clear();
}
inline const ::AdServerCommon::USER_INFO_S_USER_TAG_S& USER_INFO_S::m_user_auto_sect(int index) const {
  return m_user_auto_sect_.Get(index);
}
inline ::AdServerCommon::USER_INFO_S_USER_TAG_S* USER_INFO_S::mutable_m_user_auto_sect(int index) {
  return m_user_auto_sect_.Mutable(index);
}
inline ::AdServerCommon::USER_INFO_S_USER_TAG_S* USER_INFO_S::add_m_user_auto_sect() {
  return m_user_auto_sect_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::AdServerCommon::USER_INFO_S_USER_TAG_S >&
USER_INFO_S::m_user_auto_sect() const {
  return m_user_auto_sect_;
}
inline ::google::protobuf::RepeatedPtrField< ::AdServerCommon::USER_INFO_S_USER_TAG_S >*
USER_INFO_S::mutable_m_user_auto_sect() {
  return &m_user_auto_sect_;
}

// repeated .AdServerCommon.USER_INFO_S.USER_TAG_S m_user_auto_place = 7;
inline int USER_INFO_S::m_user_auto_place_size() const {
  return m_user_auto_place_.size();
}
inline void USER_INFO_S::clear_m_user_auto_place() {
  m_user_auto_place_.Clear();
}
inline const ::AdServerCommon::USER_INFO_S_USER_TAG_S& USER_INFO_S::m_user_auto_place(int index) const {
  return m_user_auto_place_.Get(index);
}
inline ::AdServerCommon::USER_INFO_S_USER_TAG_S* USER_INFO_S::mutable_m_user_auto_place(int index) {
  return m_user_auto_place_.Mutable(index);
}
inline ::AdServerCommon::USER_INFO_S_USER_TAG_S* USER_INFO_S::add_m_user_auto_place() {
  return m_user_auto_place_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::AdServerCommon::USER_INFO_S_USER_TAG_S >&
USER_INFO_S::m_user_auto_place() const {
  return m_user_auto_place_;
}
inline ::google::protobuf::RepeatedPtrField< ::AdServerCommon::USER_INFO_S_USER_TAG_S >*
USER_INFO_S::mutable_m_user_auto_place() {
  return &m_user_auto_place_;
}

// optional int32 m_user_group = 8;
inline bool USER_INFO_S::has_m_user_group() const {
  return (_has_bits_[0] & 0x00000080u) != 0;
}
inline void USER_INFO_S::set_has_m_user_group() {
  _has_bits_[0] |= 0x00000080u;
}
inline void USER_INFO_S::clear_has_m_user_group() {
  _has_bits_[0] &= ~0x00000080u;
}
inline void USER_INFO_S::clear_m_user_group() {
  m_user_group_ = 0;
  clear_has_m_user_group();
}
inline ::google::protobuf::int32 USER_INFO_S::m_user_group() const {
  return m_user_group_;
}
inline void USER_INFO_S::set_m_user_group(::google::protobuf::int32 value) {
  set_has_m_user_group();
  m_user_group_ = value;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace AdServerCommon

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_userinfo_2eproto__INCLUDED
