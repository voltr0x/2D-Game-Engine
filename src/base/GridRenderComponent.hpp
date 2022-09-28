#if !defined(GRID_RENDER_COMPONENT_HPP)
#define GRID_RENDER_COMPONENT_HPP

#include <sstream>
#include "GameObject.hpp"
#include "RectRenderComponent.hpp"
#include "../Globals.hpp"

class GridRenderComponent : public RenderComponent {
 public:
  GridRenderComponent(GameObject& gameObject, float size, int xsz, int ysz)
      : RenderComponent(gameObject),
        // mSize(size),
        mXsz(xsz),
        mYsz(ysz) {
  }

  virtual void render(SDL_Renderer* renderer) const override {
    TTF_Font* mFont = RESOURCE_MANAGER.getFont(FONT_NORMAL, 14);
    std::stringstream mText;

    SDL_SetRenderDrawColor(renderer, 0x33, 0x33, 0x33, 0xaa);

    const GameObject& gameObject = getGameObject();
    for (int ii = 0; ii < mXsz; ++ii) {
      for (int jj = 0; jj < mYsz; ++jj) {
        int mX_ = int(gameObject.x() + ii * mXsz);
        int mY_ = int(gameObject.y() + jj * mYsz);
        SDL_Rect drawRect = {mX_, mY_, mXsz, mYsz};
        SDL_RenderDrawRect(renderer, &drawRect);

        mText.str("");
        mText << jj << ":" << ii;
        TextTexture* mTextTexture = RESOURCE_MANAGER.getTextTexture(mFont, mText.str().c_str(), {200, 200, 200, 120});
        mTextTexture->render(renderer, mX_ + 5, mY_ + 2);
      }
    }
  }

 private:
  // const float mSize;
  const int mXsz, mYsz;
};

#endif  // GRID_RENDER_COMPONENT_HPP