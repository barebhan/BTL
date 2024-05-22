#pragma once // Đảm bảo rằng file header này chỉ được include một lần trong quá trình biên dịch.

#include "meo.h" // Bao gồm lớp meo, quản lý nhân vật mèo.
#include "pipe.h" // Bao gồm lớp pipe, quản lý các ống trong trò chơi.
#include "land.h" // Bao gồm lớp land, quản lý mặt đất.
#include "sound.h" // Bao gồm lớp sound, quản lý âm thanh trong trò chơi.
#include <string> // Bao gồm thư viện chuẩn C++ cho xử lý chuỗi.
#include <fstream> // Bao gồm thư viện chuẩn C++ cho đọc và ghi file.
#include <sstream> // Bao gồm thư viện chuẩn C++ cho luồng string.

using namespace std; // Sử dụng không gian tên std để truy cập các tính năng chuẩn dễ dàng hơn.

// Lớp game kế thừa từ LTexture.
class game:LTexture
{
public:
    // Cấu trúc định nghĩa các loại đầu vào của người chơi.
    struct input
    {
        enum type { QUIT, PLAY, NONE, PAUSE}; // Liệt kê các trạng thái đầu vào.
        type Type; // Biến lưu trạng thái đầu vào hiện tại.
    };
    input userInput; // Biến quản lý đầu vào người chơi.
    meo character; // Đối tượng nhân vật mèo.
    pipe pipe; // Đối tượng quản lý ống.
    sound sound; // Đối tượng quản lý âm thanh.
    land land; // Đối tượng quản lý mặt đất.

public:
    game(); // Constructor của lớp game.

    ~game(); // Destructor của lớp game.

    bool initGraphic(); // Khởi tạo đồ họa cho trò chơi.

    bool isQuit() // Kiểm tra liệu trò chơi có được yêu cầu dừng lại.
    {
        return quit;
    }

    bool isDie() // Kiểm tra liệu nhân vật mèo có đang trong trạng thái "chết".
    {
        return die;
    }

    int getPipeWidth() // Lấy chiều rộng của ống.
    {
        return pipe.width();
    }

    int getPipeHeight() // Lấy chiều cao của ống.
    {
        return pipe.height();
    }

    void takeInput(); // Xử lý các đầu vào từ người chơi.

    void display(); // Hiển thị trò chơi lên màn hình.

    void releaseGraphic(); // Giải phóng tài nguyên đồ họa.

    void renderScoreSmall(); // Hiển thị điểm số nhỏ.

    void renderScoreLarge(); // Hiển thị điểm số lớn.

    void renderBestScore(); // Hiển thị điểm số tốt nhất.

    void renderMessage(); // Hiển thị thông điệp trò chơi.

    void renderBackground(); // Hiển thị hình nền bình thường.

    void renderBackgroundNight(); // Hiển thị hình nền chế độ đêm.

    void renderLand(); // Hiển thị mặt đất.

    void resume(); // Hiển thị nút tiếp tục trò chơi.

    void pause(); // Hiển thị nút tạm dừng trò chơi.

    void renderPauseTab(); // Hiển thị tab tạm dừng.

    void lightTheme(); // Áp dụng chủ đề sáng cho trò chơi.

    void darkTheme(); // Áp dụng chủ đề tối cho trò chơi.

    void nextButton(); // Hiển thị các nút điều hướng.

    bool changeTheme(); // Thay đổi chủ đề của trò chơi.

    void renderGameOver(); // Hiển thị màn hình Game Over.

    void renderMedal(); // Hiển thị huy chương dựa trên điểm số.

    void replay(); // Hiển thị nút chơi lại.

    bool checkReplay(); // Kiểm tra xem người chơi có chọn chơi lại không.

    void Restart(); // Khởi động lại trò chơi.

private:
    const double scaleNumberS = 0.7; // Tỉ lệ thu nhỏ cho các số điểm.
    short int bestScore; // Điểm số tốt nhất được ghi nhận.
};
