// @file main.cpp
// @brief Entry point for the protobuf AddressBook example.
//
// Demonstrates creation, modification, and retrieval of Person
// protobuf objects stored within an AddressBook.

#include <spdlog/spdlog.h>

#include "address_book.h"

using tutorial::AddressBook;
using tutorial::Person;

/// @brief Program entry point.
/// @return int Exit status.
int main() {
  AddressBook book;

  Person alice;
  alice.set_name("Alice");
  alice.set_id(1);
  alice.set_email("alice@example.com");

  Person bob;
  bob.set_name("Bob");
  bob.set_id(2);
  bob.set_email("bob@example.com");

  book.addPerson(alice);
  book.addPerson(bob);

  // Modify an existing record
  if (Person* p = book.getPersonMutable(2)) {
    p->set_email("bob@newdomain.com");
  }

  // Print all entries
  for (const auto& person : book.listPeople()) {
    spdlog::info("ID: {}, Name: {}, Email: {}",
                 person.id(),
		 person.name(),
		 person.email()
		 );
  }

  book.removePerson(1);

  spdlog::info("Final AddressBook size: {}", book.size());

  return 0;
}
