#pragma once

#include <unordered_map>
#include <vector>
#include <optional>


#include "person.pb.h"

namespace tutorial {

  class AddressBook {
  public:
    /// @brief Add a new person to the address book
    ///
    /// @param person: The Person to add.
    /// @return true if the person was added successfully
    /// @return false if a person with the same ID already exists
    bool addPerson(const Person& person);

    /// @brief updates an existing person
    ///
    /// The person is identified by its ID. All fields are replaced.
    ///
    /// @param person The updated person data.
    /// @return true if the update was successful
    /// @return false if no person with the given ID exists
    bool updatePerson(const Person& person);

    /// @brief Remove a person by ID
    /// @param id The ID of the person to remove
    /// @return true if the person was removed.
    /// @return false if the ID was not found.
    bool removePerson(int id);


    /// @brief Retrieve a copy of a person by ID
    /// This method provides read-only access by returning a copy.
    /// @param id The ID of the person to retrieve
    /// @return std::optional<Person> containing the person if found.
    std::optional<Person> getPerson(int id) const;

    /// @brief Retrieve mutable access to a person by ID
    /// This allows callers to modify the stored Person directly
    /// @param id The ID of the person to retrieve.
    /// @return Pointer to the Person if found, otherwise nullptr.
    Person* getPersonMutable(int id);

    /// @brief Retrieve all stored People
    ///
    /// @return A vector containing copies of all Person records.
    std::vector<Person> listPeople() const;

    /// @brief Get the number of people in the address book
    ///
    /// @return Number of stored Person records.
    size_t size() const;

  private:
    /// @brief Internal storage of people indexed by ID
    std::unordered_map<int, Person> m_people;
  };
}
    
