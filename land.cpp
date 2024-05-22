#include "land.h" // Bao gồm file tiêu đề cho lớp land.
#include <stdio.h> // Bao gồm thư viện chuẩn C cho việc nhập xuất.
#include <iostream> // Bao gồm thư viện C++ cho việc nhập xuất.
#include <stdlib.h> // Bao gồm thư viện chuẩn cho các hàm chung.

bool land::init() // Hàm khởi tạo cho lớp land.
{
    posLand.getPos(0, SCREEN_HEIGHT - LAND_HEIGHT); // Đặt vị trí ban đầu của đất ở dưới cùng màn hình.
    string back_path = "res/image/land.png"; // Đường dẫn tệp ảnh cho đất.
    if (isNULL()) // Kiểm tra nếu texture hiện tại là NULL.
    {
        if (Load(back_path.c_str(), 1)) // Tải ảnh đất từ đường dẫn đã cho.
        {
            return true; // Trả về true nếu tải thành công.
        }
        else
        {
            return false; // Trả về false nếu tải thất bại.
        }
    }
    return false; // Trả về false nếu không cần tải ảnh mới.
}

void land::Free() // Hàm giải phóng tài nguyên cho land.
{
    free(); // Gọi hàm free để giải phóng texture của đất.
}

void land::render() // Hàm vẽ đất lên màn hình.
{
    if (posLand.x > 0) // Kiểm tra nếu vị trí x của đất lớn hơn 0.
    {
        Render(posLand.x, posLand.y); // Chỉ vẽ một lần nếu đất chưa di chuyển ra khỏi màn hình.
    }
    else if (posLand.x > -SCREEN_WIDTH && posLand.x <= 0) // Nếu đất đã di chuyển ra ngoài màn hình một phần.
    {
        Render(posLand.x, posLand.y); // Vẽ phần còn lại của đất.
        Render(posLand.x + SCREEN_WIDTH, posLand.y, 0, NULL); // Vẽ thêm một phần đất nữa để tạo hiệu ứng liền mạch.
    }
    else
    {
        posLand.getPos(0, SCREEN_HEIGHT - LAND_HEIGHT); // Đặt lại vị trí của đất.
        Render(posLand.x, posLand.y); // Vẽ đất.
    }
}

void land::update() // Hàm cập nhật vị trí của đất.
{
    posLand.x -= 3; // Di chuyển đất sang trái 3 đơn vị mỗi lần cập nhật.
}
