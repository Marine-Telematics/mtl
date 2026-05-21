///-----------------------------------------------------------------------------
/// MarineTelematics Template Library - (c) 2025 Marine Telematics
///-----------------------------------------------------------------------------
///
/// @file token_list.h
/// @author Gabriel Novalski (gabriel@marinetelematics.com.br)
/// @date 01-02-2026
///
///-----------------------------------------------------------------------------

#ifndef MTL_TOKEN_LIST_H
#define MTL_TOKEN_LIST_H

#include <span>
#include <array>
#include <string>
#include <string_view>

namespace mtl
{
/// @brief Splits a comma-separated value into a span of trimmed tokens.
///
/// The tokens are copied into static storage so the returned string_views stay
/// valid regardless of later changes to the parsed source file.
template<size_t N>
class token_list
{
    public:
    static constexpr size_t max_items = N;

    std::array<std::string, max_items>      _storage{};
    std::array<std::string_view, max_items> _views{};
    size_t                                  _count = 0u;

    auto parse(const std::string &csv) -> std::span<const std::string_view>
    {
        this->_count = 0u;

        size_t start = 0u;
        while((start <= csv.size()) && (this->_count < max_items))
        {
            size_t comma = csv.find(',', start);
            if(comma == std::string::npos)
            {
                comma = csv.size();
            }

            std::string token = csv.substr(start, comma - start);
            trim(token);

            if(!token.empty())
            {
                this->_storage[this->_count] = token;
                this->_views[this->_count]   = this->_storage[this->_count];
                this->_count += 1u;
            }

            start = comma + 1u;
        }

        return {this->_views.data(), this->_count};
    }

    private:
    /// @brief Returns a string of whitespace characters.
    constexpr auto whitespaces() -> const char* { return " \t\n\r\f\v"; }

    /// @brief Trims a string in place.
    void trim(std::string &str)
    {
        // first erasing from end should be slighty more efficient
        // because erasing from start potentially moves all chars
        // multiple indices towards the front.

        auto lastpos = str.find_last_not_of(whitespaces());
        if(lastpos == std::string::npos)
        {
            str.clear();
            return;
        }

        str.erase(lastpos + 1);
        str.erase(0, str.find_first_not_of(whitespaces()));
    }
};

}

#endif
