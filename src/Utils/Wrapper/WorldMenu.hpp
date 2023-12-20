#pragma once
#include <string>
#include <Utils/Color.hpp>
#include <fmt/core.h>

class WorldMenu {
public:
    WorldMenu() { m_result.clear(); }
    ~WorldMenu() = default;

    [[nodiscard]] std::string Get() const { return m_result; }

    WorldMenu* AddFloater(const std::string& text, const int& player_count, const double& scale, const Color& color) {
        m_result.append(fmt::format("add_floater|{}|{}|{}|{}\n", text, player_count, scale, color.GetInt()));
        return this;
    }
    WorldMenu* AddButton(const std::string& text, const std::string& name, const int& scale, const Color& color) {
        m_result.append(fmt::format("add_button|{}|{}|{}|{}\n", text, name, scale, color.GetInt()));
        return this;
    }
    WorldMenu* SetDefault(const std::string& name) {
        m_result.append(fmt::format("default|{}\n", name));
        return this;
    }
    WorldMenu* AddHeading(const std::string& text) {
        m_result.append(fmt::format("add_heading|{}\n", text));
        return this;
    }
    WorldMenu* AddFilter() {
        m_result.append("add_filter\n");
        return this;
    }
    WorldMenu* SetMaxRows(const int& count) {
        m_result.append(fmt::format("set_max_rows|{}\n", count));
        return this;
    }
    WorldMenu* SetupSimpleMenu() {
        m_result.append("setup_simple_menu\n");
        return this;
    }
private:
    std::string m_result;
};