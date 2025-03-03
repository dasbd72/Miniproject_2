#include "ButtonImage.hpp"

#include <functional>
#include <memory>

#include "Collider.hpp"
#include "EngineGame.hpp"
#include "Image.hpp"
#include "Point.hpp"
#include "Resources.hpp"

namespace Engine {
ButtonImage::ButtonImage(std::string img, std::string imgIn, float x, float y, float w, float h, float anchorX, float anchorY) : Image(img, x, y, w, h, anchorX, anchorY), imgOut(Resources::GetInstance().GetBitmap(img)), imgIn(Resources::GetInstance().GetBitmap(imgIn)) {
    Point mouse = EngineGame::GetInstance().GetMousePosition();
    mouseIn = Collider::IsPointInBitmap(Point((mouse.x - Position.x) * GetBitmapWidth() / Size.x + Anchor.x * GetBitmapWidth(), (mouse.y - Position.y) * GetBitmapHeight() / Size.y + Anchor.y * GetBitmapHeight()), bmp);
    if (!mouseIn || !Enabled)
        bmp = imgOut;
    else
        bmp = this->imgIn;
}
void ButtonImage::SetOnClickCallback(std::function<void(void)> onClickCallback) {
    OnClickCallback = onClickCallback;
}
void ButtonImage::OnMouseDown(int button, int mx, int my) {
    if ((button & 1) && mouseIn && Enabled) {
        if (OnClickCallback)
            OnClickCallback();
    }
}
void ButtonImage::OnMouseMove(int mx, int my) {
    mouseIn = Collider::IsPointInBitmap(Point((mx - Position.x) * GetBitmapWidth() / Size.x + Anchor.x * GetBitmapWidth(), (my - Position.y) * GetBitmapHeight() / Size.y + Anchor.y * GetBitmapHeight()), bmp);
    if (!mouseIn || !Enabled)
        bmp = imgOut;
    else
        bmp = imgIn;
}
}  // namespace Engine
