#pragma once
// Đảm bảo rằng tệp tiêu đề chỉ được bao gồm một lần trong quá trình biên dịch.

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
// Bao gồm các tệp tiêu đề SDL để xử lý đa phương tiện, xử lý hình ảnh, và xử lý phông chữ.

#include <string>
#include <vector>
#include <stdio.h>
// Bao gồm các thư viện chuẩn cho chuỗi, mảng động, và các chức năng nhập/xuất chuẩn.

using namespace std;

class position
{
public:
    short int x, y, angle, state;
    // Khai báo các biến thành viên công khai cho tọa độ x, y, góc xoay, và trạng thái.

    void getPos(const short int x, const short int y);
    // Khai báo một hàm thành viên công khai để cập nhật tọa độ của đối tượng position.
};

class LTexture
{
public:
    LTexture();
    // Khai báo một hàm tạo cho lớp LTexture.

    ~LTexture() {}
    // Khai báo một hàm hủy rỗng.

    bool isNULL();
    // Khai báo một hàm thành viên để kiểm tra texture có phải là NULL không.

    bool Load(string path, double scale = 1);
    // Khai báo một hàm thành viên để tải texture từ một tệp với một hệ số tỷ lệ tùy chọn.

    short int getWidth();
    short int getHeight();
    // Khai báo các hàm thành viên để lấy chiều rộng và chiều cao của texture.

    void free();
    // Khai báo một hàm thành viên để giải phóng các tài nguyên của texture.

    void Render(short int x, short int y, short int angle = 0, SDL_Rect* clip = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
    // Khai báo một hàm thành viên để render texture tại một vị trí cụ thể, với một góc xoay tùy chọn, hình chữ nhật cắt, và chế độ lật.

public:
    SDL_Texture* Texture;
    // Khai báo một con trỏ công khai đến một SDL_Texture.

    short int tWidth, tHeight;
    // Khai báo các biến thành viên công khai cho chiều rộng và chiều cao của texture.

public:
    static SDL_Window* gWindow;
    static SDL_Renderer* gRenderer;
    static SDL_Event event;
    // Khai báo các thành viên tĩnh cho cửa sổ SDL, bộ kết xuất, và xử lý sự kiện.

    static bool quit;
    static bool die;
    static short int score;
    // Khai báo các cờ boolean tĩnh để điều khiển trò chơi và một biến điểm tĩnh.

    static const short int SCREEN_WIDTH = 350;
    static const short int SCREEN_HEIGHT = 625;
    static const short int PIPE_SPACE = 160;
    static const short int TOTAL_PIPE = 4;
    static const short int PIPE_DISTANCE = 220;
    static const short int LAND_HEIGHT = 140;
    static const short int CHARACTER_WIDTH = 50;
    static const short int CHARACTER_HEIGHT = 35;
    // Khai báo các hằng số tĩnh cho kích thước màn hình, cơ chế trò chơi như khoảng cách ống, và kích thước nhân vật.
};
