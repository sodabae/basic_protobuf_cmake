#include <gtest/gtest.h>

#include "address_book.h"

using tutorial::AddressBook;
using tutorial::Person;

/// @brief Test adding and retrieving a person
TEST(AddressBookTest, AddAndGetPerson) {
  AddressBook book;

  Person alice;
  alice.set_id(1);
  alice.set_name("Alice");
  alice.set_email("alice@example.com");

  book.addPerson(alice);

  auto result = book.getPerson(1);
  ASSERT_TRUE(result.has_value());
  EXPECT_EQ(result->name(), "Alice");
  EXPECT_EQ(result->email(), "alice@example.com");
}

/// @brief Test modifying an existing person
TEST(AddressBookTest, ModifyPerson) {
  AddressBook book;

  Person bob;
  bob.set_id(2);
  bob.set_name("Bob");
  bob.set_email("bob@example.com");

  book.addPerson(bob);

  Person updated = *book.getPerson(2);
  updated.set_email("bob@newdomain.com");
  book.addPerson(updated);

  auto result = book.getPerson(2);
  ASSERT_TRUE(result.has_value());
  EXPECT_EQ(result->email(), "bob@newdomain.com");
}

/// @brief Test removing a person
TEST(AddressBookTest, RemovePerson) {
  AddressBook book;

  Person alice;
  alice.set_id(1);
  alice.set_name("Alice");

  book.addPerson(alice);
  EXPECT_EQ(book.size(), 1u);

  EXPECT_TRUE(book.removePerson(1));
  EXPECT_EQ(book.size(), 0u);
}

/// @brief Test removing a non-existent person
TEST(AddressBookTest, RemoveMissingPerson) {
  AddressBook book;
  EXPECT_FALSE(book.removePerson(999));
}
