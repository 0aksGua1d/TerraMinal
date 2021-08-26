#pragma once

#include "GraphicBuffers.h"
#include "Renderable.h"
#include "con_script/Logical.h"
#include "con_script/data/Scope.h"
#include "utils/property.h"

using Scope = ConScript::Scope;
using Logical = ConScript::Logical;

class Sprite;
class Animation;

class StatesLoaderBase;

class RenderableState : public Logical, public Renderable, public std::enable_shared_from_this<RenderableState> {
    friend class StatesLoaderBase;
public:
    explicit RenderableState(const std::shared_ptr<Animation>& anim);
    explicit RenderableState(const std::shared_ptr<Animation>& anim, const std::shared_ptr<Scope>& init_scope);
    RenderableState(const RenderableState&);
    RenderableState(RenderableState&&) noexcept;
    RenderableState& operator=(const RenderableState&);
    RenderableState& operator=(RenderableState&&) noexcept;

    void init_ptr();

    bool need_update(size_t dTimeMilli) const override;

    void update(size_t dTimeMilli) override;

    std::shared_ptr<Renderable> copy() override;

    void draw(std::shared_ptr<Screen> screen, Position pos, unsigned long id) const override;

    void erase(std::shared_ptr<Screen> screen, Position pos, unsigned long id) const override;

private:
    std::shared_ptr<Animation> animation;

    PROPERTY(std::shared_ptr<Logical>, animation_logical);
    PROPERTY(std::weak_ptr<Logical>, parent_sprite);
    PROPERTY((std::map<size_t, std::any>), frame_callbacks);

    std::weak_ptr<Sprite> sprite;
};