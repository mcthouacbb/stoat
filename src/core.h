/*
 * Stoat, a USI shogi engine
 * Copyright (C) 2025 Ciekce
 *
 * Stoat is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Stoat is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Stoat. If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include "types.h"

#include <cassert>
#include <iostream>

namespace stoat {
    class Color {
    public:
        constexpr Color() = default;

        constexpr Color(const Color&) = default;
        constexpr Color(Color&&) = default;

        [[nodiscard]] constexpr u8 raw() const {
            return m_id;
        }

        [[nodiscard]] constexpr usize idx() const {
            return static_cast<usize>(m_id);
        }

        [[nodiscard]] constexpr Color flip() const {
            assert(m_id != kNoneId);
            return Color{static_cast<u8>(m_id ^ 1)};
        }

        [[nodiscard]] static constexpr Color fromRaw(u8 id) {
            assert(id <= kNoneId);
            return Color{id};
        }

        [[nodiscard]] constexpr explicit operator bool() const {
            return m_id != kNoneId;
        }

        [[nodiscard]] constexpr bool operator==(const Color&) const = default;

        constexpr Color& operator=(const Color&) = default;
        constexpr Color& operator=(Color&&) = default;

    private:
        explicit constexpr Color(u8 id) :
                m_id{id} {}

        u8 m_id{};

        enum : u8 {
            kWhiteId = 0,
            kBlackId,
            kNoneId,
        };

        friend struct Colors;
    };

    struct Colors {
        Colors() = delete;

        static constexpr Color kWhite{Color::kWhiteId};
        static constexpr Color kBlack{Color::kBlackId};
        static constexpr Color kNone{Color::kNoneId};

        static constexpr usize kCount = kNone.idx();
    };

    class Piece;

    class PieceType {
    public:
        constexpr PieceType() = default;

        constexpr PieceType(const PieceType&) = default;
        constexpr PieceType(PieceType&&) = default;

        [[nodiscard]] constexpr u8 raw() const {
            return m_id;
        }

        [[nodiscard]] constexpr usize idx() const {
            return static_cast<usize>(m_id);
        }

        [[nodiscard]] constexpr bool isPromoted() const {
            assert(m_id <= kNoneId);
            return m_id == kPromotedPawnId || m_id == kPromotedLanceId || m_id == kPromotedKnightId
                || m_id == kPromotedSilverId || m_id == kPromotedBishopId || m_id == kPromotedRookId;
        }

        [[nodiscard]] constexpr Piece withColor(Color c) const;

        [[nodiscard]] constexpr PieceType promoted() const {
            switch (m_id) {
                case kPawnId:
                    return PieceType{kPromotedPawnId};
                case kLanceId:
                    return PieceType{kPromotedLanceId};
                case kKnightId:
                    return PieceType{kPromotedKnightId};
                case kSilverId:
                    return PieceType{kPromotedSilverId};
                case kBishopId:
                    return PieceType{kPromotedBishopId};
                case kRookId:
                    return PieceType{kPromotedRookId};
                default:
                    return PieceType{kNoneId};
            }
        }

        [[nodiscard]] static constexpr PieceType fromRaw(u8 id) {
            assert(id <= kNoneId);
            return PieceType{id};
        }

        [[nodiscard]] static constexpr PieceType unpromotedFromChar(char c) {
            switch (c) {
                case 'P':
                case 'p':
                    return PieceType{kPawnId};
                case 'L':
                case 'l':
                    return PieceType{kLanceId};
                case 'N':
                case 'n':
                    return PieceType{kKnightId};
                case 'S':
                case 's':
                    return PieceType{kSilverId};
                case 'G':
                case 'g':
                    return PieceType{kGoldId};
                case 'B':
                case 'b':
                    return PieceType{kBishopId};
                case 'R':
                case 'r':
                    return PieceType{kRookId};
                case 'K':
                case 'k':
                    return PieceType{kKingId};
                default:
                    return PieceType{kNoneId};
            }
        }

        [[nodiscard]] constexpr explicit operator bool() const {
            return m_id != kNoneId;
        }

        [[nodiscard]] constexpr bool operator==(const PieceType&) const = default;

        constexpr PieceType& operator=(const PieceType&) = default;
        constexpr PieceType& operator=(PieceType&&) = default;

    private:
        explicit constexpr PieceType(u8 id) :
                m_id{id} {}

        u8 m_id{};

        enum : u8 {
            kPawnId = 0,
            kPromotedPawnId,
            kLanceId,
            kKnightId,
            kPromotedLanceId,
            kPromotedKnightId,
            kSilverId,
            kPromotedSilverId,
            kGoldId,
            kBishopId,
            kRookId,
            kPromotedBishopId,
            kPromotedRookId,
            kKingId,
            kNoneId,
        };

        friend struct PieceTypes;

        friend inline std::ostream& operator<<(std::ostream& stream, PieceType pt) {
            switch (pt.raw()) {
                case kPawnId:
                    stream << " P";
                    break;
                case kPromotedPawnId:
                    stream << "+P";
                    break;
                case kLanceId:
                    stream << " L";
                    break;
                case kKnightId:
                    stream << " N";
                    break;
                case kPromotedLanceId:
                    stream << "+L";
                    break;
                case kPromotedKnightId:
                    stream << "+N";
                    break;
                case kSilverId:
                    stream << " S";
                    break;
                case kPromotedSilverId:
                    stream << "+S";
                    break;
                case kGoldId:
                    stream << " G";
                    break;
                case kBishopId:
                    stream << " B";
                    break;
                case kRookId:
                    stream << " R";
                    break;
                case kPromotedBishopId:
                    stream << "+B";
                    break;
                case kPromotedRookId:
                    stream << "+R";
                    break;
                case kKingId:
                    stream << " K";
                    break;
                default:
                    stream << " ?";
                    break;
            }

            return stream;
        }
    };

    struct PieceTypes {
        PieceTypes() = delete;

        static constexpr PieceType kPawn{PieceType::kPawnId};
        static constexpr PieceType kPromotedPawn{PieceType::kPromotedPawnId};
        static constexpr PieceType kLance{PieceType::kLanceId};
        static constexpr PieceType kKnight{PieceType::kKnightId};
        static constexpr PieceType kPromotedLance{PieceType::kPromotedLanceId};
        static constexpr PieceType kPromotedKnight{PieceType::kPromotedKnightId};
        static constexpr PieceType kSilver{PieceType::kSilverId};
        static constexpr PieceType kPromotedSilver{PieceType::kPromotedSilverId};
        static constexpr PieceType kGold{PieceType::kGoldId};
        static constexpr PieceType kBishop{PieceType::kBishopId};
        static constexpr PieceType kRook{PieceType::kRookId};
        static constexpr PieceType kPromotedBishop{PieceType::kPromotedBishopId};
        static constexpr PieceType kPromotedRook{PieceType::kPromotedRookId};
        static constexpr PieceType kKing{PieceType::kKingId};
        static constexpr PieceType kNone{PieceType::kNoneId};

        static constexpr usize kCount = kNone.idx();
    };

    class Piece {
    public:
        constexpr Piece() = default;

        constexpr Piece(const Piece&) = default;
        constexpr Piece(Piece&&) = default;

        [[nodiscard]] constexpr u8 raw() const {
            return m_id;
        }

        [[nodiscard]] constexpr usize idx() const {
            return static_cast<usize>(m_id);
        }

        [[nodiscard]] constexpr PieceType type() const {
            assert(m_id != kNoneId);
            return PieceType::fromRaw(m_id >> 1);
        }

        [[nodiscard]] constexpr Color color() const {
            assert(m_id != kNoneId);
            return Color::fromRaw(m_id & 0b1);
        }

        [[nodiscard]] constexpr Piece promoted() const {
            return type().promoted().withColor(color());
        }

        [[nodiscard]] static constexpr Piece fromRaw(u8 id) {
            assert(id <= kNoneId);
            return Piece{id};
        }

        [[nodiscard]] static constexpr Piece unpromotedFromChar(char c) {
            switch (c) {
                case 'P':
                    return Piece{kBlackPawnId};
                case 'p':
                    return Piece{kWhitePawnId};
                case 'L':
                    return Piece{kBlackLanceId};
                case 'l':
                    return Piece{kWhiteLanceId};
                case 'N':
                    return Piece{kBlackKnightId};
                case 'n':
                    return Piece{kWhiteKnightId};
                case 'S':
                    return Piece{kBlackSilverId};
                case 's':
                    return Piece{kWhiteSilverId};
                case 'G':
                    return Piece{kBlackGoldId};
                case 'g':
                    return Piece{kWhiteGoldId};
                case 'B':
                    return Piece{kBlackBishopId};
                case 'b':
                    return Piece{kWhiteBishopId};
                case 'R':
                    return Piece{kBlackRookId};
                case 'r':
                    return Piece{kWhiteRookId};
                case 'K':
                    return Piece{kBlackKingId};
                case 'k':
                    return Piece{kWhiteKingId};
                default:
                    return Piece{kNoneId};
            }
        }

        [[nodiscard]] static constexpr Piece fromStr(std::string_view str) {
            if (str.empty()) {
                return Piece{kNoneId};
            }

            if (str.length() == 2 && str[0] == ' ') {
                str = str.substr(1);
            }

            if (str.length() != 1 && str.length() != 2 || str.length() == 2 && str[0] != '+') {
                return Piece{kNoneId};
            }

            const auto piece = unpromotedFromChar(str.back());
            return str.length() == 2 ? piece.promoted() : piece;
        }

        [[nodiscard]] constexpr explicit operator bool() const {
            return m_id != kNoneId;
        }

        [[nodiscard]] constexpr bool operator==(const Piece&) const = default;

        constexpr Piece& operator=(const Piece&) = default;
        constexpr Piece& operator=(Piece&&) = default;

    private:
        explicit constexpr Piece(u8 id) :
                m_id{id} {}

        u8 m_id{};

        enum : u8 {
            kBlackPawnId = 0,
            kWhitePawnId,
            kBlackPromotedPawnId,
            kWhitePromotedPawnId,
            kBlackLanceId,
            kWhiteLanceId,
            kBlackKnightId,
            kWhiteKnightId,
            kBlackPromotedLanceId,
            kWhitePromotedLanceId,
            kBlackPromotedKnightId,
            kWhitePromotedKnightId,
            kBlackSilverId,
            kWhiteSilverId,
            kBlackPromotedSilverId,
            kWhitePromotedSilverId,
            kBlackGoldId,
            kWhiteGoldId,
            kBlackBishopId,
            kWhiteBishopId,
            kBlackRookId,
            kWhiteRookId,
            kBlackPromotedBishopId,
            kWhitePromotedBishopId,
            kBlackPromotedRookId,
            kWhitePromotedRookId,
            kBlackKingId,
            kWhiteKingId,
            kNoneId,
        };

        friend struct Pieces;

        friend inline std::ostream& operator<<(std::ostream& stream, Piece piece) {
            switch (piece.raw()) {
                case kBlackPawnId:
                    stream << " P";
                    break;
                case kWhitePawnId:
                    stream << " p";
                    break;
                case kBlackPromotedPawnId:
                    stream << "+P";
                    break;
                case kWhitePromotedPawnId:
                    stream << "+p";
                    break;
                case kBlackLanceId:
                    stream << " L";
                    break;
                case kWhiteLanceId:
                    stream << " l";
                    break;
                case kBlackKnightId:
                    stream << " N";
                    break;
                case kWhiteKnightId:
                    stream << " n";
                    break;
                case kBlackPromotedLanceId:
                    stream << "+L";
                    break;
                case kWhitePromotedLanceId:
                    stream << "+l";
                    break;
                case kBlackPromotedKnightId:
                    stream << "+N";
                    break;
                case kWhitePromotedKnightId:
                    stream << "+n";
                    break;
                case kBlackSilverId:
                    stream << " S";
                    break;
                case kWhiteSilverId:
                    stream << " s";
                    break;
                case kBlackPromotedSilverId:
                    stream << "+S";
                    break;
                case kWhitePromotedSilverId:
                    stream << "+s";
                    break;
                case kBlackGoldId:
                    stream << " G";
                    break;
                case kWhiteGoldId:
                    stream << " g";
                    break;
                case kBlackBishopId:
                    stream << " B";
                    break;
                case kWhiteBishopId:
                    stream << " b";
                    break;
                case kBlackRookId:
                    stream << " R";
                    break;
                case kWhiteRookId:
                    stream << " r";
                    break;
                case kBlackPromotedBishopId:
                    stream << "+B";
                    break;
                case kWhitePromotedBishopId:
                    stream << "+b";
                    break;
                case kBlackPromotedRookId:
                    stream << "+R";
                    break;
                case kWhitePromotedRookId:
                    stream << "+r";
                    break;
                case kBlackKingId:
                    stream << " K";
                    break;
                case kWhiteKingId:
                    stream << " k";
                    break;
                default:
                    stream << " ?";
                    break;
            }

            return stream;
        }
    };

    constexpr Piece PieceType::withColor(Color c) const {
        assert(*this != PieceTypes::kNone);
        assert(c != Colors::kNone);

        return Piece::fromRaw((m_id << 1) | c.raw());
    }

    struct Pieces {
        Pieces() = delete;

        static constexpr Piece kBlackPawn{Piece::kBlackPawnId};
        static constexpr Piece kWhitePawn{Piece::kWhitePawnId};
        static constexpr Piece kBlackPromotedPawn{Piece::kBlackPromotedPawnId};
        static constexpr Piece kWhitePromotedPawn{Piece::kWhitePromotedPawnId};
        static constexpr Piece kBlackLance{Piece::kBlackLanceId};
        static constexpr Piece kWhiteLance{Piece::kWhiteLanceId};
        static constexpr Piece kBlackKnight{Piece::kBlackKnightId};
        static constexpr Piece kWhiteKnight{Piece::kWhiteKnightId};
        static constexpr Piece kBlackPromotedLance{Piece::kBlackPromotedLanceId};
        static constexpr Piece kWhitePromotedLance{Piece::kWhitePromotedLanceId};
        static constexpr Piece kBlackPromotedKnight{Piece::kBlackPromotedKnightId};
        static constexpr Piece kWhitePromotedKnight{Piece::kWhitePromotedKnightId};
        static constexpr Piece kBlackSilver{Piece::kBlackSilverId};
        static constexpr Piece kWhiteSilver{Piece::kWhiteSilverId};
        static constexpr Piece kBlackPromotedSilver{Piece::kBlackPromotedSilverId};
        static constexpr Piece kWhitePromotedSilver{Piece::kWhitePromotedSilverId};
        static constexpr Piece kBlackGold{Piece::kBlackGoldId};
        static constexpr Piece kWhiteGold{Piece::kWhiteGoldId};
        static constexpr Piece kBlackBishop{Piece::kBlackBishopId};
        static constexpr Piece kWhiteBishop{Piece::kWhiteBishopId};
        static constexpr Piece kBlackRook{Piece::kBlackRookId};
        static constexpr Piece kWhiteRook{Piece::kWhiteRookId};
        static constexpr Piece kBlackPromotedBishop{Piece::kBlackPromotedBishopId};
        static constexpr Piece kWhitePromotedBishop{Piece::kWhitePromotedBishopId};
        static constexpr Piece kBlackPromotedRook{Piece::kBlackPromotedRookId};
        static constexpr Piece kWhitePromotedRook{Piece::kWhitePromotedRookId};
        static constexpr Piece kBlackKing{Piece::kBlackKingId};
        static constexpr Piece kWhiteKing{Piece::kWhiteKingId};
        static constexpr Piece kNone{Piece::kNoneId};

        static constexpr usize kCount = kNone.idx();
    };

    class Square {
    public:
        constexpr Square() = default;

        constexpr Square(const Square&) = default;
        constexpr Square(Square&&) = default;

        [[nodiscard]] constexpr u8 raw() const {
            return m_id;
        }

        [[nodiscard]] constexpr usize idx() const {
            return static_cast<usize>(m_id);
        }

        [[nodiscard]] constexpr u128 bit() const {
            assert(m_id != kNoneId);
            return u128{1} << m_id;
        }

        [[nodiscard]] constexpr Square offset(i32 offset) const {
            assert(m_id + offset >= 0);
            assert(m_id + offset < kNoneId);
            return fromRaw(m_id + offset);
        }

        [[nodiscard]] constexpr Square rotate() const {
            return fromRaw(kNoneId - m_id - 1);
        }

        [[nodiscard]] static constexpr Square fromRaw(u8 id) {
            assert(id <= kNoneId);
            return Square{id};
        }

        [[nodiscard]] static constexpr Square fromStr(std::string_view str) {
            if (str.length() != 2) {
                return Square{kNoneId};
            }

            if (str[0] < '1' || str[0] > '9' || str[1] < 'a' || str[1] > 'h') {
                return Square{kNoneId};
            }

            const u32 file = str[0] - '1';
            const u32 rank = str[1] - 'a';

            return fromRaw(rank * 9 + file);
        }

        [[nodiscard]] constexpr explicit operator bool() const {
            return m_id != kNoneId;
        }

        [[nodiscard]] constexpr bool operator==(const Square&) const = default;

        constexpr Square& operator=(const Square&) = default;
        constexpr Square& operator=(Square&&) = default;

    private:
        explicit constexpr Square(u8 id) :
                m_id{id} {}

        u8 m_id{};

        enum : u8 {
            k1AId,
            k2AId,
            k3AId,
            k4AId,
            k5AId,
            k6AId,
            k7AId,
            k8AId,
            k9AId,
            k1BId,
            k2BId,
            k3BId,
            k4BId,
            k5BId,
            k6BId,
            k7BId,
            k8BId,
            k9BId,
            k1CId,
            k2CId,
            k3CId,
            k4CId,
            k5CId,
            k6CId,
            k7CId,
            k8CId,
            k9CId,
            k1DId,
            k2DId,
            k3DId,
            k4DId,
            k5DId,
            k6DId,
            k7DId,
            k8DId,
            k9DId,
            k1EId,
            k2EId,
            k3EId,
            k4EId,
            k5EId,
            k6EId,
            k7EId,
            k8EId,
            k9EId,
            k1FId,
            k2FId,
            k3FId,
            k4FId,
            k5FId,
            k6FId,
            k7FId,
            k8FId,
            k9FId,
            k1GId,
            k2GId,
            k3GId,
            k4GId,
            k5GId,
            k6GId,
            k7GId,
            k8GId,
            k9GId,
            k1HId,
            k2HId,
            k3HId,
            k4HId,
            k5HId,
            k6HId,
            k7HId,
            k8HId,
            k9HId,
            kNoneId,
        };

        friend struct Squares;

        friend inline std::ostream& operator<<(std::ostream& stream, Square square) {
            if (square.raw() == kNoneId) {
                stream << "??";
                return stream;
            }

            std::cout << static_cast<char>('1' + (square.raw() % 9));
            std::cout << static_cast<char>('a' + (square.raw() / 9));

            return stream;
        }
    };

    struct Squares {
        Squares() = delete;

        static constexpr Square k1A{Square::k1AId};
        static constexpr Square k2A{Square::k2AId};
        static constexpr Square k3A{Square::k3AId};
        static constexpr Square k4A{Square::k4AId};
        static constexpr Square k5A{Square::k5AId};
        static constexpr Square k6A{Square::k6AId};
        static constexpr Square k7A{Square::k7AId};
        static constexpr Square k8A{Square::k8AId};
        static constexpr Square k9A{Square::k9AId};
        static constexpr Square k1B{Square::k1BId};
        static constexpr Square k2B{Square::k2BId};
        static constexpr Square k3B{Square::k3BId};
        static constexpr Square k4B{Square::k4BId};
        static constexpr Square k5B{Square::k5BId};
        static constexpr Square k6B{Square::k6BId};
        static constexpr Square k7B{Square::k7BId};
        static constexpr Square k8B{Square::k8BId};
        static constexpr Square k9B{Square::k9BId};
        static constexpr Square k1C{Square::k1CId};
        static constexpr Square k2C{Square::k2CId};
        static constexpr Square k3C{Square::k3CId};
        static constexpr Square k4C{Square::k4CId};
        static constexpr Square k5C{Square::k5CId};
        static constexpr Square k6C{Square::k6CId};
        static constexpr Square k7C{Square::k7CId};
        static constexpr Square k8C{Square::k8CId};
        static constexpr Square k9C{Square::k9CId};
        static constexpr Square k1D{Square::k1DId};
        static constexpr Square k2D{Square::k2DId};
        static constexpr Square k3D{Square::k3DId};
        static constexpr Square k4D{Square::k4DId};
        static constexpr Square k5D{Square::k5DId};
        static constexpr Square k6D{Square::k6DId};
        static constexpr Square k7D{Square::k7DId};
        static constexpr Square k8D{Square::k8DId};
        static constexpr Square k9D{Square::k9DId};
        static constexpr Square k1E{Square::k1EId};
        static constexpr Square k2E{Square::k2EId};
        static constexpr Square k3E{Square::k3EId};
        static constexpr Square k4E{Square::k4EId};
        static constexpr Square k5E{Square::k5EId};
        static constexpr Square k6E{Square::k6EId};
        static constexpr Square k7E{Square::k7EId};
        static constexpr Square k8E{Square::k8EId};
        static constexpr Square k9E{Square::k9EId};
        static constexpr Square k1F{Square::k1FId};
        static constexpr Square k2F{Square::k2FId};
        static constexpr Square k3F{Square::k3FId};
        static constexpr Square k4F{Square::k4FId};
        static constexpr Square k5F{Square::k5FId};
        static constexpr Square k6F{Square::k6FId};
        static constexpr Square k7F{Square::k7FId};
        static constexpr Square k8F{Square::k8FId};
        static constexpr Square k9F{Square::k9FId};
        static constexpr Square k1G{Square::k1GId};
        static constexpr Square k2G{Square::k2GId};
        static constexpr Square k3G{Square::k3GId};
        static constexpr Square k4G{Square::k4GId};
        static constexpr Square k5G{Square::k5GId};
        static constexpr Square k6G{Square::k6GId};
        static constexpr Square k7G{Square::k7GId};
        static constexpr Square k8G{Square::k8GId};
        static constexpr Square k9G{Square::k9GId};
        static constexpr Square k1H{Square::k1HId};
        static constexpr Square k2H{Square::k2HId};
        static constexpr Square k3H{Square::k3HId};
        static constexpr Square k4H{Square::k4HId};
        static constexpr Square k5H{Square::k5HId};
        static constexpr Square k6H{Square::k6HId};
        static constexpr Square k7H{Square::k7HId};
        static constexpr Square k8H{Square::k8HId};
        static constexpr Square k9H{Square::k9HId};
        static constexpr Square kNone{Square::kNoneId};

        static constexpr usize kCount = kNone.idx();
    };
} // namespace stoat
