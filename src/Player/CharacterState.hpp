#pragma once
#include <Utils/Color.hpp>
#include <array>

enum eStateFlags {
    STATEFLAG_NOCLIP,
    STATEFLAG_DOUBLE_JUMP,
    STATEFLAG_INVISIBLE,
    STATEFLAG_NO_HAND,
    STATEFLAG_NO_EYE,
    STATEFLAG_NO_BODY,
    STATEFLAG_DEVIL_HORN,
    STATEFLAG_GOLDEN_HALO,
    STATEFLAG_UNKNOWN_8,
    STATEFLAG_UNKNOWN_9,
    STATEFLAG_UNKNOWN_10,
    STATEFLAG_FROZEN,
    STATEFLAG_CURSED,
    STATEFLAG_DUCT_TAPE,
    STATEFLAG_CIGAR,
    STATEFLAG_SHINING,
    STATEFLAG_ZOMBIE,
    STATEFLAG_RED_BODY,
    STATEFLAG_HAUNTED_SHADOWS,
    STATEFLAG_GEIGER_RADIATION,
    STATEFLAG_SPOTLIGHT,
    STATEFLAG_YELLOW_BODY,
    STATEFLAG_PINEAPPLE_FLAG,
    STATEFLAG_FLYING_PINEAPPLE,
    STATEFLAG_SUPER_SUPPORTER_NAME,
    STATEFLAG_SUPER_PINEAPPLE,
    NUM_STATE_FLAGS
};

class CharacterState {
public:
    CharacterState() {
        for (uint8_t index = 0; index < NUM_STATE_FLAGS; index++)
            this->RemoveFlag((eStateFlags)index);
    }
    ~CharacterState() = default;

    bool IsFlagOn(const eStateFlags& flag) const {
        if (m_flags[flag])
            return true;
        return false;
    }
    void SertFlag(const eStateFlags& flag) { m_flags[flag] = true; }
    void RemoveFlag(const eStateFlags& flag) { m_flags[flag] = false; }

    uint8_t GetPunchID() const { return m_punch_id; }
    uint8_t GetPunchRange() const { return m_punch_range * 32; }
    uint8_t GetBuildRange() const { return m_build_range * 32; }
    float GetWaterSpeed() const { return m_water_speed; }
    float GetSpeed() const { return m_speed; }
    float GetGravity() const { return m_gravity; }
    float GetAcceleration() const { return m_acceleration; }
    float GetPunchStrength() const { return m_punch_strength; }
    uint32_t GetFlags() const {
        uint32_t flags = 0;
        for (auto index = 0; index < 26; index++)
            flags |= m_flags[index] << index;
        return flags;
    }

    Color GetPupilColor() const { return m_pupil_color; }
    Color GetHairColor() const { return m_hair_color; }
    Color GetEyesColor() const { return m_eyes_color; }

private:
    uint8_t m_punch_id = 0;
    uint8_t m_punch_range = 1;
    uint8_t m_build_range = 2;

    float m_water_speed = 150.0f;
    float m_speed = 260.0f;
    float m_gravity = 1000.0f;
    float m_acceleration = 1000.0f;
    float m_punch_strength = 350.0f;
    std::array<bool, NUM_STATE_FLAGS> m_flags;

    Color m_pupil_color{ 0, 0, 0, 0xFF };
    Color m_hair_color{ 0xFF, 0xFF, 0xFF, 0xFF };
    Color m_eyes_color{ 0xFF, 0xFF, 0xFF, 0xFF };
};