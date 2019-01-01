#pragma once

#include <cstdint>
#include <utils/string.h>

namespace ZenLoad
{
    enum
    {
        ANIEVENT_MAX_NUM_VALUES = 4
    };

    // TODO: these should be general flags?
    enum EModelScriptAniFlags
    {
        MSB_MOVE_MODEL   = 0x00000001, ///< Animation moves model in world space
        MSB_ROTATE_MODEL = 0x00000002, ///< Animation rotates model in world space
        MSB_QUEUE_ANI    = 0x00000004, ///< Animation is queued after the current any on layer instead of started immediately
        MSB_FLY          = 0x00000008, ///< Don't stick to ground
        MSB_IDLE         = 0x00000010, ///< Idle animation
    };

    // TODO: should general enum?
    enum EModelScriptAniDir
    {
        MSB_FORWARD,
        MSB_BACKWARD
    };

    struct zCModelScriptAni
    {
        /// Add + ".MAN" for the animation data
        Utils::String m_Name;
        uint32_t m_Layer = 0;
        Utils::String m_Next;
        float m_BlendIn = 0;
        float m_BlendOut = 0;
        uint32_t m_Flags = 0;
        Utils::String m_Asc;
        EModelScriptAniDir m_Dir = MSB_FORWARD;
        int32_t m_FirstFrame = 0;
        int32_t m_LastFrame = 0;
        float m_MaxFps = 0.0f;
        float m_Speed = 0.0f;
        float m_ColVolScale = 1.0f;
    };

    struct zCModelScriptAniAlias
    {
        /// Add + ".MAN" for the animation data
        Utils::String m_Name;
        uint32_t m_Layer = 0;
        Utils::String m_Next;
        float m_BlendIn = 0;
        float m_BlendOut = 0;
        uint32_t m_Flags = 0;
        Utils::String m_Alias;
        EModelScriptAniDir m_Dir = MSB_FORWARD;
    };

    struct zCModelScriptAniBlend
    {
        Utils::String m_Name;
        uint32_t m_Layer = 0;
        Utils::String m_Next;
        float m_BlendIn = 0;
        float m_BlendOut = 0;
    };

    struct zCModelScriptAniSync
    {
        Utils::String m_Name;
        uint32_t m_Layer = 0;
        Utils::String m_Next;
    };

    struct zCModelScriptAniCombine
    {
        Utils::String m_Name;
        uint32_t m_Layer = 0;
        Utils::String m_Next;
        float m_BlendIn = 0;
        float m_BlendOut = 0;
        uint32_t m_Flags = 0;
        Utils::String m_Asc;
        uint32_t m_LastFrame = 0;
    };

    struct zCModelScriptAniDisable
    {
        Utils::String m_Name;
    };

    struct zCModelScriptEventTag
    {
        int32_t m_Frame;
        Utils::String m_Tag;
        Utils::String m_Argument;
    };

    struct zCModelScriptEventSfx
    {
        int32_t m_Frame = 0;
        Utils::String m_Name;

        /**
         * If non-zero, will overwrite the default sound range of the character
         */
        float m_Range = 0.0f;

        /**
         * If true, the sound shall be played in a new "empty slow", which means
         * that it should not overwrite the currently playing sound.
         */
        bool m_EmptySlot = false;
    };

    struct zCModelScriptEventPfx
    {
        int32_t m_Frame;
        int32_t m_Num;
        Utils::String m_Name;
        Utils::String m_Pos;
        bool m_isAttached = false;

    };
    struct zCModelScriptEventPfxStop
    {
        int32_t m_Frame;
        int32_t m_Num;

    };
} //namespace ZenLoad
