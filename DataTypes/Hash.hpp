

#include <cstdint>
#include <functional>
#include <string>

#ifndef HASH_HPP
#define HASH_HPP
template <typename T>
struct Hash;

template <>
struct Hash<std::string> {
  std::size_t operator()(std::string const& name,
                         std::string const& surname) const noexcept;

  std::size_t operator()(std::string const& name) const noexcept;
};
template <>
struct Hash<size_t> {
  std::size_t operator()(size_t const& number) const noexcept;
};
#endif