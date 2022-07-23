#include  "message.pb.h"
#include <iostream>

int main()
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    PbMessage msg;

    std::cout << "Initial has_type() " << (msg.has_type() ? "true" : "false") << std::endl;
    std::cout << "IsInitialized() " << (msg.IsInitialized() ? "true" : "false") << std::endl;
    std::cout << "ByteSizeLong() " << msg.ByteSizeLong() << std::endl;

    msg.set_type(PbMessage::COMMAND);
    std::cout << "set_type() called, now has_type() " << (msg.has_type() ? "true" : "false") << std::endl;
    std::cout << "IsInitialized() " << (msg.IsInitialized() ? "true" : "false") << std::endl;
    std::cout << "ByteSizeLong() " << msg.ByteSizeLong() << std::endl;

    msg.set_msg("Hello");
    std::cout << "set_type() called, now has_type() " << (msg.has_type() ? "true" : "false") << std::endl;
    std::cout << "IsInitialized() " << (msg.IsInitialized() ? "true" : "false") << std::endl;
    std::cout << "ByteSizeLong() " << msg.ByteSizeLong() << std::endl;

    std::cout << "DebugString() " << msg.DebugString();
    std::cout << "Type " << msg.type() << std::endl;
    std::cout << "Message " << msg.msg() << std::endl;

    msg.clear_type();
    std::cout << "clear_type() called, now has_type() " << (msg.has_type() ? "true" : "false") << std::endl;
    std::cout << "IsInitialized() " << (msg.IsInitialized() ? "true" : "false") << std::endl;
    std::cout << "ByteSizeLong() " << msg.ByteSizeLong() << std::endl;

    msg.clear_msg();
    std::cout << "clear_type() called, now has_type() " << (msg.has_type() ? "true" : "false") << std::endl;
    std::cout << "IsInitialized() " << (msg.IsInitialized() ? "true" : "false") << std::endl;
    std::cout << "ByteSizeLong() " << msg.ByteSizeLong() << std::endl;
}
