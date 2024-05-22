// Đưa vào tệp tiêu đề chính của trò chơi và thư viện iostream.
#include "game.h"
#include <iostream>

// Khai báo biến tĩnh để quản lý trạng thái thoát và trạng thái 'chết' của nhân vật, cũng như điểm số.
bool LTexture::quit = false;
bool LTexture::die = true;
short int LTexture::score = 0;

// Khai báo biến tĩnh cho cửa sổ và bộ kết xuất của SDL, và sự kiện.
SDL_Window* LTexture::gWindow = NULL;
SDL_Renderer* LTexture::gRenderer = NULL;
SDL_Event LTexture::event;

// Constructor của lớp LTexture khởi tạo texture là NULL.
LTexture::LTexture()
{
    Texture = NULL;
}

// Hàm lấy chiều rộng của texture.
short int LTexture::getWidth()
{
    return tWidth;
}

// Hàm lấy chiều cao của texture.
short int LTexture::getHeight()
{
    return tHeight;
}

// Hàm giải phóng bộ nhớ của texture.
void LTexture::free()
{
    if( Texture != NULL ) // Kiểm tra nếu texture không phải là NULL.
    {
        SDL_DestroyTexture( Texture ); // Hủy texture.
        Texture = NULL; // Đặt lại texture là NULL.
        tWidth = 0; // Đặt lại chiều rộng.
        tHeight = 0; // Đặt lại chiều cao.
    }
}

// Hàm render texture lên màn hình.
void LTexture::Render(short int x, short int y, short int angle, SDL_Rect* clip, SDL_RendererFlip flip)
{
    SDL_Rect Rec_Render = { x, y, tWidth, tHeight }; // Tạo hình chữ nhật để render.

    if( clip != NULL ) // Nếu có clip (vùng cụ thể của texture).
    {
        Rec_Render.w = clip->w; // Đặt chiều rộng của hình chữ nhật bằng chiều rộng của clip.
        Rec_Render.h = clip->h; // Đặt chiều cao của hình chữ nhật bằng chiều cao của clip.
    }

    SDL_RenderCopyEx( gRenderer, Texture, clip, &Rec_Render, angle, NULL, flip ); // Thực hiện render texture với các tùy chỉnh.
}

// Hàm tải texture từ đường dẫn file.
bool LTexture::Load(string path, double scale)
{
    free(); // Giải phóng texture hiện tại trước khi tải texture mới.

    SDL_Surface* loadedSurface = IMG_Load( path.c_str() ); // Tải hình ảnh từ đường dẫn.
    if( loadedSurface == NULL ) // Nếu tải thất bại.
    {
        printf( "Unable to load image %s! Error: %s", path.c_str(), IMG_GetError() ); // In lỗi tải hình ảnh.
    }
    else
    {
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0x00, 0xFF, 0xFF ) ); // Thiết lập màu xanh lam làm màu trong suốt.

        Texture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface ); // Tạo texture từ surface đã tải.
        if( Texture == NULL ) // Nếu tạo texture thất bại.
        {
            printf( "Unable to create texture from %s! Error: %s", path.c_str(), SDL_GetError() ); // In lỗi tạo texture.
        }
        else
        {
            tWidth = static_cast<short int>(loadedSurface->w * scale); // Đặt chiều rộng của texture sau khi đã áp dụng tỉ lệ.
            tHeight = static_cast<short int>(loadedSurface->h * scale); // Đặt chiều cao của texture sau khi đã áp dụng tỉ lệ.
        }

        SDL_FreeSurface( loadedSurface ); // Giải phóng bộ nhớ của surface.
    }
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF , 0xFF); // Đặt màu vẽ mặc định cho renderer.

    return Texture != NULL; // Trả về true nếu texture được tạo thành công.
}

// Hàm kiểm tra xem texture có phải là NULL không.
bool LTexture::isNULL()
{
    return Texture == NULL;
}

// Hàm lấy vị trí đã được truyền vào và cập nhật vào các biến thành viên x, y của lớp position.
void position::getPos(const short int x, const short int y)
{
    this->x = x; // Cập nhật giá trị x.
    this->y = y; // Cập nhật giá trị y.
}
