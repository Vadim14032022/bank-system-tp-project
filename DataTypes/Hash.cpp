#include "Hash.hpp"

std::size_t Hash<std::string>::operator()(
    std::string const& name, std::string const& surname) const noexcept {
  std::size_t h1 = std::hash<std::string>{}(name);
  std::size_t h2 = std::hash<std::string>{}(surname);
  return h1 ^ (h2 << 1);  // or use boost::hash_combine
}

std::size_t Hash<std::string>::operator()(
    std::string const& name) const noexcept {
  std::size_t h1 = std::hash<std::string>{}(name);
  std::size_t h2 = std::hash<std::string>{}('@' + name + '#');
  return h1 ^ (h2 << 1);  // or use boost::hash_combine
}

std::size_t Hash<size_t>::operator()(size_t const& number) const noexcept {
  return number;
}