#include <iostream>
#include "person.pb.h"

int main() {
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    tutorial::Person p;
    p.set_name("Alice");
    p.set_id(123);
    p.set_email("alice@example.com");

    std::string serialized;
    p.SerializeToString(&serialized);

    tutorial::Person p2;
    p2.ParseFromString(serialized);

    std::cout << "Name: " << p2.name() << "\n";
    std::cout << "ID: " << p2.id() << "\n";
    std::cout << "Email: " << p2.email() << "\n";

    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}
