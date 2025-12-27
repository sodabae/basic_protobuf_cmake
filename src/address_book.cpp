#include "address_book.h"
#include "person.pb.h"

namespace tutorial {

  bool AddressBook::addPerson(const Person& person) {
    auto [it, inserted] = m_people.emplace(person.id(), person);
    return inserted;
  }

  bool AddressBook::updatePerson(const Person& person){
    auto it = m_people.find(person.id());
    if (it == m_people.end())
      return false;
    it->second = person;
    return true;
  }

  bool AddressBook::removePerson(int id){
    return m_people.erase(id) > 0;
  }

  std::optional<Person> AddressBook::getPerson(int id) const{
    auto it = m_people.find(id);
    if (it == m_people.end())
      return std::nullopt;
    return it->second;
  }

  Person* AddressBook::getPersonMutable(int id){
    auto it = m_people.find(id);
    if (it == m_people.end()) {
      return nullptr;
    }
    return &it->second;
  }

  std::vector<Person> AddressBook::listPeople() const{
    std::vector<Person> result;
    result.reserve(size());
    for (const auto& entry : m_people){
      result.push_back(entry.second);
    }
    return result;
  }

  size_t AddressBook::size() const {
    return m_people.size();
  }
}
