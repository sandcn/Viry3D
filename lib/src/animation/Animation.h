/*
* Viry3D
* Copyright 2014-2018 by Stack - stackos@qq.com
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#pragma once

#include "Node.h"
#include "AnimationCurve.h"

namespace Viry3D
{
    enum class CurvePropertyType
    {
        Unknown = 0,

        LocalPositionX,
        LocalPositionY,
        LocalPositionZ,
        LocalRotationX,
        LocalRotationY,
        LocalRotationZ,
        LocalRotationW,
        LocalScaleX,
        LocalScaleY,
        LocalScaleZ,
    };

    struct AnimationCurveWrapper
    {
        String path;
        Vector<CurvePropertyType> property_types;
        Vector<AnimationCurve> curves;
    };

    enum class AnimationWrapMode
    {
        Default = 0,
        Once = 1,
        Loop = 2,
        PingPong = 4,
        ClampForever = 8,
    };

    struct AnimationClip
    {
        String name;
        float length;
        float fps;
        AnimationWrapMode wrap_mode;
        Vector<AnimationCurveWrapper> curves;
    };

    class Animation : public Node
    {
    public:
        Animation();
        virtual ~Animation();
        void SetClips(Vector<AnimationClip>&& clips) { m_clips = std::move(clips); }
        int GetClipCount() const { return m_clips.Size(); }
        const String& GetClipName(int index) const;
        void Play(int index);
        void Stop();
        void Update();

    private:
        void Sample(const AnimationClip& clip, float time);

    private:
        Vector<AnimationClip> m_clips;
        int m_clip_index;
        float m_play_start_time;
        Vector<Node*> m_targets;
    };
}
