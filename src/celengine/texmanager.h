// texmanager.h
//
// Copyright (C) 2001 Chris Laurel <claurel@shatters.net>
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.

#ifndef _TEXMANAGER_H_
#define _TEXMANAGER_H_

#include <celutil/resmanager.h>
#include <celengine/texture.h>
#include "multitexture.h"


class TextureInfo : public ResourceInfo<Texture>
{
 public:
    fs::path source;
    fs::path path;
    unsigned int flags;
    float bumpHeight;
    unsigned int resolution;

    enum {
        WrapTexture      = 0x1,
        CompressTexture  = 0x2,
        NoMipMaps        = 0x4,
        AutoMipMaps      = 0x8,
        AllowSplitting   = 0x10,
        BorderClamp      = 0x20,
    };

    TextureInfo(const fs::path& _source,
                const fs::path& _path,
                unsigned int _flags,
                unsigned int _resolution = medres) :
        source(_source),
        path(_path),
        flags(_flags),
        bumpHeight(0.0f),
        resolution(_resolution) {};

    TextureInfo(const fs::path& _source,
                const fs::path& _path,
                float _bumpHeight,
                unsigned int _flags,
                unsigned int _resolution = medres) :
        source(_source),
        path(_path),
        flags(_flags),
        bumpHeight(_bumpHeight),
        resolution(_resolution) {};

    TextureInfo(const fs::path& _source,
                unsigned int _flags,
                unsigned int _resolution = medres) :
        source(_source),
        path(""),
        flags(_flags),
        bumpHeight(0.0f),
        resolution(_resolution) {};

    fs::path resolve(const fs::path&) override;
    Texture* load(const fs::path&) override;
};

inline bool operator<(const TextureInfo& ti0, const TextureInfo& ti1)
{
    if (ti0.resolution == ti1.resolution)
    {
        if (ti0.source == ti1.source)
            return ti0.path < ti1.path;
        else
            return ti0.source < ti1.source;
    }
    else
    {
        return ti0.resolution < ti1.resolution;
    }
}

typedef ResourceManager<TextureInfo> TextureManager;

extern TextureManager* GetTextureManager();

#endif // _TEXMANAGER_H_

