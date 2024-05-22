#pragma once // Đảm bảo rằng file header này chỉ được include một lần trong quá trình biên dịch.

#include "lib.h" // Bao gồm các định nghĩa chung và thư viện cần thiết từ file lib.h.
#include <iostream> // Bao gồm thư viện chuẩn C++ để sử dụng nhập xuất.
#include <vector> // Bao gồm thư viện chuẩn C++ cho container vector.

using namespace std; // Sử dụng không gian tên std để dễ dàng truy cập các tính năng chuẩn.

extern vector<position> posPipe; // Khai báo biến toàn cục để lưu trữ vị trí của các ống, được định nghĩa ở nơi khác.

// Lớp pipe, kế thừa từ lớp LTexture.
class pipe : LTexture
{
private:
    const short int randMin = -373 + 30; // Giới hạn dưới của khoảng cách ngẫu nhiên cho vị trí ống, tránh chạm vào đất.
    const short int randMax = SCREEN_HEIGHT - LAND_HEIGHT - 373 - PIPE_DISTANCE - 30; // Giới hạn trên của khoảng cách ngẫu nhiên cho vị trí ống, tránh chạm vào trần.

public:
    bool init(); // Phương thức khởi tạo các ống, tải texture và thiết lập vị trí ban đầu.

    void Free(); // Phương thức giải phóng tài nguyên.

    void render(); // Phương thức vẽ ống lên màn hình.

    void update(); // Phương thức cập nhật vị trí của các ống để tạo hiệu ứng di chuyển.

    short int width() { return getWidth(); } // Trả về chiều rộng của ống, sử dụng phương thức từ lớp cha LTexture.

    short int height() { return getHeight(); } // Trả về chiều cao của ống, sử dụng phương thức từ lớp cha LTexture.
};
/*
Lớp pipe có các thành phần chính sau:

Biến toàn cục posPipe: Lưu trữ vị trí của các ống trong trò chơi.
                        Được quản lý như một vector của cấu trúc position, mỗi phần tử chứa thông tin về vị trí x, y của một ống.
Hàm init: Khởi tạo ống, tải texture và đặt vị trí ban đầu dựa trên các giá trị ngẫu nhiên trong khoảng đã xác định.
Hàm Free: Giải phóng tài nguyên, đặc biệt là texture đã được tải, để tránh rò rỉ bộ nhớ.
Hàm render: Hiển thị ống trên màn hình, sử dụng bộ kết xuất của SDL.
Hàm update: Cập nhật vị trí của các ống, dịch chuyển chúng sang trái để tạo hiệu ứng di chuyển liên tục.
Các hàm width và height: Trả về kích thước của ống, hỗ trợ trong việc xác định khi nào ống cần được reset vị trí hoặc khi kiểm tra va chạm.
Lớp này chịu trách nhiệm quản lý hình ảnh, vị trí và di chuyển của các ống trong trò chơi, đóng vai trò quan trọng trong việc tạo ra thách thức cho người chơi.
*/
