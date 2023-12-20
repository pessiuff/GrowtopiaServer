#pragma once
#include <cstdint>
#include <sqlpp11/table.h>
#include <sqlpp11/char_sequence.h>
#include <sqlpp11/column_types.h>

namespace PlayerInterface {
    struct ID {
        struct _alias_t {
            static constexpr const char _literal[] = "ID";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
            template <typename T>
            struct _member_t {
                T Id;
                T& operator()() { return Id; }
                const T& operator()() const { return Id; }
            };
        };
        using _traits = ::sqlpp::make_traits<::sqlpp::integral, ::sqlpp::tag::must_not_insert, ::sqlpp::tag::must_not_update>;
    };
    struct TankIDName {
        struct _alias_t {
            static constexpr const char _literal[] = "TankIDName";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
            template <typename T>
            struct _member_t {
                T tankIdName;
                T& operator()() { return tankIdName; }
                const T& operator()() const { return tankIdName; }
            };
        };
        using _traits = ::sqlpp::make_traits<::sqlpp::varchar>;
    };
    struct TankIDPass {
        struct _alias_t {
            static constexpr const char _literal[] = "TankIDPass";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
            template <typename T>
            struct _member_t {
                T tankIdPass;
                T& operator()() { return tankIdPass; }
                const T& operator()() const { return tankIdPass; }
            };
        };
        using _traits = ::sqlpp::make_traits<::sqlpp::varchar>;
    };
}

struct PlayerDB
: sqlpp::table_t<PlayerDB,
    PlayerInterface::ID,
    PlayerInterface::TankIDName,
    PlayerInterface::TankIDPass> {
    struct _alias_t {
        static constexpr const char _literal[] = "Players";
        using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
        template <typename T>
        struct _member_t {
            T playerDB;
            T& operator()() { return playerDB; }
            const T& operator()() const { return playerDB; }
        };
    };
};