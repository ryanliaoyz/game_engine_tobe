#pragma once

#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>

namespace tobe {

using GenomeSymbol = std::uint8_t;

struct Genome {
  static constexpr std::size_t length = 64;
  static constexpr std::size_t codon_size = 3;

  // Hardcoded neutral padding for v1.
  static constexpr GenomeSymbol pad_symbol = 0xF;

  std::array<GenomeSymbol, length> symbols{};

  std::uint32_t decoder_version = 1;

  Genome() { symbols.fill(pad_symbol); }

  explicit Genome(const std::array<GenomeSymbol, length> &code)
      : symbols(code) {
    assert_valid_symbols();
  }

  std::size_t size() const { return length; }

  static constexpr std::size_t codon_count() {
    return length - codon_size + 1;
  }

  static constexpr bool is_valid_symbol(GenomeSymbol symbol) {
    return symbol <= 0xF;
  }

  bool is_valid() const {
    for (auto symbol : symbols) {
      if (!is_valid_symbol(symbol))
        return false;
    }
    return true;
  }

private:
  void assert_valid_symbols() const {
    assert(is_valid() && "Genome contains symbol outside hex range 0x0-0xF");
  }
};

} // namespace tobe
