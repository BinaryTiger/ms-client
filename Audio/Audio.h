//	This file is part of the continued Journey MMORPG client
//	Copyright (C) 2015-2019  Daniel Allendorf, Ryan Payton, lain3d
//
//	This program is free software: you can redistribute it and/or modify
//	it under the terms of the GNU Affero General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	(at your option) any later version.
//
//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//	GNU Affero General Public License for more details.
//
//	You should have received a copy of the GNU Affero General Public License
//	along with this program.  If not, see <https://www.gnu.org/licenses/>.
#pragma once

#ifdef _WIN32
#include <nlnx/node.hpp>
#include <unordered_map>

#include "../Error.h"
#include "../MSClient.h"
#include "../Template/EnumMap.h"

namespace ms {
class Sound {
public:
    // Preloaded sounds
    enum Name {
        /// UI
        BUTTONCLICK,
        BUTTONOVER,
        CHARSELECT,
        DLGNOTICE,
        MENUDOWN,
        MENUUP,
        RACESELECT,
        SCROLLUP,
        SELECTMAP,
        TAB,
        WORLDSELECT,
        DRAGSTART,
        DRAGEND,
        WORLDMAPOPEN,
        WORLDMAPCLOSE,

        /// Login
        GAMESTART,

        /// Game
        JUMP,
        DROP,
        PICKUP,
        PORTAL,
        LEVELUP,
        TOMBSTONE,
        LENGTH
    };

    Sound(Name name);
    Sound(int32_t itemid);
    Sound(nl::node src);
    Sound();

    void play() const;

    static Error init();
    static void close();
    static bool set_sfxvolume(uint8_t volume);

private:
    size_t id;

    static void play(size_t id);

    static size_t add_sound(nl::node src);
    static void add_sound(Name name, nl::node src);
    static void add_sound(std::string itemid, nl::node src);

    static std::string format_id(int32_t itemid);

    static std::unordered_map<size_t, uint64_t> samples;
    static EnumMap<Name, size_t> soundids;
    static std::unordered_map<std::string, size_t> itemids;
};

class Music {
public:
    Music(std::string path);

    void play() const;
    void play_once() const;

    static Error init();
    static bool set_bgmvolume(uint8_t volume);
    static void update_context();

private:
    std::string path;
};
}  // namespace ms
#else
#include <AL/al.h>
#include <AL/alure2.h>

#include <array>
#include <cstdint>
#include <nlnx/node.hpp>
#include <string>
#include <unordered_map>

#include "../Error.h"
#include "../MSClient.h"
#include "../Template/EnumMap.h"
#include "membuf.h"

class FileFactory final : public alure::FileIOFactory {
private:
    std::unordered_map<std::string, membuf *> *audiodb_;

public:
    FileFactory(std::unordered_map<std::string, membuf *> *audiodb_in) :
        audiodb_(audiodb_in) {}

    alure::UniquePtr<std::istream> openFile(
        const alure::String &name) noexcept override {
        auto stream = alure::MakeUnique<std::istream>(audiodb_->at(name));
        if (stream->fail()) {
            throw std::runtime_error("Failed to create stream.");
        }
        return stream;
    }
};

namespace ms {
class Sound {
public:
    // Preloaded sounds
    enum Name {
        /// UI
        BUTTONCLICK,
        BUTTONOVER,
        CHARSELECT,
        DLGNOTICE,
        MENUDOWN,
        MENUUP,
        RACESELECT,
        SCROLLUP,
        SELECTMAP,
        TAB,
        WORLDSELECT,
        DRAGSTART,
        DRAGEND,
        WORLDMAPOPEN,
        WORLDMAPCLOSE,

        /// Login
        GAMESTART,

        /// Game
        JUMP,
        DROP,
        PICKUP,
        PORTAL,
        LEVELUP,
        TOMBSTONE,
        LENGTH
    };

    Sound(Name name);

    Sound(int32_t itemid);

    Sound(const nl::node &src);

    Sound();
    //~Sound();

    void play();

    static Error init();

    static void close();

    static bool set_sfxvolume(uint8_t volume);

private:
    size_t id;

    static size_t add_sound(const nl::node &src);

    static void add_sound(Name name, const nl::node &src);

    static void add_sound(const std::string &itemid, const nl::node &src);

    void create_alure_source();

    static std::string format_id(int32_t itemid);

    static EnumMap<Name, size_t> soundids_;
    static std::unordered_map<std::string, size_t> itemids_;
    alure::Source sound_src_;
    static size_t source_inc_;
    static alure::Source sound_srcs_[100];
};

class Music {
public:
    Music(std::string path);

    void play() const;

    void play_once() const;

    static Error init();

    static bool set_bgmvolume(uint8_t volume);

    static void update_context();

private:
    std::string path_;
    static std::unordered_map<std::string, membuf *> audiodb_;
    static alure::DeviceManager dev_mgr_;
    static alure::Device dev_;
    static alure::Context ctx_;
    static alure::Source music_src_;
    static alure::Buffer music_buff_;

    friend Sound;
};
}  // namespace ms
#endif