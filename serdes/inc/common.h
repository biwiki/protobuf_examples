#pragma once

#include "message.pb.h"
#include <string>
#include <vector>
#include <memory>

//#include <google/protobuf/message.h>
//#include <google/protobuf/descriptor.h>
//#include <google/protobuf/io/zero_copy_stream_impl.h>
//#include <google/protobuf/io/coded_stream.h>
//#include <google/protobuf/io/zero_copy_stream_impl_lite.h>

using namespace google::protobuf::io;


constexpr static int          PORT {1234};
const     static std::string  ADDRESS {"127.0.0.1"};

PbMessage genMessage(PbMessage::MESSAGE_TYPE type, const std::string& msg)
{
    PbMessage message;
    message.set_type(type);
    message.set_msg(msg);

    return message;
}
