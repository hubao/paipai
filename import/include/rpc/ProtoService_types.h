/**
 * Autogenerated by Thrift Compiler (0.11.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef ProtoService_TYPES_H
#define ProtoService_TYPES_H

#include <iosfwd>

#include <thrift/Thrift.h>
#include <thrift/TApplicationException.h>
#include <thrift/TBase.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/transport/TTransport.h>

#include <thrift/stdcxx.h>


namespace proto_rpc {

class ProtoRequest;

class ProtoReply;


class ProtoRequest : public virtual ::apache::thrift::TBase {
 public:

  ProtoRequest(const ProtoRequest&);
  ProtoRequest& operator=(const ProtoRequest&);
  ProtoRequest() : type(0), sharding_id(0), content() {
  }

  virtual ~ProtoRequest() throw();
  int32_t type;
  int64_t sharding_id;
  std::string content;

  void __set_type(const int32_t val);

  void __set_sharding_id(const int64_t val);

  void __set_content(const std::string& val);

  bool operator == (const ProtoRequest & rhs) const
  {
    if (!(type == rhs.type))
      return false;
    if (!(sharding_id == rhs.sharding_id))
      return false;
    if (!(content == rhs.content))
      return false;
    return true;
  }
  bool operator != (const ProtoRequest &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const ProtoRequest & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(ProtoRequest &a, ProtoRequest &b);

std::ostream& operator<<(std::ostream& out, const ProtoRequest& obj);


class ProtoReply : public virtual ::apache::thrift::TBase {
 public:

  ProtoReply(const ProtoReply&);
  ProtoReply& operator=(const ProtoReply&);
  ProtoReply() : type(0), result(0), content() {
  }

  virtual ~ProtoReply() throw();
  int32_t type;
  int64_t result;
  std::string content;

  void __set_type(const int32_t val);

  void __set_result(const int64_t val);

  void __set_content(const std::string& val);

  bool operator == (const ProtoReply & rhs) const
  {
    if (!(type == rhs.type))
      return false;
    if (!(result == rhs.result))
      return false;
    if (!(content == rhs.content))
      return false;
    return true;
  }
  bool operator != (const ProtoReply &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const ProtoReply & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(ProtoReply &a, ProtoReply &b);

std::ostream& operator<<(std::ostream& out, const ProtoReply& obj);

} // namespace

#endif
