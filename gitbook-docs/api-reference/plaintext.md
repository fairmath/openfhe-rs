# Plaintext

This document provides an API reference for the `Plaintext` class, which is a part of the `openfhe` namespace. The `Plaintext` class is a final class that provides various methods to manipulate and query plaintext data.

## Member functions
### Constructors and assignment operators

- **Plaintext() = default**: Default constructor.
- **Plaintext(std::shared_ptr<PlaintextImpl>&& plaintext) noexcept**: Constructor with a `PlaintextImpl` object.
- **Plaintext(const Plaintext&) = delete**: Copy constructor (deleted).
- **Plaintext(Plaintext&&) = delete**: Move constructor (deleted).
- **Plaintext& operator=(const Plaintext&) = delete**: Copy assignment operator (deleted).
- **Plaintext& operator=(Plaintext&&) = delete**: Move assignment operator (deleted).

### Methods

- **void SetLength(const size_t newSize) const**: Sets the length of the plaintext.
- **void SetLevel(const size_t l) const noexcept**: Sets the level of the plaintext.
- **[[nodiscard]] bool IsEncoded() const noexcept**: Checks if the plaintext is encoded.
- **[[nodiscard]] int64_t HighBound() const noexcept**: Gets the high bound of the plaintext.
- **[[nodiscard]] int64_t LowBound() const noexcept**: Gets the low bound of the plaintext.
- **[[nodiscard]] double GetLogPrecision() const**: Gets the log precision of the plaintext.
- **[[nodiscard]] rust::String GetString() const**: Gets the string representation of the plaintext.
- **[[nodiscard]] size_t GetLength() const noexcept**: Gets the length of the plaintext.
- **[[nodiscard]] size_t GetLevel() const noexcept**: Gets the level of the plaintext.
- **[[nodiscard]] double GetLogError() const**: Gets the log error of the plaintext.
- **[[nodiscard]] size_t GetNoiseScaleDeg() const noexcept**: Gets the noise scale degree of the plaintext.
- **[[nodiscard]] double GetScalingFactor() const noexcept**: Gets the scaling factor of the plaintext.
- **[[nodiscard]] SCHEME GetSchemeID() const noexcept**: Gets the scheme ID of the plaintext.
- **[[nodiscard]] uint32_t GetSlots() const noexcept**: Gets the number of slots of the plaintext.
- **[[nodiscard]] bool Encode() const**: Encodes the plaintext.
- **[[nodiscard]] bool Decode() const**: Decodes the plaintext.
- **void SetFormat(const Format fmt) const**: Sets the format of the plaintext.
- **void SetIntVectorValue(const std::vector<int64_t>& val) const**: Sets the integer vector value of the plaintext.
- **void SetNoiseScaleDeg(const size_t nsd) const noexcept**: Sets the noise scale degree of the plaintext.
- **void SetScalingFactor(const double sf) const noexcept**: Sets the scaling factor of the plaintext.
- **void SetSlots(const uint32_t s) const noexcept**: Sets the number of slots of the plaintext.
- **void SetStringValue(const std::string& value) const**: Sets the string value of the plaintext.
- **[[nodiscard]] std::unique_ptr<std::vector<ComplexPair>> GetCopyOfCKKSPackedValue() const**: Gets a copy of the CKKS packed value.
- **[[nodiscard]] const std::vector<int64_t>& GetPackedValue() const**: Gets the packed value of the plaintext.
- **[[nodiscard]] std::unique_ptr<std::vector<double>> GetRealPackedValue() const**: Gets the real packed value of the plaintext.
- **[[nodiscard]] const std::vector<int64_t>& GetCoefPackedValue() const**: Gets the coefficient packed value of the plaintext.
- **[[nodiscard]] const std::string& GetStringValue() const**: Gets the string value of the plaintext.
- **[[nodiscard]] const std::shared_ptr<PlaintextImpl>& GetRef() const noexcept**: Gets a const reference to the internal `PlaintextImpl` object.
- **[[nodiscard]] std::shared_ptr<PlaintextImpl>& GetRef() noexcept**: Gets a reference to the internal `PlaintextImpl` object.

## Generator functions

- **[[nodiscard]] std::unique_ptr<Plaintext> GenNullPlainText()**: Generates a null plaintext object.

## Namespace

All the components are encapsulated within the `openfhe` namespace.

```cpp
namespace openfhe
{
    // Class and methods definitions
}
```

## Usage example

Here is a simple usage example in Rust:

```rust
use openfhe::Plaintext;

fn main() {
    let plaintext = Plaintext::new();
    plaintext.set_length(128);
    if plaintext.is_encoded() {
        println!("Plaintext is encoded.");
    } else {
        println!("Plaintext is not encoded.");
    }
}
```
